#include "session.hpp"

namespace nomgr {

Calendar::Calendar(i64 first_opens_at, i64 interval, i64 sitting)
    : first_(first_opens_at), interval_(interval > 0 ? interval : 1),
      sitting_(sitting > 0 ? sitting : 1) {}

i64 Calendar::session_index(i64 now) const {
    if (now < first_) return -1;
    return (now - first_) / interval_;
}

bool Calendar::in_session(i64 now) const {
    const i64 ix = session_index(now);
    if (ix < 0) return false;
    const i64 opened = first_ + ix * interval_;
    return now < opened + sitting_;
}

i64 Calendar::next_opens_at(i64 now) const {
    if (now < first_) return first_;
    const i64 ix = session_index(now);
    if (in_session(now)) return first_ + ix * interval_;
    return first_ + (ix + 1) * interval_;
}

Session* Calendar::current(i64 now) {
    if (!in_session(now)) return nullptr;
    const i64 ix = session_index(now);
    for (Session& s : sessions_)
        if (s.id == ix) return &s;

    Session s;
    s.id = ix;
    s.opens_at = first_ + ix * interval_;
    s.closes_at = s.opens_at + sitting_;
    // Anything filed while the chamber was dark is taken up now.
    s.bills = held_;
    held_.clear();
    sessions_.push_back(s);
    return &sessions_.back();
}

i64 Calendar::file(const BillRecord& bill, i64 now) {
    Session* s = current(now);
    if (s) {
        s->bills.push_back(bill);
        return s->id;
    }
    held_.push_back(bill);
    // It will be heard by whichever session opens next.
    const i64 opens = next_opens_at(now);
    return (opens - first_) / interval_;
}

std::vector<SessionResult> Calendar::close_due(i64 now,
                                               std::vector<LawRecord>& code,
                                               const Weighting& w,
                                               const Threshold& t,
                                               i64& next_law_id) {
    std::vector<SessionResult> results;

    for (Session& s : sessions_) {
        if (s.closed || now < s.closes_at) continue;

        SessionResult r;
        r.session_id = s.id;

        // Every bill is decided against the law AS IT STOOD when the session
        // opened, then the passing ones are applied. Deciding them in filing
        // order instead would let a bill depend on an earlier bill in the same
        // session having passed, which makes the order of filing decide
        // outcomes -- exactly what a fixed sitting should prevent.
        std::vector<LawRecord> snapshot = code;

        for (const BillRecord& b : s.bills) {
            // Decide against the snapshot: a repeal only finds laws that were
            // already in force when the session opened.
            std::vector<LawRecord> trial = snapshot;
            i64 trial_id = next_law_id;
            Outcome o = enact(b, trial, w, t, s.closes_at, trial_id);

            if (o.passed) {
                // Apply for real, to the live body of law.
                if (b.repeal) {
                    for (LawRecord& l : code)
                        if (l.id == b.target_law_id && l.valid_end == 0) {
                            l.valid_end = s.closes_at;
                            break;
                        }
                    r.repealed++;
                } else {
                    LawRecord l;
                    l.id = next_law_id++;
                    l.title = b.title;
                    l.classification = b.classification;
                    l.valid_start = s.closes_at;
                    l.valid_end = 0;
                    code.push_back(l);
                    r.enacted++;
                }
            } else {
                r.rejected++;
            }
            r.outcomes.push_back(o);
        }

        s.closed = true;
        results.push_back(r);
    }
    return results;
}

}  // namespace nomgr
