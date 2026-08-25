// sat2.hpp -- linear-time 2-SAT for NOMGR trade checking.
//
// The original solver in NOMGR.cpp builds an implication graph and then
// searches assignments through it with a backtracking binary counter. That is
// exponential in the worst case: O(2^n).
//
// 2-SAT does not need search. Aspvall, Plass and Tarjan (1979) showed that a
// 2-CNF formula is satisfiable if and only if no variable lies in the same
// strongly connected component as its own negation, which is decidable in
// O(n + k) -- linear in the number of variables plus clauses.
//
// Threading a linear algorithm across cores is usually a loss. The parallelism
// that pays here is across INDEPENDENT trade checks, which is what
// solve_batch does.
//
// Literal convention, kept compatible with the original code:
//   * variables are numbered from 2 upward; 1 and -1 are reserved sentinels
//   * a positive value v means "variable v is true"
//   * a negative value -v means "variable v is false"
//   * a clause with either side equal to FALSE_2SAT (-1) is skipped

#ifndef NOMGR_SAT2_HPP
#define NOMGR_SAT2_HPP

#include <cstdint>
#include <vector>

namespace nomgr {

using i64 = std::int64_t;

constexpr i64 kTrue2Sat = 1;
constexpr i64 kFalse2Sat = -1;

// One 2-CNF instance: clauses (l | r), plus optionally forced literals.
struct Instance {
    i64 n = 0;                       // one past the highest variable index
    std::vector<i64> lst_l;          // left literal of each clause
    std::vector<i64> lst_r;          // right literal of each clause
    std::vector<char> forced_true;   // size n; forced_true[v] pins v to true
    std::vector<char> forced_false;  // size n; forced_false[v] pins v to false

    void add_clause(i64 l, i64 r) { lst_l.push_back(l); lst_r.push_back(r); }
};

struct Result {
    bool satisfiable = false;
    // assignment[v] is meaningful only when satisfiable; index by variable.
    std::vector<char> assignment;
};

// Decide one instance. O(n + k) time and memory.
Result solve(const Instance& inst);

// Decide many independent instances in parallel.
//
// threads == 0 asks for hardware_concurrency(). Instances are handed out from
// a shared atomic counter rather than pre-sliced, so one slow instance cannot
// leave a core idle while another thread still has a queue.
std::vector<Result> solve_batch(const std::vector<Instance>& instances,
                                unsigned threads = 0);

// Reference implementation: exhaustive over 2^v assignments. Only for testing
// the fast path against something obviously correct on small inputs.
Result solve_bruteforce(const Instance& inst);

}  // namespace nomgr

#endif
