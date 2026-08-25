#include "rollback.hpp"

namespace nomgr {

Outcome ratify(const std::string& title,
               const Ballot& b,
               const Weighting& w,
               const Threshold& to_ratify,
               std::vector<Amendment>& amendments,
               i64 now,
               i64& next_id) {
    Outcome o = decide(b, w, to_ratify);
    if (!o.passed) return o;

    Amendment a;
    a.id = next_id++;
    a.title = title;
    a.ratified_at = now;
    a.rolled_back_at = 0;
    amendments.push_back(a);
    o.reason = "ratified";
    return o;
}

RollbackOutcome roll_back(const RollbackProposal& p,
                          const Weighting& w,
                          const Threshold& to_roll_back,
                          std::vector<Amendment>& amendments,
                          i64 now) {
    RollbackOutcome r;
    r.outcome = decide(p.ballot, w, to_roll_back);

    if (!r.outcome.passed) {
        r.note = "rollback did not carry";
        return r;
    }

    for (Amendment& a : amendments) {
        if (a.id != p.target_amendment_id) continue;
        if (!a.in_force()) {
            r.note = "that amendment had already been rolled back";
            return r;
        }
        a.rolled_back_at = now;      // kept on the record, not deleted
        r.rolled_back = true;
        r.note = "rolled back";
        return r;
    }

    r.note = "no such amendment";
    return r;
}

Reversibility examine(const Threshold& to_ratify, const Threshold& to_roll_back) {
    Reversibility v;
    v.ratified_at_share = to_ratify.share;
    v.needed_to_reverse = to_roll_back.share;

    // To reverse, that share must vote FOR rollback, so the share able to
    // block reversal is everything above the remainder.
    v.entrenching_minority = 1.0 - to_roll_back.share;

    // Entrenchment matters when the group that could ratify is also large
    // enough to block any reversal -- i.e. the losers of the original vote
    // cannot reach the rollback bar even if every one of them turns out.
    v.minority_can_entrench = (1.0 - to_ratify.share) >= v.entrenching_minority;
    return v;
}

}  // namespace nomgr
