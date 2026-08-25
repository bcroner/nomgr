// NOMGR.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#ifndef __NOMGR_C__
#define __NOMGR_C__

#include "NOMGR.hpp"
#include "triggerable.hpp"

#include <iostream>
#include <set>
#include <future>
#include <list>
#include <random>
#include <stdio.h>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <vector>
#include <functional>

Article_V_Option** simp_article_v_option_vector_create(__int64 init_sz) {

    Article_V_Option** ret = new Article_V_Option*[init_sz];
    return ret;

}

Article_V_Option* simp_article_v_option_vector_read(Article_V_Option** v, __int64 vtop, __int64 vcap, __int64 loc) {

    if (loc > vtop)
        return 0;

    return v[loc];
}

void simp_article_v_option_vector_append(Article_V_Option*** v, __int64* vtop, __int64* vcap, Article_V_Option* data) {

    *vtop = *vtop + 1;

    if (*vtop < *vcap)
        (*v)[*vtop] = data;
    else {
        Article_V_Option** newv = new Article_V_Option * [*vcap * 2];
        for (__int64 i = 0; i < *vcap * 2; i++)
            newv[i] = 0;
        for (__int64 i = 0; i < *vcap; i++)
            newv[i] = (*v)[i];
        *vcap = *vcap * 2;
        delete[](*v);
        *v = newv;
        (*v)[*vtop] = data;
    }

}

Voucher** simp_voucher_vector_create(__int64 init_sz) {

    Voucher** ret = new Voucher * [init_sz];
    return ret;

}

Voucher* simp_voucher_vector_read(Voucher** v, __int64 vtop, __int64 vcap, __int64 loc) {

    if (loc > vtop)
        return 0;

    return v[loc];
}

void simp_voucher_vector_append(Voucher*** v, __int64* vtop, __int64* vcap, Voucher* data) {

    *vtop = *vtop + 1;

    if (*vtop < *vcap)
        (*v)[*vtop] = data;
    else {
        Voucher** newv = new Voucher * [*vcap * 2];
        for (__int64 i = 0; i < *vcap * 2; i++)
            newv[i] = 0;
        for (__int64 i = 0; i < *vcap; i++)
            newv[i] = (*v)[i];
        *vcap = *vcap * 2;
        delete[](*v);
        *v = newv;
        (*v)[*vtop] = data;
    }

}

Account** simp_account_vector_create(__int64 init_sz) {

    Account** ret = new Account * [init_sz];
    return ret;

}

Account* simp_account_vector_read(Account** v, __int64 vtop, __int64 vcap, __int64 loc) {

    if (loc > vtop)
        return 0;

    return v[loc];
}

void simp_account_vector_append(Account*** v, __int64* vtop, __int64* vcap, Account* data) {

    *vtop = *vtop + 1;

    if (*vtop < *vcap)
        (*v)[*vtop] = data;
    else {
        Account** newv = new Account * [*vcap * 2];
        for (__int64 i = 0; i < *vcap * 2; i++)
            newv[i] = 0;
        for (__int64 i = 0; i < *vcap; i++)
            newv[i] = (*v)[i];
        *vcap = *vcap * 2;
        delete[](*v);
        *v = newv;
        (*v)[*vtop] = data;
    }

}

Bank** simp_bank_vector_create(__int64 init_sz) {

    Bank** ret = new Bank*[init_sz];
    return ret;

}

Bank* simp_bank_vector_read(Bank** v, __int64 vtop, __int64 vcap, __int64 loc) {

    if (loc > vtop)
        return 0;

    return v[loc];
}

void simp_bank_vector_append(Bank*** v, __int64* vtop, __int64* vcap, Bank* data) {

    *vtop = *vtop + 1;

    if (*vtop < *vcap)
        (*v)[*vtop] = data;
    else {
        Bank** newv = new Bank*[*vcap * 2];
        for (__int64 i = 0; i < *vcap * 2; i++)
            newv[i] = 0;
        for (__int64 i = 0; i < *vcap; i++)
            newv[i] = (*v)[i];
        *vcap = *vcap * 2;
        delete[](*v);
        *v = newv;
        (*v)[*vtop] = data;
    }

}

Offer** simp_offer_vector_create(__int64 init_sz) {

    Offer** ret = new Offer*[init_sz];
    return ret;

}

Offer* simp_offer_vector_read(Offer** v, __int64 vtop, __int64 vcap, __int64 loc) {

    if (loc > vtop)
        return 0;

    return v[loc];
}

