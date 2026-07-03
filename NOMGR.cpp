// NOMGR.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#ifndef __NOMGR_C__
#define __NOMGR_C__

#include "NOMGR.hpp"

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

	SATSolver* s = new SATSolver();
	s->lst_l_parm = simp_vector_create(16);
	s->lst_r_parm = simp_vector_create(16); 
    s->lst_l_parm_vtop = -1;
	s->lst_l_parm_vcap = 16;

	bool is_sat = check_trade(s, ret->trade_check, true);

    if (is_sat)
        return ret;
    else
		return nullptr;

}

void make_offer(Market* market, __int64* participants_offering, __int64 participants_offering_vtop, __int64 participants_offering_vcap, __int64* give, __int64 give_vtop, __int64 give_vcap, __int64* give_voucher_counts, __int64 give_voucher_counts_vtop, give_voucher_counts_vcap, __int64* receive, __int64 receive_vtop, __int64 receive_vcap, __int64 receive_voucher_counts, __int64 receive_voucher_counts_vtop, __int64 receive_voucher_counts_vcap,
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

    for (__int64 i = 0; i <= market->participants[participant_ix]->require_vtop + 1; i++) {
        if (market->participants[participant_ix]->require[i] == itm) {
            require_ix = i;
            break;
        }
    }

    if (require_ix > -1)
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

    for (__int64 i = 0; i <= market->barter_system->offers[offer_ix]->require_vtop + 1; i++) {
        if (market->barter_system->offers[offer_ix]->require[i] == itm) {
            require_ix = i;
            break;
        }
    }

    if (require_ix > -1)
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

    for (__int64 i = 0; i <= market->participants[participant_ix]->bans_vtop + 1; i++) {
        if (market->participants[participant_ix]->bans[i] == itm) {
            ban_ix = i;
            break;
        }
    }

    if (ban_ix > -1)
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

    for (__int64 i = 0; i <= market->barter_system->offers[offer_ix]->bans_vtop + 1; i++) {
        if (market->barter_system->offers[offer_ix]->bans[i] == itm) {
            ban_ix = i;
            break;
        }
    }

    if (ban_ix > -1)
        return;

	for (__int64 i = ban_ix; i <= market->barter_system->offers[offer_ix]->bans_vtop - 1; i++)
		market->barter_system->offers[offer_ix]->bans[i] = market->barter_system->offers[offer_ix]->bans[i + 1];

    market->barter_system->offers[offer_ix]->bans_vtop--;

}

