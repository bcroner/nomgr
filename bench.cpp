// bench.cpp -- the original NOMGR solver against the linear-time replacement.
//
// The original algorithm below is lifted VERBATIM from NOMGR.cpp (the function
// SATSolver_isSat), renamed only so that both can live in one binary. No logic
// was altered, so this is an apples-to-apples comparison.

#include "sat2.hpp"

#include <chrono>
#include <cstdio>
#include <cstdint>
#include <random>
#include <vector>

#define TRUE_2SAT 1
#define FALSE_2SAT -1

// Vector helpers the extracted solver calls, copied verbatim from NOMGR.cpp.
static __int64* simp_vector_create(__int64 init_sz) {
    return new __int64[init_sz];
}
static __int64 simp_vector_read(__int64* v, __int64 vtop, __int64, __int64 loc) {
    if (loc > vtop) return 0;
    return v[loc];
}
static void simp_vector_append(__int64** v, __int64* vtop, __int64* vcap, __int64 data) {
    *vtop = *vtop + 1;
    if (*vtop < *vcap) { (*v)[*vtop] = data; return; }
    __int64* newv = new __int64[*vcap * 2];
    for (__int64 i = 0; i < *vcap * 2; i++) newv[i] = 0;
    for (__int64 i = 0; i < *vcap; i++) newv[i] = (*v)[i];
    *vcap = *vcap * 2;
    delete[](*v);
    *v = newv;
    (*v)[*vtop] = data;
}

struct SATSolver {
    __int64 n_parm, k_parm, chops, chop, leading_trues;
    bool* Z;
    __int64* lst_l_parm;
    __int64* lst_r_parm;
    bool* is_f;
    bool* is_t;
};

