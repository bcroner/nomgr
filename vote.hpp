// vote.hpp -- tallying for bills, Article V conventions and rollbacks.
//
// Every vote structure in NOMGR.hpp carries two independent totals:
//
//     votes_for / votes_against                  heads
//     gold_milligram_value_for / _against        money
//
// which is the configurable balance of money and the will of the masses.
//
// HOW THE BLEND HAS TO WORK
//
// The two totals cannot simply be added together. Gold is counted in
// milligrams, so a single participant holding a kilogram contributes
// 1,000,000 while a voter contributes 1. Any weighted sum of the RAW totals
// is pure plutocracy no matter what weights are chosen -- the headcount term
// is lost in the rounding.
//
// So each side is first reduced to a share of its own kind:
//
//     head_share_for = heads_for / (heads_for + heads_against)
//     gold_share_for = gold_for  / (gold_for  + gold_against)
//
// and only then blended:
//
//     score_for = head_weight * head_share_for + gold_weight * gold_share_for
//
// Now the dial means what it says. head_weight = 1 is one person one vote;
// gold_weight = 1 is one milligram one vote; anything between is a genuine
// mixture rather than a rounding error.

#ifndef NOMGR_VOTE_HPP
#define NOMGR_VOTE_HPP

#include <cstdint>
#include <string>
#include <vector>

namespace nomgr {

using i64 = std::int64_t;

// Where the balance sits. The two weights are normalised, so {1,1} and
// {50,50} mean the same thing.
struct Weighting {
    double head_weight = 0.5;
    double gold_weight = 0.5;

    static Weighting one_person_one_vote() { return {1.0, 0.0}; }
    static Weighting one_milligram_one_vote() { return {0.0, 1.0}; }
    static Weighting even() { return {0.5, 0.5}; }
};

// Raw totals for one question.
struct Ballot {
    i64 heads_for = 0;
    i64 heads_against = 0;
    i64 gold_for = 0;          // milligrams behind the "for" side
    i64 gold_against = 0;
};

struct Tally {
    double head_share_for = 0.0;   // 0.5 when nobody voted
    double gold_share_for = 0.5;
    double score_for = 0.0;        // the blended share, in [0,1]
    i64 heads_total = 0;
    i64 gold_total = 0;
    bool anyone_voted = false;
};

Tally tally(const Ballot& b, const Weighting& w);

// Thresholds are shares of the blended score, not of the headcount.
//   0.50  simple majority
//   0.667 two thirds, as Article V requires to propose
//   0.75  three quarters, as Article V requires to ratify
struct Threshold {
    double share = 0.5;
    i64 minimum_heads = 0;     // quorum: a vote nobody attended passes nothing
};

struct Outcome {
    bool passed = false;
    Tally tally;
    std::string reason;
};

Outcome decide(const Ballot& b, const Weighting& w, const Threshold& t);

// --- what a passing vote does ------------------------------------------

enum class CodeKind : int { Civil = 0, Penal = 1 };

struct LawRecord {
    i64 id = 0;
    std::string title;
    CodeKind classification = CodeKind::Civil;
    i64 valid_start = 0;
    i64 valid_end = 0;         // 0 means "still in force"
};

struct BillRecord {
    i64 id = 0;
    std::string title;
    CodeKind classification = CodeKind::Civil;
    bool repeal = false;       // repeals target_law_id instead of adding
    i64 target_law_id = 0;
    Ballot ballot;
};

// Apply a bill to a body of law, if it passes. Returns the outcome; `code` is
// modified in place only on passage.
Outcome enact(const BillRecord& bill, std::vector<LawRecord>& code,
              const Weighting& w, const Threshold& t,
              i64 now, i64& next_law_id);

// --- Article V ----------------------------------------------------------

struct ConventionOption {
    i64 id = 0;
    std::string title;
    Ballot ballot;
};

struct ConventionResult {
    bool convention_called = false;   // did the convention itself clear its bar
    bool any_option_passed = false;
    i64 winning_option_id = 0;
    Outcome convention_outcome;
    std::vector<Outcome> option_outcomes;
};

// A convention has to clear its own threshold before any of its options count,
// mirroring Article V: two thirds to call it, three quarters to ratify.
ConventionResult hold_convention(const Ballot& convention_ballot,
                                 const std::vector<ConventionOption>& options,
                                 const Weighting& w,
                                 const Threshold& to_call,
                                 const Threshold& to_ratify);

}  // namespace nomgr

#endif
