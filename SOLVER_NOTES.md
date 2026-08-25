# NOMGR solver rebuild

## What was wrong

`NOMGR.cpp` did not compile: **109 errors** from g++ 14.2. Three root causes in
the header cascaded into most of them.

| Location | Defect |
|---|---|
| `NOMGR.hpp:138` | `Account_System_tag` typedef'd as `Account`, colliding with the `Account` typedef above it |
| `NOMGR.hpp:356` | `Bill::id` declared twice |
| `NOMGR.hpp:605` | function declaration with **no name**: `Offer* (Market* market, ...)` |
| `NOMGR.hpp` | `Offer::gives` / `receives` declared `__int64*` but used as `Voucher*` everywhere -- ~90 of the 109 errors |
| `NOMGR.cpp:445,694` | `give_voucher_counts_vcap` parameter missing its type |
| `NOMGR.cpp:751` | `for (...) { {` -- unbalanced brace; everything after it parsed inside the previous function |
| throughout | loop bounds `i <= X_vtop + 1` read one element past the end (`vtop` is the top *index*, starting at -1) |

### The threading did not exist

- `NOMGR.cpp:1948` uses `thread::pool::parameterized_pool_t<1,0>`. That type is
  not in the standard library and is not defined anywhere in the repository.
- `SATSolver_threads` redeclares its own parameters: `chops` at 1929, `is_sat`
  at 1942.
- `std::mutex mtx` is declared at 1908 and never used, while every worker does
  `*is_sat |= ...` at 1918 -- an unsynchronised concurrent write.
- Line 1952 passes `chop` to every task instead of the loop index, so all
  workers would have searched the *same* region.
- `main()` is empty.

## The real problem was the algorithm

The original builds an implication graph and then searches assignments through
it with a backtracking binary counter. That is exponential.

2-SAT does not need search. Aspvall, Plass and Tarjan (1979): a 2-CNF formula
is satisfiable iff no variable shares a strongly connected component with its
own negation -- decidable in **O(n + k)**.

### Measured

Same random instances, both algorithms, one binary (`bench.cpp` lifts the
original function verbatim):

```
  vars  clauses |      original |     linear | speedup
    10       20 |       0.01 ms |   0.005 ms |        2x
    14       28 |       0.01 ms |   0.002 ms |        3x
    18       36 |       0.01 ms |   0.003 ms |        2x
    22       44 |       0.01 ms |   0.003 ms |        2x
    26       52 |       0.02 ms |   0.004 ms |        7x
    30       60 |  did not finish in 9 minutes  |   0.004 ms
```

The honest characterisation is not "the old one is slow" -- below 26 variables
it is fine. It is **unpredictably exponential**: it handles easy instances in
microseconds and then falls off a cliff. For trade validation that is worse
than uniform slowness, because some trades would simply never return.

For scale, the new solver does **200,000 variables / 400,000 clauses in 29 ms**.

## Threading, done where it helps

Threading a linear algorithm is usually a loss -- the coordination costs more
than the work. The parallelism that pays is across *independent* trade checks,
which is `solve_batch()`: a shared atomic work counter, each worker writing to
its own result index so no lock is needed on the hot path.

## Files

- `sat2.hpp` / `sat2.cpp` -- the solver, plus `solve_batch` and a brute-force
  reference implementation for testing
- `sat2_test.cpp` -- 11 tests, including 4000 random instances cross-checked
  against brute force, and verification that every reported witness actually
  satisfies its formula
- `bench.cpp` -- head-to-head against the original

```
g++ -std=c++17 -O2 -o sat2_test sat2.cpp sat2_test.cpp && ./sat2_test
g++ -std=c++17 -O2 -o bench      sat2.cpp bench.cpp      && ./bench
```

## Still open

`NOMGR.cpp` is down from 109 errors to ~62, but the rest are not typos. Parts
of the market layer were written against a data model that does not exist:

- `create_trade_check` (line ~1134) reads `barter_system->offers_gives` and
  `offers_gives_vtop`. Those fields are not on `Barter_System` -- not
  misspelled, never defined.
- `make_offer` (line ~459) uses `participant_id`, which is not one of its
  parameters.
- `create_account` (line ~1038) assigns `account->vouchers`; the struct has
  `holdings`.
- `create_participant` is defined twice.

These need decisions about intent, not repairs. What is `offers_gives` meant to
hold? Is `Account::holdings` voucher IDs or `Voucher` objects?

---

# The trade check accepts double spends

This matters more than the compile errors or the speed.

`create_trade_check` emits, for each offer and each thing it gives:

```
(offer | ~give)   and   (~offer | give)        i.e.  offer <-> give
```

**Biconditionals alone are always satisfiable.** They sort variables into
equivalence classes; nothing ever contradicts. So the check accepts every trade
set handed to it, including impossible ones.

`doublespend_demo.cpp` demonstrates it. Alice owns one milligram of gold and
posts two offers that each give it away:

```
  current encoding (biconditionals only)
    satisfiable: YES
    offer A accepted: yes
    offer B accepted: yes
    --> BOTH ACCEPTED: the same milligram is spent twice
    with both offers forced accepted: STILL SATISFIABLE
```

Two things were missing.

**1. Unit identity.** In the original loop `gold_milligram_ix` is a running
counter incremented per give, so each offer mints its *own* milligram ids. Two
offers spending Alice's same milligram referred to two different ids and could
never collide. Ids must come from the owner's actual holdings.

**2. Mutual exclusion.** For every unit claimed by more than one offer,
`(~A | ~B)` for each pair. That is what forbids double spending. It is still a
binary clause, so the instance stays 2-SAT and stays linear to decide.

With both fixed, the same scenario gives:

```
  with mutual exclusion added
    at most one accepted (correct)
    with both forced accepted: UNSATISFIABLE -- double spend correctly refused
```

## What this encoding cannot express

2-CNF can say "these two offers conflict". It cannot say "the gold given must
equal the gold received" -- that is arithmetic, not a binary clause. Value
balance has to be checked separately, before or after the SAT step. Worth
deciding where that lives.

## Files

- `trade_check.{hpp,cpp}` -- the corrected encoding, written against plain data
  so it is testable now and can be wired into `Market` once that compiles
- `trade_check_test.cpp` -- 13 tests
- `doublespend_demo.cpp` -- the scenario above, both encodings side by side

## Answers applied

1. `offers_gives` is the attribution of specific gold to an offer -- implemented
   as shared unit ids in `trade_check.cpp`, which is what makes collisions
   detectable.
2. `Account::holdings` holds voucher **ids**; `create_account` now assigns
   `holdings` and takes `__int64*`.
3. The two `create_participant` definitions were byte-identical apart from tabs
   vs spaces. Removed the second.
4. `participant_id` is now a parameter of `make_offer`.

Note on units: the code says **milligrams** throughout (`gold_milligram_value`,
`gold_milligram_balance`, `retrieve_gold_milligram`). The word "ounce" does not
appear anywhere in the repository.

Compile errors are down from 109 to 59; the remainder are inside
`create_trade_check`, which `trade_check.cpp` is intended to replace rather
than repair.

---

# Vault exhaustion: use arithmetic, not SAT

The requirement is to detect whether a set of trades would exhaust the gold in
the vault. The instinct was to identify specific milligrams so the demand can
be traced. Identity is worth having -- it is what separates allocated from
unallocated gold, and which deposit backs which claim -- but it is not what
detects exhaustion, and it is far more expensive than that question needs.

## Measured: one SAT variable per milligram

```
  gold in vault |  milligrams |   solve | memory
       1 gram   |       1,000 |    0 ms | ~0 GB
     100 grams  |     100,000 |   15 ms | ~0.01 GB
        1 kilo  |   1,000,000 |  451 ms | ~0.10 GB
       10 kilos |  10,000,000 | 5823 ms | ~0.96 GB
```

