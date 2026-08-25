// rollback.hpp -- undoing a ratified amendment.
//
// An amendment can look right and turn out badly. The case this exists for:
// a doctrine is adopted, becomes the basis on which every decision is made,
// and is found years later to have been corrosive -- with no mechanism left to
// reverse it, because reversing it needs the same supermajority that a
// coalition benefiting from it can still block.
//
// THE THRESHOLD ASYMMETRY IS THE POINT
//
// If rolling back requires the same share as ratifying, then an amendment
// ratified at 75% can only be undone by 75% against it. A 26% minority is
// enough to keep it forever. That is not a safeguard, it is entrenchment.
//
// So the rollback bar is set SEPARATELY and is expected to be lower. The
// asymmetry is the whole mechanism: hard to adopt, easier to abandon.
//
// The cost of that asymmetry is real and should be stated: amendments are less
// stable, and a measure adopted at 75% can be undone by 50% once opinion
// shifts. That is the trade, and where the bar sits is a political decision,
// not a technical one -- which is why it is a parameter.

#ifndef NOMGR_ROLLBACK_HPP
#define NOMGR_ROLLBACK_HPP

#include "vote.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace nomgr {

struct Amendment {
    i64 id = 0;
    std::string title;
    i64 ratified_at = 0;
    i64 rolled_back_at = 0;      // 0 means still in force
    bool in_force() const { return rolled_back_at == 0; }
};

struct RollbackProposal {
    i64 target_amendment_id = 0;
    std::string reason;
    Ballot ballot;               // "shall this amendment be rolled back?"
};

struct RollbackOutcome {
    bool rolled_back = false;
    Outcome outcome;
    std::string note;
};

// Ratify a new amendment.
Outcome ratify(const std::string& title,
               const Ballot& b,
               const Weighting& w,
               const Threshold& to_ratify,
               std::vector<Amendment>& amendments,
               i64 now,
               i64& next_id);

// Roll one back. The record is kept with rolled_back_at set, never deleted --
// what was in force and when has to remain answerable afterwards.
RollbackOutcome roll_back(const RollbackProposal& p,
                          const Weighting& w,
                          const Threshold& to_roll_back,
                          std::vector<Amendment>& amendments,
                          i64 now);

// Would this amendment be reversible under these two bars? Answers the
// entrenchment question directly: given the share that ratified it, what share
// of opposition is needed to undo it, and is that reachable.
struct Reversibility {
    double ratified_at_share = 0.0;
    double needed_to_reverse = 0.0;
    bool minority_can_entrench = false;
    double entrenching_minority = 0.0;   // share that suffices to block reversal
};

Reversibility examine(const Threshold& to_ratify, const Threshold& to_roll_back);

}  // namespace nomgr

#endif
