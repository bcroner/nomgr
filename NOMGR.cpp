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
#include "thread-pool/thread_pool.hpp"              // https://github.com/mtrebi/thread-pool
#include "thread-pool/thread_pool_callable.hpp"     // https://github.com/mtrebi/thread-pool
#include <stdio.h>
#include <thread>
#include <condition_variable>
#include <mutex>

Article_V_Option* simp_article_v_option_vector_create(__int64 init_sz) {

    Article_V_Option* ret = new Article_V_Option[init_sz];
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

Voucher* simp_voucher_vector_create(__int64 init_sz) {

    Voucher* ret = new Voucher[init_sz];
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
        Voucher** newv = new Voucher*[*vcap * 2];
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

Offer* simp_offer_vector_create(__int64 init_sz) {

    Offer* ret = new Offer[init_sz];
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


Bill* simp_bill_vector_create(__int64 init_sz) {

    Bill* ret = new Bill[init_sz];
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

Law* simp_law_vector_create(__int64 init_sz) {

    Law* ret = new Law[init_sz];
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

Gold_Deposit* simp_gold_deposit_vector_create(__int64 init_sz) {

    Gold_Deposit* ret = new Gold_Deposit[init_sz];
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

Participant** simp_participant_vector_create(__int64 init_sz) {

    Participant** ret = new Participant* [init_sz];
    return ret;

}

Participant* simp_participant_vector_read(Participant** v, __int64 vtop, __int64 vcap, __int64 loc) {

    if (loc > vtop)
        return 0;

    return v[loc];
}

void simp_participant_vector_append(Participant** v, __int64* vtop, __int64* vcap, Participant* data) {

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
        v = newv;
        v[*vtop] = data;
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

std::mutex qmtx;

void simp_queue_enqueue(Simp_Queue* queue, Simp_Queue* parm) {

    Simp_Queue* temp = queue->next;
    queue->next = parm;
    parm->next = temp;

}

Simp_Queue* simp_queue_dequeue(Simp_Queue* queue) {

    Simp_Queue* mover = queue;
    if (mover->next == 0)
        return 0;
    while (mover->next->next != 0)
        mover = mover->next;

    Simp_Queue* ret = mover->next;
    mover->next = 0;

    return ret;
}

void create_require_participant(Market* market, __int64 participant_id, __int64 itm) {

}

void create_require_offer(Market* market, __int64 offer_id, __int64 itm) {

}

void create_ban_participant(Market* market, __int64 participant_id, __int64 itm) {

}
void create_ban_offer(Market* market, __int64 offer_id, __int64 itm) {

}

void remove_require_participant(Market* market, __int64 participant_id, __int64 itm) {

}

void remove_require_offer(Market* market, __int64 offer_id, __int64 itm) {

}

void remove_ban_participant(Market* market, __int64 participant_id, __int64 itm) {

}

void remove_ban_offer(Market* market, __int64 offer_id, __int64 itm) {

}

Offer* create_offer(Voucher* give, __int64* give_vtop, __int64* give_vcap, __int64* give_voucher_counts, __int64* give_voucher_counts_vtop, __int64* give_voucher_counts_vcap, Voucher* receive, __int64* receive_vtop, __int64* receive_vcap, __int64* receive_voucher_counts, __int64* receive_voucher_counts_vtop, __int64* receive_voucher_counts_vcap,
    __int64 give_gold_microgram_value, __int64 receive_gold_microgram_value, __int64 valid_start, __int64 valid_end, __int64 subscription_interval, __int64 interval_type, __int64 intervals,
    __int64* insurance_policies_accepted, __int64* insurance_policies_accepted_vtop, __int64* insurance_policies_accepted_vcap, __int64* insurance_policies_applied, __int64* insurance_policies_applied_vtop, __int64* insurance_policies_applied_vcap) {

}

Market* create_market(Participant** participants) {

}

Trade_Check* create_trade_check(Market* market) {

}

bool check_trade(SATSolver* s, Trade_Check* trade_check) {

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

    return SATSolver_isSat(s, sln);

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