#ifndef __NOMGR_H__
#define __NOMGR_H__

#define TRUE_2SAT 1
#define FALSE_2SAT -1

typedef struct ID_Pool_tag {

	/*
	__int64* vouchers;
	__int64* accounts;
	__int64* banks;
	__int64* offers;
	__int64* bills;
	__int64* laws;
	__int64* gold_deposits;
	__int64* gold_milligrams;
	__int64* gold_deposit_match;
	__int64* gold_milligram_match;
	__int64* participants;
	*/

	__int64* trade_entities;

	__int64 trade_entities_vtop;
	__int64 trade_entities_vcap;

} ID_Pool;

enum vocabumalary {
	state, individual, sole_prop_ssn, sole_prop_tin, sole_prop_ein, partnership, c_corp, s_corp, single_owner_llc, multi_owner_llc, llm, llp, trust, estate, government_entity, nonprofit,
	state_sales_tax_gold, state_sales_tax_non_gold, state_income_tax_gold, state_income_tax_non_gold, gold, cold_grocery_food, feminine_hygiene_good, sales_taxable_good, healthcare_service, dental_care_service, vision_care_service, government_entity_service, other_service, government_entity_product, common_share_a, common_share_b, common_share_c, preferred_share_a, preferred_share_b, preferred_share_c, dividend,
	exchange,
	insurance_policy_required, insurance_policy_applied, insurance_policy_accepted
};

/*

	 0 state
	 1 individual
	 2 sole_prop_ssn
	 3 sole_prop_tin
	 4 sole_prop_ein
	 5 partnership
	 6 c_corp
	 7 s_corp
	 8 single_owner_llc
	 9 multi_owner_llc
	10 llm
	11 llp
	12 trust
	13 estate
	14 government_entity
	15 nonprofit
	16 state_sales_tax_gold
	17 state_sales_tax_non_gold
	18 state_income_tax_gold
	19 state_income_tax_non_gold
	20 gold
	21 cold_grocery_food
	22 feminine_hygiene_good
	23 sales_taxable_good
	24 healthcare_service
	25 dental_care_service
	26 vision_care_service
	27 government_entity_service
	28 other_service
	29 government_entity_product
	30 common_share_a
	31 common_share_b
	32 common_share_c
	33 preferred_share_a
	34 preferred_share_b
	35 preferred_share_c
	36 dividend
	37 exchange
	38 insurance_policy_required
	39 insurance_policy_applied
	40 insurance_policy_accepted


*/


typedef struct Voucher_tag {

	__int64 id;
	vocabumalary classification;
	char* title;
	char* description;
	char* media_url;
	__int64 valid_start;
	__int64 valid_end;
	__int64 subscription_interval;
	__int64 interval_type;
	__int64 intervals;
	__int64 gold_milligram_value;

	__int64 title_vtop;
	__int64 title_vcap;
	__int64 description_vtop;
	__int64 description_vcap;
	__int64 media_url_vtop;
	__int64 media_url_vcap;

} Voucher;

typedef struct Voucher_System_tag {

	Voucher** vouchers;
	__int64* vouchers_counts;

	__int64 vouchers_vtop;
	__int64 vouchers_vcap;
	__int64 vouchers_counts_vtop;
	__int64 vouchers_counts_vcap;

} Voucher_System;

typedef struct Account_tag {

	__int64 id;
	__int64 gold_milligram_balance;
	__int64* holdings;
	__int64* voucher_counts;
	__int64 vouchers_vtop;
	__int64 vouchers_vcap;
	__int64 voucher_counts_vtop;
	__int64 voucher_counts_vcap;
} Account;

typedef struct Account_System_tag {

	Account** accounts;
	__int64 accounts_vtop;
	__int64 accounts_vcap;

} Account_System;

typedef struct Bank_tag {

	__int64 id;

	__int64* accounts;
	__int64* account_holders;

	__int64 accounts_vtop;
	__int64 accounts_vcap;
	__int64 account_holders_vtop;
	__int64 account_holders_vcap;

} Bank;

