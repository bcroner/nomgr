#include "vote.hpp"

#include <algorithm>

namespace nomgr {
namespace {

// A side with no votes at all is a tie, not a win. Returning 0.5 keeps an
// empty dimension from dragging the blend to one end.
double share_of(i64 f, i64 a) {
    const i64 total = f + a;
    if (total <= 0) return 0.5;
    return static_cast<double>(f) / static_cast<double>(total);
}

}  // namespace

Tally tally(const Ballot& b, const Weighting& w) {
    Tally t;
    t.heads_total = b.heads_for + b.heads_against;
    t.gold_total = b.gold_for + b.gold_against;
    t.anyone_voted = t.heads_total > 0 || t.gold_total > 0;

    t.head_share_for = share_of(b.heads_for, b.heads_against);
    t.gold_share_for = share_of(b.gold_for, b.gold_against);

    double hw = std::max(0.0, w.head_weight);
    double gw = std::max(0.0, w.gold_weight);
    const double sum = hw + gw;
    if (sum <= 0.0) { hw = 0.5; gw = 0.5; }
    else { hw /= sum; gw /= sum; }

    t.score_for = hw * t.head_share_for + gw * t.gold_share_for;
    return t;
}

Outcome decide(const Ballot& b, const Weighting& w, const Threshold& t) {
    Outcome o;
    o.tally = tally(b, w);

    if (!o.tally.anyone_voted) {
        o.reason = "nobody voted";
        return o;
    }
    if (o.tally.heads_total < t.minimum_heads) {
        o.reason = "quorum not met: " + std::to_string(o.tally.heads_total) +
                   " of " + std::to_string(t.minimum_heads) + " required";
        return o;
    }
    if (o.tally.score_for < t.share) {
        o.reason = "below threshold";
        return o;
    }
    o.passed = true;
    o.reason = "passed";
    return o;
}

Outcome enact(const BillRecord& bill, std::vector<LawRecord>& code,
              const Weighting& w, const Threshold& t,
              i64 now, i64& next_law_id) {

    Outcome o = decide(bill.ballot, w, t);
    if (!o.passed) return o;

    if (bill.repeal) {
        bool found = false;
        for (LawRecord& l : code) {
            if (l.id == bill.target_law_id && l.valid_end == 0) {
                l.valid_end = now;      // repealed, not deleted: the record stays
                found = true;
                break;
            }
        }
        o.reason = found ? "repealed" : "passed, but no such law was in force";
        o.passed = found;
        return o;
    }

    LawRecord l;
    l.id = next_law_id++;
    l.title = bill.title;
    l.classification = bill.classification;
    l.valid_start = now;
    l.valid_end = 0;
    code.push_back(l);
    o.reason = "enacted";
    return o;
}

ConventionResult hold_convention(const Ballot& convention_ballot,
                                 const std::vector<ConventionOption>& options,
                                 const Weighting& w,
                                 const Threshold& to_call,
                                 const Threshold& to_ratify) {
    ConventionResult r;
    r.convention_outcome = decide(convention_ballot, w, to_call);
    r.convention_called = r.convention_outcome.passed;

    // Options are still tallied when the convention fails, so the record shows
    // what would have happened. Nothing is ratified.
    double best = -1.0;
    for (const ConventionOption& opt : options) {
        Outcome o = decide(opt.ballot, w, to_ratify);
        if (!r.convention_called) {
            o.passed = false;
            o.reason = "convention was not called";
        }
        if (o.passed && o.tally.score_for > best) {
            best = o.tally.score_for;
            r.winning_option_id = opt.id;
            r.any_option_passed = true;
        }
        r.option_outcomes.push_back(o);
    }
    return r;
}

}  // namespace nomgr
