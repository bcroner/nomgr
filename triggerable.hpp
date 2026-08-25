// triggerable.hpp -- the whole trade check, in one call.
//
// NOMGR accepts one offer at a time from a queue, and asks this twice: once
// when the offer is found triggerable and enqueued, and again on dequeue
// before dispersing anything, because offers queued earlier may already have
// taken the resources.
//
// Two questions, two tools:
//
//   structural   requires / bans / insurance         2-SAT, linear
//   resource     is the gold actually still there    arithmetic, linear
//
// Neither substitutes for the other. The structural half cannot express a sum;
// the arithmetic half cannot follow a chain of requires and bans.

#ifndef NOMGR_TRIGGERABLE_HPP
#define NOMGR_TRIGGERABLE_HPP

#include "structural_check.hpp"
#include "vault_check.hpp"

#include <string>
#include <vector>

namespace nomgr {

struct TriggerVerdict {
    bool triggerable = false;
    bool structural_ok = false;
    bool resources_ok = false;
    i64 shortfall = 0;
    std::string reason;
};

// Ask whether `offer` can be honoured against the market as it stands NOW.
// Call this at enqueue and again at dequeue.
TriggerVerdict is_triggerable(const MarketState& state,
                              i64 offer_id,
                              const std::vector<Deposit>& holdings,
                              const std::vector<GoldClaim>& claims);

}  // namespace nomgr

#endif
