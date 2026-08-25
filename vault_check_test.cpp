#include "vault_check.hpp"
#include <chrono>
#include <cstdio>
#include <string>

using namespace nomgr;
static int passed = 0, failed = 0;
static void check(const std::string& l, bool c) {
    if (c) { ++passed; std::printf("  PASS  %s\n", l.c_str()); }
    else { ++failed; std::printf("  FAIL  %s\n", l.c_str()); }
}

int main() {
    std::printf("\nVAULT EXHAUSTION\n--------------------------------------------------\n");

    std::vector<Deposit> vault = {{1, 500}, {2, 300}, {3, 200}};   // 1000 mg
    check("vault total sums the deposits", vault_total(vault) == 1000);

    {
        VaultVerdict v = check_exhaustion(vault, {{10, 400}, {11, 300}});
        check("demand under supply is covered", v.covered && v.shortfall == 0);
    }
    {
        VaultVerdict v = check_exhaustion(vault, {{10, 600}, {11, 500}});
        check("demand over supply is refused", !v.covered);
        check("shortfall is reported exactly", v.shortfall == 100);
    }
    {
        VaultVerdict v = check_exhaustion(vault, {{10, 1000}});
        check("demand exactly equal to supply is covered", v.covered);
    }
    {
        VaultVerdict v = check_exhaustion(vault, {});
        check("no claims is covered", v.covered && v.demanded == 0);
    }
    {
        VaultVerdict v = check_exhaustion({}, {{10, 1}});
        check("empty vault cannot cover any claim", !v.covered && v.shortfall == 1);
    }
    {
        // A wrapped total would report a vault able to cover anything.
        std::vector<Deposit> huge = {{1, INT64_MAX}, {2, INT64_MAX}};
        check("overflowing vault total saturates instead of wrapping",
              vault_total(huge) == INT64_MAX);
    }

    // National-reserve scale, which per-milligram SAT cannot reach at all.
    {
        std::vector<Deposit> big;
        const i64 n = 400000;                       // 400k deposits
        for (i64 i = 0; i < n; ++i) big.push_back({i, 1000000});  // 1 g each
        std::vector<GoldClaim> claims;
        for (i64 i = 0; i < n; ++i) claims.push_back({i, 999999});

        const auto t0 = std::chrono::steady_clock::now();
        VaultVerdict v = check_exhaustion(big, claims);
        const auto t1 = std::chrono::steady_clock::now();
        const double ms = std::chrono::duration<double, std::milli>(t1 - t0).count();

        std::printf("        %lld deposits totalling %.1f kg, %lld claims -> %.2f ms\n",
                    (long long)n, (double)v.vault_total / 1e6, (long long)claims.size(), ms);
        check("400 tonnes of gold across 400k deposits checked", v.covered);
        check("that check took under 50 ms", ms < 50.0);
    }

    std::printf("--------------------------------------------------\n");
    std::printf("  %d passed, %d failed\n\n", passed, failed);
    return failed ? 1 : 0;
}