enum economic_action {
	exchange_give, exchange_receive, accept_insurance_policy, apply_insurance_policy, require_insurance_policy, require_participant, ban_participant, require_offer, ban_offer
};

/*

0 exchange_give
1 exchange_receive
2 accept_insurance_policy
3 apply_insurance_policy
4 require_insurance_policy
5 require_participant
6 ban_participant
7 require_offer
8 ban_offer

*/

typedef struct Offer_tag {

	__int64 id;

	__int64* participants_offering;
	Voucher* gives;
	vocabumalary* gives_classifications;
	__int64* gives_voucher_counts;
	Voucher* receives;
	vocabumalary* receives_classifications;
	__int64* receives_voucher_counts;
	__int64 gives_gold_milligram_value;
	__int64 receives_gold_milligram_value;
	__int64 valid_start;
	__int64 valid_end;
	__int64 subscription_interval;
	__int64 interval_type;
	__int64 intervals;
	__int64* insurance_policies_accepted;
	__int64* insurance_policies_required;
	__int64* insurance_policies_applied;
	__int64* participants_require;
	__int64* participants_ban;
	__int64* require;
	__int64* bans;

	__int64 participants_offering_vtop;
	__int64 participants_offering_vcap;
	__int64 gives_vtop;
	__int64 gives_vcap;
	__int64 gives_classifications_vtop;
	__int64 gives_classifications_vcap;
	__int64 gives_voucher_counts_vtop;
	__int64 gives_voucher_counts_vcap;
	__int64 receives_vtop;
	__int64 receives_vcap;
	__int64 receives_classifications_vtop;
	__int64 receives_classifications_vcap;
	__int64 receive_voucher_counts_vtop;
	__int64 receive_voucher_counts_vcap;
	__int64 insurance_policies_accepted_vtop;
	__int64 insurance_policies_accepted_vcap;
	__int64 insurance_policies_required_vtop;
	__int64 insurance_policies_required_vcap;
	__int64 insurance_policies_applied_vtop;
	__int64 insurance_policies_applied_vcap;
	__int64 participants_require_vtop;
	__int64 participants_require_vcap;
	__int64 participants_ban_vtop;
	__int64 participants_ban_vcap;
	__int64 require_vtop;
	__int64 require_vcap;
	__int64 bans_vtop;
	__int64 bans_vcap;

} Offer;

typedef struct Barter_System_tag {

	Offer** offers;

	__int64 offers_vtop;
	__int64 offers_vcap;

} Barter_System;

typedef struct Article_V_Option_tag {

	char* source;
	char* title;
	char* description;
	char* media_url;
	__int64* votes_for;
	__int64* votes_against;
	__int64* vouchers_for;
	__int64* for_voucher_counts;
	__int64* vouchers_against;
	__int64* against_voucher_counts;
	__int64 gold_milligram_value_for;
	__int64 gold_milligram_value_against;

	__int64 source_vtop;
	__int64 source_vcap;
	__int64 title_vtop;
	__int64 title_vcap;
	__int64 description_vtop;
	__int64 description_vcap;
	__int64 media_url_vtop;
	__int64 media_url_vcap;
	__int64 votes_for_vtop;
	__int64 votes_for_vcap;
	__int64 votes_against_vtop;
	__int64 votes_against_vcap;
	__int64 vouchers_for_vtop;
	__int64 vouchers_for_vcap;
	__int64 for_voucher_counts_vtop;
	__int64 for_voucher_counts_vcap;
	__int64 vouchers_against_vtop;
	__int64 vouchers_against_vcap;
	__int64 against_voucher_counts_vtop;
	__int64 against_voucher_counts_vcap;

} Article_V_Option ;

typedef struct Article_V_Convention_tag {

	Article_V_Option* options;
	__int64 interval;
	__int64* votes_for;
	__int64* votes_against;
	__int64* vouchers_for;
	__int64* for_voucher_counts;
	__int64* vouchers_against;
	__int64* against_voucher_counts;
	__int64 gold_milligram_value_for;
	__int64 gold_milligram_value_against;

	__int64 options_vtop;
	__int64 options_vcap;
	__int64 votes_for_vtop;
	__int64 votes_for_vcap;
	__int64 votes_against_vtop;
	__int64 votes_against_vcap;
	__int64 vouchers_for_vtop;
	__int64 vouchers_for_vcap;
	__int64 for_voucher_counts_vtop;
	__int64 for_voucher_counts_vcap;
	__int64 vouchers_against_vtop;
	__int64 vouchers_against_vcap;
	__int64 against_voucher_counts_vtop;
	__int64 against_voucher_counts_vcap;

} Article_V_Convention;

