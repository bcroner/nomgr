import pathlib

# ---------------------------------------------------------------- header ----
h = pathlib.Path("NOMGR.hpp")
s = h.read_text(encoding="utf-8", errors="replace")

# Trade_Check used to carry raw SAT clause arrays. Those are now an internal
# detail of the solver, so it just names what is being checked.
old_tc_start = s.index("typedef struct Trade_Check_tag {")
old_tc_end = s.index("} Trade_Check;") + len("} Trade_Check;")
s = s[:old_tc_start] + """typedef struct Trade_Check_tag {

\t// What is being checked, and against what. The clause arrays that used to
\t// live here are now internal to the solver (see structural_check.hpp).
\tMarket* market;
\tVault* vault;
\t__int64 offer_id;

} Trade_Check;""" + s[old_tc_end:]
print("header: Trade_Check redefined")

# The old SATSolver struct is superseded by sat2.hpp.
sat_start = s.index("typedef struct SATSolver_tag {")
sat_end = s.index("} SATSolver;") + len("} SATSolver;")
s = s[:sat_start] + s[sat_end:]
print("header: SATSolver struct removed")

# Replace the trade-check and solver declarations.
decl_start = s.index("Trade_Check* create_trade_check(Market* market);")
decl_end = s.index("bool SATSolver_threads(bool* arr, bool* is_sat, __int64* lst_l_parm, __int64* lst_r_parm, __int64 k_parm, __int64 n_parm, bool* is_f, bool* is_t, __int64 chops, __int64 chop, __int64 leading_trues);")
decl_end += len("bool SATSolver_threads(bool* arr, bool* is_sat, __int64* lst_l_parm, __int64* lst_r_parm, __int64 k_parm, __int64 n_parm, bool* is_f, bool* is_t, __int64 chops, __int64 chop, __int64 leading_trues);")
s = s[:decl_start] + """Trade_Check* create_trade_check(Market* market, Vault* vault, __int64 offer_id);
bool check_trade(Trade_Check* trade_check);""" + s[decl_end:]
print("header: declarations replaced")

# create_offer took participant_exclude parameters that make_offer never passed.
s = s.replace("__int64* participant_exclude, __int64 participant_exclude_vtop, __int64 participant_exclude_vcap, ", "")
print("header: dropped unused participant_exclude parameters")

h.write_text(s, encoding="utf-8")

# ------------------------------------------------------------------- cpp ----
c = pathlib.Path("NOMGR.cpp")
t = c.read_text(encoding="utf-8", errors="replace")

t = t.replace('#include "NOMGR.hpp"', '#include "NOMGR.hpp"\n#include "triggerable.hpp"')
print("cpp: included triggerable.hpp")

t = t.replace("__int64* participant_exclude, __int64 participant_exclude_vtop, __int64 participant_exclude_vcap, ", "")

# Queue dequeue: the second check, now through the new API.
t = t.replace("""\tSATSolver* s = new SATSolver();
\ts->lst_l_parm = simp_vector_create(16);
\ts->lst_r_parm = simp_vector_create(16);
    s->lst_l_parm_vtop = -1;
\ts->lst_l_parm_vcap = 16;

\tbool is_sat = check_trade(s, ret->trade_check, true);

    if (is_sat)
        return ret;
    else
\t\treturn nullptr;
""",
"""\t// The second check. Offers queued earlier may already have taken the
\t// resources, so triggerability is re-tested before anything is dispersed.
\tif (check_trade(ret->data))
\t\treturn ret;

\treturn nullptr;
""")
print("cpp: dequeue re-check rewired")

# gives / receives are Voucher arrays.
t = t.replace("offer->gives = simp_vector_create(give_vtop+1);",
              "offer->gives = new Voucher[give_vtop + 1 > 0 ? give_vtop + 1 : 1]();")
t = t.replace("offer->receives = simp_vector_create(16);",
              "offer->receives = new Voucher[16]();")
print("cpp: gives/receives allocated as Voucher arrays")

# id_pool_retrieve passed the pointer by value where the callee wants its address.
t = t.replace("simp_vector_append(*id_pool, id_pool_vtop, id_pool_vcap, 0);",
              "simp_vector_append(&id_pool, id_pool_vtop, id_pool_vcap, 0);")
print("cpp: id_pool_retrieve append fixed")

# Bank stores account and holder IDs.
t = t.replace("Bank* create_bank(Market* market, Account* accounts, Participant** account_holders,",
              "Bank* create_bank(Market* market, __int64* accounts, __int64* account_holders,")
print("cpp: create_bank takes id arrays")

# Replace create_trade_check, check_trade and the whole old solver in one cut.
cut_start = t.index("Trade_Check* create_trade_check(Market* market) {")
cut_end = t.index("int main() {")

