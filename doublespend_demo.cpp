// doublespend_demo.cpp
//
// Scenario: Alice holds ONE milligram of gold. She posts two offers, each of
// which gives that same milligram away. Exactly one of them can be honoured.
//
// This encodes the scenario twice: once with the clause pattern that
// create_trade_check currently emits, and once with the missing constraint
// added. The point is to show what each one decides.

#include "sat2.hpp"
#include <cstdio>

using namespace nomgr;

// Variable numbering (variables start at 2; 1 and -1 are sentinels)
enum : i64 {
    OFFER_A = 2,
    OFFER_B = 3,
    GIVE_A  = 4,   // "offer A hands over its gold"
    GIVE_B  = 5,   // "offer B hands over its gold"
    GOLD_MG = 6,   // the single milligram Alice actually owns
    N_VARS  = 7,
};

static void iff(Instance& in, i64 x, i64 y) {
    in.add_clause(x, -y);      // (x | ~y)
    in.add_clause(-x, y);      // (~x | y)
}

int main() {
    std::printf("\nDOUBLE-SPEND CHECK\n");
    std::printf("Alice owns 1 mg of gold and posts two offers that each give it away.\n");
    std::printf("A correct trade check must refuse to accept both.\n\n");

    // ---- 1. exactly what create_trade_check emits today -------------------
    {
        Instance in;
        in.n = N_VARS;
        iff(in, OFFER_A, GIVE_A);
        iff(in, OFFER_B, GIVE_B);
        iff(in, GIVE_A, GOLD_MG);
        iff(in, GIVE_B, GOLD_MG);

        Result r = solve(in);
        std::printf("  current encoding (biconditionals only)\n");
        std::printf("    satisfiable: %s\n", r.satisfiable ? "YES" : "no");
        if (r.satisfiable) {
            std::printf("    offer A accepted: %s\n", r.assignment[OFFER_A] ? "yes" : "no");
            std::printf("    offer B accepted: %s\n", r.assignment[OFFER_B] ? "yes" : "no");
            const bool both = r.assignment[OFFER_A] && r.assignment[OFFER_B];
            std::printf("    --> %s\n", both
                ? "BOTH ACCEPTED: the same milligram is spent twice"
                : "only one accepted");
        }
    }

    // Force both offers to be accepted and see whether the encoding objects.
    {
        Instance in;
        in.n = N_VARS;
        iff(in, OFFER_A, GIVE_A);
        iff(in, OFFER_B, GIVE_B);
        iff(in, GIVE_A, GOLD_MG);
        iff(in, GIVE_B, GOLD_MG);
        in.add_clause(OFFER_A, OFFER_A);      // unit clause: A accepted
        in.add_clause(OFFER_B, OFFER_B);      // unit clause: B accepted

        Result r = solve(in);
        std::printf("\n    with both offers forced accepted: %s\n",
                    r.satisfiable ? "STILL SATISFIABLE -- double spend allowed"
                                  : "unsatisfiable (correctly rejected)");
    }

    // ---- 2. with the missing mutual-exclusion clause ----------------------
    {
        Instance in;
        in.n = N_VARS;
        iff(in, OFFER_A, GIVE_A);
        iff(in, OFFER_B, GIVE_B);
        iff(in, GIVE_A, GOLD_MG);
        iff(in, GIVE_B, GOLD_MG);
        // The constraint that is absent today: one milligram, one spender.
        in.add_clause(-OFFER_A, -OFFER_B);

        Result r = solve(in);
        std::printf("\n  with mutual exclusion added\n");
        std::printf("    satisfiable: %s\n", r.satisfiable ? "YES" : "no");
        if (r.satisfiable) {
            std::printf("    offer A accepted: %s\n", r.assignment[OFFER_A] ? "yes" : "no");
            std::printf("    offer B accepted: %s\n", r.assignment[OFFER_B] ? "yes" : "no");
            const bool both = r.assignment[OFFER_A] && r.assignment[OFFER_B];
            std::printf("    --> %s\n", both ? "BOTH ACCEPTED (wrong)"
                                             : "at most one accepted (correct)");
        }

        Instance forced = in;
        forced.add_clause(OFFER_A, OFFER_A);
        forced.add_clause(OFFER_B, OFFER_B);
        Result f = solve(forced);
        std::printf("    with both forced accepted: %s\n",
                    f.satisfiable ? "satisfiable (wrong)"
                                  : "UNSATISFIABLE -- double spend correctly refused");
    }

    std::printf("\n");
    return 0;
}