void simp_offer_vector_append(Offer*** v, __int64* vtop, __int64* vcap, Offer* data) {

    *vtop = *vtop + 1;

    if (*vtop < *vcap)
        (*v)[*vtop] = data;
    else {
        Offer** newv = new Offer * [*vcap * 2];
        for (__int64 i = 0; i < *vcap * 2; i++)
            newv[i] = 0;
        for (__int64 i = 0; i < *vcap; i++)
            newv[i] = (*v)[i];
        *vcap = *vcap * 2;
        delete[](*v);
        *v = newv;
        (*v)[*vtop] = data;
    }

}


Bill** simp_bill_vector_create(__int64 init_sz) {

    Bill** ret = new Bill*[init_sz];
    return ret;

}

Bill* simp_bill_vector_read(Bill** v, __int64 vtop, __int64 vcap, __int64 loc) {

    if (loc > vtop)
        return 0;

    return v[loc];
}

void simp_bill_vector_append(Bill*** v, __int64* vtop, __int64* vcap, Bill* data) {

    *vtop = *vtop + 1;

    if (*vtop < *vcap)
        (*v)[*vtop] = data;
    else {
        Bill** newv = new Bill* [*vcap * 2];
        for (__int64 i = 0; i < *vcap * 2; i++)
            newv[i] = 0;
        for (__int64 i = 0; i < *vcap; i++)
            newv[i] = (*v)[i];
        *vcap = *vcap * 2;
        delete[](*v);
        *v = newv;
        (*v)[*vtop] = data;
    }

}

Law** simp_law_vector_create(__int64 init_sz) {

    Law** ret = new Law*[init_sz];
    return ret;

}

Law* simp_law_vector_read(Law** v, __int64 vtop, __int64 vcap, __int64 loc) {

    if (loc > vtop)
        return 0;

    return v[loc];
}

void simp_law_vector_append(Law*** v, __int64* vtop, __int64* vcap, Law* data) {

    *vtop = *vtop + 1;

    if (*vtop < *vcap)
        (*v)[*vtop] = data;
    else {
        Law** newv = new Law * [*vcap * 2];
        for (__int64 i = 0; i < *vcap * 2; i++)
            newv[i] = 0;
        for (__int64 i = 0; i < *vcap; i++)
            newv[i] = (*v)[i];
        *vcap = *vcap * 2;
        delete[](*v);
        *v = newv;
        (*v)[*vtop] = data;
    }

}

Participant** simp_participant_vector_create(__int64 init_sz) {

    Participant** ret = new Participant* [init_sz];
    return ret;

}

Participant* simp_participant_vector_read(Participant** v, __int64 vtop, __int64 vcap, __int64 loc) {

    if (loc > vtop)
        return 0;

    return v[loc];
}

void simp_participant_vector_append(Participant*** v, __int64* vtop, __int64* vcap, Participant* data) {

    *vtop = *vtop + 1;

    if (*vtop < *vcap)
        (*v)[*vtop] = data;
    else {
        Participant** newv = new Participant * [*vcap * 2];
        for (__int64 i = 0; i < *vcap * 2; i++)
            newv[i] = 0;
        for (__int64 i = 0; i < *vcap; i++)
            newv[i] = (*v)[i];
        *vcap = *vcap * 2;
        delete[](*v);
        *v = newv;
        (*v)[*vtop] = data;
    }
}

Gold_Deposit** simp_gold_deposit_vector_create(__int64 init_sz) {

    Gold_Deposit** ret = new Gold_Deposit * [init_sz];
    return ret;

}

Gold_Deposit* simp_gold_deposit_vector_read(Gold_Deposit** v, __int64 vtop, __int64 vcap, __int64 loc) {

    if (loc > vtop)
        return 0;

    return v[loc];
}

void simp_gold_deposit_vector_append(Gold_Deposit*** v, __int64* vtop, __int64* vcap, Gold_Deposit* data) {

    *vtop = *vtop + 1;

    if (*vtop < *vcap)
        (*v)[*vtop] = data;
    else {
        Gold_Deposit** newv = new Gold_Deposit * [*vcap * 2];
        for (__int64 i = 0; i < *vcap * 2; i++)
            newv[i] = 0;
        for (__int64 i = 0; i < *vcap; i++)
            newv[i] = (*v)[i];
        *vcap = *vcap * 2;
        delete[](*v);
        *v = newv;
        (*v)[*vtop] = data;
    }
}