Offer* create_offer(Market* market, __int64* participants_offering, __int64 participants_offering_vtop, __int64 participants_offering_vcap, __int64* give, __int64 give_vtop, __int64 give_vcap, __int64* give_voucher_counts, __int64 give_voucher_counts_vtop, give_voucher_counts_vcap, __int64* receive, __int64 receive_vtop, __int64 receive_vcap, __int64 receive_voucher_counts, __int64 receive_voucher_counts_vtop, __int64 receive_voucher_counts_vcap,
    __int64 valid_start, __int64 valid_end, __int64 subscription_interval, __int64 interval_type, __int64 intervals,
    __int64* insurance_policies_accepted, __int64 insurance_policies_accepted_vtop, __int64 insurance_policies_accepted_vcap, __int64* insurance_policies_applied, __int64 insurance_policies_applied_vtop, __int64 insurance_policies_applied_vcap,
    __int64* participants_require, __int64 participants_require_vtop, __int64 participants_require_vcap, __int64* participants_ban, __int64 participants_ban_vtop, __int64 participants_ban_vcap,
    __int64* require, __int64 require_vtop, __int64 require_vcap, __int64* bans, __int64 bans_vtop, __int64 bans_vcap) {

    Offer* offer = new Offer();

	offer->id = retrieve_offer_id(market->id_pool);

    offer->participants_offering = simp_vector_create(participants_offering_vtop + 1);
    offer->gives = simp_vector_create(give_vtop+1);
    offer->gives_voucher_counts = simp_vector_create(16);
    offer->receives = simp_vector_create(16);
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

	for (__int64 i = 0; i <= participants_offering_vtop + 1; i++)
		simp_participant_vector_append(&(offer->participants_offering), &participants_offering_vtop, &participants_offering_vcap), simp_participant_vector_read(offer->participants_offering, participants_offering_vtop, participants_offering_vcap, i));


	for (__int64 i = 0; i <= give_vtop + 1; i++) { {
            
		offer->gives->id = give[i].id;

		for (__int64 j = 0; j <= give[i].title_vtop+1; j++)
			offer->gives->title[j] = give[i].title[j];
		offer->gives->title_vtop = give[i].title_vtop;
		offer->gives->title_vcap = give[i].title_vcap;

        for (__int64 j = 0; j <= give[i].description_vtop + 1; j++)
            offer->gives->description[j] = give[i].description[j];
        offer->gives->description_vtop = give[i].description_vtop;
        offer->gives->description_vcap = give[i].description_vcap;

        for (__int64 j = 0; j <= give[i].media_url_vtop + 1; j++)
            offer->gives->media_url[j] = give[i].media_url[j];
        offer->gives->media_url_vtop = give[i].media_url_vtop;
        offer->gives->media_url_vcap = give[i].media_url_vcap;

        offer->valid_start = give[i].valid_start;
        offer->valid_end = give[i].valid_end;
        offer->subscription_interval = give[i].subscription_interval;
        offer->interval_type = give[i].interval_type;
        offer->intervals = give[i].intervals;

        offer->gives_gold_milligram_value = 0;

		for (__int64 j = 0; j <= give_voucher_counts_vtop + 1; j++)
            offer->gives_gold_milligram_value += give->gold_milligram_value;
	}

    for (__int64 i = 0; i <= receive_vtop + 1; i++) {

        offer->receives->id = receive[i].id;

        for (__int64 j = 0; j <= receive[i].title_vtop + 1; j++)
            offer->receives->title[j] = receive[i].title[j];
        offer->receives->title_vtop = receive[i].title_vtop;
        offer->receives->title_vcap = receive[i].title_vcap;

        for (__int64 j = 0; j <= receive[i].description_vtop + 1; j++)
            offer->receives->description[j] = receive[i].description[j];
        offer->receives->description_vtop = receive[i].description_vtop;
        offer->receives->description_vcap = receive[i].description_vcap;

        for (__int64 j = 0; j <= receive[i].media_url_vtop + 1; j++)
            offer->receives->media_url[j] = receive[i].media_url[j];
        offer->receives->media_url_vtop = receive[i].media_url_vtop;
        offer->receives->media_url_vcap = receive[i].media_url_vcap;

        offer->valid_start = receive[i].valid_start;
        offer->valid_end = receive[i].valid_end;
        offer->subscription_interval = receive[i].subscription_interval;
        offer->interval_type = receive[i].interval_type;
        offer->intervals = receive[i].intervals;

        offer->receives_gold_milligram_value = 0;

        for (__int64 j = 0; j <= receive_voucher_counts_vtop + 1; j++)
            offer->receives_gold_milligram_value += receive->gold_milligram_value;
    }

    offer->valid_start = give[0].valid_start;

	for (__int64 j = 1; j <= give_vtop + 1; j++)
		if (give[j].valid_start < offer->valid_start)
			offer->valid_start = give[j].valid_start;

    offer->valid_end = give[0].valid_end;

    for (__int64 j = 1; j <= give_vtop + 1; j++)
        if (give[j].valid_end < offer->valid_end)
            offer->valid_end = give[j].valid_end;


    offer->subscription_interval = subscription_interval;
    offer->interval_type = interval_type;
    offer->intervals = intervals;

	for (__int64 j = 0; j <= insurance_policies_accepted_vtop + 1; j++)
		offer->insurance_policies_accepted[j] = insurance_policies_accepted[j];

    for (__int64 j = 0; j <= insurance_policies_applied_vtop + 1; j++)
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

int id_pool_retrieve(__int64* id_pool, __int64* id_pool_vtop, __int64* id_pool_vcap) {

    if (*id_pool_vtop == -1) {
        simp_vector_append(*id_pool, id_pool_vtop, id_pool_vcap, 0);
        return 0;
    }

    __int64 id = id_pool[*id_pool_vtop + 1];

    __int64 ix = -1;

    for (__int64 i = 0; i <= *id_pool_vtop + 1; i++) {
        if (id_pool[i] > id) {
            ix = i;
            break;
        }
    }

    for (__int64 i = ix; i <= *id_pool_vtop; i++)
        id_pool[i] = id_pool[i + 1];

    return id;

}

void id_pool_submit(__int64* id_pool, __int64* id_pool_vtop, __int64* id_pool_vcap, __int64 id) {

    __int64 ix = -1;

    for (__int64 i = 0; i <= *id_pool_vtop + 1; i++) {
        if (id_pool[i] > id) {
            ix = i;
            break;
        }
    }

    simp_vector_append(&(id_pool), id_pool_vtop, id_pool_vcap, id_pool[*id_pool_vtop + 1]);

    for (__int64 i = ix; i <= *id_pool_vtop; i++)
        id_pool[i] = id_pool[i + 1];

    id_pool[ix] = id;

}

__int64 retrieve_voucher_id(ID_Pool* id_pool) {
    return id_pool_retrieve(id_pool->trade_entities, &(id_pool->trade_entities_vtop), &(id_pool->trade_entities_vcap));
}

void submit_voucher_id(ID_Pool* id_pool, __int64 id) {
    id_pool_submit(id_pool->trade_entities, &(id_pool->trade_entities_vtop), &(id_pool->trade_entities_vcap), id);
}

__int64 retrieve_account_id(ID_Pool* id_pool) {
    return id_pool_retrieve(id_pool->trade_entities, &(id_pool->trade_entities_vtop), &(id_pool->trade_entities_vcap));
}

void submit_account_id(ID_Pool* id_pool, __int64 id) {
    id_pool_submit(id_pool->trade_entities, &(id_pool->trade_entities_vtop), &(id_pool->trade_entities_vcap), id);
}

__int64 retrieve_bank_id(ID_Pool* id_pool) {
    return id_pool_retrieve(id_pool->trade_entities, &(id_pool->trade_entities_vtop), &(id_pool->trade_entities_vcap));
}

void submit_bank_id(ID_Pool* id_pool, __int64 id) {
    id_pool_submit(id_pool->trade_entities, &(id_pool->trade_entities_vtop), &(id_pool->trade_entities_vcap), id);
}

__int64 retrieve_offer_id(ID_Pool* id_pool) {
    return id_pool_retrieve(id_pool->trade_entities, &(id_pool->trade_entities_vtop), &(id_pool->trade_entities_vcap));
}

void submit_offer_id(ID_Pool* id_pool, __int64 id) {
    id_pool_submit(id_pool->trade_entities, &(id_pool->trade_entities_vtop), &(id_pool->trade_entities_vcap), id);
}

__int64 retrieve_bill_id(ID_Pool* id_pool) {
    return id_pool_retrieve(id_pool->trade_entities, &(id_pool->trade_entities_vtop), &(id_pool->trade_entities_vcap));
}

void submit_bill_id(ID_Pool* id_pool, __int64 id) {
    id_pool_submit(id_pool->trade_entities, &(id_pool->trade_entities_vtop), &(id_pool->trade_entities_vcap), id);
}

__int64 retrieve_law_id(ID_Pool* id_pool) {
    return id_pool_retrieve(id_pool->trade_entities, &(id_pool->trade_entities_vtop), &(id_pool->trade_entities_vcap));
}

void submit_law_id(ID_Pool* id_pool, __int64 id) {
    id_pool_submit(id_pool->trade_entities, &(id_pool->trade_entities_vtop), &(id_pool->trade_entities_vcap), id);
}

__int64 retrieve_gold_deposit_id(ID_Pool* id_pool) {
    return id_pool_retrieve(id_pool->trade_entities, &(id_pool->trade_entities_vtop), &(id_pool->trade_entities_vcap));
}

void submit_gold_deposit_id(ID_Pool* id_pool, __int64 id) {
    id_pool_submit(id_pool->trade_entities, &(id_pool->trade_entities_vtop), &(id_pool->trade_entities_vcap), id);
}

__int64 retrieve_gold_milligrams_id(ID_Pool* id_pool) {
    return id_pool_retrieve(id_pool->trade_entities, &(id_pool->trade_entities_vtop), &(id_pool->trade_entities_vcap));
}

void submit_gold_milligrams_id(ID_Pool* id_pool, __int64 id) {
    id_pool_submit(id_pool->trade_entities, &(id_pool->trade_entities_vtop), &(id_pool->trade_entities_vcap), id);
}

__int64 retrieve_gold_deposit_match_id(ID_Pool* id_pool) {
    return id_pool_retrieve(id_pool->trade_entities, &(id_pool->trade_entities_vtop), &(id_pool->trade_entities_vcap));
}

void submit_gold_deposit_match_id(ID_Pool* id_pool, __int64 id) {
    id_pool_submit(id_pool->trade_entities, &(id_pool->trade_entities_vtop), &(id_pool->trade_entities_vcap), id);
}

__int64 retrieve_gold_milligram_match_id(ID_Pool* id_pool) {
    return id_pool_retrieve(id_pool->trade_entities, &(id_pool->trade_entities_vtop), &(id_pool->trade_entities_vcap));
}

void submit_gold_milligram_match_id(ID_Pool* id_pool, __int64 id) {
    id_pool_submit(id_pool->trade_entities, &(id_pool->trade_entities_vtop), &(id_pool->trade_entities_vcap), id);
}

__int64 retrieve_participant_id(ID_Pool* id_pool) {
    return id_pool_retrieve(id_pool->trade_entities, &(id_pool->trade_entities_vtop), &(id_pool->trade_entities_vcap));
}

void submit_participant_id(ID_Pool* id_pool, __int64 id) {
    id_pool_submit(id_pool->trade_entities, &(id_pool->trade_entities_vtop), &(id_pool->trade_entities_vcap), id);
}

ID_Pool* create_id_pool() {

    ID_Pool* id_pool = new ID_Pool();

    id_pool->trade_entities = simp_vector_create(16);
    
    id_pool->trade_entities_vtop = -1;
    id_pool->trade_entities_vcap = 16;

	id_pool_retrieve(id_pool->trade_entities, &(id_pool->trade_entities_vtop), &(id_pool->trade_entities_vcap));
    id_pool_retrieve(id_pool->trade_entities, &(id_pool->trade_entities_vtop), &(id_pool->trade_entities_vcap));

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

Account* create_account(Market* market, __int64 gold_milligram_balance, Voucher* vouchers, __int64* voucher_counts, __int64 vouchers_vtop, __int64 vouchers_vcap, __int64 voucher_counts_vtop, __int64 voucher_counts_vcap) {

    Account* account = new Account();

    account->id = retrieve_account_id(market->id_pool);

    account->gold_milligram_balance = gold_milligram_balance;
    account->vouchers = vouchers;
    account->voucher_counts = voucher_counts;
    account->vouchers_vtop = vouchers_vtop;
    account->vouchers_vcap = vouchers_vcap;
    account->voucher_counts_vtop = voucher_counts_vtop;
    account->voucher_counts_vcap = voucher_counts_vcap;

    return account;
}

Bank* create_bank(Market* market, Account* accounts, Participant** account_holders, __int64 accounts_vtop, __int64 accounts_vcap, __int64 account_holders_vtop, __int64 account_holders_vcap) {

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

Trade_Check* create_trade_check(Market* market) {

	Trade_Check* trade_check = new Trade_Check();

    trade_check->vocabumalary_tracker_class = simp_vector_create(16);
    trade_check->vocabumalary_tracker_id = simp_vector_create(16);

    trade_check->vocabumalary_tracker_class_vtop = -1;
    trade_check->vocabumalary_tracker_class_vcap = 16;
    trade_check->vocabumalary_tracker_id_vtop = -1;
    trade_check->vocabumalary_tracker_id_vcap = 16;

    trade_check->lst_l = simp_vector_create(16);
    trade_check->lst_r = simp_vector_create(16);

    trade_check->lst_l_vtop = -1;
    trade_check->lst_r_vcap = 16;
    trade_check->lst_l_vtop = -1;
    trade_check->lst_r_vcap = 16;

    __int64 gold_milligram_ix = 0;

	for (__int64 i = 0; i <= market->barter_system->offers_vtop + 1; i++) {

        __int64 offer = simp_vector_read(&(market->barter_system->offers), &(market->barter_system->offers_vtop), (market->barter_system->offers_vcap), i);

        for (__int64 j = 0; j <= market->barter_system->offers_gives_vtop + 1; j++) {

            __int64 give = simp_vector_read(&(market->barter_system->offers_gives), &(market->barter_system->offers_gives_vtop), (market->barter_system->offers_gives_vcap), j);

            simp_vector_append(&(trade_check->lst_l), &(trade_check->lst_l_vtop), &(trade_check->lst_l_vcap), offer_ix);
            simp_vector_append(&(trade_check->lst_r), &(trade_check->lst_r_vtop), &(trade_check->lst_r_vcap), -give);

            simp_vector_append(&(trade_check->lst_l), &(trade_check->lst_l_vtop), &(trade_check->lst_l_vcap), -offer_ix);
            simp_vector_append(&(trade_check->lst_r), &(trade_check->lst_r_vtop), &(trade_check->lst_r_vcap), give);

            if (market->barter_system->offers_gives_classifications == gold)
                for (__int64 k = 0; k <= offer->gives_vtop + 1; k++) {

                    __int64 gold_milligram_id = retrieve_gold_milligram(market->id_pool, gold_milligram_ix);
                    gold_milligram_ix++;

                    simp_vector_append(&(trade_check->lst_l), &(trade_check->lst_l_vtop), &(trade_check->lst_l_vcap), offer);
                    simp_vector_append(&(trade_check->lst_r), &(trade_check->lst_r_vtop), &(trade_check->lst_r_vcap), -give);

                    simp_vector_append(&(trade_check->lst_l), &(trade_check->lst_l_vtop), &(trade_check->lst_l_vcap), -offer);
                    simp_vector_append(&(trade_check->lst_r), &(trade_check->lst_r_vtop), &(trade_check->lst_r_vcap), give);

                    simp_vector_append(&(trade_check->lst_l), &(trade_check->lst_l_vtop), &(trade_check->lst_l_vcap), give);
                    simp_vector_append(&(trade_check->lst_r), &(trade_check->lst_r_vtop), &(trade_check->lst_r_vcap), -gold_milligram_ix);

                    simp_vector_append(&(trade_check->lst_l), &(trade_check->lst_l_vtop), &(trade_check->lst_l_vcap), -give);
                    simp_vector_append(&(trade_check->lst_r), &(trade_check->lst_r_vtop), &(trade_check->lst_r_vcap), gold_milligram_ix);

                }

            simp_vector_append(&(trade_check->vocabumalary_tracker_class), &(trade_check->vocabumalary_tracker_class_vtop), &(trade_check->vocabumalary_tracker_class_vcap), exchange_give);
            simp_vector_append(&(trade_check->vocabumalary_tracker_id), &(trade_check->vocabumalary_tracker_id_vtop), &(trade_check->vocabumalary_tracker_id_vcap), give);

        }

        for (__int64 j = 0; j <= market->barter_system->offers_receives_vtop + 1; j++) {

			__int64 receive = simp_vector_read(&(market->barter_system->offers_receives), &(market->barter_system->offers_receives_vtop), (market->barter_system->offers_receives_vcap), j);

            simp_vector_append(&(trade_check->lst_l), &(trade_check->lst_l_vtop), &(trade_check->lst_l_vcap), offers_ix);
            simp_vector_append(&(trade_check->lst_r), &(trade_check->lst_r_vtop), &(trade_check->lst_r_vcap), -receive);

            simp_vector_append(&(trade_check->lst_l), &(trade_check->lst_l_vtop), &(trade_check->lst_l_vcap), -offers_ix);
            simp_vector_append(&(trade_check->lst_r), &(trade_check->lst_r_vtop), &(trade_check->lst_r_vcap), receive);

            if (market->barter_system->offers_receives_classifications == gold)
                for (__int64 k = 0; k <= offer->receives_vtop+1; k++) {

                    simp_vector_append(&(trade_check->lst_l), &(trade_check->lst_l_vtop), &(trade_check->lst_l_vcap), offer);
                    simp_vector_append(&(trade_check->lst_r), &(trade_check->lst_r_vtop), &(trade_check->lst_r_vcap), -receive);

                    simp_vector_append(&(trade_check->lst_l), &(trade_check->lst_l_vtop), &(trade_check->lst_l_vcap), -offer);
                    simp_vector_append(&(trade_check->lst_r), &(trade_check->lst_r_vtop), &(trade_check->lst_r_vcap), receive);

                }

            simp_vector_append(&(trade_check->vocabumalary_tracker_class), &(trade_check->vocabumalary_tracker_class_vtop), &(trade_check->vocabumalary_tracker_class_vcap), exchange_receive);
            simp_vector_append(&(trade_check->vocabumalary_tracker_id), &(trade_check->vocabumalary_tracker_id_vtop), &(trade_check->vocabumalary_tracker_id_vcap), receive);

        }

        for (__int64 j = 0; j <= market->barter_system->offers_require_vtop + 1; j++) {

            __int64 require = simp_vector_read(&(market->barter_system->offers_requires), &(market->barter_system->offers_requires_vtop), (market->barter_system->offers_requires_vcap), j);

            simp_vector_append(&(trade_check->lst_l), &(trade_check->lst_l_vtop), &(trade_check->lst_l_vcap), require);
            simp_vector_append(&(trade_check->lst_r), &(trade_check->lst_r_vtop), &(trade_check->lst_r_vcap), FALSE_2SAT);

            simp_vector_append(&(trade_check->vocabumalary_tracker_class), &(trade_check->vocabumalary_tracker_class_vtop), &(trade_check->vocabumalary_tracker_class_vcap), require_offer);
            simp_vector_append(&(trade_check->vocabumalary_tracker_id), &(trade_check->vocabumalary_tracker_id_vtop), &(trade_check->vocabumalary_tracker_id_vcap), require);

        }

        for (__int64 j = 0; j <= market->barter_system->offers_bans_vtop + 1; j++) {

            __int64 ban = simp_vector_read(&(market->barter_system->offers_bans), &(market->barter_system->offers_bans_vtop), (market->barter_system->offers_bans_vcap), j);

            simp_vector_append(&(trade_check->lst_l), &(trade_check->lst_l_vtop), &(trade_check->lst_l_vcap), ban);
            simp_vector_append(&(trade_check->lst_r), &(trade_check->lst_r_vtop), &(trade_check->lst_r_vcap), FALSE_2SAT);

            simp_vector_append(&(trade_check->vocabumalary_tracker_class), &(trade_check->vocabumalary_tracker_class_vtop), &(trade_check->vocabumalary_tracker_class_vcap), ban_offer);
            simp_vector_append(&(trade_check->vocabumalary_tracker_id), &(trade_check->vocabumalary_tracker_id_vtop), &(trade_check->vocabumalary_tracker_id_vcap), ban);
        }

        for (__int64 j = 0; j <= market->barter_system->offers_insurance_policies_required_vtop + 1; j++) {

            __int64 require = simp_vector_read(&(market->barter_system->offers[i]->insurance_policies_required), &(market->barter_system->offers[i]->insurance_policies_required_vtop), &(market->barter_system->offers[i]->insurance_policies_required_vcap), j);

            simp_vector_append(&(trade_check->lst_l), &(trade_check->lst_l_vtop), &(trade_check->lst_l_vcap), offer_ix);
            simp_vector_append(&(trade_check->lst_l), &(trade_check->lst_l_vtop), &(trade_check->lst_l_vcap), require);

            simp_vector_append(&(trade_check->vocabumalary_tracker_class), &(trade_check->vocabumalary_tracker_class_vtop), &(trade_check->vocabumalary_tracker_class_vcap), require_insurance_policy);
            simp_vector_append(&(trade_check->vocabumalary_tracker_id), &(trade_check->vocabumalary_tracker_id_vtop), &(trade_check->vocabumalary_tracker_id_vcap), require);

        }

        for (__int64 j = 0; i <= market->barter_system->offers_insurance_policies_applied_vtop + 1; j++) {
            
            __int64 applied = simp_vector_read(&(market->barter_system->offers[i]->insurance_policies_applied), &(market->barter_system->offers[i]->insurance_policies_applied_vtop), &(market->barter_system->offers[i]->insurance_policies_applied_vcap), j);

            simp_vector_append(&(trade_check->lst_l), &(trade_check->lst_l_vtop), &(trade_check->lst_l_vcap), offer_ix);
            simp_vector_append(&(trade_check->lst_l), &(trade_check->lst_l_vtop), &(trade_check->lst_l_vcap), -applied);

            simp_vector_append(&(trade_check->vocabumalary_tracker_class), &(trade_check->vocabumalary_tracker_class_vtop), &(trade_check->vocabumalary_tracker_class_vcap), apply_insurance_policy);
            simp_vector_append(&(trade_check->vocabumalary_tracker_id), &(trade_check->vocabumalary_tracker_id_vtop), &(trade_check->vocabumalary_tracker_id_vcap), applied);

        }

        for (__int64 j = 0; j <= market->barter_system->offers_insurance_policies_accepted_vtop + 1; j++) {

            __int64 accepted = simp_vector_read(&(market->barter_system->offers[i]->insurance_policies_accepted), &(market->barter_system->offers[i]->insurance_policies_accepted_vtop), &(market->barter_system->offers[i]->insurance_policies_accepted_vcap), j);

            simp_vector_append(&(trade_check->lst_l), &(trade_check->lst_l_vtop), &(trade_check->lst_l_vcap), offers_ix);
            simp_vector_append(&(trade_check->lst_r), &(trade_check->lst_r_vtop), &(trade_check->lst_r_vcap), -insurance_policies_accepted_ix);

            simp_vector_append(&(trade_check->lst_l), &(trade_check->lst_l_vtop), &(trade_check->lst_l_vcap), -offers_ix);
            simp_vector_append(&(trade_check->lst_r), &(trade_check->lst_r_vtop), &(trade_check->lst_r_vcap), insurance_policies_accepted_ix);

            simp_vector_append(&(trade_check->vocabumalary_tracker_class), &(trade_check->vocabumalary_tracker_class_vtop), &(trade_check->vocabumalary_tracker_class_vcap), accept_insurance_policy);
            simp_vector_append(&(trade_check->vocabumalary_tracker_id), &(trade_check->vocabumalary_tracker_id_vtop), &(trade_check->vocabumalary_tracker_id_vcap), accepted);

        }

    for (__int64 i = 0; i <= market->participants_vtop + 1; i++) {
        
		__int64 participant = simp_vector_read(&(market->participants), &(market->participants_vtop), &(market->participants_vcap), i);

        for (__int64 j = 0; j <= market->participants[i]->require_vtop + 1; j++) {

			__int64 require = simple_vector_read(&(market->participants[i]->require), &(market->participants[i]->require_vtop), &(market->participants[i]->require_vcap), j);

            simp_vector_append(&(trade_check->lst_l), &(trade_check->lst_l_vtop), &(trade_check->lst_l_vcap), participant);
            simp_vector_append(&(trade_check->lst_r), &(trade_check->lst_r_vtop), &(trade_check->lst_r_vcap), -require);

            simp_vector_append(&(trade_check->vocabumalary_tracker_class), &(trade_check->vocabumalary_tracker_class_vtop), &(trade_check->vocabumalary_tracker_class_vcap), require_participant);
            simp_vector_append(&(trade_check->vocabumalary_tracker_id), &(trade_check->vocabumalary_tracker_id_vtop), &(trade_check->vocabumalary_tracker_id_vcap), participant);

        }

        for (__int64 j = 0; j <= market->participants[i]->bans_vtop + 1; j++) {

            __int64 ban = simple_vector_read(&(market->participants[i]->bans), &(market->participants[i]->bans_vtop), &(market->participants[i]->bans_vcap), j);

            simp_vector_append(&(trade_check->lst_l), &(trade_check->lst_l_vtop), &(trade_check->lst_l_vcap), -participant);
            simp_vector_append(&(trade_check->lst_r), &(trade_check->lst_r_vtop), &(trade_check->lst_r_vcap), -ban)

            simp_vector_append(&(trade_check->vocabumalary_tracker_class), &(trade_check->vocabumalary_tracker_class_vtop), &(trade_check->vocabumalary_tracker_class_vcap), ban_participant);
            simp_vector_append(&(trade_check->vocabumalary_tracker_id), &(trade_check->vocabumalary_tracker_id_vtop), &(trade_check->vocabumalary_tracker_id_vcap), ban);

        }

    }

	return trade_check;

}

Code* create_code() {

	Code* code = new Code();

	code->laws = simp_law_vector_create(16);

	code->laws_vtop = -1;
	code->laws_vcap = 16;

	return code;
}

Legal_System* create_legal_system() {

	Legal_System* legal_system = new Legal_System();

    legal_system->civil_code = create_code();
    legal_system->penal_code = create_code();

    return legal_system;
}

Vault* create_vault() {

	Vault* vault = new Vault();

	vault->gold_deposits = simp_gold_deposit_vector_create(16);
	vault->gold_deposits_vtop = simp_vector_create(16);
	vault->gold_deposits_vcap = simp_vector_create(16);

	return vault;
}

System* create_system() {

	System* system = new System();

    system->market = create_market();
    system->legal_system = create_legal_system();
    system->vault = create_vault();

	return system;
}

void check_trade(SATSolver* s, Trade_Check* trade_check, bool repeat) {

	s->k_parm = trade_check->lst_l_vtop + 1;

	s->lst_l_parm = new __int64[s->k_parm];
    s->lst_r_parm = new __int64[s->k_parm];

    __int64* unique_checker = simp_vector_create(16);
	__int64 unique_checker_vtop = -1;
	__int64 unique_checker_vcap = 16;

    for (__int64 i = 0; i < s->k_parm; i++) {

        __int64 l_abs = trade_check->lst_l[i] < 0 ? -(trade_check->lst_l[i]) : trade_check->lst_l[i];
        __int64 r_abs = trade_check->lst_r[i] < 0 ? -(trade_check->lst_r[i]) : trade_check->lst_r[i];

		bool l_abs_found = false;
		bool r_abs_found = false;

        for (__int64 j = 0; j <= unique_checker_vtop + 1; j++) {

            if (unique_checker[j] == l_abs)
                l_abs_found = true;
            if (unique_checker[j] == r_abs)
                r_abs_found = true;

            if (l_abs_found && r_abs_found)
				break;
		}
		if (!l_abs_found)
            simp_vector_append(&(unique_checker), &(unique_checker_vtop), &(unique_checker_vcap), l_abs);
        if (!r_abs_found)
            simp_vector_append(&(unique_checker), &(unique_checker_vtop), &(unique_checker_vcap), r_abs);
	}

	s->n_parm = unique_checker_vtop + 2; // from 2..n_parm to 2..n

    s->is_f = new bool[s->n_parm];
    s->is_t = new bool[s->n_parm];

	s->Z = new bool[s->n_parm];

    for (__int64 i = 0; i < s->k_parm; i++) {
		s->lst_l_parm[i] = trade_check->lst_l[i];
		s->lst_r_parm[i] = trade_check->lst_r[i];
    }


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

    __int64 num_threads = std::thread::hardware_concurrency();
    if (num_threads <= 0) num_threads = 1;

    __int64 chops = 0;
    __int64 counter = 1;

    for (counter = 1; counter < num_threads; counter *= 2)
        chops++;

    //chops += 2;

    __int64 search_sz = 1;

    for (__int64 i = 0; i < chops; i++)
        search_sz *= 2;

    SATSolver** s;

    for (__int64 i = 0; i < search_sz; i++)
        SATSolver_create(&s, trade_check->lst_l, trade_check->lst_r, k, n);

    bool* sln = new bool[n];

    bool is_sat = SATSolver_isSat(s, sln);

    if (is_sat) {

		Simp_Queue* node = new Simp_Queue();
        node->data = trade_check;

		if (!repeat)
            simp_queue_enqueue(trade_check);

    }

}

bool* SATSolver_create_boundary(bool begin, __int64 chop, __int64 offs, __int64 n, __int64 leading_trues) {

    bool* ret = new bool[n];

    for (__int64 i = 0; i < leading_trues; i++)
        ret[i] = false;
    for (__int64 i = n - leading_trues; i < n; i++)
        ret[i] = true;

    for (__int64 i = 0; i < chop; i++) {

        __int64 pow2 = 1;
        for (__int64 j = chop - 1 - i; j > 0; j--)
            pow2 *= 2;

        if (offs >= pow2) {
            ret[n - 1 - leading_trues - i] = true;
            offs -= pow2;
        }
        else
            ret[n - 1 - leading_trues - i] = false;
    }

    for (__int64 i = 0; i < n - leading_trues - chop; i++)
        ret[i] = begin ? false : true;

    return ret;

}

void SATSolver_create(SATSolver*** s, __int64* lst_l_parm, __int64* lst_r_parm, __int64 k_parm, __int64 n_parm) {

    __int64 num_threads = std::thread::hardware_concurrency();
    if (num_threads <= 0) num_threads = 1;

    __int64 chops = 0;
    __int64 counter = 1;

    for (counter = 1; counter < num_threads; counter *= 2)
        chops++;

    //chops += 2;

    __int64 search_sz = 1;

    for (__int64 i = 0; i < chops; i++)
        search_sz *= 2;

	*s = new SATSolver * [search_sz];

	for (__int64 i = 0; i < search_sz; i++) {

        (*s)[i] = new SATSolver();
        (*s)[i]->chops = chops;

        (*s)[i]->is_f = new bool[n_parm];
        (*s)[i]->is_t = new bool[n_parm];
		
		for (__int64 j = 0; j < n_parm; j++) {
            (*s)[i]->is_f[j] = false;
            (*s)[i]->is_t[j] = false;
		}

        (*s)[i]->Z = SATSolver_create_boundary(true, chops, i, n_parm, 0);

        (*s)[i]->lst_l_parm = new __int64[k_parm];
        (*s)[i]->lst_r_parm = new __int64[k_parm];

        for (__int64 j = 0; j < k_parm; j++) {

            ((*s)[i]->lst_l_parm)[j] = lst_l_parm[j];
            ((*s)[i]->lst_r_parm)[j] = lst_l_parm[j];

        }

        bool* is_f = new bool[n_parm];
        bool* is_t = new bool[n_parm];

        for (__int64 j = 0; j < n_parm; j++) {

			is_f[j] = false;
            is_t[j] = false;

        }

        for (__int64 j = 0; j < n_parm; j++) {

            (*s)[i]->is_f[j] = !(*s)[i]->Z[j];
            (*s)[i]->is_t[j] = (*s)[i]->Z[j];

        }

        (*s)[i]->k_parm = k_parm;
        (*s)[i]->n_parm = n_parm;

        (*s)[i]->chops = chops;
        (*s)[i]->chop = i;
        (*s)[i]->leading_trues = 0;

	}    
}

void SATSolver_destroy(SATSolver*** s) {

    __int64 num_threads = std::thread::hardware_concurrency();
    if (num_threads <= 0) num_threads = 1;

    __int64 chops = 0;
    __int64 counter = 1;

    for (counter = 1; counter < num_threads; counter *= 2)
        chops++;

    //chops += 2;

    __int64 search_sz = 1;

    for (__int64 i = 0; i < chops; i++)
        search_sz *= 2;

    __int64 n = (*s)[0]->n_parm;

	for (__int64 i = 0; i < search_sz; i++) {
		delete[](*s)[i]->lst_l_parm;
		delete[](*s)[i]->lst_r_parm;
		delete[](*s)[i]->is_f;
		delete[](*s)[i]->is_t;
		delete[](*s)[i]->Z;
		delete (*s)[i];
	}

    delete[] (*s);

}

bool bool_equals(bool* A, bool* B, __int64 n) {

    for (__int64 i = 0; i < n; i++)
        if (A[i] != B[i])
            return false;

    return true;
}

bool SATSolver_isSat(SATSolver* s, bool* sln) {

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



std::mutex mtx;

void thread_2SAT(bool* arr, bool* is_sat, __int64* lst_l_parm, __int64* lst_r_parm, __int64 k_parm, __int64 n_parm, bool* is_f, bool* is_t, __int64 chops, __int64 chop, __int64 leading_trues) {

    if (*is_sat)
        return;

    SATSolver* s = new SATSolver();
    SATSolver_create(s, lst_l_parm, lst_r_parm, k_parm, n_parm, is_f, is_t, chops, chop, leading_trues);

    *is_sat |= SATSolver_isSat(s, arr);

    SATSolver_destroy(s);
    delete s;
}

bool SATSolver_threads(bool* arr, bool* is_sat, __int64* lst_l_parm, __int64* lst_r_parm, __int64 k_parm, __int64 n_parm, bool* is_f, bool* is_t, __int64 chops, __int64 chop, __int64 leading_trues) {

    __int64 num_threads = std::thread::hardware_concurrency();
    if (num_threads <= 0) num_threads = 1;

    __int64 chops = 0;
    __int64 counter = 1;

    for (counter = 1; counter < num_threads; counter *= 2)
        chops++;

    //chops += 2;

    __int64 search_sz = 1;

    for (__int64 i = 0; i < chops; i++)
        search_sz *= 2;

    bool is_sat = false;

    // A list of futures.
    std::list<std::future<void>> list;

    // Producer and consumer thread pools.
    thread::pool::parameterized_pool_t<1, 0> pool_of_consumers(num_threads);

    // Scheduling the consumers
    for (__int64 i = 0; i < search_sz; i++) {
        list.push_back(pool_of_consumers.schedule(thread_2SAT, arr, &is_sat, lst_l_parm, lst_r_parm, k_parm, n_parm, is_f, is_t, chops, chop, leading_trues));
    }

    // Waiting for the consumers to complete.
    for (std::future<void>& future : list)
        future.wait();

    return is_sat;
}



int main() {
}

#endif