bool original_isSat(SATSolver* s, bool* sln) {

    __int64* encoding = new __int64[s->n_parm]; // from 2..n_parm to 2..n

    for (__int64 i = 0; i < s->n_parm; i++)
        encoding[i] = 0;

    bool* used = new bool[s->n_parm];

    for (__int64 i = 0; i < s->n_parm; i++)
        used[i] = false;

    for (__int64 i = 2; i < s->n_parm; i++)
        if (s->is_f[i] || s->is_t[i])
            used[i] = true;

    for (__int64 i = 0; i < s->k_parm; i++) {

        if ((s->lst_l_parm)[i] == FALSE_2SAT || (s->lst_r_parm)[i] == FALSE_2SAT)
            continue;
        else {

            __int64 l_abs = (s->lst_l_parm)[i] < 0 ? -((s->lst_l_parm)[i]) : (s->lst_l_parm)[i];
            __int64 r_abs = (s->lst_r_parm)[i] < 0 ? -((s->lst_r_parm)[i]) : (s->lst_r_parm)[i];

            used[l_abs] = true;
            used[r_abs] = true;
        }
    }

    __int64 n = 2;

    for (__int64 i = 2; i < s->n_parm; i++)
        if (used[i]) {
            encoding[i] = n;
            n++;
        }

    __int64* lst_l = new __int64[s->k_parm];
    __int64* lst_r = new __int64[s->k_parm];

    for (__int64 i = 0; i < s->k_parm; i++) {
        lst_l[i] = 0;
        lst_r[i] = 0;
    }

    __int64 k = 0;

    for (__int64 i = 0; i < s->k_parm; i++) {

        if (s->lst_l_parm[i] == FALSE_2SAT || s->lst_r_parm[i] == FALSE_2SAT)
            continue;
        else {

            __int64 l_abs = s->lst_l_parm[i] < 0 ? -(s->lst_l_parm[i]) : s->lst_l_parm[i];
            __int64 r_abs = s->lst_r_parm[i] < 0 ? -(s->lst_r_parm[i]) : s->lst_r_parm[i];

            lst_l[k] = s->lst_l_parm[i] < 0 ? -encoding[l_abs] : encoding[l_abs];
            lst_r[k] = s->lst_r_parm[i] < 0 ? -encoding[r_abs] : encoding[r_abs];

            k++;
        }
    }

    /*
    for (__int64 i = 0; i < k_parm; i++)
        printf_s("%lld: %lld %lld\n", i, lst_l[i], lst_r[i]);
    printf_s("\n");
    //*/

    __int64* false_implies_top = new __int64[n];
    __int64* false_implies_cap = new __int64[n];
    __int64** false_implies = new __int64* [n];
    __int64* true_implies_top = new __int64[n];
    __int64* true_implies_cap = new __int64[n];
    __int64** true_implies = new __int64* [n];

    for (__int64 i = 0; i < n; i++) {
        false_implies_top[i] = -1;
        false_implies_cap[i] = 16;
        false_implies[i] = simp_vector_create(false_implies_cap[i]);
        true_implies_top[i] = -1;
        true_implies_cap[i] = 16;
        true_implies[i] = simp_vector_create(true_implies_cap[i]);
    }

    for (__int64 i = 0; i < k; i++) {

        __int64 l_abs = lst_l[i] < 0 ? -lst_l[i] : lst_l[i];
        __int64 r_abs = lst_r[i] < 0 ? -lst_r[i] : lst_r[i];

        if (lst_l[i] < 0)
            simp_vector_append(&(true_implies[l_abs]), &(true_implies_top[l_abs]), &(true_implies_cap[l_abs]), lst_r[i]);
        else
            simp_vector_append(&(false_implies[l_abs]), &(false_implies_top[l_abs]), &(false_implies_cap[l_abs]), lst_r[i]);

        if (lst_r[i] < 0)
            simp_vector_append(&(true_implies[r_abs]), &(true_implies_top[r_abs]), &(true_implies_cap[r_abs]), lst_l[i]);
        else
            simp_vector_append(&(false_implies[r_abs]), &(false_implies_top[r_abs]), &(false_implies_cap[r_abs]), lst_l[i]);

    }

    bool is_sat = false;
    __int64 ix = n - 1;
    bool* Z = new bool[n];
    for (__int64 i = 0; i < n; i++)
        Z[i] = s->Z[i];

    bool* falses = new bool[n];
    bool* trues = new bool[n];

    while (true) {

        for (__int64 i = 0; i < n; i++) {
            falses[i] = false;
            trues[i] = false;
        }

        for (__int64 i = 2; i < s->n_parm; i++) {
            if (s->is_f[i])
                falses[encoding[i]] = true;
            if (s->is_t[i])
                trues[encoding[i]] = true;
        }

        for (__int64 i = ix; i < n; i++)
            if (Z[i])
                trues[i] = true;
            else
                falses[i] = true;

        bool changed;

        do {

            changed = false;

            for (__int64 i = 2; i < n; i++) {
                if (trues[i]) {
                    for (__int64 j = 0; j < true_implies_top[i] + 1; j++) {

                        __int64 val = true_implies[i][j];
                        __int64 val_abs = val < 0 ? -val : val;

                        if (val < 0) {
                            if (!falses[val_abs]) {
                                falses[val_abs] = true;
                                changed = true;
                            }
                        }
                        else {
                            if (!trues[val_abs]) {
                                trues[val_abs] = true;
                                changed = true;
                            }
                        }
                    }
                }
                if (falses[i])
                    for (__int64 j = 0; j < false_implies_top[i] + 1; j++) {

                        __int64 val = false_implies[i][j];
                        __int64 val_abs = val < 0 ? -val : val;

                        if (val < 0) {
                            if (!falses[val_abs]) {
                                falses[val_abs] = true;
                                changed = true;
                            }
                        }
                        else {
                            if (!trues[val_abs]) {
                                trues[val_abs] = true;
                                changed = true;
                            }
                        }
                    }
            }
        } while (changed);

        bool contradiction = false;

        for (__int64 i = 2; i < n; i++)
            if (trues[i] && falses[i]) {
                contradiction = true;
                break;
            }

        if (!contradiction && ix == 2) {
            is_sat = true;
            break;
        }
        else if (!contradiction)
            ix--;
        else if (contradiction) {

            while (ix < n)
                if (Z[ix]) {
                    Z[ix] = false;
                    ix++;
                }
                else {
                    Z[ix] = true;
                    break;
                }

            for (__int64 i = ix - 1; i >= 0; i--)
                Z[i] = false;

        }

        if (ix >= s->n_parm - s->leading_trues - s->chops)
            break;

    }

    // clean up

    delete[] falses;
    delete[] trues;

    delete[] Z;

    for (__int64 i = 0; i < n; i++)
        delete[] false_implies[i];

    delete[] false_implies_top;
    delete[] false_implies_cap;
    delete[] false_implies;

    for (__int64 i = 0; i < n; i++)
        delete[] true_implies[i];

    delete[] true_implies_top;
    delete[] true_implies_cap;
    delete[] true_implies;

    delete[] encoding;

    delete[] used;

    delete[] lst_l;
    delete[] lst_r;

    return is_sat;
}