char* simp_char_vector_create(__int64 init_sz) {

    char* ret = new char[init_sz];
    return ret;

}

char simp_char_vector_read(char* v, __int64 vtop, __int64 vcap, __int64 loc) {

    if (loc > vtop)
        return 0;

    return v[loc];
}

void simp_char_vector_append(char** v, __int64* vtop, __int64* vcap, char data) {

    *vtop = *vtop + 1;

    if (*vtop < *vcap)
        (*v)[*vtop] = data;
    else {
        char* newv = new char[*vcap * 2];
        for (__int64 i = 0; i < *vcap * 2; i++)
            newv[i] = 0;
        for (__int64 i = 0; i < *vcap; i++)
            newv[i] = (*v)[i];
        *vcap = *vcap * 2;
        delete[](*v);
        *v = newv;
        (*v)[*vtop] = data;
    }

}

__int64* simp_vector_create(__int64 init_sz) {

    __int64* ret = new __int64[init_sz];
    return ret;

}

__int64 simp_vector_read(__int64* v, __int64 vtop, __int64 vcap, __int64 loc) {

    if (loc > vtop)
        return 0;

    return v[loc];
}

void simp_vector_append(__int64** v, __int64* vtop, __int64* vcap, __int64 data) {

    *vtop = *vtop + 1;

    if (*vtop < *vcap)
        (*v)[*vtop] = data;
    else {
        __int64* newv = new __int64[*vcap * 2];
        for (__int64 i = 0; i < *vcap * 2; i++)
            newv[i] = 0;
        for (__int64 i = 0; i < *vcap; i++)
            newv[i] = (*v)[i];
        *vcap = *vcap * 2;
        delete[](*v);
        *v = newv;
        (*v)[*vtop] = data;
    }

}

std::atomic_flag lock_flag = ATOMIC_FLAG_INIT;


void simp_queue_enqueue(Simp_Queue* queue, Simp_Queue* parm) {
	Simp_Queue* temp = queue->next;
	queue->next = parm;
	parm->next = temp;
}

Simp_Queue * simp_queue_dequeue(Simp_Queue* queue) {

	Simp_Queue* prev = queue;
    Simp_Queue* ret = queue->next;

    if (ret == nullptr)
		return nullptr;

    while (ret->next != nullptr){
		prev = prev->next;
        ret = ret->next;
	}

	prev->next = nullptr;

	// The second check. Offers queued earlier may already have taken the
	// resources, so triggerability is re-tested before anything is dispersed.
	if (check_trade(ret->data))
		return ret;

	return nullptr;

}

void make_offer(Market* market, __int64 participant_id, __int64* participants_offering, __int64 participants_offering_vtop, __int64 participants_offering_vcap, Voucher* give, __int64 give_vtop, __int64 give_vcap, __int64* give_voucher_counts, __int64 give_voucher_counts_vtop, __int64 give_voucher_counts_vcap, Voucher* receive, __int64 receive_vtop, __int64 receive_vcap, __int64* receive_voucher_counts, __int64 receive_voucher_counts_vtop, __int64 receive_voucher_counts_vcap,
    __int64 valid_start, __int64 valid_end, __int64 subscription_interval, __int64 interval_type, __int64 intervals,
    __int64* insurance_policies_accepted, __int64 insurance_policies_accepted_vtop, __int64 insurance_policies_accepted_vcap, __int64* insurance_policies_applied, __int64 insurance_policies_applied_vtop, __int64 insurance_policies_applied_vcap,
    __int64* participants_require, __int64 participants_require_vtop, __int64 participants_require_vcap, __int64* participants_ban, __int64 participants_ban_vtop, __int64 participants_ban_vcap,
    __int64* require, __int64 require_vtop, __int64 require_vcap, __int64* bans, __int64 bans_vtop, __int64 bans_vcap) {

	Offer* offer = create_offer(market, participants_offering, participants_offering_vtop, participants_offering_vcap, give, give_vtop, give_vcap, give_voucher_counts, give_voucher_counts_vtop, give_voucher_counts_vcap, receive, receive_vtop, receive_vcap, receive_voucher_counts, receive_voucher_counts_vtop, receive_voucher_counts_vcap,
        valid_start, valid_end, subscription_interval, interval_type, intervals,
        insurance_policies_accepted, insurance_policies_accepted_vtop, insurance_policies_accepted_vcap, insurance_policies_applied, insurance_policies_applied_vtop, insurance_policies_applied_vcap,
        participants_require, participants_require_vtop, participants_require_vcap, participants_ban, participants_ban_vtop, participants_ban_vcap,
        require, require_vtop, require_vcap, bans, bans_vtop, bans_vcap);

	__int64 participant_ix = 0;
	for (__int64 i = 0; i <= market->participants_vtop; i++) {
		if (market->participants[i]->id == participant_id) {
			participant_ix = i;
			break;
		}
	}
	simp_offer_vector_append(&(market->barter_system->offers), &(market->barter_system->offers_vtop), &(market->barter_system->offers_vcap), offer);
}

