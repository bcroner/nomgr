// session.hpp -- legislative sessions on a fixed interval.
//
// Legislation is not always-on. Sessions open on a schedule, bills are filed
// into whichever session is open, and nothing is enacted until that session
// closes and its bills are tallied together.
//
// Two consequences worth being explicit about:
//
//   * A bill filed while no session is open is not lost. It is held for the
//     next one, which is what an interval-based legislature means in practice.
//
//   * Nothing takes effect mid-session. A bill filed on day one and a bill
//     filed on the last day are decided at the same moment, so neither can
//     depend on the other having already passed.

#ifndef NOMGR_SESSION_HPP
#define NOMGR_SESSION_HPP

#include "vote.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace nomgr {

struct Session {
    i64 id = 0;
    i64 opens_at = 0;
    i64 closes_at = 0;
    bool closed = false;
    std::vector<BillRecord> bills;
};

struct SessionResult {
    i64 session_id = 0;
    std::vector<Outcome> outcomes;      // one per bill, in filing order
    i64 enacted = 0;
    i64 repealed = 0;
    i64 rejected = 0;
};

// Sessions recur: the first opens at `first_opens_at` and each runs for
// `sitting` before closing, with the next opening one `interval` after the
// last one opened.
class Calendar {
public:
    Calendar(i64 first_opens_at, i64 interval, i64 sitting);

    bool in_session(i64 now) const;
    i64 session_index(i64 now) const;        // -1 before the first ever opens
    i64 next_opens_at(i64 now) const;

    // The session accepting filings right now, opening one if it is time.
    // Returns nullptr before the first session ever opens.
    Session* current(i64 now);

    // File a bill. If no session is open it is held for the next one, and the
    // id of the session that will hear it is returned.
    i64 file(const BillRecord& bill, i64 now);

    // Close any session whose sitting has ended, tally its bills against the
    // body of law, and return what happened.
    std::vector<SessionResult> close_due(i64 now,
                                         std::vector<LawRecord>& code,
                                         const Weighting& w,
                                         const Threshold& t,
                                         i64& next_law_id);

    const std::vector<Session>& sessions() const { return sessions_; }
    const std::vector<BillRecord>& held() const { return held_; }

private:
    i64 first_ = 0, interval_ = 0, sitting_ = 0;
    std::vector<Session> sessions_;
    std::vector<BillRecord> held_;      // waiting for the next session to open
};

}  // namespace nomgr

#endif
