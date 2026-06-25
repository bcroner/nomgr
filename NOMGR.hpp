#ifndef __NOMGR_H__
#define __NOMGR_H__

#define TRUE_2SAT 1
#define FALSE_2SAT -1

typedef struct ID_Pool_tag {

	__int64* vouchers;
	__int64* accounts;
	__int64* banks;
	__int64* offers;
	__int64* bills;
	__int64* laws;
	__int64* gold_deposits;
	__int64* participants;

	__int64 vouchers_vtop;
	__int64 vouchers_vcap;
	__int64 accounts_vtop;
	__int64 accounts_vcap;
	__int64 banks_vtop;
	__int64 banks_vcap;
	__int64 offers_vtop;
	__int64 offers_vcap;
	__int64 bills_vtop;
	__int64 bills_vcap;
	__int64 laws_vtop;
	__int64 laws_vcap;
	__int64 gold_deposits_vtop;
	__int64 gold_deposits_vcap;
	__int64 participants_vtop;
	__int64 participants_vcap;

} ID_Pool;

typedef struct Voucher_tag {

	__int64 id;
	char* title;
	char* description;
	char* media_url;
	__int64 valid_start;
	__int64 valid_end;
	__int64 subscription_interval;
	__int64 interval_type;
	__int64 intervals;
	__int64 gold_microgram_value;

	__int64 title_vtop;
	__int64 title_vcap;
	__int64 description_vtop;
	__int64 description_vcap;
	__int64 media_url_vtop;
	__int64 media_url_vcap;

} Voucher;

typedef struct Account_tag {

	__int64 id;
	__int64 gold_microgram_balance;
	Voucher* vouchers;
	__int64* voucher_counts;
	__int64 vouchers_vtop;
	__int64 vouchers_vcap;
	__int64 voucher_counts_vtop;
	__int64 voucher_counts_vcap;
} Account;

typedef struct Bank_tag {

	__int64 id;

	Account* accounts;
	Participant** account_holders;

	__int64 accounts_vtop;
	__int64 accounts_vcap;
	__int64 account_holders_vtop;
	__int64 account_holders_vcap;

} Bank;

typedef struct Voucher_System_tag {

	Voucher* vouchers;
	__int64* voucher_counts;

	__int64 vouchers_vtop;
	__int64 vouchers_vcap;
	__int64 voucher_counts_vtop;
	__int64 voucher_counts_vcap;

} Voucher_System;

