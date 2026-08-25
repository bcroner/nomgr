#include "triggerable.hpp"
#include <cstdio>
#include <deque>
#include <string>

using namespace nomgr;
static int passed = 0, failed = 0;
static void check(const std::string& l, bool c) {
    if (c) { ++passed; std::printf("  PASS  %s\n", l.c_str()); }
    else { ++failed; std::printf("  FAIL  %s\n", l.c_str()); }
}

int main() {
    std::printf("\nTRIGGERABILITY (structural + resources)\n");
    std::printf("--------------------------------------------------------------\n");

    MarketState clear_state;                       // no requires or bans
    std::vector<Deposit> vault = {{1, 1000}};

    {
        TriggerVerdict v = is_triggerable(clear_state, 1, vault, {{1, 500}});
        check("clear conditions, gold available -> triggerable", v.triggerable);
    }
    {
        TriggerVerdict v = is_triggerable(clear_state, 1, vault, {{1, 1500}});
        check("clear conditions, not enough gold -> refused", !v.triggerable);
        check("the shortfall is reported", v.shortfall == 500);
        check("it reports a resource failure, not a structural one",
              v.structural_ok && !v.resources_ok);
    }
    {
        MarketState st;
        st.conditions = {{offer_ref(1), {}, {participant_ref(9)}}};
        st.in_force = {participant_ref(9)};
        TriggerVerdict v = is_triggerable(st, 1, vault, {{1, 10}});
        check("banned participant present -> refused", !v.triggerable);
        check("it reports a structural failure, not a resource one",
              !v.structural_ok && !v.resources_ok);
    }

    // The full queue, both checks, exactly as NOMGR runs it.
    {
        std::printf("\n  queue walk-through, one offer at a time:\n");
        i64 held = 100;
        std::deque<i64> queue;
        const i64 demand = 100;

        for (i64 id : {1, 2}) {
            std::vector<Deposit> now = {{1, held}};
            TriggerVerdict v = is_triggerable(clear_state, id, now, {{id, demand}});
            std::printf("    offer %lld enqueue: %s\n", (long long)id, v.reason.c_str());
            if (v.triggerable) queue.push_back(id);
        }
        while (!queue.empty()) {
            const i64 id = queue.front(); queue.pop_front();
            std::vector<Deposit> now = {{1, held}};
            TriggerVerdict v = is_triggerable(clear_state, id, now, {{id, demand}});
            std::printf("    offer %lld dequeue: %s", (long long)id, v.reason.c_str());
            if (v.triggerable) { held -= demand; std::printf(" -> executed, %lld mg left\n", (long long)held); }
            else std::printf(" -> refused\n");
        }
        check("the queue never overdraws the vault", held >= 0);
        check("exactly one of the two competing offers executed", held == 0);
    }

    std::printf("--------------------------------------------------------------\n");
    std::printf("  %d passed, %d failed\n\n", passed, failed);
    return failed ? 1 : 0;
}
