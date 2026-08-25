// Tests for the linear-time 2-SAT solver.
//
// The important one is the randomised cross-check: thousands of small random
// instances decided both by the fast path and by brute force, with the answers
// compared. A solver that gets sat/unsat right but returns a bogus witness is
// still broken, so every satisfiable answer is checked by substituting the
// assignment back into the formula.

#include "sat2.hpp"

#include <chrono>
#include <cstdio>
#include <random>
#include <string>

using namespace nomgr;

static int passed = 0, failed = 0;

static void check(const std::string& label, bool cond, const std::string& detail = "") {
    if (cond) { ++passed; std::printf("  PASS  %s\n", label.c_str()); }
    else { ++failed; std::printf("  FAIL  %s%s%s\n", label.c_str(),
                                 detail.empty() ? "" : "  -- ", detail.c_str()); }
}

// Substitute an assignment back into the formula.
static bool satisfies(const Instance& inst, const std::vector<char>& a) {
    for (i64 v = 0; v < inst.n; ++v) {
        const std::size_t uv = static_cast<std::size_t>(v);
        if (uv < inst.forced_true.size() && inst.forced_true[uv] && !a[uv]) return false;
        if (uv < inst.forced_false.size() && inst.forced_false[uv] && a[uv]) return false;
    }
    const std::size_t k = std::min(inst.lst_l.size(), inst.lst_r.size());
    for (std::size_t i = 0; i < k; ++i) {
        const i64 x = inst.lst_l[i], y = inst.lst_r[i];
        if (x == kFalse2Sat || y == kFalse2Sat) continue;
        if (x == 0 || y == 0) continue;
        const bool lx = x > 0 ? a[static_cast<std::size_t>(x)] : !a[static_cast<std::size_t>(-x)];
        const bool ly = y > 0 ? a[static_cast<std::size_t>(y)] : !a[static_cast<std::size_t>(-y)];
        if (!lx && !ly) return false;
    }
    return true;
}