NEW = '''// ---------------------------------------------------------------------------
// Trade checking now lives in the tested modules:
//
//   structural_check.hpp  requires / bans / insurance     2-SAT, linear
//   vault_check.hpp       vault exhaustion                arithmetic, linear
//   triggerable.hpp       both halves, one call
//
// The SATSolver that used to live here searched assignments by backtracking,
// which is exponential; it did not finish 30 variables in nine minutes, while
// the replacement does 200,000 in 29 ms. See SOLVER_NOTES.md.
// ---------------------------------------------------------------------------

static void collect_refs(const __int64* ids, __int64 vtop, nomgr::Kind kind,
                         std::vector<nomgr::Ref>& out) {
    if (!ids) return;
    for (__int64 i = 0; i <= vtop; i++)
        out.push_back(nomgr::Ref{kind, ids[i]});
}

// Translate the market's require / ban / insurance lists into the form the
// structural check understands.
static nomgr::MarketState market_state_from(Market* market) {

    nomgr::MarketState st;
    if (!market) return st;

    for (__int64 i = 0; i <= market->participants_vtop; i++) {

        Participant* p = market->participants[i];
        if (!p) continue;

        nomgr::Conditions c;
        c.subject = nomgr::participant_ref(p->id);
        collect_refs(p->require, p->require_vtop, nomgr::Kind::Offer, c.requires_all);
        collect_refs(p->bans, p->bans_vtop, nomgr::Kind::Offer, c.bans);
        st.conditions.push_back(c);

        // A participant present in the market is in force.
        st.in_force.push_back(nomgr::participant_ref(p->id));
    }

    if (!market->barter_system) return st;

    for (__int64 i = 0; i <= market->barter_system->offers_vtop; i++) {

        Offer* o = market->barter_system->offers[i];
        if (!o) continue;

        nomgr::Conditions c;
        c.subject = nomgr::offer_ref(o->id);

        collect_refs(o->require, o->require_vtop,
                     nomgr::Kind::Offer, c.requires_all);
        collect_refs(o->bans, o->bans_vtop,
                     nomgr::Kind::Offer, c.bans);
        collect_refs(o->participants_require, o->participants_require_vtop,
                     nomgr::Kind::Participant, c.requires_all);
        collect_refs(o->participants_ban, o->participants_ban_vtop,
                     nomgr::Kind::Participant, c.bans);
        collect_refs(o->insurance_policies_required, o->insurance_policies_required_vtop,
                     nomgr::Kind::Policy, c.requires_all);

        st.conditions.push_back(c);

        // Policies this offer accepts count as available.
        collect_refs(o->insurance_policies_accepted, o->insurance_policies_accepted_vtop,
                     nomgr::Kind::Policy, st.in_force);
        collect_refs(o->insurance_policies_applied, o->insurance_policies_applied_vtop,
                     nomgr::Kind::Policy, st.in_force);
    }

    return st;
}

static std::vector<nomgr::Deposit> vault_deposits(Vault* vault) {

    std::vector<nomgr::Deposit> out;
    if (!vault || !vault->gold_deposits) return out;

    for (__int64 i = 0; i <= vault->gold_deposits_vtop; i++) {
        Gold_Deposit* d = vault->gold_deposits[i];
        if (d) out.push_back(nomgr::Deposit{d->id, d->gold_milligram_value});
    }
    return out;
}

Trade_Check* create_trade_check(Market* market, Vault* vault, __int64 offer_id) {

    Trade_Check* trade_check = new Trade_Check();

    trade_check->market = market;
    trade_check->vault = vault;
    trade_check->offer_id = offer_id;

    return trade_check;
}

// Called twice per offer: once when it is found triggerable and queued, and
// again on dequeue before anything is dispersed.
bool check_trade(Trade_Check* trade_check) {

    if (!trade_check || !trade_check->market || !trade_check->market->barter_system)
        return false;

    Market* market = trade_check->market;

    Offer* offer = nullptr;
    for (__int64 i = 0; i <= market->barter_system->offers_vtop; i++)
        if (market->barter_system->offers[i] &&
            market->barter_system->offers[i]->id == trade_check->offer_id) {
            offer = market->barter_system->offers[i];
            break;
        }

    if (!offer) return false;

    const nomgr::MarketState state = market_state_from(market);
    const std::vector<nomgr::Deposit> held = vault_deposits(trade_check->vault);

    std::vector<nomgr::GoldClaim> claims;
    claims.push_back(nomgr::GoldClaim{offer->id, offer->gives_gold_milligram_value});

    const nomgr::TriggerVerdict verdict =
        nomgr::is_triggerable(state, offer->id, held, claims);

    return verdict.triggerable;
}

'''

t = t[:cut_start] + NEW + t[cut_end:]
print("cpp: create_trade_check / check_trade replaced, old solver removed")

c.write_text(t, encoding="utf-8")
print("done")
