// market_test.cpp -- exercise the wired market layer.
//
// NOMGR.cpp has an empty main(), so nothing here was ever run. This drives the
// pieces that were wired to the new trade check.

#include "NOMGR.hpp"
#include "triggerable.hpp"

#include <cstdio>
#include <string>

static int passed = 0, failed = 0;
static void check(const std::string& l, bool c) {
    if (c) { ++passed; std::printf("  PASS  %s\n", l.c_str()); }
    else { ++failed; std::printf("  FAIL  %s\n", l.c_str()); }
}

int main() {
    std::printf("\nMARKET LAYER\n--------------------------------------------------------\n");

    Market* market = create_market();
    check("market is created", market != nullptr);
    check("market has a barter system", market && market->barter_system != nullptr);
    check("market has an id pool", market && market->id_pool != nullptr);

    Participant* a = create_participant(market);
    Participant* b = create_participant(market);
    check("participants are created", a && b);
    check("participants get distinct ids", a && b && a->id != b->id);

    // Register them so the market can see them.
    simp_participant_vector_append(&(market->participants),
                                   &(market->participants_vtop),
                                   &(market->participants_vcap), a);
    simp_participant_vector_append(&(market->participants),
                                   &(market->participants_vtop),
                                   &(market->participants_vcap), b);
    check("participants are registered", market->participants_vtop == 2);  // create_market adds the state participant

    // --- the add/remove round trip that was broken -----------------------
    create_require_participant(market, a->id, 4242);
    check("require is added", a->require_vtop == 0 && a->require[0] == 4242);

    create_require_participant(market, a->id, 4242);
    check("adding the same require twice is a no-op", a->require_vtop == 0);

    remove_require_participant(market, a->id, 4242);
    check("require is actually removed", a->require_vtop == -1);

    // Removing something absent must do nothing -- this used to walk off the
    // front of the array and decrement the count.
    const __int64 before = a->require_vtop;
    remove_require_participant(market, a->id, 999999);
    check("removing an absent require leaves the count alone",
          a->require_vtop == before);

    create_ban_participant(market, b->id, 77);
    check("ban is added", b->bans_vtop == 0 && b->bans[0] == 77);
    remove_ban_participant(market, b->id, 77);
    check("ban is actually removed", b->bans_vtop == -1);
    const __int64 bbefore = b->bans_vtop;
    remove_ban_participant(market, b->id, 555);
    check("removing an absent ban leaves the count alone", b->bans_vtop == bbefore);

    // --- the trade check, through the market ------------------------------
    Vault* vault = new Vault();
    vault->gold_deposits = simp_gold_deposit_vector_create(4);
    vault->gold_deposits_vtop = -1;
    vault->gold_deposits_vcap = 4;
    Gold_Deposit* d = new Gold_Deposit();
    d->id = 1;
    d->gold_milligram_value = 1000;
    simp_gold_deposit_vector_append(&(vault->gold_deposits),
                                    &(vault->gold_deposits_vtop),
                                    &(vault->gold_deposits_vcap), d);
    check("vault holds one 1000 mg deposit", vault->gold_deposits_vtop == 0);

    Offer* offer = new Offer();
    offer->id = 500;
    offer->gives_gold_milligram_value = 400;
    offer->require = simp_vector_create(4);  offer->require_vtop = -1; offer->require_vcap = 4;
    offer->bans = simp_vector_create(4);     offer->bans_vtop = -1;    offer->bans_vcap = 4;
    offer->participants_require = simp_vector_create(4);
    offer->participants_require_vtop = -1;   offer->participants_require_vcap = 4;
    offer->participants_ban = simp_vector_create(4);
    offer->participants_ban_vtop = -1;       offer->participants_ban_vcap = 4;
    offer->insurance_policies_required = simp_vector_create(4);
    offer->insurance_policies_required_vtop = -1;
    offer->insurance_policies_required_vcap = 4;
    offer->insurance_policies_accepted = simp_vector_create(4);
    offer->insurance_policies_accepted_vtop = -1;
    offer->insurance_policies_accepted_vcap = 4;
    offer->insurance_policies_applied = simp_vector_create(4);
    offer->insurance_policies_applied_vtop = -1;
    offer->insurance_policies_applied_vcap = 4;
    simp_offer_vector_append(&(market->barter_system->offers),
                             &(market->barter_system->offers_vtop),
                             &(market->barter_system->offers_vcap), offer);

    Trade_Check* tc = create_trade_check(market, vault, offer->id);
    check("trade check is created", tc && tc->offer_id == 500);
    check("offer wanting 400 of 1000 mg is triggerable", check_trade(tc));

    // Now ask for more gold than the vault holds.
    offer->gives_gold_milligram_value = 5000;
    check("offer wanting 5000 of 1000 mg is refused", !check_trade(tc));

    // Back within budget. An offer that both REQUIRES and BANS the same
    // participant is self-contradictory and must be refused. (Banning someone
    // who is not party to the trade is vacuous, and correctly allowed -- a ban
    // stops a trade, it does not expel a person from the market.)
    offer->gives_gold_milligram_value = 400;
    offer->participants_require = simp_vector_create(4);
    offer->participants_require_vtop = -1;
    offer->participants_require_vcap = 4;
    simp_vector_append(&(offer->participants_require), &(offer->participants_require_vtop),
                       &(offer->participants_require_vcap), b->id);
    check("offer requiring b alone is fine", check_trade(tc));

    simp_vector_append(&(offer->participants_ban), &(offer->participants_ban_vtop),
                       &(offer->participants_ban_vcap), b->id);
    check("offer both requiring and banning b is refused", !check_trade(tc));

    // Remove the ban and it should clear again -- this only works because the
    // remove functions were fixed.
    offer->participants_ban_vtop = -1;
    check("clearing the ban makes it triggerable again", check_trade(tc));

    // Unknown offer id.
    // --- an offer inherits the standing of whoever posted it --------------
    //
    // An offer is made BY participants, so it carries their standing. If a
    // counterparty boycotts one of them, the trade cannot clear. A boycott by
    // someone NOT party to the trade must not block it -- a boycott means "I
    // will not trade with you", not "you are expelled from the market".
    {
        Offer* o2 = new Offer();
        o2->id = 600;
        o2->gives_gold_milligram_value = 100;
        o2->require = simp_vector_create(4);  o2->require_vtop = -1; o2->require_vcap = 4;
        o2->bans = simp_vector_create(4);     o2->bans_vtop = -1;    o2->bans_vcap = 4;
        o2->participants_require = simp_vector_create(4);
        o2->participants_require_vtop = -1;   o2->participants_require_vcap = 4;
        o2->participants_ban = simp_vector_create(4);
        o2->participants_ban_vtop = -1;       o2->participants_ban_vcap = 4;
        o2->insurance_policies_required = simp_vector_create(4);
        o2->insurance_policies_required_vtop = -1;
        o2->insurance_policies_required_vcap = 4;
        o2->insurance_policies_accepted = simp_vector_create(4);
        o2->insurance_policies_accepted_vtop = -1;
        o2->insurance_policies_accepted_vcap = 4;
        o2->insurance_policies_applied = simp_vector_create(4);
        o2->insurance_policies_applied_vtop = -1;
        o2->insurance_policies_applied_vcap = 4;
        o2->participants_offering = simp_vector_create(4);
        o2->participants_offering_vtop = -1;  o2->participants_offering_vcap = 4;

        // a posts the offer; b is required as a counterparty
        simp_vector_append(&(o2->participants_offering),
                           &(o2->participants_offering_vtop),
                           &(o2->participants_offering_vcap), a->id);
        simp_vector_append(&(o2->participants_require),
                           &(o2->participants_require_vtop),
                           &(o2->participants_require_vcap), b->id);

        simp_offer_vector_append(&(market->barter_system->offers),
                                 &(market->barter_system->offers_vtop),
                                 &(market->barter_system->offers_vcap), o2);

        Trade_Check* tc2 = create_trade_check(market, vault, o2->id);
        check("an offer from an unencumbered participant triggers", check_trade(tc2));

        create_ban_participant(market, b->id, a->id);
        check("the boycott is recorded", b->bans_vtop == 0 && b->bans[0] == a->id);
        check("a's offer is refused while counterparty b boycotts a", !check_trade(tc2));

        remove_ban_participant(market, b->id, a->id);
        check("a's offer clears once the boycott is lifted", check_trade(tc2));

        Participant* c3 = create_participant(market);
        simp_participant_vector_append(&(market->participants),
                                       &(market->participants_vtop),
                                       &(market->participants_vcap), c3);
        create_ban_participant(market, c3->id, a->id);
        check("a boycott by a non-party does not block the trade", check_trade(tc2));
    }

    Trade_Check* bad = create_trade_check(market, vault, 99999);
    check("a trade check for an unknown offer is refused", !check_trade(bad));

    std::printf("--------------------------------------------------------\n");
    std::printf("  %d passed, %d failed\n\n", passed, failed);
    return failed ? 1 : 0;
}
