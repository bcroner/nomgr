#include "structural_check.hpp"

#include <map>

namespace nomgr {
namespace {

// Assigns a SAT variable to each distinct Ref. Variables start at 2 because
// 1 and -1 are reserved sentinels in this codebase.
class VarMap {
public:
    i64 get(const Ref& r) {
        auto it = map_.find(r);
        if (it != map_.end()) return it->second;
        const i64 v = next_++;
        map_.emplace(r, v);
        return v;
    }
    i64 count() const { return next_; }
private:
    std::map<Ref, i64> map_;
    i64 next_ = 2;
};

}  // namespace

Instance build_structural(const MarketState& state, const Ref& subject) {
    VarMap vars;
    Instance in;

    // The subject gets a variable first so it is stable and easy to find.
    const i64 subject_var = vars.get(subject);

    for (const Conditions& c : state.conditions) {
        const i64 sv = vars.get(c.subject);
        // subject -> required        becomes  (~subject | required)
        for (const Ref& r : c.requires_all) in.add_clause(-sv, vars.get(r));
        // subject -> not banned      becomes  (~subject | ~banned)
        for (const Ref& r : c.bans)         in.add_clause(-sv, -vars.get(r));
    }

    // Pin what is already known about the world, and pin the subject true --
    // the question is whether the subject CAN hold, not whether the formula
    // has some solution with the subject false.
    const i64 n = vars.count();
    in.n = n;
    in.forced_true.assign(static_cast<std::size_t>(n), 0);
    in.forced_false.assign(static_cast<std::size_t>(n), 0);

    auto pin_true = [&](const Ref& r) {
        const i64 v = vars.get(r);
        if (v < n) in.forced_true[static_cast<std::size_t>(v)] = 1;
    };
    auto pin_false = [&](const Ref& r) {
        const i64 v = vars.get(r);
        if (v < n) in.forced_false[static_cast<std::size_t>(v)] = 1;
    };

    for (const Ref& r : state.in_force) pin_true(r);
    for (const Ref& r : state.not_in_force) pin_false(r);
    in.forced_true[static_cast<std::size_t>(subject_var)] = 1;

    // A Ref that only appeared in in_force / not_in_force may have widened the
    // map after n was taken; recompute so nothing is out of range.
    const i64 n2 = vars.count();
    if (n2 > n) {
        in.n = n2;
        in.forced_true.resize(static_cast<std::size_t>(n2), 0);
        in.forced_false.resize(static_cast<std::size_t>(n2), 0);
        for (const Ref& r : state.in_force) pin_true(r);
        for (const Ref& r : state.not_in_force) pin_false(r);
    }
    return in;
}

StructuralVerdict can_trigger(const MarketState& state, const Ref& subject) {
    StructuralVerdict v;
    const Instance in = build_structural(state, subject);
    const Result r = solve(in);
    v.triggerable = r.satisfiable;
    v.reason = r.satisfiable
        ? "conditions are consistent"
        : "requires/bans cannot all be satisfied at once";
    return v;
}

}  // namespace nomgr
