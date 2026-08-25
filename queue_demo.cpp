// queue_demo.cpp -- the sequential double-spend, in NOMGR's own architecture.
//
// Offers are accepted one at a time from a queue. An offer found triggerable
// is enqueued, and triggerability is checked a SECOND time on dequeue, because
// offers enqueued earlier may already have consumed the resources.
//
// That design is right. But a guard only helps if it can fail, and the clause
// pattern create_trade_check emits -- biconditionals only -- is satisfiable no
// matter what the vault contains. So the second check passes exactly when the
// first one did, and the guard never fires.
//
// Scenario: Alice holds 100 mg. Two offers each give away 100 mg. Each is
// individually fine at enqueue time. Only the first may actually execute.

#include "sat2.hpp"
#include "vault_check.hpp"

#include <cstdio>
#include <deque>
#include <vector>

using namespace nomgr;

struct Offer {
    i64 id;
    i64 gives_milligrams;
};

// The check as it exists today: offer <-> give, nothing else.
static bool check_as_written(const Offer& o, i64 /*alice_balance*/) {
    Instance in;
    in.n = 4;
    const i64 OFFER = 2, GIVE = 3;
    in.add_clause(OFFER, -GIVE);
    in.add_clause(-OFFER, GIVE);
    (void)o;
    return solve(in).satisfiable;
}

// The check with the balance actually consulted.
static bool check_with_balance(const Offer& o, i64 alice_balance) {
    if (!check_as_written(o, alice_balance)) return false;
    const std::vector<Deposit> held = {{1, alice_balance}};
    const std::vector<GoldClaim> want = {{o.id, o.gives_milligrams}};
    return check_exhaustion(held, want).covered;
}

static void run(const char* label, bool (*check)(const Offer&, i64)) {
    i64 alice = 100;
    std::deque<Offer> queue;

    const std::vector<Offer> incoming = {{1, 100}, {2, 100}};

    std::printf("\n  %s\n", label);
    std::printf("    Alice starts with %lld mg\n", (long long)alice);

    // Enqueue pass: each offer checked against the balance at the time.
    for (const Offer& o : incoming) {
        const bool ok = check(o, alice);
        std::printf("    offer %lld enqueue check: %s\n",
                    (long long)o.id, ok ? "triggerable -> queued" : "refused");
        if (ok) queue.push_back(o);
    }

    // Dequeue pass: the SECOND check, then execute.
    while (!queue.empty()) {
        const Offer o = queue.front();
        queue.pop_front();
        const bool still = check(o, alice);
        std::printf("    offer %lld re-check on dequeue: %s",
                    (long long)o.id, still ? "still triggerable" : "NO LONGER triggerable");
        if (still) {
            alice -= o.gives_milligrams;
            std::printf(" -> executed, Alice now %lld mg\n", (long long)alice);
        } else {
            std::printf(" -> refused\n");
        }
    }

    std::printf("    final balance: %lld mg  %s\n", (long long)alice,
                alice < 0 ? "<-- OVERDRAWN: gold that never existed was dispersed"
                          : "<-- sound");
}

int main() {
    std::printf("\nSEQUENTIAL DOUBLE-SPEND (one offer at a time, with re-check)\n");
    std::printf("------------------------------------------------------------");
    run("check as written today (biconditionals only)", check_as_written);
    run("check with the balance consulted", check_with_balance);
    std::printf("\n");
    return 0;
}
