#include "sat2.hpp"

#include <algorithm>
#include <atomic>
#include <thread>

namespace nomgr {
namespace {

// Internal literal encoding: variable v in [0, n) maps to
//   2v     "v is true"
//   2v + 1 "v is false"
inline std::size_t lit_true(i64 v) { return static_cast<std::size_t>(2 * v); }
inline std::size_t lit_false(i64 v) { return static_cast<std::size_t>(2 * v + 1); }
inline std::size_t negate_lit(std::size_t l) { return l ^ 1u; }

// Signed external literal -> internal index.
inline std::size_t encode(i64 signed_lit) {
    return signed_lit > 0 ? lit_true(signed_lit) : lit_false(-signed_lit);
}

// Compressed-sparse-row implication graph.
struct Graph {
    std::vector<std::size_t> head;   // size V + 1
    std::vector<std::size_t> edges;
};

Graph build(const Instance& inst, std::size_t V) {
    std::vector<std::size_t> degree(V, 0);

    auto count = [&](std::size_t from) { ++degree[from]; };

    const std::size_t k = std::min(inst.lst_l.size(), inst.lst_r.size());
    for (std::size_t i = 0; i < k; ++i) {
        const i64 a = inst.lst_l[i];
        const i64 b = inst.lst_r[i];
        if (a == kFalse2Sat || b == kFalse2Sat) continue;
        if (a == 0 || b == 0) continue;
        // (a | b) becomes  ~a -> b  and  ~b -> a
        count(negate_lit(encode(a)));
        count(negate_lit(encode(b)));
    }
    // A forced literal is the unit clause (x), i.e. (x | x): ~x -> x.
    for (i64 v = 0; v < inst.n; ++v) {
        if (v < static_cast<i64>(inst.forced_true.size()) && inst.forced_true[v])
            count(lit_false(v));
        if (v < static_cast<i64>(inst.forced_false.size()) && inst.forced_false[v])
            count(lit_true(v));
    }

    Graph g;
    g.head.assign(V + 1, 0);
    for (std::size_t i = 0; i < V; ++i) g.head[i + 1] = g.head[i] + degree[i];
    g.edges.resize(g.head[V]);

    std::vector<std::size_t> cursor(g.head.begin(), g.head.end() - 1);
    auto add = [&](std::size_t from, std::size_t to) { g.edges[cursor[from]++] = to; };

    for (std::size_t i = 0; i < k; ++i) {
        const i64 a = inst.lst_l[i];
        const i64 b = inst.lst_r[i];
        if (a == kFalse2Sat || b == kFalse2Sat) continue;
        if (a == 0 || b == 0) continue;
        const std::size_t la = encode(a), lb = encode(b);
        add(negate_lit(la), lb);
        add(negate_lit(lb), la);
    }
    for (i64 v = 0; v < inst.n; ++v) {
        if (v < static_cast<i64>(inst.forced_true.size()) && inst.forced_true[v])
            add(lit_false(v), lit_true(v));
        if (v < static_cast<i64>(inst.forced_false.size()) && inst.forced_false[v])
            add(lit_true(v), lit_false(v));
    }
    return g;
}

// Tarjan's SCC, written iteratively. A recursive version blows the stack once
// the implication graph gets deep, which on a real market it will.
std::vector<i64> scc(const Graph& g, std::size_t V) {
    std::vector<i64> index(V, -1), low(V, 0), comp(V, -1);
    std::vector<char> on_stack(V, 0);
    std::vector<std::size_t> stk;
    stk.reserve(V);

    i64 next_index = 0, next_comp = 0;

    // Explicit call stack: (vertex, position within its edge range)
    std::vector<std::pair<std::size_t, std::size_t>> call;

    for (std::size_t root = 0; root < V; ++root) {
        if (index[root] != -1) continue;
        call.push_back({root, g.head[root]});
        index[root] = low[root] = next_index++;
        stk.push_back(root);
        on_stack[root] = 1;

        while (!call.empty()) {
            auto& [v, ei] = call.back();
            if (ei < g.head[v + 1]) {
                const std::size_t w = g.edges[ei++];
                if (index[w] == -1) {
                    index[w] = low[w] = next_index++;
                    stk.push_back(w);
                    on_stack[w] = 1;
                    call.push_back({w, g.head[w]});
                } else if (on_stack[w]) {
                    low[v] = std::min(low[v], index[w]);
                }
            } else {
                if (low[v] == index[v]) {
                    while (true) {
                        const std::size_t w = stk.back();
                        stk.pop_back();
                        on_stack[w] = 0;
                        comp[w] = next_comp;
                        if (w == v) break;
                    }
                    ++next_comp;
                }
                const std::size_t finished = v;
                call.pop_back();
                if (!call.empty()) {
                    auto& parent = call.back().first;
                    low[parent] = std::min(low[parent], low[finished]);
                }
            }
        }
    }
    return comp;
}

}  // namespace

Result solve(const Instance& inst) {
    Result out;
    if (inst.n <= 0) {
        out.satisfiable = true;
        return out;
    }
    const std::size_t V = static_cast<std::size_t>(2 * inst.n);
    const Graph g = build(inst, V);
    const std::vector<i64> comp = scc(g, V);

    out.assignment.assign(static_cast<std::size_t>(inst.n), 0);
    for (i64 v = 0; v < inst.n; ++v) {
        const i64 ct = comp[lit_true(v)];
        const i64 cf = comp[lit_false(v)];
        if (ct == cf) {            // v and ~v mutually implied: contradiction
            out.satisfiable = false;
            out.assignment.clear();
            return out;
        }
        // Tarjan numbers components in reverse topological order, so the
        // literal with the SMALLER component index comes LATER in topological
        // order and is the one to satisfy.
        out.assignment[static_cast<std::size_t>(v)] = (ct < cf) ? 1 : 0;
    }
    out.satisfiable = true;
    return out;
}

std::vector<Result> solve_batch(const std::vector<Instance>& instances,
                                unsigned threads) {
    std::vector<Result> out(instances.size());
    if (instances.empty()) return out;

    unsigned n_threads = threads ? threads : std::thread::hardware_concurrency();
    if (n_threads == 0) n_threads = 1;
    n_threads = std::min<unsigned>(n_threads,
                                   static_cast<unsigned>(instances.size()));

    std::atomic<std::size_t> next{0};
    auto worker = [&]() {
        for (;;) {
            const std::size_t i = next.fetch_add(1, std::memory_order_relaxed);
            if (i >= instances.size()) return;
            out[i] = solve(instances[i]);   // distinct index per worker: no lock needed
        }
    };

    if (n_threads == 1) {
        worker();
        return out;
    }

    std::vector<std::thread> pool;
    pool.reserve(n_threads);
    for (unsigned t = 0; t < n_threads; ++t) pool.emplace_back(worker);
    for (auto& th : pool) th.join();
    return out;
}

Result solve_bruteforce(const Instance& inst) {
    Result out;
    if (inst.n <= 0) { out.satisfiable = true; return out; }
    if (inst.n > 22) return out;            // refuse to be silly

    const std::size_t nv = static_cast<std::size_t>(inst.n);
    const std::size_t k = std::min(inst.lst_l.size(), inst.lst_r.size());

    for (std::uint64_t mask = 0; mask < (1ull << nv); ++mask) {
        std::vector<char> a(nv, 0);
        for (std::size_t v = 0; v < nv; ++v) a[v] = (mask >> v) & 1u;

        bool ok = true;
        for (i64 v = 0; ok && v < inst.n; ++v) {
            const std::size_t uv = static_cast<std::size_t>(v);
            if (uv < inst.forced_true.size() && inst.forced_true[uv] && !a[uv]) ok = false;
            if (uv < inst.forced_false.size() && inst.forced_false[uv] && a[uv]) ok = false;
        }
        for (std::size_t i = 0; ok && i < k; ++i) {
            const i64 x = inst.lst_l[i], y = inst.lst_r[i];
            if (x == kFalse2Sat || y == kFalse2Sat) continue;
            if (x == 0 || y == 0) continue;
            const bool lx = x > 0 ? a[static_cast<std::size_t>(x)]
                                  : !a[static_cast<std::size_t>(-x)];
            const bool ly = y > 0 ? a[static_cast<std::size_t>(y)]
                                  : !a[static_cast<std::size_t>(-y)];
            if (!lx && !ly) ok = false;
        }
        if (ok) { out.satisfiable = true; out.assignment = a; return out; }
    }
    return out;
}

}  // namespace nomgr
