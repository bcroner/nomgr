#include "trade_check.hpp"

#include <map>
#include <vector>

namespace nomgr {

TradeCheck build_trade_check(const std::vector<OfferSpec>& offers) {
    TradeCheck tc;

    // Variables start at 2; 1 and -1 are reserved sentinels in this codebase.
    i64 next_var = 2;

    tc.offer_var.resize(offers.size());
    for (std::size_t i = 0; i < offers.size(); ++i)
        tc.offer_var[i] = next_var++;

    // Every distinct unit id gets one variable, shared by every offer that
    // touches it. This is the identity the original encoding lacked.
    std::map<i64, i64> unit_var;
    auto var_for_unit = [&](i64 unit) -> i64 {
        auto it = unit_var.find(unit);
        if (it != unit_var.end()) return it->second;
        const i64 v = next_var++;
        unit_var.emplace(unit, v);
        return v;
    };

    // Which offers claim each given unit, so we know what conflicts.
    std::map<i64, std::vector<std::size_t>> claimants;

    for (std::size_t i = 0; i < offers.size(); ++i) {
        const OfferSpec& o = offers[i];
        const i64 ov = tc.offer_var[i];

        for (const i64 unit : o.gives) {
            const i64 uv = var_for_unit(unit);
            tc.instance.add_clause(ov, -uv);      // (offer | ~unit)
            tc.instance.add_clause(-ov, uv);      // (~offer | unit)  => offer <-> unit
            claimants[unit].push_back(i);
        }
        for (const i64 unit : o.receives) {
            const i64 uv = var_for_unit(unit);
            tc.instance.add_clause(ov, -uv);
            tc.instance.add_clause(-ov, uv);
        }
    }

    // The constraint the original was missing: one unit, one spender.
    // Pairwise is O(k^2) clauses in the number of offers claiming a unit, but
    // every clause stays binary, so the instance stays 2-SAT and linear to
    // decide. A commander encoding would be smaller but needs ternary clauses,
    // which would leave 2-SAT entirely.
    for (const auto& entry : claimants) {
        const std::vector<std::size_t>& who = entry.second;
        for (std::size_t a = 0; a < who.size(); ++a)
            for (std::size_t b = a + 1; b < who.size(); ++b)
                tc.instance.add_clause(-tc.offer_var[who[a]], -tc.offer_var[who[b]]);
    }

    // Pinned offers become unit clauses (x | x).
    tc.instance.n = next_var;
    tc.instance.forced_true.assign(static_cast<std::size_t>(next_var), 0);
    tc.instance.forced_false.assign(static_cast<std::size_t>(next_var), 0);
    for (std::size_t i = 0; i < offers.size(); ++i)
        if (offers[i].forced)
            tc.instance.forced_true[static_cast<std::size_t>(tc.offer_var[i])] = 1;

    return tc;
}

bool all_can_clear(const std::vector<OfferSpec>& offers) {
    std::vector<OfferSpec> pinned = offers;
    for (OfferSpec& o : pinned) o.forced = true;
    return solve(build_trade_check(pinned).instance).satisfiable;
}

}  // namespace nomgr
