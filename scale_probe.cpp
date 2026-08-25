// scale_probe.cpp -- how much gold can we track at one variable per milligram?
//
// If every milligram in the vault is its own SAT variable, vault exhaustion is
// prevented automatically: an offer can only claim milligrams that exist, and
// the exclusion clauses stop any one being claimed twice.
//
// The only question is how many variables that is. This measures it.

#include "sat2.hpp"

#include <chrono>
#include <cstdio>
#include <random>

using namespace nomgr;

static double solve_ms(i64 nvars, i64 nclauses, bool& sat) {
    std::mt19937_64 rng(42);
    Instance in;
    in.n = nvars + 2;
    in.lst_l.reserve(nclauses);
    in.lst_r.reserve(nclauses);
    for (i64 c = 0; c < nclauses; ++c) {
        i64 a = 2 + (i64)(rng() % nvars);
        i64 b = 2 + (i64)(rng() % nvars);
        if (rng() & 1) a = -a;
        if (rng() & 1) b = -b;
        in.add_clause(a, b);
    }
    const auto t0 = std::chrono::steady_clock::now();
    const Result r = solve(in);
    const auto t1 = std::chrono::steady_clock::now();
    sat = r.satisfiable;
    return std::chrono::duration<double, std::milli>(t1 - t0).count();
}

int main() {
    std::printf("\nONE VARIABLE PER MILLIGRAM -- how far does it go?\n");
    std::printf("----------------------------------------------------------------\n");
    std::printf("  gold in vault |    milligrams |   clauses |    solve | verdict\n");
    std::printf("----------------------------------------------------------------\n");

    struct Row { const char* label; i64 mg; };
    const Row rows[] = {
        {"      1 gram", 1000LL},
        {"    100 grams", 100000LL},
        {"       1 kilo", 1000000LL},
        {"      10 kilos", 10000000LL},
    };

    for (const Row& row : rows) {
        const i64 clauses = row.mg * 2;
        bool sat = false;
        const double ms = solve_ms(row.mg, clauses, sat);
        // rough resident cost: CSR head+edges plus four SCC arrays over 2n verts
        const double gb = (double)(2 * row.mg) * 8.0 * 6.0 / 1e9;
        std::printf("  %13s | %13lld | %9lld | %6.0f ms | ~%.2f GB\n",
                    row.label, (long long)row.mg, (long long)clauses, ms, gb);
        std::fflush(stdout);
    }

    std::printf("----------------------------------------------------------------\n");
    std::printf("\nExtrapolating from the per-variable cost above:\n");
    std::printf("     1 tonne of gold  = 1,000,000,000 mg\n");
    std::printf("   400 tonnes (a mid-size national reserve) = 4e11 mg\n");
    std::printf("\n");
    return 0;
}
