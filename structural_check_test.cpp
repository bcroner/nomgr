#include "structural_check.hpp"
#include <cstdio>
#include <string>

using namespace nomgr;
static int passed = 0, failed = 0;
static void check(const std::string& l, bool c) {
    if (c) { ++passed; std::printf("  PASS  %s\n", l.c_str()); }
    else { ++failed; std::printf("  FAIL  %s\n", l.c_str()); }
}

int main() {
    std::printf("\nSTRUCTURAL CHECK\n----------------------------------------------------------\n");

    // An offer with no conditions can always trigger.
    {
        MarketState st;
        check("an unconstrained offer triggers", can_trigger(st, offer_ref(1)).triggerable);
    }

    // Requires a participant who is present.
    {
        MarketState st;
        st.conditions = {{offer_ref(1), {participant_ref(7)}, {}}};
        st.in_force = {participant_ref(7)};
        check("required participant present -> triggers",
              can_trigger(st, offer_ref(1)).triggerable);
    }
    // Requires a participant who is absent.
    {
        MarketState st;
        st.conditions = {{offer_ref(1), {participant_ref(7)}, {}}};
        st.not_in_force = {participant_ref(7)};
        check("required participant absent -> refused",
              !can_trigger(st, offer_ref(1)).triggerable);
    }
    // Bans a participant who is present.
    {
        MarketState st;
        st.conditions = {{offer_ref(1), {}, {participant_ref(9)}}};
        st.in_force = {participant_ref(9)};
        check("banned participant present -> refused",
              !can_trigger(st, offer_ref(1)).triggerable);
    }
    // Requires an insurance policy that is in force.
    {
        MarketState st;
        st.conditions = {{offer_ref(1), {policy_ref(3)}, {}}};
        st.in_force = {policy_ref(3)};
        check("required policy in force -> triggers",
              can_trigger(st, offer_ref(1)).triggerable);
    }
    {
        MarketState st;
        st.conditions = {{offer_ref(1), {policy_ref(3)}, {}}};
        st.not_in_force = {policy_ref(3)};
        check("required policy absent -> refused",
              !can_trigger(st, offer_ref(1)).triggerable);
    }

    // Requiring and banning the same thing is self-contradictory.
    {
        MarketState st;
        st.conditions = {{offer_ref(1), {participant_ref(4)}, {participant_ref(4)}}};
        check("requiring and banning the same participant -> refused",
              !can_trigger(st, offer_ref(1)).triggerable);
    }

    // THE CASE THAT NEEDS A SOLVER:
    // A requires B, B requires C, C bans A.  A -> B -> C -> ~A, so A cannot hold.
    {
        MarketState st;
        st.conditions = {
            {offer_ref(1), {offer_ref(2)}, {}},
            {offer_ref(2), {offer_ref(3)}, {}},
            {offer_ref(3), {}, {offer_ref(1)}},
        };
        check("transitive requires ending in a ban -> refused",
              !can_trigger(st, offer_ref(1)).triggerable);
        // ...but C itself is perfectly fine.
        check("the offer at the end of that chain still triggers",
              can_trigger(st, offer_ref(3)).triggerable);
    }

    // A longer chain that stays consistent.
    {
        MarketState st;
        st.conditions = {
            {offer_ref(1), {offer_ref(2)}, {}},
            {offer_ref(2), {offer_ref(3)}, {}},
            {offer_ref(3), {offer_ref(4)}, {}},
            {offer_ref(4), {}, {offer_ref(9)}},
        };
        check("a long consistent chain triggers", can_trigger(st, offer_ref(1)).triggerable);
    }

    // Participant-level conditions, which the header also gives.
    {
        MarketState st;
        st.conditions = {
            {offer_ref(1), {participant_ref(5)}, {}},
            {participant_ref(5), {}, {policy_ref(2)}},   // participant bans a policy
        };
        st.in_force = {policy_ref(2)};
        check("participant's own ban propagates to the offer",
              !can_trigger(st, offer_ref(1)).triggerable);
    }

    // Mutual bans: each alone is fine.
    {
        MarketState st;
        st.conditions = {
            {offer_ref(1), {}, {offer_ref(2)}},
            {offer_ref(2), {}, {offer_ref(1)}},
        };
        check("mutually banning offers -- offer 1 alone triggers",
              can_trigger(st, offer_ref(1)).triggerable);
        check("mutually banning offers -- offer 2 alone triggers",
              can_trigger(st, offer_ref(2)).triggerable);
    }

    std::printf("----------------------------------------------------------\n");
    std::printf("  %d passed, %d failed\n\n", passed, failed);
    return failed ? 1 : 0;
}