typedef struct Rollback_Article_V_Convention_tag {

	char* source;
	char* title;
	char* description;
	char* media_url;
	__int64 interval;
	__int64* votes_for;
	__int64* votes_against;
	__int64* vouchers_for;
	__int64* for_voucher_counts;
	__int64* vouchers_against;
	__int64* aagainst_voucher_counts;
	__int64 gold_milligram_value_for;
	__int64 gold_milligram_value_against;

	__int64 source_vtop;
	__int64 source_vcap;
	__int64 title_vtop;
	__int64 title_vcap;
	__int64 description_vtop;
	__int64 description_vcap;
	__int64 media_url_vtop;
	__int64 media_url_vcap;
	__int64 votes_for_vtop;
	__int64 votes_for_vcap;
	__int64 votes_against_vtop;
	__int64 votes_against_vcap;
	__int64 vouchers_for_vtop;
	__int64 vouchers_for_vcap;
	__int64 for_voucher_counts_vtop;
	__int64 for_voucher_counts_vcap;
	__int64 vouchers_against_vtop;
	__int64 vouchers_against_vcap;
	__int64 aagainst_voucher_counts_vtop;
	__int64 aagainst_voucher_counts_vcap;

} Rollback_Article_V_Convention;

enum code_classification {
	civil_code, penal_code,
};

typedef struct Bill_tag {

	__int64 id;
	char* title;
	char* description;
	char* media_url;
	code_classification classification;
	bool repeal;
	__int64 interval;
	__int64* votes_for;
	__int64* votes_against;
	__int64* vouchers_for;
	__int64* for_voucher_counts;
	__int64* vouchers_against;
	__int64* against_voucher_counts;
	__int64 gold_milligram_value_for;
	__int64 gold_milligram_value_against;

	__int64 title_vtop;
	__int64 title_vcap;
	__int64 description_vtop;
	__int64 description_vcap;
	__int64 media_url_vtop;
	__int64 media_url_vcap;
	__int64 votes_for_vtop;
	__int64 votes_for_vcap;
	__int64 votes_against_vtop;
	__int64 votes_against_vcap;
	__int64 vouchers_for_vtop;
	__int64 vouchers_for_vcap;
	__int64 for_voucher_counts_vtop;
	__int64 for_voucher_counts_vcap;
	__int64 vouchers_against_vtop;
	__int64 vouchers_against_vcap;
	__int64 against_voucher_counts_vtop;
	__int64 against_voucher_counts_vcap;

} Bill ;

typedef struct Legislative_Session_tag {

	char* title;
	char* description;
	char* media_url;
	__int64 interval;
	Bill* bill;

	__int64 title_vtop;
	__int64 title_vcap;
	__int64 description_vtop;
	__int64 description_vcap;
	__int64 media_url_vtop;
	__int64 media_url_vcap;
	__int64 bill_vtop;
	__int64 bill_vcap;

} Legislative_Session;

typedef struct Law_tag {

	__int64 id;
	char* title;
	char* description;
	char* media_url;
	code_classification classification;
	__int64 valid_start;
	__int64 valid_end;

	__int64 title_vtop;
	__int64 title_vcap;
	__int64 description_vtop;
	__int64 description_vcap;
	__int64 media_url_vtop;
	__int64 media_url_vcap;

} Law;

typedef struct Code_tag {

	Law** laws;

	__int64 laws_vtop;
	__int64 laws_vcap;

} Code;

typedef struct Legal_System_tag {

	Code* civil_code;
	Code* penal_code;

} Legal_System;

typedef struct Gold_Deposit_tag {

	__int64 id;
	__int64 deposit_date;
	__int64 gold_milligram_value;

} Gold_Deposit;

