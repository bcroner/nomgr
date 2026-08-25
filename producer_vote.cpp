#include "producer_vote.hpp"

namespace nomgr {
namespace {

ProducerOutcome tally_only(const ProducerVote& v,
                           const ProducerWeight& pw,
                           const Threshold& democratic_bar,
                           const Threshold& producer_bar) {
    ProducerOutcome o;

    // The producer chamber: heads that committed, and value committed.
    Ballot producer_ballot;
    for (const Commitment& c : v.commitments) {
        if (c.gold_milligram_value < 0) continue;
        if (c.in_favour) {
            producer_ballot.heads_for += 1;
            producer_ballot.gold_for += c.gold_milligram_value;
            o.committed_for += c.gold_milligram_value;
        } else {
            producer_ballot.heads_against += 1;
            producer_ballot.gold_against += c.gold_milligram_value;
            o.committed_against += c.gold_milligram_value;
        }
    }

    // The people choose how much committed value counts inside the producer
    // chamber. share = 0 makes it one producer one vote; share = 1 makes it
    // decided purely by what was staked.
    double s = pw.share;
    if (s < 0.0) s = 0.0;
    if (s > 1.0) s = 1.0;
    const Weighting producer_weighting{1.0 - s, s};

    o.democratic = decide(v.democratic, Weighting::one_person_one_vote(), democratic_bar);
    o.producer = decide(producer_ballot, producer_weighting, producer_bar);

    // Both conditions, not either.
    o.passed = o.democratic.passed && o.producer.passed;

    if (o.passed)                       o.reason = "passed both chambers";
    else if (!o.democratic.passed && !o.producer.passed)
                                        o.reason = "failed both chambers";
    else if (!o.democratic.passed)      o.reason = "producers carried it, the people did not";
    else                                o.reason = "the people carried it, producers did not";

    return o;
}

}  // namespace

ProducerOutcome preview_producer_vote(const ProducerVote& v,
                                      const ProducerWeight& pw,
                                      const Threshold& democratic_bar,
                                      const Threshold& producer_bar) {
    return tally_only(v, pw, democratic_bar, producer_bar);
}

ProducerOutcome hold_producer_vote(const ProducerVote& v,
                                   const ProducerWeight& pw,
                                   const Threshold& democratic_bar,
                                   const Threshold& producer_bar,
                                   GovernmentFund& fund) {
    ProducerOutcome o = tally_only(v, pw, democratic_bar, producer_bar);
    if (!o.passed) return o;             // nothing is collected on a failed vote

    // The measure carried, so everything staked on it is collected -- from
    // both sides. Committing is a real commitment either way.
    for (const Commitment& c : v.commitments) {
        if (c.gold_milligram_value < 0) continue;
        o.collected += c.gold_milligram_value;
        for (const i64 id : c.voucher_ids) {
            o.collected_vouchers.push_back(id);
            fund.vouchers.push_back(id);
        }
    }
    fund.gold_milligrams += o.collected;
    return o;
}

}  // namespace nomgr