void create_require_participant(Market* market, __int64 participant_id, __int64 itm) {

    __int64 participant_ix = 0;

	for (__int64 i = 0; i <= market->participants_vtop; i++) {
		if (market->participants[i]->id == participant_id) {
			participant_ix = i;
			break;
		}
	}

	__int64 require_ix = -1;

	for (__int64 i = 0; i <= market->participants[participant_ix]->require_vtop + 1; i++) {
		if (market->participants[participant_ix]->require[i] == itm) {
			require_ix = i;
			break;
		}
	}

    if (require_ix > -1)
        return;

	simp_vector_append(&(market->participants[participant_ix]->require), &(market->participants[participant_ix]->require_vtop), &(market->participants[participant_ix]->require_vcap), itm);

}

void create_require_offer(Market* market, __int64 offer_id, __int64 itm) {

    __int64 offer_ix = 0;

    for (__int64 i = 0; i <= market->barter_system->offers_vtop; i++) {
        if (market->barter_system->offers[i]->id == offer_id) {
            offer_ix = i;
            break;
        }
    }

    __int64 require_ix = -1;

    for (__int64 i = 0; i <= market->barter_system->offers[offer_ix]->require_vtop + 1; i++) {
        if (market->barter_system->offers[offer_ix]->require[i] == itm) {
            require_ix = i;
            break;
        }
    }

    if (require_ix > -1)
        return;

    simp_vector_append(&(market->barter_system->offers[offer_ix]->require), &(market->barter_system->offers[offer_ix]->require_vtop), &(market->barter_system->offers[offer_ix]->require_vcap), itm);

}

void create_ban_participant(Market* market, __int64 participant_id, __int64 itm) {

    __int64 participant_ix = 0;

    for (__int64 i = 0; i <= market->participants_vtop; i++) {
        if (market->participants[i]->id == participant_id) {
            participant_ix = i;
            break;
        }
    }

    __int64 ban_ix = -1;

    for (__int64 i = 0; i <= market->participants[participant_ix]->bans_vtop + 1; i++) {
        if (market->participants[participant_ix]->bans[i] == itm) {
            ban_ix = i;
            break;
        }
    }

    if (ban_ix > -1)
        return;

    simp_vector_append(&(market->participants[participant_ix]->bans), &(market->participants[participant_ix]->bans_vtop), &(market->participants[participant_ix]->bans_vcap), itm);

}
void create_ban_offer(Market* market, __int64 offer_id, __int64 itm) {

    __int64 offer_ix = 0;

    for (__int64 i = 0; i <= market->barter_system->offers_vtop; i++) {
        if (market->barter_system->offers[i]->id == offer_id) {
            offer_ix = i;
            break;
        }
    }

    __int64 ban_ix = -1;

    for (__int64 i = 0; i <= market->barter_system->offers[offer_ix]->bans_vtop + 1; i++) {
        if (market->barter_system->offers[offer_ix]->bans[i] == itm) {
            ban_ix = i;
            break;
        }
    }

    if (ban_ix > -1)
        return;

    simp_vector_append(&(market->barter_system->offers[offer_ix]->bans), &(market->barter_system->offers[offer_ix]->bans_vtop), &(market->barter_system->offers[offer_ix]->bans_vcap), itm);

}

void remove_require_participant(Market* market, __int64 participant_id, __int64 itm) {

    __int64 participant_ix = 0;

    for (__int64 i = 0; i <= market->participants_vtop; i++) {
        if (market->participants[i]->id == participant_id) {
            participant_ix = i;
            break;
        }
    }

    __int64 require_ix = -1;

    for (__int64 i = 0; i <= market->participants[participant_ix]->require_vtop; i++) {
        if (market->participants[participant_ix]->require[i] == itm) {
            require_ix = i;
            break;
        }
    }

    if (require_ix == -1)        // not present: nothing to remove
        return;

    for (__int64 i = require_ix; i <= market->participants[participant_ix]->require_vtop - 1; i++)
        market->participants[participant_ix]->require[i] = market->participants[participant_ix]->require[i + 1];

    market->participants[participant_ix]->require_vtop--;

}