int main() {
    std::printf("\nNOMGR 2-SAT\n------------------------------------------------\n");

    // --- hand-built cases ----------------------------------------------
    {
        Instance in; in.n = 5;
        in.add_clause(2, 3);
        in.add_clause(-2, 4);
        check("simple satisfiable formula", solve(in).satisfiable);
    }
    {
        // (a|a) and (~a|~a): forces a true and a false at once.
        Instance in; in.n = 3;
        in.add_clause(2, 2);
        in.add_clause(-2, -2);
        check("direct contradiction is unsatisfiable", !solve(in).satisfiable);
    }
    {
        // All four clauses over two variables: unsatisfiable.
        Instance in; in.n = 4;
        in.add_clause(2, 3);
        in.add_clause(2, -3);
        in.add_clause(-2, 3);
        in.add_clause(-2, -3);
        check("all four clauses over two vars is unsatisfiable", !solve(in).satisfiable);
    }
    {
        Instance in; in.n = 4;
        in.add_clause(2, 3);
        in.forced_true.assign(4, 0);
        in.forced_false.assign(4, 0);
        in.forced_false[2] = 1;              // pin var 2 false -> var 3 must be true
        const Result r = solve(in);
        check("forced literal propagates", r.satisfiable && r.assignment[3] == 1);
    }
    {
        Instance in; in.n = 3;
        in.forced_true.assign(3, 0);
        in.forced_false.assign(3, 0);
        in.forced_true[2] = 1;
        in.forced_false[2] = 1;              // pinned both ways
        check("contradictory pinning is unsatisfiable", !solve(in).satisfiable);
    }
    {
        Instance in; in.n = 5;
        in.add_clause(2, kFalse2Sat);        // sentinel clause is skipped
        check("FALSE_2SAT sentinel clauses are ignored", solve(in).satisfiable);
    }

    // --- randomised cross-check against brute force ---------------------
    {
        std::mt19937_64 rng(12345);
        int agree = 0, disagree = 0, bad_witness = 0, sat_seen = 0, unsat_seen = 0;
        for (int trial = 0; trial < 4000; ++trial) {
            const i64 nv = 2 + static_cast<i64>(rng() % 7);   // vars 2..nv+1
            Instance in;
            in.n = nv + 2;
            const int k = static_cast<int>(rng() % 14) + 1;
            for (int c = 0; c < k; ++c) {
                i64 a = 2 + static_cast<i64>(rng() % nv);
                i64 b = 2 + static_cast<i64>(rng() % nv);
                if (rng() & 1) a = -a;
                if (rng() & 1) b = -b;
                in.add_clause(a, b);
            }
            const Result fast = solve(in);
            const Result slow = solve_bruteforce(in);
            if (fast.satisfiable != slow.satisfiable) ++disagree;
            else ++agree;
            if (fast.satisfiable) {
                ++sat_seen;
                if (!satisfies(in, fast.assignment)) ++bad_witness;
            } else {
                ++unsat_seen;
            }
        }
        check("fast and brute force agree on 4000 random instances",
              disagree == 0, "disagreements: " + std::to_string(disagree));
        check("every reported witness actually satisfies its formula",
              bad_witness == 0, "bad witnesses: " + std::to_string(bad_witness));
        std::printf("        (%d satisfiable, %d unsatisfiable -- both arms exercised)\n",
                    sat_seen, unsat_seen);
        check("the random set contains both outcomes", sat_seen > 0 && unsat_seen > 0);
    }

    // --- batch results match one-at-a-time ------------------------------
    {
        std::mt19937_64 rng(999);
        std::vector<Instance> batch;
        for (int i = 0; i < 500; ++i) {
            Instance in; in.n = 40;
            for (int c = 0; c < 80; ++c) {
                i64 a = 2 + static_cast<i64>(rng() % 38);
                i64 b = 2 + static_cast<i64>(rng() % 38);
                if (rng() & 1) a = -a;
                if (rng() & 1) b = -b;
                in.add_clause(a, b);
            }
            batch.push_back(in);
        }
        const std::vector<Result> par = solve_batch(batch, 0);
        int mismatch = 0, unsat = 0;
        for (std::size_t i = 0; i < batch.size(); ++i) {
            const Result one = solve(batch[i]);
            if (one.satisfiable != par[i].satisfiable) ++mismatch;
            if (!one.satisfiable) ++unsat;
            if (par[i].satisfiable && !satisfies(batch[i], par[i].assignment)) ++mismatch;
        }
        check("parallel batch matches serial on 500 instances",
              mismatch == 0, "mismatches: " + std::to_string(mismatch));
        std::printf("        (%d of 500 were unsatisfiable)\n", unsat);
    }

    // --- scale ----------------------------------------------------------
    {
        std::mt19937_64 rng(7);
        Instance in;
        in.n = 200002;
        for (int c = 0; c < 400000; ++c) {
            i64 a = 2 + static_cast<i64>(rng() % 200000);
            i64 b = 2 + static_cast<i64>(rng() % 200000);
            if (rng() & 1) a = -a;
            if (rng() & 1) b = -b;
            in.add_clause(a, b);
        }
        const auto t0 = std::chrono::steady_clock::now();
        const Result r = solve(in);
        const auto t1 = std::chrono::steady_clock::now();
        const double ms = std::chrono::duration<double, std::milli>(t1 - t0).count();
        std::printf("        200,000 variables / 400,000 clauses solved in %.1f ms (%s)\n",
                    ms, r.satisfiable ? "satisfiable" : "unsatisfiable");
        check("large instance solves in under two seconds", ms < 2000.0,
              std::to_string(ms) + " ms");
        if (r.satisfiable)
            check("large witness verifies", satisfies(in, r.assignment));
    }

    std::printf("------------------------------------------------\n");
    std::printf("  %d passed, %d failed\n\n", passed, failed);
    return failed ? 1 : 0;
}
