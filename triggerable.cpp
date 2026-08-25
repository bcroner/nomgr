#include "triggerable.hpp"

namespace nomgr {

TriggerVerdict is_triggerable(const MarketState& state,
                              i64 offer_id,
                              const std::vector<Deposit>& holdings,
                              const std::vector<GoldClaim>& claims) {
    TriggerVerdict v;

    const StructuralVerdict s = can_trigger(state, offer_ref(offer_id));
    v.structural_ok = s.triggerable;
    if (!v.structural_ok) {
        v.reason = "structural: " + s.reason;
        return v;
    }

    const VaultVerdict r = check_exhaustion(holdings, claims);
    v.resources_ok = r.covered;
    v.shortfall = r.shortfall;
    if (!v.resources_ok) {
        v.reason = "resources: short by " + std::to_string(r.shortfall) +
                   " gold milligrams";
        return v;
    }

    v.triggerable = true;
    v.reason = "triggerable";
    return v;
}

}  // namespace nomgr