typedef struct Offer_tag {

	__int64 id;

	Voucher* gives;
	__int64* gives_voucher_counts;
	Voucher* receives;
	__int64* receives_voucher_counts;
	__int64 gives_gold_microgram_value;
	__int64 receives_gold_microgram_value;
	__int64 valid_start;
	__int64 valid_end;
	__int64 subscription_interval;
	__int64 interval_type;
	__int64 intervals;
	__int64* insurance_policies_accepted;
	__int64* insurance_policies_required;
	__int64* insurance_policies_applied;
	__int64* require;
	__int64* bans;

	__int64 gives_vtop;
	__int64 gives_vcap;
	__int64 gives_voucher_counts_vtop;
	__int64 gives_voucher_counts_vcap;
	__int64 receives_vtop;
	__int64 receives_vcap;
	__int64 receive_voucher_counts_vtop;
	__int64 receive_voucher_counts_vcap;
	__int64 insurance_policies_accepted_vtop;
	__int64 insurance_policies_accepted_vcap;
	__int64 insurance_policies_required_vtop;
	__int64 insurance_policies_required_vcap;
	__int64 insurance_policies_applied_vtop;
	__int64 insurance_policies_applied_vcap;
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

typedef struct Offer_Triggered_Trade_Queue_tag {

	__int64* offers;

	__int64 offers_vtop;
	__int64 offers_vcap;
	
} Offer_Triggered_Trade_Queue;

typedef struct Article_V_Option_tag {

	char* source;
	char* title;
	char* description;
	char* media_url;
	__int64* votes_for;
	__int64* votes_against;
	Voucher* vouchers_for;
	__int64* for_voucher_counts;
	Voucher* vouchers_against;
	__int64* against_voucher_counts;
	__int64 gold_microgram_value_for;
	__int64 gold_microgram_value_against;

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
	Voucher* vouchers_for;
	__int64* for_voucher_counts;
	Voucher* vouchers_against;
	__int64* against_voucher_counts;
	__int64 gold_microgram_value_for;
	__int64 gold_microgram_value_against;

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
	Voucher* vouchers_for;
	__int64* for_voucher_counts;
	Voucher* vouchers_against;
	__int64* aagainst_voucher_counts;
	__int64 gold_microgram_value_for;
	__int64 gold_microgram_value_against;

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

typedef struct Bill_tag {

	__int64 id;
	char* title;
	char* description;
	char* media_url;
	__int64 classification;
	__int64 repeal_id;
	__int64 interval;
	__int64* votes_for;
	__int64* votes_against;
	Voucher* vouchers_for;
	__int64* for_voucher_counts;
	Voucher* vouchers_against;
	__int64* against_voucher_counts;
	__int64 gold_microgram_value_for;
	__int64 gold_microgram_value_against;

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
	__int64 classification;
	__int64 repeal_id;
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
	__int64 gold_microgram_value;

} Gold_Deposit;

typedef struct Vault_tag {

	Gold_Deposit** gold_deposits;
	__int64* gold_deposits_counts;

	__int64* gold_deposits_vtop;
	__int64* gold_deposits_vcap;
	__int64* gold_deposits_counts_vtop;
	__int64* gold_deposits_counts_vcap;

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

	__int64* lst_l;
	__int64* lst_r;

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

	__int64 data;

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

	__int64* lst_l_parm_vtop;
	__int64* lst_l_parm_vcap;
	__int64* lst_r_parm_vtop;
	__int64* lst_r_parm_vcap;
	__int64* is_f_vtop;
	__int64* is_f_vcap;
	__int64* is_t_vtop;
	__int64* is_t_vcap;

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
void create_require_participant(Market* market, __int64 participant_id, __int64 itm);
void create_require_offer(Market* market, __int64 offer_id, __int64 itm);
void create_ban_participant(Market* market, __int64 participant_id, __int64 itm);
void create_ban_offer(Market* market, __int64 offer_id, __int64 itm);
void remove_require_participant(Market* market, __int64 participant_id, __int64 itm);
void remove_require_offer(Market* market, __int64 offer_id, __int64 itm);
void remove_ban_participant(Market* market, __int64 participant_id, __int64 itm);
void remove_ban_offer(Market* market, __int64 offer_id, __int64 itm);
Offer* create_offer(__int64 id, Voucher* give, __int64 give_vtop, __int64 give_vcap, __int64* give_voucher_counts, __int64 give_voucher_counts_vtop, __int64 give_voucher_counts_vcap, Voucher* receive, __int64 receive_vtop, __int64 receive_vcap, __int64 receive_voucher_counts, __int64 receive_voucher_counts_vtop, __int64 receive_voucher_counts_vcap,
	__int64 valid_start, __int64 valid_end, __int64 subscription_interval, __int64 interval_type, __int64 intervals,
	__int64* insurance_policies_accepted, __int64 insurance_policies_accepted_vtop, __int64 insurance_policies_accepted_vcap, __int64* insurance_policies_applied, __int64 insurance_policies_applied_vtop, __int64 insurance_policies_applied_vcap,
	__int64* participant_exclude, __int64 participant_exclude_vtop, __int64 participant_exclude_vcap, __int64* participant_require, __int64 participant_require_vtop, __int64 participant_require_vcap, __int64* participant_ban, __int64 participant_ban_vtop, __int64 participant_ban_vcap,
	__int64* require, __int64 require_vtop, __int64 require_vcap, __int64* ban, __int64 ban_vtop, __int64 ban_vcap);
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
Account* create_account(Market* market, __int64 gold_microgram_balance, Voucher* vouchers, __int64* voucher_counts, __int64 vouchers_vtop, __int64 vouchers_vcap, __int64 voucher_counts_vtop, __int64 voucher_counts_vcap);
Bank* create_bank(Market* market, Account* accounts, Participant** account_holders, __int64 accounts_vtop, __int64 accounts_vcap, __int64 account_holders_vtop, __int64 account_holders_vcap);
Barter_System* create_barter_system();
Market* create_market();
ID_Pool* create_id_pool();
System* create_system();
Trade_Check* create_trade_check(Market* market);
bool check_trade(SATSolver* s, Trade_Check* trade_check);
bool* SATSolver_create_boundary(bool begin, __int64 chop, __int64 offs, __int64 n, __int64 leading_trues);
void SATSolver_create(SATSolver*** s, __int64* lst_l_parm, __int64* lst_r_parm, __int64 k_parm, __int64 n_parm);
void SATSolver_destroy(SATSolver*** s);
bool SATSolver_isSat(SATSolver* s, bool* sln);
void thread_2SAT(bool* arr, bool* is_sat, __int64* lst_l_parm, __int64* lst_r_parm, __int64 k_parm, __int64 n_parm, bool* is_f, bool* is_t, __int64 chops, __int64 chop, __int64 leading_trues);
bool SATSolver_threads(bool* arr, bool* is_sat, __int64* lst_l_parm, __int64* lst_r_parm, __int64 k_parm, __int64 n_parm, bool* is_f, bool* is_t, __int64 chops, __int64 chop, __int64 leading_trues);

#endif