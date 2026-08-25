// producer_vote.hpp -- votes backed by committed vouchers, and the fund they
// pay into.
//
// A vote has two constituencies:
//
//   * everyone who turns up, whether or not they hold anything -- the
//     democratic side
//   * producers, who back their vote by COMMITTING vouchers
//
// Two things follow from that, and both matter.
//
// 1. Committing is not a signal. If the measure passes, the committed vouchers
//    are collected and paid into a government fund. Backing a vote with
//    resources costs you exactly when you win, which is what stops resource
//    voting from being free.
//
// 2. How much a producer's commitment counts is set by the democratic side --
//    the people choose how much weight production carries. That is the
//    "chosen percentage".
//
// PASSAGE
//
// Both conditions must be met: the democratic side clears its threshold AND
// the producer side clears its own. One chamber cannot carry a measure over
// the other's objection. A measure with overwhelming money and no popular
// support fails, and so does one with overwhelming support and no backing.
//
// (If a single blended score was intended instead, vote.hpp already does that
// and this file is the wrong shape -- say so and it is a small change.)

#ifndef NOMGR_PRODUCER_VOTE_HPP
#define NOMGR_PRODUCER_VOTE_HPP

#include "vote.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace nomgr {

// One producer putting vouchers behind a side.
struct Commitment {
    i64 participant_id = 0;
    std::vector<i64> voucher_ids;
    i64 gold_milligram_value = 0;   // what those vouchers are worth
    bool in_favour = true;
};

struct ProducerVote {
    Ballot democratic;                       // heads, no resources needed
    std::vector<Commitment> commitments;     // producers backing a side
};

// Set by the democratic side: how much a producer's committed value counts
// relative to a head. 0.0 means commitment carries no weight at all; 1.0 means
// the producer chamber is decided purely on committed value.
struct ProducerWeight {
    double share = 0.5;
};

struct GovernmentFund {
    i64 gold_milligrams = 0;
    std::vector<i64> vouchers;

    i64 total() const { return gold_milligrams; }
};

struct ProducerOutcome {
    bool passed = false;

    Outcome democratic;          // did the people's side clear its bar
    Outcome producer;            // did the producers' side clear its bar

    i64 committed_for = 0;       // milligrams behind each side
    i64 committed_against = 0;
    i64 collected = 0;           // paid into the fund, 0 unless passed
    std::vector<i64> collected_vouchers;

    std::string reason;
};

// Tally a producer-backed vote. On passage the committed vouchers are moved
// into `fund` -- from BOTH sides, since the measure carried and everyone who
// staked resources on it staked them.
ProducerOutcome hold_producer_vote(const ProducerVote& v,
                                   const ProducerWeight& pw,
                                   const Threshold& democratic_bar,
                                   const Threshold& producer_bar,
                                   GovernmentFund& fund);

// Same tally without touching the fund, for previewing an outcome.
ProducerOutcome preview_producer_vote(const ProducerVote& v,
                                      const ProducerWeight& pw,
                                      const Threshold& democratic_bar,
                                      const Threshold& producer_bar);

}  // namespace nomgr

#endif