typedef struct Vault_tag {

	Gold_Deposit** gold_deposits;
	__int64* gold_deposits_counts;

	__int64 gold_deposits_vtop;
	__int64 gold_deposits_vcap;
	__int64 gold_deposits_counts_vtop;
	__int64 gold_deposits_counts_vcap;

} Vault;

typedef struct Participant_tag {

	__int64 id;

	__int64* require;
	__int64* bans;
	
	__int64 require_vtop;
	__int64 require_vcap;
	__int64 bans_vtop;
	__int64 bans_vcap;

} Participant;

typedef struct Market_tag {

	ID_Pool* id_pool;
	Barter_System* barter_system;
	Participant** participants;
	Account** accounts;
	Bank** banks;

	__int64 participants_vtop;
	__int64 participants_vcap;
	__int64 accounts_vtop;
	__int64 accounts_vcap;
	__int64 banks_vtop;
	__int64 banks_vcap;

} Market;

typedef struct Trade_Check_tag {

	__int64* vocabumalary_tracker_class;
	__int64* vocabumalary_tracker_id;

	__int64* lst_l;
	__int64* lst_r;

	__int64 vocabumalary_tracker_class_vtop;
	__int64 vocabumalary_tracker_class_vcap;
	__int64 vocabumalary_tracker_id_vtop;
	__int64 vocabumalary_tracker_id_vcap;

	__int64 lst_l_vtop;
	__int64 lst_l_vcap;
	__int64 lst_r_vtop;
	__int64 lst_r_vcap;

} Trade_Check;

typedef struct System_tag {
	Market* market;
	Legal_System* legal_system;
	Vault* vault;
} System;

typedef struct Simp_Queue_tag {

	Trade_Check* data;

	Simp_Queue_tag* next;

} Simp_Queue;

typedef struct SATSolver_tag {

	__int64 n_parm;
	__int64 k_parm;

	__int64 chops;
	__int64 chop;

	__int64 leading_trues;

	bool* Z;				// current state of advancement through search space

	__int64* lst_l_parm;
	__int64* lst_r_parm;

	bool* is_f;
	bool* is_t;

	__int64 lst_l_parm_vtop;
	__int64 lst_l_parm_vcap;
	__int64 lst_r_parm_vtop;
	__int64 lst_r_parm_vcap;
	__int64 is_f_vtop;
	__int64 is_f_vcap;
	__int64 is_t_vtop;
	__int64 is_t_vcap;

} SATSolver;