void remove_require_offer(Market* market, __int64 offer_id, __int64 itm) {

    __int64 offer_ix = 0;

    for (__int64 i = 0; i <= market->barter_system->offers_vtop; i++) {
        if (market->barter_system->offers[i]->id == offer_id) {
            offer_ix = i;
            break;
        }
    }

    __int64 require_ix = -1;

    for (__int64 i = 0; i <= market->barter_system->offers[offer_ix]->require_vtop; i++) {
        if (market->barter_system->offers[offer_ix]->require[i] == itm) {
            require_ix = i;
            break;
        }
    }

    if (require_ix == -1)        // not present: nothing to remove
        return;

    for (__int64 i = require_ix; i <= market->barter_system->offers[offer_ix]->require_vtop - 1; i++)
        market->barter_system->offers[offer_ix]->require[i] = market->barter_system->offers[offer_ix]->require[i + 1];

    market->barter_system->offers[offer_ix]->require_vtop--;

}

void remove_ban_participant(Market* market, __int64 participant_id, __int64 itm) {

    __int64 participant_ix = 0;

    for (__int64 i = 0; i <= market->participants_vtop; i++) {
        if (market->participants[i]->id == participant_id) {
            participant_ix = i;
            break;
        }
    }

    __int64 ban_ix = -1;

    for (__int64 i = 0; i <= market->participants[participant_ix]->bans_vtop; i++) {
        if (market->participants[participant_ix]->bans[i] == itm) {
            ban_ix = i;
            break;
        }
    }

    if (ban_ix == -1)        // not present: nothing to remove
        return;

    for (__int64 i = ban_ix; i <= market->participants[participant_ix]->bans_vtop - 1; i++)
        market->participants[participant_ix]->bans[i] = market->participants[participant_ix]->bans[i + 1];

    market->participants[participant_ix]->bans_vtop--;

}

void remove_ban_offer(Market* market, __int64 offer_id, __int64 itm) {

    __int64 offer_ix = 0;

    for (__int64 i = 0; i <= market->barter_system->offers_vtop; i++) {
        if (market->barter_system->offers[i]->id == offer_id) {
            offer_ix = i;
            break;
        }
    }

    __int64 ban_ix = -1;

    for (__int64 i = 0; i <= market->barter_system->offers[offer_ix]->bans_vtop; i++) {
        if (market->barter_system->offers[offer_ix]->bans[i] == itm) {
            ban_ix = i;
            break;
        }
    }

    if (ban_ix == -1)        // not present: nothing to remove
        return;

	for (__int64 i = ban_ix; i <= market->barter_system->offers[offer_ix]->bans_vtop - 1; i++)
		market->barter_system->offers[offer_ix]->bans[i] = market->barter_system->offers[offer_ix]->bans[i + 1];

    market->barter_system->offers[offer_ix]->bans_vtop--;

}

