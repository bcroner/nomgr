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
