// trade_check.hpp -- build the 2-SAT instance for a set of proposed trades.
//
// This replaces create_trade_check. It is written against plain data rather
// than Market/Offer so that it can be tested now, and wired into the market
// structs once those compile.
//
// WHAT THE ORIGINAL ENCODING MISSED
//
// create_trade_check emits, for every offer and each thing it gives:
//
//     (offer | ~give)  and  (~offer | give)      i.e.  offer <-> give
//
// Biconditionals alone are ALWAYS satisfiable -- they sort variables into
// equivalence classes and nothing ever contradicts. So the check accepted
// every trade set it was given, including two offers spending the same
// milligram of gold. See doublespend_demo.cpp.
//
// Two things are needed to make it decide anything:
//
//   1. Unit identity. A gold milligram (or any voucher) must carry the SAME
//      id wherever it appears. The original minted a fresh id per offer from
//      a running counter, so two offers spending one milligram referred to
//      two different ids and could never collide.
//
//   2. Mutual exclusion. For every unit claimed by more than one offer, emit
//      (~A | ~B) for each pair. That is what forbids double spending, and it
//      is still a binary clause, so the problem stays 2-SAT and stays linear.
//
// WHAT THIS ENCODING CANNOT EXPRESS
//
// 2-CNF can say "these two offers conflict". It cannot say "the gold given
// must equal the gold received" -- that is arithmetic, not a binary clause.
// Value balance has to be checked separately, before or after the SAT step.

#ifndef NOMGR_TRADE_CHECK_HPP
#define NOMGR_TRADE_CHECK_HPP

#include "sat2.hpp"

#include <cstdint>
#include <vector>

namespace nomgr {

// One proposed trade. `gives` and `receives` are unit ids -- a voucher id, or
// the id of a specific milligram of gold. The same physical unit must carry
// the same id across every offer that touches it.
struct OfferSpec {
    i64 id = 0;
    std::vector<i64> gives;
    std::vector<i64> receives;
    bool forced = false;      // pin this offer to accepted (for "can these all clear?")
};

struct TradeCheck {
    Instance instance;
    // offer_var[i] is the SAT variable for instances[i]; useful for reading
    // an assignment back out.
    std::vector<i64> offer_var;
};

// Build the instance. Emits, for each offer:
//   offer <-> each give, offer <-> each receive     (the original's intent)
//   (~A | ~B) for every pair of offers claiming the same give unit
TradeCheck build_trade_check(const std::vector<OfferSpec>& offers);

// Convenience: can every offer in the set be honoured at once?
bool all_can_clear(const std::vector<OfferSpec>& offers);

}  // namespace nomgr

#endif