Offer* create_offer(Market* market, __int64* participants_offering, __int64 participants_offering_vtop, __int64 participants_offering_vcap, Voucher* give, __int64 give_vtop, __int64 give_vcap, __int64* give_voucher_counts, __int64 give_voucher_counts_vtop, __int64 give_voucher_counts_vcap, Voucher* receive, __int64 receive_vtop, __int64 receive_vcap, __int64* receive_voucher_counts, __int64 receive_voucher_counts_vtop, __int64 receive_voucher_counts_vcap,
    __int64 valid_start, __int64 valid_end, __int64 subscription_interval, __int64 interval_type, __int64 intervals,
    __int64* insurance_policies_accepted, __int64 insurance_policies_accepted_vtop, __int64 insurance_policies_accepted_vcap, __int64* insurance_policies_applied, __int64 insurance_policies_applied_vtop, __int64 insurance_policies_applied_vcap,
    __int64* participants_require, __int64 participants_require_vtop, __int64 participants_require_vcap, __int64* participants_ban, __int64 participants_ban_vtop, __int64 participants_ban_vcap,
    __int64* require, __int64 require_vtop, __int64 require_vcap, __int64* bans, __int64 bans_vtop, __int64 bans_vcap) {

    Offer* offer = new Offer();

	offer->id = retrieve_offer_id(market->id_pool);

    offer->participants_offering = simp_vector_create(participants_offering_vtop + 1);
    offer->gives = new Voucher[give_vtop + 1 > 0 ? give_vtop + 1 : 1]();
    offer->gives_voucher_counts = simp_vector_create(16);
    offer->receives = new Voucher[16]();
    offer->receives_voucher_counts = simp_vector_create(16);
    offer->gives_gold_milligram_value = 0;
    offer->receives_gold_milligram_value = 0;
    offer->valid_start = 0;
    offer->valid_end = 0;
	offer->subscription_interval = 0;
	offer->interval_type = 0;
    offer->intervals = 0;
	offer->insurance_policies_accepted = simp_vector_create(16);
	offer->insurance_policies_applied = simp_vector_create(16);
    offer->participants_require = simp_vector_create(16);
    offer->participants_ban = simp_vector_create(16);
    offer->require = simp_vector_create(16);
    offer->bans = simp_vector_create(16);

    offer->participants_offering_vtop = -1;
    offer->participants_offering_vcap = 16;
    offer->gives_vtop = -1;
    offer->gives_vcap = 16;
    offer->gives_voucher_counts_vtop = -1;
    offer->gives_voucher_counts_vcap = 16;
    offer->receives_vtop = -1;
    offer->receives_vcap = 16;
    offer->receive_voucher_counts_vtop = -1;
    offer->receive_voucher_counts_vcap = 16;
    offer->insurance_policies_accepted_vtop = -1;
    offer->insurance_policies_accepted_vcap = 16;
    offer->insurance_policies_applied_vtop = -1;
    offer->insurance_policies_applied_vcap = 16;
    offer->participants_require_vtop = -1;
    offer->participants_require_vcap = 16;
    offer->participants_ban_vtop = -1;
    offer->participants_ban_vcap = 16;
    offer->require_vtop = -1;
    offer->require_vcap = 16;
    offer->bans_vtop = -1;
    offer->bans_vcap = 16;

	for (__int64 i = 0; i <= participants_offering_vtop; i++)
		simp_vector_append(&(offer->participants_offering), &(offer->participants_offering_vtop), &(offer->participants_offering_vcap),
			simp_vector_read(participants_offering, participants_offering_vtop, participants_offering_vcap, i));


	for (__int64 i = 0; i <= give_vtop; i++) {
            
		offer->gives->id = give[i].id;

		for (__int64 j = 0; j <= give[i].title_vtop+1; j++)
			offer->gives->title[j] = give[i].title[j];
		offer->gives->title_vtop = give[i].title_vtop;
		offer->gives->title_vcap = give[i].title_vcap;

        for (__int64 j = 0; j <= give[i].description_vtop; j++)
            offer->gives->description[j] = give[i].description[j];
        offer->gives->description_vtop = give[i].description_vtop;
        offer->gives->description_vcap = give[i].description_vcap;

        for (__int64 j = 0; j <= give[i].media_url_vtop; j++)
            offer->gives->media_url[j] = give[i].media_url[j];
        offer->gives->media_url_vtop = give[i].media_url_vtop;
        offer->gives->media_url_vcap = give[i].media_url_vcap;

        offer->valid_start = give[i].valid_start;
        offer->valid_end = give[i].valid_end;
        offer->subscription_interval = give[i].subscription_interval;
        offer->interval_type = give[i].interval_type;
        offer->intervals = give[i].intervals;

        offer->gives_gold_milligram_value = 0;

		for (__int64 j = 0; j <= give_voucher_counts_vtop; j++)
            offer->gives_gold_milligram_value += give->gold_milligram_value;
	}

    for (__int64 i = 0; i <= receive_vtop; i++) {

        offer->receives->id = receive[i].id;

        for (__int64 j = 0; j <= receive[i].title_vtop; j++)
            offer->receives->title[j] = receive[i].title[j];
        offer->receives->title_vtop = receive[i].title_vtop;
        offer->receives->title_vcap = receive[i].title_vcap;

        for (__int64 j = 0; j <= receive[i].description_vtop; j++)
            offer->receives->description[j] = receive[i].description[j];
        offer->receives->description_vtop = receive[i].description_vtop;
        offer->receives->description_vcap = receive[i].description_vcap;

        for (__int64 j = 0; j <= receive[i].media_url_vtop; j++)
            offer->receives->media_url[j] = receive[i].media_url[j];
        offer->receives->media_url_vtop = receive[i].media_url_vtop;
        offer->receives->media_url_vcap = receive[i].media_url_vcap;

        offer->valid_start = receive[i].valid_start;
        offer->valid_end = receive[i].valid_end;
        offer->subscription_interval = receive[i].subscription_interval;
        offer->interval_type = receive[i].interval_type;
        offer->intervals = receive[i].intervals;

        offer->receives_gold_milligram_value = 0;

        for (__int64 j = 0; j <= receive_voucher_counts_vtop; j++)
            offer->receives_gold_milligram_value += receive->gold_milligram_value;
    }

    offer->valid_start = give[0].valid_start;

	for (__int64 j = 1; j <= give_vtop; j++)
		if (give[j].valid_start < offer->valid_start)
			offer->valid_start = give[j].valid_start;

    offer->valid_end = give[0].valid_end;

    for (__int64 j = 1; j <= give_vtop; j++)
        if (give[j].valid_end < offer->valid_end)
            offer->valid_end = give[j].valid_end;


    offer->subscription_interval = subscription_interval;
    offer->interval_type = interval_type;
    offer->intervals = intervals;

	for (__int64 j = 0; j <= insurance_policies_accepted_vtop; j++)
		offer->insurance_policies_accepted[j] = insurance_policies_accepted[j];

    for (__int64 j = 0; j <= insurance_policies_applied_vtop; j++)
        offer->insurance_policies_applied[j] = insurance_policies_applied[j];

    offer->gives_vtop = -1;
    offer->gives_vcap = 16;
    offer->gives_voucher_counts_vtop = -1;
    offer->gives_voucher_counts_vcap = 16;
    offer->receives_vtop = -1;
    offer->receives_vcap = 16;
    offer->receive_voucher_counts_vtop = -1;
    offer->receive_voucher_counts_vcap = 16;
    offer->insurance_policies_accepted_vtop = -1;
    offer->insurance_policies_accepted_vcap = 16;
    offer->insurance_policies_applied_vtop = -1;
    offer->insurance_policies_applied_vcap = 16;

    return offer;

}

