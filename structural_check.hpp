// structural_check.hpp -- can this offer trigger, given the market's
// requires / bans / insurance conditions?
//
// This is the 2-SAT half of the trade check. The other half, whether the
// resources are actually there, is arithmetic and lives in vault_check.hpp.
//
// WHY A SOLVER AND NOT A LOOKUP PASS
//
// Requires and bans chain between offers. If A requires B, B requires C, and
// C bans A, then A implies B implies C implies not-A, so A can never trigger.
// Walking the lists once will not see that. Building the implication graph and
// asking whether A can be true does, and does it in linear time.
//
// The full constraint set, per the design:
//   participant requires / bans   (Participant::require, Participant::bans)
//   offer requires / bans participants
//   offer requires / bans offers
//   insurance policies required / accepted / applied

#ifndef NOMGR_STRUCTURAL_CHECK_HPP
#define NOMGR_STRUCTURAL_CHECK_HPP

#include "sat2.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace nomgr {

// Every constrainable thing gets a kind and an id. Ids are only unique within
// a kind, so the pair is the key.
enum class Kind : int { Offer = 0, Participant = 1, Policy = 2 };

struct Ref {
    Kind kind = Kind::Offer;
    i64 id = 0;
    bool operator<(const Ref& o) const {
        if (kind != o.kind) return static_cast<int>(kind) < static_cast<int>(o.kind);
        return id < o.id;
    }
    bool operator==(const Ref& o) const { return kind == o.kind && id == o.id; }
};

inline Ref offer_ref(i64 id) { return {Kind::Offer, id}; }
inline Ref participant_ref(i64 id) { return {Kind::Participant, id}; }
inline Ref policy_ref(i64 id) { return {Kind::Policy, id}; }

// One entity's conditions. Applies to both offers and participants -- the
// header gives Participant a require/bans pair as well.
struct Conditions {
    Ref subject;
    std::vector<Ref> requires_all;   // subject implies each of these
    std::vector<Ref> bans;           // subject implies NOT each of these
};

struct MarketState {
    std::vector<Conditions> conditions;
    std::vector<Ref> in_force;       // pinned true: already active
    std::vector<Ref> not_in_force;   // pinned false: known absent
};

struct StructuralVerdict {
    bool triggerable = false;
    std::string reason;
};

// Can `subject` be true given everything in `state`?
StructuralVerdict can_trigger(const MarketState& state, const Ref& subject);

// Build the instance without solving, for inspection or batching.
Instance build_structural(const MarketState& state, const Ref& subject);

}  // namespace nomgr

#endif
