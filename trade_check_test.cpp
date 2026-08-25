#include "trade_check.hpp"

#include <cstdio>
#include <string>

using namespace nomgr;

static int passed = 0, failed = 0;

static void check(const std::string& label, bool cond) {
    if (cond) { ++passed; std::printf("  PASS  %s\n", label.c_str()); }
    else { ++failed; std::printf("  FAIL  %s\n", label.c_str()); }
}

int main() {
    std::printf("\nTRADE CHECK\n------------------------------------------------------\n");

    // Alice owns milligram #100 and offers it twice.
    {
        std::vector<OfferSpec> offers = {
            {1, {100}, {200}, false},
            {2, {100}, {300}, false},
        };
        check("two offers spending the same milligram cannot both clear",
              !all_can_clear(offers));
        // ...but either one alone is fine.
        check("offer 1 alone clears", all_can_clear({offers[0]}));
        check("offer 2 alone clears", all_can_clear({offers[1]}));
    }

    // Disjoint gold: no conflict.
    {
        std::vector<OfferSpec> offers = {
            {1, {100}, {200}, false},
            {2, {101}, {300}, false},
        };
        check("offers spending different milligrams both clear", all_can_clear(offers));
    }

    // Three offers over one unit: none of the pairs may co-exist.
    {
        std::vector<OfferSpec> offers = {
            {1, {100}, {201}, false},
            {2, {100}, {202}, false},
            {3, {100}, {203}, false},
        };
        check("three offers over one unit cannot all clear", !all_can_clear(offers));
        check("any single one of the three clears", all_can_clear({offers[1]}));
    }

    // A multi-unit trade where only part of the gold collides.
    {
        std::vector<OfferSpec> offers = {
            {1, {100, 101, 102}, {200}, false},
            {2, {102, 103},      {300}, false},   // 102 is shared
        };
        check("partial overlap still blocks both clearing", !all_can_clear(offers));
    }
    {
        std::vector<OfferSpec> offers = {
            {1, {100, 101, 102}, {200}, false},
            {2, {103, 104},      {300}, false},
        };
        check("no overlap across multi-unit trades clears", all_can_clear(offers));
    }

    // Receiving the same unit is not a conflict -- two parties can both be
    // promised the same voucher only if one offer gives it, so the exclusion
    // is on gives, not receives.
    {
        std::vector<OfferSpec> offers = {
            {1, {100}, {500}, false},
            {2, {101}, {500}, false},
        };
        check("two offers receiving the same unit is not itself a conflict",
              all_can_clear(offers));
    }

    // Empty set.
    check("an empty trade set clears", all_can_clear({}));

    // Scale: 2000 offers, all disjoint, must clear.
    {
        std::vector<OfferSpec> offers;
        for (i64 i = 0; i < 2000; ++i)
            offers.push_back({i, {1000 + i}, {50000 + i}, false});
        check("2000 disjoint offers clear", all_can_clear(offers));
    }
    // Scale: 2000 offers all fighting over one unit -- must not clear.
    {
        std::vector<OfferSpec> offers;
        for (i64 i = 0; i < 2000; ++i)
            offers.push_back({i, {7}, {50000 + i}, false});
        check("2000 offers over one unit do not clear", !all_can_clear(offers));
    }

    // Batch: many independent markets decided in parallel.
    {
        std::vector<Instance> batch;
        for (int m = 0; m < 400; ++m) {
            std::vector<OfferSpec> offers = {
                {1, {100}, {200}, true},
                {2, {(m % 2) ? 101 : 100}, {300}, true},   // even m collides
            };
            batch.push_back(build_trade_check(offers).instance);
        }
        const std::vector<Result> rs = solve_batch(batch, 0);
        int wrong = 0;
        for (int m = 0; m < 400; ++m) {
            const bool expect_clear = (m % 2) != 0;
            if (rs[m].satisfiable != expect_clear) ++wrong;
        }
        check("400 markets decided in parallel, all correct", wrong == 0);
    }

    std::printf("------------------------------------------------------\n");
    std::printf("  %d passed, %d failed\n\n", passed, failed);
    return failed ? 1 : 0;
}