Offer** create_offers() {
	Offer** offers = simp_offer_vector_create(16);
	return offers;
}

Barter_System* create_barter_system() {

	Barter_System* barter_system = new Barter_System();
	barter_system->offers = create_offers();
	barter_system->offers_vtop = -1;
	barter_system->offers_vcap = 16;
	return barter_system;

}

// A free list. Ids returned by id_pool_submit are reissued first; when none
// are waiting, mint the next fresh one. The original always returned 0 and
// then read one past the top of an uninitialised array.
__int64 id_pool_retrieve(ID_Pool* id_pool) {

    if (id_pool->trade_entities_vtop >= 0) {
        const __int64 id = id_pool->trade_entities[id_pool->trade_entities_vtop];
        id_pool->trade_entities_vtop--;
        return id;
    }

    return id_pool->next_id++;
}

void id_pool_submit(ID_Pool* id_pool, __int64 id) {

    simp_vector_append(&(id_pool->trade_entities),
                       &(id_pool->trade_entities_vtop),
                       &(id_pool->trade_entities_vcap), id);
}

__int64 retrieve_voucher_id(ID_Pool* id_pool) {
    return id_pool_retrieve(id_pool);
}

void submit_voucher_id(ID_Pool* id_pool, __int64 id) {
    id_pool_submit(id_pool, id);
}

__int64 retrieve_account_id(ID_Pool* id_pool) {
    return id_pool_retrieve(id_pool);
}

void submit_account_id(ID_Pool* id_pool, __int64 id) {
    id_pool_submit(id_pool, id);
}

__int64 retrieve_bank_id(ID_Pool* id_pool) {
    return id_pool_retrieve(id_pool);
}

void submit_bank_id(ID_Pool* id_pool, __int64 id) {
    id_pool_submit(id_pool, id);
}

__int64 retrieve_offer_id(ID_Pool* id_pool) {
    return id_pool_retrieve(id_pool);
}

void submit_offer_id(ID_Pool* id_pool, __int64 id) {
    id_pool_submit(id_pool, id);
}

__int64 retrieve_bill_id(ID_Pool* id_pool) {
    return id_pool_retrieve(id_pool);
}

void submit_bill_id(ID_Pool* id_pool, __int64 id) {
    id_pool_submit(id_pool, id);
}

__int64 retrieve_law_id(ID_Pool* id_pool) {
    return id_pool_retrieve(id_pool);
}

void submit_law_id(ID_Pool* id_pool, __int64 id) {
    id_pool_submit(id_pool, id);
}

