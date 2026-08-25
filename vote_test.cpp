#include "vote.hpp"

#include <cstdio>
#include <string>

using namespace nomgr;

static int passed = 0, failed = 0;
static void check(const std::string& l, bool c) {
    if (c) { ++passed; std::printf("  PASS  %s\n", l.c_str()); }
    else { ++failed; std::printf("  FAIL  %s\n", l.c_str()); }
}

int main() {
    std::printf("\nVOTING\n----------------------------------------------------------------\n");

    // The scenario the whole design turns on: a large poor majority against a
    // small rich minority.
    Ballot contested;
    contested.heads_for = 100;          // 100 ordinary voters in favour
    contested.heads_against = 5;        // 5 wealthy holders against
    contested.gold_for = 1000;          // between them the 100 hold 1 gram
    contested.gold_against = 9000000;   // the 5 hold 9 kilograms

    {
        Tally t = tally(contested, Weighting::one_person_one_vote());
        check("one person one vote: the majority carries it", t.score_for > 0.9);
    }
    {
        Tally t = tally(contested, Weighting::one_milligram_one_vote());
        check("one milligram one vote: the money carries it", t.score_for < 0.01);
    }
    {
        Tally t = tally(contested, Weighting::even());
        check("even blend lands between the two", t.score_for > 0.4 && t.score_for < 0.6);
    }

    // The dial, printed, so it can be seen moving.
    std::printf("\n  100 voters holding 1 g in favour, 5 holding 9 kg against:\n");
    std::printf("    head weight | gold weight | share for | passes at 50%%?\n");
    for (int i = 0; i <= 10; ++i) {
        const double hw = i / 10.0;
        Weighting w{hw, 1.0 - hw};
        Tally t = tally(contested, w);
        std::printf("        %4.1f    |    %4.1f     |   %.3f   | %s\n",
                    hw, 1.0 - hw, t.score_for, t.score_for >= 0.5 ? "yes" : "no");
    }
    std::printf("\n");
    {
        // Somewhere in the middle the answer flips. That is the dial working.
        bool low = tally(contested, {0.0, 1.0}).score_for >= 0.5;
        bool high = tally(contested, {1.0, 0.0}).score_for >= 0.5;
        check("the outcome flips somewhere along the dial", low != high);
    }

    // Why the shares are normalised first.
    {
        // Blending the RAW totals: gold_for=1000 vs gold_against=9000000 swamps
        // any headcount, so even a 50/50 weighting is pure plutocracy.
        const double raw_for = 0.5 * 100.0 + 0.5 * 1000.0;
        const double raw_against = 0.5 * 5.0 + 0.5 * 9000000.0;
        const double raw_share = raw_for / (raw_for + raw_against);
        Tally t = tally(contested, Weighting::even());
        check("raw-total blending would be plutocracy in disguise", raw_share < 0.001);
        check("share-normalised blending is genuinely even", t.score_for > 0.4);
        std::printf("        raw-total blend gives the people %.4f%% of the say;"
                    " normalised gives %.1f%%\n\n", raw_share * 100.0, t.score_for * 100.0);
    }

    // Empty and one-sided ballots.
    {
        Outcome o = decide(Ballot{}, Weighting::even(), Threshold{0.5, 0});
        check("an empty ballot passes nothing", !o.passed);
    }
    {
        Ballot b; b.heads_for = 3; b.gold_for = 10;
        Outcome o = decide(b, Weighting::even(), Threshold{0.5, 10});
        check("quorum is enforced", !o.passed);
        check("the quorum failure says so", o.reason.find("quorum") != std::string::npos);
    }
    {
        Ballot b; b.heads_for = 60; b.heads_against = 40;
        b.gold_for = 60; b.gold_against = 40;
        check("60/40 clears a simple majority",
              decide(b, Weighting::even(), Threshold{0.5, 0}).passed);
        check("60/40 does not clear two thirds",
              !decide(b, Weighting::even(), Threshold{0.667, 0}).passed);
    }

    // Bills becoming law.
    {
        std::vector<LawRecord> code;
        i64 next_id = 1;

        BillRecord bill;
        bill.id = 10;
        bill.title = "An act concerning weights and measures";
        bill.classification = CodeKind::Civil;
        bill.ballot.heads_for = 70;
        bill.ballot.heads_against = 30;
        bill.ballot.gold_for = 7000;
        bill.ballot.gold_against = 3000;

        Outcome o = enact(bill, code, Weighting::even(), Threshold{0.5, 0}, 1000, next_id);
        check("a passing bill becomes law", o.passed && code.size() == 1);
        check("the law records when it took effect", code[0].valid_start == 1000);
        check("the law is in force", code[0].valid_end == 0);

        BillRecord failing = bill;
        failing.title = "An act nobody wanted";
        failing.ballot.heads_for = 10;
        failing.ballot.heads_against = 90;
        failing.ballot.gold_for = 1000;
        failing.ballot.gold_against = 9000;
        Outcome f = enact(failing, code, Weighting::even(), Threshold{0.5, 0}, 1001, next_id);
        check("a failing bill adds no law", !f.passed && code.size() == 1);

        BillRecord repeal;
        repeal.id = 11;
        repeal.repeal = true;
        repeal.target_law_id = code[0].id;
        repeal.ballot.heads_for = 80;
        repeal.ballot.heads_against = 20;
        repeal.ballot.gold_for = 8000;
        repeal.ballot.gold_against = 2000;
        Outcome r = enact(repeal, code, Weighting::even(), Threshold{0.5, 0}, 2000, next_id);
        check("a repeal ends the law", r.passed && code[0].valid_end == 2000);
        check("the repealed law is kept on the record, not deleted", code.size() == 1);

        Outcome again = enact(repeal, code, Weighting::even(), Threshold{0.5, 0}, 3000, next_id);
        check("repealing an already repealed law does nothing", !again.passed);
    }

    // Article V: two thirds to call, three quarters to ratify.
    {
        Ballot call;
        call.heads_for = 70; call.heads_against = 30;
        call.gold_for = 7000; call.gold_against = 3000;

        std::vector<ConventionOption> options;
        ConventionOption a; a.id = 1; a.title = "Option A";
        a.ballot.heads_for = 80; a.ballot.heads_against = 20;
        a.ballot.gold_for = 8000; a.ballot.gold_against = 2000;
        ConventionOption b; b.id = 2; b.title = "Option B";
        b.ballot.heads_for = 60; b.ballot.heads_against = 40;
        b.ballot.gold_for = 6000; b.ballot.gold_against = 4000;
        options.push_back(a);
        options.push_back(b);

        ConventionResult r = hold_convention(call, options, Weighting::even(),
                                             Threshold{0.667, 0}, Threshold{0.75, 0});
        check("70% calls the convention (two thirds needed)", r.convention_called);
        check("the 80% option ratifies (three quarters needed)", r.any_option_passed);
        check("the winning option is the one that cleared the bar", r.winning_option_id == 1);
        check("the 60% option does not ratify", !r.option_outcomes[1].passed);
    }
    {
        // Convention falls short: nothing ratifies even though an option would.
        Ballot call;
        call.heads_for = 55; call.heads_against = 45;
        call.gold_for = 5500; call.gold_against = 4500;

        std::vector<ConventionOption> options;
        ConventionOption a; a.id = 1;
        a.ballot.heads_for = 90; a.ballot.heads_against = 10;
        a.ballot.gold_for = 9000; a.ballot.gold_against = 1000;
        options.push_back(a);

        ConventionResult r = hold_convention(call, options, Weighting::even(),
                                             Threshold{0.667, 0}, Threshold{0.75, 0});
        check("55% does not call the convention", !r.convention_called);
        check("no option ratifies when the convention was not called",
              !r.any_option_passed);
        check("the record says why", r.option_outcomes[0].reason.find("not called")
                                     != std::string::npos);
    }

    std::printf("----------------------------------------------------------------\n");
    std::printf("  %d passed, %d failed\n\n", passed, failed);
    return failed ? 1 : 0;
}