Article_V_Option** simp_article_v_option_vector_create(__int64 init_sz);
Article_V_Option* simp_article_v_option_vector_read(Article_V_Option** v, __int64 vtop, __int64 vcap, __int64 loc);
void simp_article_v_option_vector_append(Article_V_Option*** v, __int64* vtop, __int64* vcap, Article_V_Option* data);
Voucher** simp_voucher_vector_create(__int64 init_sz);
Voucher* simp_voucher_vector_read(Voucher** v, __int64 vtop, __int64 vcap, __int64 loc);
void simp_voucher_vector_append(Voucher*** v, __int64* vtop, __int64* vcap, Voucher* data);
Account** simp_account_vector_create(__int64 init_sz);
Account* simp_account_vector_read(Account** v, __int64 vtop, __int64 vcap, __int64 loc);
void simp_account_vector_append(Account*** v, __int64* vtop, __int64* vcap, Account* data);
Bank** simp_bank_vector_create(__int64 init_sz);
Bank* simp_bank_vector_read(Bank** v, __int64 vtop, __int64 vcap, __int64 loc);
void simp_bank_vector_append(Bank*** v, __int64* vtop, __int64* vcap, Bank* data);
Offer** simp_offer_vector_create(__int64 init_sz);
Offer* simp_offer_vector_read(Offer** v, __int64 vtop, __int64 vcap, __int64 loc);
void simp_offer_vector_append(Offer*** v, __int64* vtop, __int64* vcap, Offer* data);
Bill** simp_bill_vector_create(__int64 init_sz);
Bill* simp_bill_vector_read(Bill** v, __int64 vtop, __int64 vcap, __int64 loc);
void simp_bill_vector_append(Bill*** v, __int64* vtop, __int64* vcap, Bill* data);
Law** simp_law_vector_create(__int64 init_sz);
Law* simp_law_vector_read(Law** v, __int64 vtop, __int64 vcap, __int64 loc);
void simp_law_vector_append(Law*** v, __int64* vtop, __int64* vcap, Law* data);
Gold_Deposit** simp_gold_deposit_vector_create(__int64 init_sz);
Gold_Deposit* simp_gold_deposit_vector_read(Gold_Deposit** v, __int64 vtop, __int64 vcap, __int64 loc);
void simp_gold_deposit_vector_append(Gold_Deposit*** v, __int64* vtop, __int64* vcap, Gold_Deposit* data);
Participant** simp_participant_vector_create(__int64 init_sz);
Participant* simp_participant_vector_read(Participant** v, __int64 vtop, __int64 vcap, __int64 loc);
void simp_participant_vector_append(Participant*** v, __int64* vtop, __int64* vcap, Participant* data);
char* simp_char_vector_create(__int64 init_sz);
char simp_char_vector_read(char* v, __int64 vtop, __int64 vcap, __int64 loc);
void simp_char_vector_append(char** v, __int64* vtop, __int64* vcap, char data);
__int64* simp_vector_create(__int64 init_sz);
__int64 simp_vector_read(__int64* v, __int64 vtop, __int64 vcap, __int64 loc);
void simp_vector_append(__int64** v, __int64* vtop, __int64* vcap, __int64 data);
void simp_queue_enqueue(Simp_Queue* queue, Simp_Queue* parm);
Simp_Queue* simp_queue_dequeue(Simp_Queue* queue);
Trade_Check* simp_queue_peek(Simp_Queue* queue);
void make_offer(Market* market, __int64 participant_id, __int64* participants_offering, __int64 participants_offering_vtop, __int64 participants_offering_vcap, Voucher* give, __int64 give_vtop, __int64 give_vcap, __int64* give_voucher_counts, __int64 give_voucher_counts_vtop, __int64 give_voucher_counts_vcap, Voucher* receive, __int64 receive_vtop, __int64 receive_vcap, __int64* receive_voucher_counts, __int64 receive_voucher_counts_vtop, __int64 receive_voucher_counts_vcap,
	__int64 valid_start, __int64 valid_end, __int64 subscription_interval, __int64 interval_type, __int64 intervals,
	__int64* insurance_policies_accepted, __int64 insurance_policies_accepted_vtop, __int64 insurance_policies_accepted_vcap, __int64* insurance_policies_applied, __int64 insurance_policies_applied_vtop, __int64 insurance_policies_applied_vcap,
	__int64* participant_exclude, __int64 participant_exclude_vtop, __int64 participant_exclude_vcap, __int64* participant_require, __int64 participant_require_vtop, __int64 participant_require_vcap, __int64* participant_ban, __int64 participant_ban_vtop, __int64 participant_ban_vcap,
	__int64* require, __int64 require_vtop, __int64 require_vcap, __int64* bans, __int64 bans_vtop, __int64 bans_vcap);
