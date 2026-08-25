#include "producer_vote.hpp"

#include <cstdio>
#include <string>

using namespace nomgr;

static int passed = 0, failed = 0;
static void check(const std::string& l, bool c) {
    if (c) { ++passed; std::printf("  PASS  %s\n", l.c_str()); }
    else { ++failed; std::printf("  FAIL  %s\n", l.c_str()); }
}

static Commitment commit(i64 who, i64 value, bool favour, std::vector<i64> vouchers) {
    Commitment c;
    c.participant_id = who;
    c.gold_milligram_value = value;
    c.in_favour = favour;
    c.voucher_ids = vouchers;
    return c;
}

int main() {
    std::printf("\nPRODUCER-BACKED VOTES\n");
    std::printf("--------------------------------------------------------------\n");

    const Threshold bar{0.5, 0};

    // Both chambers agree.
    {
        ProducerVote v;
        v.democratic.heads_for = 70;
        v.democratic.heads_against = 30;
        v.commitments = {
            commit(1, 5000, true,  {101, 102}),
            commit(2, 3000, true,  {103}),
            commit(3, 1000, false, {104}),
        };

        GovernmentFund fund;
        ProducerOutcome o = hold_producer_vote(v, {0.5}, bar, bar, fund);

        check("a measure both chambers back passes", o.passed);
        check("everything staked is collected, from both sides",
              o.collected == 9000);
        check("the fund receives it", fund.gold_milligrams == 9000);
        check("the vouchers move with it", fund.vouchers.size() == 4);
    }

    // Money without the people.
    {
        ProducerVote v;
        v.democratic.heads_for = 10;
        v.democratic.heads_against = 90;
        v.commitments = {
            commit(1, 9000000, true, {201}),
        };

        GovernmentFund fund;
        ProducerOutcome o = hold_producer_vote(v, {0.5}, bar, bar, fund);

        check("overwhelming money cannot carry it alone", !o.passed);
        check("the reason names which chamber refused",
              o.reason.find("the people did not") != std::string::npos);
        check("nothing is collected on a failed vote", o.collected == 0);
        check("the fund is untouched", fund.gold_milligrams == 0 && fund.vouchers.empty());
    }

    // The people without any backing.
    {
        ProducerVote v;
        v.democratic.heads_for = 95;
        v.democratic.heads_against = 5;
        v.commitments = {
            commit(1, 100, false, {301}),      // the only producer is against
        };

        GovernmentFund fund;
        ProducerOutcome o = hold_producer_vote(v, {0.5}, bar, bar, fund);

        check("overwhelming support cannot carry it without backing", !o.passed);
        check("the reason names the producers",
              o.reason.find("producers did not") != std::string::npos);
        check("nothing is collected", fund.gold_milligrams == 0);
    }

    // Nobody commits anything at all.
    {
        ProducerVote v;
        v.democratic.heads_for = 99;
        v.democratic.heads_against = 1;
        GovernmentFund fund;
        ProducerOutcome o = hold_producer_vote(v, {0.5}, bar, bar, fund);
        check("a measure with no commitment at all does not pass", !o.passed);
    }

    // The dial inside the producer chamber: many small producers against one
    // large one.
    {
        ProducerVote v;
        v.democratic.heads_for = 80;
        v.democratic.heads_against = 20;
        v.commitments = {
            commit(1, 100, true, {401}),
            commit(2, 100, true, {402}),
            commit(3, 100, true, {403}),
            commit(4, 100, true, {404}),
            commit(5, 5000000, false, {405}),   // one holder outweighs all four
        };

        std::printf("\n  four small producers in favour, one large against:\n");
        std::printf("    committed-value share | producer chamber | measure\n");
        bool flipped = false, first = true, prev = false;
        for (int i = 0; i <= 10; ++i) {
            const double s = i / 10.0;
            ProducerOutcome o = preview_producer_vote(v, {s}, bar, bar);
            std::printf("             %4.1f         |      %-7s     | %s\n",
                        s, o.producer.passed ? "carries" : "refuses",
                        o.passed ? "passes" : "fails");
            if (!first && prev != o.producer.passed) flipped = true;
            prev = o.producer.passed;
            first = false;
        }
        std::printf("\n");
        check("the producer weighting changes the outcome", flipped);

        // At share 0 it is one producer one vote: four beat one.
        check("share 0 is one producer one vote",
              preview_producer_vote(v, {0.0}, bar, bar).producer.passed);
        // At share 1 it is decided purely by value: one beats four.
        check("share 1 is decided purely by value staked",
              !preview_producer_vote(v, {1.0}, bar, bar).producer.passed);
    }

    // The fund accumulates across measures.
    {
        GovernmentFund fund;
        for (int i = 0; i < 3; ++i) {
            ProducerVote v;
            v.democratic.heads_for = 60;
            v.democratic.heads_against = 40;
            v.commitments = { commit(1, 1000, true, {500 + i}) };
            hold_producer_vote(v, {0.5}, bar, bar, fund);
        }
        check("the fund accumulates across measures", fund.gold_milligrams == 3000);
        check("and keeps every voucher", fund.vouchers.size() == 3);
    }

    // preview must not move anything.
    {
        ProducerVote v;
        v.democratic.heads_for = 90;
        v.democratic.heads_against = 10;
        v.commitments = { commit(1, 4444, true, {601}) };
        GovernmentFund fund;
        ProducerOutcome p = preview_producer_vote(v, {0.5}, bar, bar);
        check("preview reports the same result", p.passed);
        check("preview leaves the fund alone", fund.gold_milligrams == 0);
        hold_producer_vote(v, {0.5}, bar, bar, fund);
        check("holding it for real does move the fund", fund.gold_milligrams == 4444);
    }

    std::printf("--------------------------------------------------------------\n");
    std::printf("  %d passed, %d failed\n\n", passed, failed);
    return failed ? 1 : 0;
}
