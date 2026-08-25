#include "rollback.hpp"
#include <cstdio>
#include <string>

using namespace nomgr;
static int passed = 0, failed = 0;
static void check(const std::string& l, bool c) {
    if (c) { ++passed; std::printf("  PASS  %s\n", l.c_str()); }
    else { ++failed; std::printf("  FAIL  %s\n", l.c_str()); }
}

static Ballot at(double share_for, i64 population = 1000) {
    Ballot b;
    b.heads_for = (i64)(population * share_for);
    b.heads_against = population - b.heads_for;
    b.gold_for = b.heads_for * 100;
    b.gold_against = b.heads_against * 100;
    return b;
}

int main() {
    std::printf("\nAMENDMENT ROLLBACK\n");
    std::printf("--------------------------------------------------------------\n");

    const Weighting w = Weighting::even();
    const Threshold ratify_bar{0.75, 0};      // three quarters, as Article V asks

    // --- the entrenchment trap, stated as numbers ------------------------
    std::printf("\n  If rolling back needs the same share as ratifying:\n");
    {
        Reversibility v = examine(ratify_bar, Threshold{0.75, 0});
        std::printf("    ratified at %.0f%%, reversal needs %.0f%% against it\n",
                    v.ratified_at_share * 100, v.needed_to_reverse * 100);
        std::printf("    so a %.0f%% minority can block reversal forever\n",
                    v.entrenching_minority * 100);
        check("symmetric thresholds let a minority entrench an amendment",
              v.minority_can_entrench);
    }
    std::printf("\n  With the rollback bar set lower:\n");
    {
        Reversibility v = examine(ratify_bar, Threshold{0.5, 0});
        std::printf("    ratified at %.0f%%, reversal needs %.0f%% against it\n",
                    v.ratified_at_share * 100, v.needed_to_reverse * 100);
        check("an asymmetric bar removes the entrenchment",
              !v.minority_can_entrench);
    }
    std::printf("\n");

    // --- the same thing played out on an actual amendment ----------------
    {
        std::vector<Amendment> amendments;
        i64 next = 1;

        Outcome o = ratify("Decisions shall maximise shareholder value",
                           at(0.80), w, ratify_bar, amendments, 1000, next);
        check("an 80% amendment ratifies", o.passed && amendments.size() == 1);
        check("it is in force", amendments[0].in_force());

        // Opinion turns: 70% now want it gone. Under a symmetric bar that is
        // not enough, and the 30% who still want it keep it.
        RollbackProposal p;
        p.target_amendment_id = amendments[0].id;
        p.reason = "it turned out badly";
        p.ballot = at(0.70);

        std::vector<Amendment> symmetric = amendments;
        RollbackOutcome sym = roll_back(p, w, Threshold{0.75, 0}, symmetric, 5000);
        check("70% against is NOT enough under a symmetric bar", !sym.rolled_back);
        check("the amendment survives on a 30% minority",
              symmetric[0].in_force());

        // Under the asymmetric bar the same 70% carries it.
        RollbackOutcome asym = roll_back(p, w, Threshold{0.5, 0}, amendments, 5000);
        check("the same 70% rolls it back under an asymmetric bar",
              asym.rolled_back);
        check("the amendment is out of force", !amendments[0].in_force());
        check("but the record survives -- not deleted",
              amendments.size() == 1 && amendments[0].rolled_back_at == 5000);
        check("and when it was in force is still answerable",
              amendments[0].ratified_at == 1000 && amendments[0].rolled_back_at == 5000);
    }

    // --- ordinary guards ---------------------------------------------------
    {
        std::vector<Amendment> amendments;
        i64 next = 1;
        ratify("Something", at(0.90), w, ratify_bar, amendments, 100, next);

        RollbackProposal weak;
        weak.target_amendment_id = 1;
        weak.ballot = at(0.30);
        check("a rollback nobody wants does not carry",
              !roll_back(weak, w, Threshold{0.5, 0}, amendments, 200).rolled_back);
        check("the amendment is untouched", amendments[0].in_force());

        RollbackProposal strong;
        strong.target_amendment_id = 1;
        strong.ballot = at(0.80);
        check("a supported rollback carries",
              roll_back(strong, w, Threshold{0.5, 0}, amendments, 300).rolled_back);

        RollbackOutcome again = roll_back(strong, w, Threshold{0.5, 0}, amendments, 400);
        check("rolling back twice does nothing", !again.rolled_back);
        check("and says why", again.note.find("already") != std::string::npos);

        RollbackProposal missing;
        missing.target_amendment_id = 999;
        missing.ballot = at(0.90);
        RollbackOutcome m = roll_back(missing, w, Threshold{0.5, 0}, amendments, 500);
        check("rolling back an amendment that does not exist does nothing",
              !m.rolled_back && m.note.find("no such") != std::string::npos);
    }

    // A failing ratification leaves nothing behind.
    {
        std::vector<Amendment> amendments;
        i64 next = 1;
        Outcome o = ratify("Not wanted", at(0.60), w, ratify_bar, amendments, 100, next);
        check("60% does not reach three quarters", !o.passed);
        check("and no amendment is recorded", amendments.empty());
    }

    std::printf("--------------------------------------------------------------\n");
    std::printf("  %d passed, %d failed\n\n", passed, failed);
    return failed ? 1 : 0;
}