int main() {
    std::printf("\nSOLVER COMPARISON -- identical instances, both algorithms\n");
    std::printf("--------------------------------------------------------------\n");
    std::printf("  vars  clauses |      original |     linear | speedup\n");
    std::printf("--------------------------------------------------------------\n");

    std::mt19937_64 rng(2026);
    bool original_viable = true;

    const int sizes[] = {10, 14, 18, 22, 26, 30, 34, 38};
    for (int si = 0; si < 8; ++si) {
        const int nv = sizes[si];
        const int k = nv * 2;

        std::vector<__int64> L(k), R(k);
        nomgr::Instance in;
        in.n = nv + 2;
        for (int c = 0; c < k; ++c) {
            __int64 a = 2 + (__int64)(rng() % nv);
            __int64 b = 2 + (__int64)(rng() % nv);
            if (rng() & 1) a = -a;
            if (rng() & 1) b = -b;
            L[c] = a; R[c] = b;
            in.add_clause(a, b);
        }

        const auto t0 = std::chrono::steady_clock::now();
        const nomgr::Result fast = nomgr::solve(in);
        const auto t1 = std::chrono::steady_clock::now();
        const double fast_ms = std::chrono::duration<double, std::milli>(t1 - t0).count();

        double slow_ms = -1.0;
        bool slow_sat = false;

        if (original_viable) {
            const __int64 n_parm = nv + 2;
            SATSolver s;
            s.n_parm = n_parm;
            s.k_parm = k;
            s.chops = 0;
            s.chop = 0;
            s.leading_trues = 0;
            bool* Z = new bool[n_parm + 2]();
            bool* isf = new bool[n_parm + 2]();
            bool* ist = new bool[n_parm + 2]();
            bool* sln = new bool[n_parm + 2]();
            s.Z = Z;
            s.is_f = isf;
            s.is_t = ist;
            s.lst_l_parm = L.data();
            s.lst_r_parm = R.data();

            const auto u0 = std::chrono::steady_clock::now();
            slow_sat = original_isSat(&s, sln);
            const auto u1 = std::chrono::steady_clock::now();
            slow_ms = std::chrono::duration<double, std::milli>(u1 - u0).count();

            delete[] Z;
            delete[] isf;
            delete[] ist;
            delete[] sln;

            if (slow_ms > 15000.0) original_viable = false;
        }

        if (slow_ms >= 0.0) {
            std::printf("  %4d  %7d | %10.2f ms | %7.3f ms | %8.0fx%s\n",
                        nv, k, slow_ms, fast_ms,
                        fast_ms > 0.0 ? slow_ms / fast_ms : 0.0,
                        (slow_sat == fast.satisfiable) ? "" : "   <-- ANSWERS DIFFER");
        } else {
            std::printf("  %4d  %7d |    (gave up)  | %7.3f ms |       --\n",
                        nv, k, fast_ms);
        }
        std::fflush(stdout);
    }

    std::printf("--------------------------------------------------------------\n\n");
    return 0;
}
