// vault_check.hpp -- can the vault cover the accepted trades?
//
// Exhaustion is a COUNTING question, not a satisfiability question. Summing
// what the accepted offers demand and comparing it to what the vault holds is
// O(n) arithmetic and exact at any scale. Encoding one SAT variable per
// milligram answers the same question far more expensively: measured, that
// tops out near 10 kg of gold (10 million variables, ~6 s, ~1 GB), while a
// single tonne is 10^9 milligrams.
//
// Identity of specific milligrams is still worth having -- it is what
// distinguishes allocated from unallocated gold, and which deposit backs which
// claim. It just is not what detects exhaustion.
//
// Division of labour:
//   trade_check.hpp  2-SAT: which offers CONFLICT (contest the same unit)
//   vault_check.hpp  arithmetic: whether the vault can COVER what is accepted

#ifndef NOMGR_VAULT_CHECK_HPP
#define NOMGR_VAULT_CHECK_HPP

#include "sat2.hpp"
#include <cstdint>
#include <vector>

namespace nomgr {

struct Deposit {
    i64 id = 0;
    i64 gold_milligram_value = 0;
};

struct GoldClaim {
    i64 offer_id = 0;
    i64 gold_milligrams = 0;   // how much this offer moves out of the vault
};

struct VaultVerdict {
    bool covered = false;      // vault can honour every claim
    i64 vault_total = 0;
    i64 demanded = 0;
    i64 shortfall = 0;         // 0 when covered
};

// Total gold currently held.
i64 vault_total(const std::vector<Deposit>& deposits);

// Can the vault cover all these claims at once?
VaultVerdict check_exhaustion(const std::vector<Deposit>& deposits,
                              const std::vector<GoldClaim>& claims);

}  // namespace nomgr

#endif
