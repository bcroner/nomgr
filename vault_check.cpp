#include "vault_check.hpp"

namespace nomgr {

i64 vault_total(const std::vector<Deposit>& deposits) {
    i64 total = 0;
    for (const Deposit& d : deposits) {
        // Guard against overflow rather than wrapping silently: a wrapped
        // total would report a vault that can cover anything.
        if (d.gold_milligram_value < 0) continue;
        if (total > INT64_MAX - d.gold_milligram_value) return INT64_MAX;
        total += d.gold_milligram_value;
    }
    return total;
}

VaultVerdict check_exhaustion(const std::vector<Deposit>& deposits,
                              const std::vector<GoldClaim>& claims) {
    VaultVerdict v;
    v.vault_total = vault_total(deposits);

    i64 demanded = 0;
    for (const GoldClaim& c : claims) {
        if (c.gold_milligrams <= 0) continue;
        if (demanded > INT64_MAX - c.gold_milligrams) { demanded = INT64_MAX; break; }
        demanded += c.gold_milligrams;
    }
    v.demanded = demanded;
    v.covered = demanded <= v.vault_total;
    v.shortfall = v.covered ? 0 : demanded - v.vault_total;
    return v;
}

}  // namespace nomgr