void create_require_participant(Market* market, __int64 participant_id, __int64 itm);
void create_require_offer(Market* market, __int64 offer_id, __int64 itm);
void create_ban_participant(Market* market, __int64 participant_id, __int64 itm);
void create_ban_offer(Market* market, __int64 offer_id, __int64 itm);
void remove_require_participant(Market* market, __int64 participant_id, __int64 itm);
void remove_require_offer(Market* market, __int64 offer_id, __int64 itm);
void remove_ban_participant(Market* market, __int64 participant_id, __int64 itm);
void remove_ban_offer(Market* market, __int64 offer_id, __int64 itm);
Offer* create_offer(Market* market, __int64* participants_offering, __int64 participants_offering_vtop, __int64 participants_offering_vcap, Voucher* give, __int64 give_vtop, __int64 give_vcap, __int64* give_voucher_counts, __int64 give_voucher_counts_vtop, __int64 give_voucher_counts_vcap, Voucher* receive, __int64 receive_vtop, __int64 receive_vcap, __int64* receive_voucher_counts, __int64 receive_voucher_counts_vtop, __int64 receive_voucher_counts_vcap,
	__int64 valid_start, __int64 valid_end, __int64 subscription_interval, __int64 interval_type, __int64 intervals,
	__int64* insurance_policies_accepted, __int64 insurance_policies_accepted_vtop, __int64 insurance_policies_accepted_vcap, __int64* insurance_policies_applied, __int64 insurance_policies_applied_vtop, __int64 insurance_policies_applied_vcap,
	__int64* participant_exclude, __int64 participant_exclude_vtop, __int64 participant_exclude_vcap, __int64* participant_require, __int64 participant_require_vtop, __int64 participant_require_vcap, __int64* participant_ban, __int64 participant_ban_vtop, __int64 participant_ban_vcap,
	__int64* require, __int64 require_vtop, __int64 require_vcap, __int64* bans, __int64 bans_vtop, __int64 bans_vcap);
int id_pool_retrieve(__int64* id_pool, __int64* id_pool_vtop, __int64* id_pool_vcap);
void id_pool_submit(__int64* id_pool, __int64* id_pool_vtop, __int64* id_pool_vcap, __int64 id);
__int64 retrieve_voucher_id(ID_Pool* id_pool);
void submit_voucher_id(ID_Pool* id_pool, __int64 id);
__int64 retrieve_account_id(ID_Pool* id_pool);
void submit_account_id(ID_Pool* id_pool, __int64 id);
__int64 retrieve_bank_id(ID_Pool* id_pool);
void submit_bank_id(ID_Pool* id_pool, __int64 id);
__int64 retrieve_offer_id(ID_Pool* id_pool);
void submit_offer_id(ID_Pool* id_pool, __int64 id);
__int64 retrieve_bill_id(ID_Pool* id_pool);
void submit_bill_id(ID_Pool* id_pool, __int64 id);
__int64 retrieve_law_id(ID_Pool* id_pool);
void submit_law_id(ID_Pool* id_pool, __int64 id);
__int64 retrieve_gold_deposit_id(ID_Pool* id_pool);
void submit_gold_deposit_id(ID_Pool* id_pool, __int64 id);
__int64 retrieve_participant_id(ID_Pool* id_pool);
void submit_participant_id(ID_Pool* id_pool, __int64 id);
Offer** create_offers();
Participant* create_participant(Market* market);
Account* create_account(Market* market, __int64 gold_milligram_balance, __int64* holdings, __int64* voucher_counts, __int64 vouchers_vtop, __int64 vouchers_vcap, __int64 voucher_counts_vtop, __int64 voucher_counts_vcap);
Bank* create_bank(Market* market, __int64* accounts, __int64* account_holders, __int64 accounts_vtop, __int64 accounts_vcap, __int64 account_holders_vtop, __int64 account_holders_vcap);
Barter_System* create_barter_system();
Market* create_market();
ID_Pool* create_id_pool();
System* create_system();
Trade_Check* create_trade_check(Market* market);
void check_trade(SATSolver** s, Trade_Check* trade_check, bool** sln, bool repeat);
bool* SATSolver_create_boundary(bool begin, __int64 chop, __int64 offs, __int64 n, __int64 leading_trues);
void SATSolver_create(SATSolver*** s, __int64* lst_l_parm, __int64* lst_r_parm, __int64 k_parm, __int64 n_parm);
void SATSolver_destroy(SATSolver*** s);
bool SATSolver_isSat(SATSolver* s, bool* sln);
void thread_2SAT(bool* arr, bool* is_sat, __int64* lst_l_parm, __int64* lst_r_parm, __int64 k_parm, __int64 n_parm, bool* is_f, bool* is_t, __int64 chops, __int64 chop, __int64 leading_trues);
bool SATSolver_threads(bool* arr, bool* is_sat, __int64* lst_l_parm, __int64* lst_r_parm, __int64 k_parm, __int64 n_parm, bool* is_f, bool* is_t, __int64 chops, __int64 chop, __int64 leading_trues);

#endif