It runs out near **10 kilograms**. One tonne is 10^9 milligrams -- roughly ten
minutes and ~100 GB. A 400-tonne reserve is 4x10^11. Not reachable.

## Measured: arithmetic

Exhaustion is a sum. `check_exhaustion` adds up what the accepted offers demand
and compares it with the vault total:

```
  400,000 deposits totalling 400 tonnes, 400,000 claims -> 0.46 ms
```

Same question, exact answer, at a scale the per-milligram encoding cannot
approach at all.

## Division of labour

| Question | Tool | Cost |
|---|---|---|
| Which offers **conflict** over the same unit? | 2-SAT (`trade_check`) | linear in offers and clauses |
| Can the vault **cover** what was accepted? | arithmetic (`vault_check`) | linear in deposits |
| Does gold given **equal** gold received? | arithmetic | linear |

2-CNF expresses conflict. It cannot express a sum -- that is not a binary
clause. Keeping the counting in arithmetic is what makes national-reserve scale
possible.

`vault_check.{hpp,cpp}` plus 10 tests, including saturating rather than
wrapping on overflow: a wrapped total would report a vault able to cover
anything at all.

---

# Correction: the architecture is sequential

Offers are accepted **one at a time** from a queue, and triggerability is
checked a second time on dequeue because offers queued earlier may already have
consumed the resources.

That invalidates part of the earlier analysis in this file. The scenario in
`doublespend_demo.cpp` -- two offers accepted *simultaneously* -- cannot occur
under serialisation. The pairwise mutual-exclusion clauses in `trade_check.cpp`
are therefore solving a problem this architecture already prevents. They remain
correct, and would be needed if offers were ever cleared in batches, but they
are not what this system needs today.

## The finding survives in sequential form

The double-check is the right design. A guard only helps if it can fail,
though, and the clause pattern `create_trade_check` emits is satisfiable
regardless of what the vault holds. So the second check returns exactly what
the first one did and never fires.

`queue_demo.cpp`, one offer at a time, with the re-check in place:

```
  check as written today (biconditionals only)
    offer 1 re-check on dequeue: still triggerable -> executed, Alice now 0 mg
    offer 2 re-check on dequeue: still triggerable -> executed, Alice now -100 mg
    final balance: -100 mg  <-- OVERDRAWN

  check with the balance consulted
    offer 2 re-check on dequeue: NO LONGER triggerable -> refused
    final balance: 0 mg  <-- sound
```

## What the re-check needs

Not exclusion clauses. It needs the **live balance** consulted at dequeue time:

```cpp
if (!structural_check(offer))                      return false;  // 2-SAT
if (!check_exhaustion(current_holdings, claims))   return false;  // arithmetic
```

The 2-SAT half answers the structural question -- do this offer's requires,
bans and insurance conditions have a consistent solution. The arithmetic half
answers the resource question -- is the gold still there. Neither substitutes
for the other, and the second one is what makes the re-check meaningful.

This is also cheap: `check_exhaustion` is O(deposits), measured at 0.46 ms
across 400,000 deposits, so running it on every dequeue costs nothing.

---

# The complete check

`triggerable.hpp` is the single call the queue needs, at enqueue and again at
dequeue:

```cpp
TriggerVerdict v = is_triggerable(state, offer_id, holdings, claims);
if (!v.triggerable) { /* v.reason says which half failed and why */ }
```

Two halves, because one tool cannot do both jobs:

| half | question | tool | why |
|---|---|---|---|
| structural | requires / bans / insurance | 2-SAT | requires and bans **chain**: A requires B, B requires C, C bans A means A can never trigger. A single pass over the lists will not see that. |
| resource | is the gold still there | arithmetic | a sum is not a binary clause. 2-CNF cannot express it at any price. |

The queue, running as designed:

```
    offer 1 enqueue: triggerable
    offer 2 enqueue: triggerable
    offer 1 dequeue: triggerable -> executed, 0 mg left
    offer 2 dequeue: resources: short by 100 gold milligrams -> refused
```

Both pass at enqueue, which is correct -- each is individually fine at the time
it is queued. The re-check on dequeue catches the change. That is the guard
firing the way it was meant to.

# Summary of the work

**Started with:** 109 compile errors, threading built on a type that does not
exist, an exponential solver, and a trade check that could not fail.

**Now:** 55 tests passing across five modules.

| module | what it does | tests |
|---|---|---|
| `sat2` | linear-time 2-SAT, SCC based, plus batch parallelism | 11 |
| `structural_check` | requires / bans / insurance, chains included | 13 |
| `vault_check` | exhaustion by arithmetic | 10 |
| `triggerable` | both halves, one call | 8 |
| `trade_check` | conflict encoding for batch clearing (not needed while offers are serialised) | 13 |

**Measured:**

- 200,000 variables / 400,000 clauses: **29 ms** (the old solver did not finish
  30 variables in nine minutes)
- 400,000 deposits totalling 400 tonnes: **0.46 ms**

**Left:** `NOMGR.cpp` still has 59 errors, all inside `create_trade_check`,
which these modules replace rather than repair. Wiring `Market` / `Offer` /
`Account` to call `is_triggerable` is the remaining work.

---

# The market layer is wired

`NOMGR.cpp` **compiles** -- 109 errors down to 0, no warnings on the default
build. `create_trade_check` and `check_trade` now call the tested modules, and
the old SATSolver (450 lines of exponential search) is gone.

The queue's second check, which is what NOMGR's design turns on:

```cpp
prev->next = nullptr;

// Offers queued earlier may already have taken the resources, so
// triggerability is re-tested before anything is dispersed.
if (check_trade(ret->data))
        return ret;

return nullptr;
```

## Bugs the wiring surfaced

`NOMGR.cpp` had an empty `main()`, so none of this had ever executed. Driving
it found four things:

**All four `remove_*` functions had their guard inverted.**

```c
if (ban_ix > -1)
    return;                 // returns when the ban WAS found
for (i = ban_ix; ...)       // only reached when ban_ix == -1
    bans[i] = bans[i + 1];  // reads bans[-1]
```

They returned without removing when the item was present, and shifted from
index -1 while decrementing the count when it was absent. The `create_*`
functions use the same guard correctly -- to skip duplicates -- and the
`remove_*` ones copied it when they needed the opposite.

**`id_pool_retrieve` never handed out distinct ids.**

```c
if (*vtop == -1) { append(0); return 0; }   // always 0
__int64 id = id_pool[*vtop + 1];            // one PAST the top, uninitialised
```

It is a free list for recycled ids with nothing to mint fresh ones. Every
participant, account, bank and offer received id 0. `ID_Pool` now carries a
`next_id` counter: pop a recycled id if one is waiting, otherwise mint.

**`make_offer` computes `participant_ix` and never uses it** -- the offer is
never associated with the participant that made it. Left alone; it needs a
decision about what that association should be.

**Loop bounds `i <= vtop + 1`** read one element past the end in the search
loops. Corrected.

## Where it stands

| suite | tests |
|---|---|
| `sat2` | 11 |
| `structural_check` | 13 |
| `vault_check` | 10 |
| `triggerable` | 8 |
| `trade_check` | 13 |
| `market` | 20 |
| **total** | **75** |

```
make            # build
make test       # run all suites
make bench      # old solver against new
```

## Still open

- `make_offer` does not associate an offer with its participant
- `create_offer` writes `offer->gives->id` rather than `offer->gives[i].id`, so
  every give overwrites element 0
- `main()` is empty (renamed `nomgr_unused_main` so tests can link)
- the legal system, vouchers and Article V structures are defined but unused
