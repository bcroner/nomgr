#include "session.hpp"
#include <cstdio>
#include <string>

using namespace nomgr;
static int passed = 0, failed = 0;
static void check(const std::string& l, bool c) {
    if (c) { ++passed; std::printf("  PASS  %s\n", l.c_str()); }
    else { ++failed; std::printf("  FAIL  %s\n", l.c_str()); }
}

static BillRecord bill(const std::string& title, i64 f, i64 a, bool repeal = false, i64 target = 0) {
    BillRecord b;
    b.title = title;
    b.repeal = repeal;
    b.target_law_id = target;
    b.ballot.heads_for = f;
    b.ballot.heads_against = a;
    b.ballot.gold_for = f * 100;
    b.ballot.gold_against = a * 100;
    return b;
}

int main() {
    std::printf("\nLEGISLATIVE SESSIONS\n");
    std::printf("--------------------------------------------------------------\n");

    // Sessions open at t=100 and every 1000 thereafter, sitting for 200.
    Calendar cal(100, 1000, 200);

    check("nothing is in session before the first opens", !cal.in_session(50));
    check("the first session is open at its start", cal.in_session(100));
    check("still open partway through", cal.in_session(299));
    check("closed once the sitting ends", !cal.in_session(300));
    check("closed in the gap", !cal.in_session(900));
    check("the second session opens on the interval", cal.in_session(1100));
    check("next opening is reported while dark", cal.next_opens_at(500) == 1100);

    std::vector<LawRecord> code;
    Weighting w = Weighting::even();
    Threshold t{0.5, 0};
    i64 next_law_id = 1;

    // File during the first session.
    cal.file(bill("Weights and measures", 70, 30), 150);
    cal.file(bill("A bill nobody wants", 10, 90), 160);
    check("two bills are before the first session", cal.sessions()[0].bills.size() == 2);

    // Nothing has happened yet -- the session has not closed.
    auto none = cal.close_due(250, code, w, t, next_law_id);
    check("nothing is decided while the session still sits", none.empty());
    check("no law exists yet", code.empty());

    // File while the chamber is dark: held, not lost.
    const i64 heard_by = cal.file(bill("Filed in the gap", 80, 20), 700);
    check("a bill filed while dark is held, not lost", cal.held().size() == 1);
    check("it is assigned to the next session", heard_by == 1);

    // Close the first session.
    auto r1 = cal.close_due(300, code, w, t, next_law_id);
    check("the first session closes exactly once", r1.size() == 1);
    check("its passing bill became law", r1[0].enacted == 1);
    check("its failing bill did not", r1[0].rejected == 1);
    check("the body of law has one entry", code.size() == 1);
    check("the law took effect when the session closed", code[0].valid_start == 300);

    // Closing again changes nothing.
    auto again = cal.close_due(400, code, w, t, next_law_id);
    check("a closed session is not reheard", again.empty());
    check("and no law was added", code.size() == 1);

    // The held bill is taken up when the next session opens.
    Session* s2 = cal.current(1100);
    check("the second session opens", s2 != nullptr);
    check("it picks up the bill filed in the gap", s2 && s2->bills.size() == 1);
    check("nothing is left holding", cal.held().empty());

    // Repeal the first law in the second session.
    cal.file(bill("Repeal weights and measures", 75, 25, true, code[0].id), 1150);
    auto r2 = cal.close_due(1300, code, w, t, next_law_id);
    check("the second session closes", r2.size() == 1);
    check("it enacted one and repealed one", r2[0].enacted == 1 && r2[0].repealed == 1);
    check("the repealed law is marked ended, not deleted",
          code[0].valid_end == 1300 && code.size() == 2);

    // Nothing takes effect mid-session: two bills in one session are decided
    // together, so the second cannot depend on the first having passed.
    {
        Calendar c2(0, 1000, 100);
        std::vector<LawRecord> code2;
        i64 id2 = 1;
        c2.file(bill("Create a law", 90, 10), 10);
        // A repeal aimed at a law that does not exist yet -- filed in the SAME
        // session that creates it. It must not find it.
        c2.file(bill("Repeal that same law", 90, 10, true, 1), 20);
        auto rr = c2.close_due(100, code2, w, t, id2);
        check("both bills in one session are decided together", rr.size() == 1);
        check("the creating bill passed", rr[0].enacted == 1);
        check("the repeal in the same session found nothing to repeal",
              rr[0].outcomes[1].reason.find("no such law") != std::string::npos);
    }

    std::printf("--------------------------------------------------------------\n");
    std::printf("  %d passed, %d failed\n\n", passed, failed);
    return failed ? 1 : 0;
}