__int64 retrieve_gold_deposit_id(ID_Pool* id_pool) {
    return id_pool_retrieve(id_pool);
}

void submit_gold_deposit_id(ID_Pool* id_pool, __int64 id) {
    id_pool_submit(id_pool, id);
}

__int64 retrieve_gold_milligrams_id(ID_Pool* id_pool) {
    return id_pool_retrieve(id_pool);
}

void submit_gold_milligrams_id(ID_Pool* id_pool, __int64 id) {
    id_pool_submit(id_pool, id);
}

__int64 retrieve_gold_deposit_match_id(ID_Pool* id_pool) {
    return id_pool_retrieve(id_pool);
}

void submit_gold_deposit_match_id(ID_Pool* id_pool, __int64 id) {
    id_pool_submit(id_pool, id);
}

__int64 retrieve_gold_milligram_match_id(ID_Pool* id_pool) {
    return id_pool_retrieve(id_pool);
}

void submit_gold_milligram_match_id(ID_Pool* id_pool, __int64 id) {
    id_pool_submit(id_pool, id);
}

__int64 retrieve_participant_id(ID_Pool* id_pool) {
    return id_pool_retrieve(id_pool);
}

void submit_participant_id(ID_Pool* id_pool, __int64 id) {
    id_pool_submit(id_pool, id);
}

ID_Pool* create_id_pool() {

    ID_Pool* id_pool = new ID_Pool();

    id_pool->trade_entities = simp_vector_create(16);
    
    id_pool->trade_entities_vtop = -1;
    id_pool->trade_entities_vcap = 16;
    id_pool->next_id = 0;

    return id_pool;
}

Participant* create_participant(Market* market) {

	Participant* participant = new Participant();

	participant->id = retrieve_participant_id(market->id_pool);
	participant->require = new __int64[16];
	participant->bans = new __int64[16];
	participant->require_vtop = -1;
	participant->require_vcap = 16;
	participant->bans_vtop = -1;
	participant->bans_vcap = 16;

	return participant;
}

Account* create_account(Market* market, __int64 gold_milligram_balance, __int64* holdings, __int64* voucher_counts, __int64 vouchers_vtop, __int64 vouchers_vcap, __int64 voucher_counts_vtop, __int64 voucher_counts_vcap) {

    Account* account = new Account();

    account->id = retrieve_account_id(market->id_pool);

    account->gold_milligram_balance = gold_milligram_balance;
    account->holdings = holdings;
    account->voucher_counts = voucher_counts;
    account->vouchers_vtop = vouchers_vtop;
    account->vouchers_vcap = vouchers_vcap;
    account->voucher_counts_vtop = voucher_counts_vtop;
    account->voucher_counts_vcap = voucher_counts_vcap;

    return account;
}

Bank* create_bank(Market* market, __int64* accounts, __int64* account_holders, __int64 accounts_vtop, __int64 accounts_vcap, __int64 account_holders_vtop, __int64 account_holders_vcap) {

	Bank* bank = new Bank();

	bank->id = retrieve_bank_id(market->id_pool);

	bank->accounts = accounts;
	bank->account_holders = account_holders;
	bank->accounts_vtop = accounts_vtop;
	bank->accounts_vcap = accounts_vcap;
	bank->account_holders_vtop = account_holders_vtop;
	bank->accounts_vcap = account_holders_vcap;

    return bank;

}

Market* create_market() {

	Market* market = new Market();

    market->id_pool = create_id_pool();
    market->barter_system = create_barter_system();
    market->participants = simp_participant_vector_create(16);
    market->accounts = simp_account_vector_create(16);
    market->banks = simp_bank_vector_create(16);

    market->participants_vtop = -1;
    market->participants_vcap = 16;
    market->accounts_vtop = -1;
    market->accounts_vcap = 16;
    market->banks_vtop = -1;
    market->banks_vcap = 16;

	// create the state participant and the state account so people can pay their taxes and successful votes on bills and Article V issues may result in the issuance of new vouchers to the state account.

	Participant* state_participant = create_participant(market);
	Account* state_account = create_account(market, 0, 0, nullptr, -1, 16, -1, 16);

	simp_participant_vector_append(&(market->participants), &(market->participants_vtop), &(market->participants_vcap), state_participant);
	simp_account_vector_append(&(market->accounts), &(market->accounts_vtop), &(market->accounts_vcap), state_account);

	return market;
}

// ---------------------------------------------------------------------------
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

int nomgr_unused_main() {
}

#endif