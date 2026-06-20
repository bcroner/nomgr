#ifndef __NOMGR_H__
#define __NOMGR_H__

#define TRUE_2SAT 1
#define FALSE_2SAT -1

typedef struct Voucher_tag {

	__int64 id;
	char* title;
	char* description;
	char* media_url;
	__int64 valid_start;
	__int64 valid_end;
	__int64 gold_microgram_value;

} Voucher;

typedef struct Voucher_System_tag {

	Voucher* vouchers;

} Voucher_System;

typedef struct Offer_tag {

	Voucher* give;
	Voucher* receive;
	__int64 give_gold_microgram_value;
	__int64 receive_gold_microgram_value;
	__int64 valid_start;
	__int64 valid_end;

} Offer;

typedef struct Barter_System_tag {

	Offer* offers;

};

typedef struct Offer_Triggered_Trade_Queue_tag {

	__int64* offers;
	
} Offer_Triggered_Trade_Queue;

typedef struct Article_V_Option_tag {

	char* source;
	char* title;
	char* description;
	char* media_url;
	__int64 votes_for;
	__int64 votes_against;
	__int64 gold_microgram_value_for;
	__int64 gold_microgram_value_against;

} Article_V_Option ;

typedef struct Article_V_Convention_tag {

	Article_V_Option* options;
	__int64 interval;
	__int64 votes_for;
	__int64 votes_against;
	__int64 gold_microgram_value_for;
	__int64 gold_microgram_value_against;

} Article_V_Convention_System;

typedef struct Rollback_Article_V_Convention_tag {

	char* source;
	char* title;
	char* description;
	char* media_url;
	__int64 interval;
	__int64 votes_for;
	__int64 votes_against;
	__int64 gold_microgram_value_for;
	__int64 gold_microgram_value_against;

} Rollback_Article_V_Convention;

typedef struct Bill_tag {

	__int64 id;
	char* title;
	char* description;
	char* media_url;
	__int64 classification;
	__int64 repeal_id;
	__int64 interval;
	__int64 votes_for;
	__int64 votes_against;
	Voucher* vouchers_for;
	Voucher* vouchers_against;
	__int64 gold_microgram_value_for;
	__int64 gold_microgram_value_against;

} Bill ;

typedef struct Legislative_Session_tag {

	char* title;
	char* description;
	char* media_url;
	__int64 interval;
	Bill* bill;

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

} Law;

typedef struct Code_tag {

	Law* laws;

} Code;

typedef struct Legal_System_tag {

	Code civil_code;
	Code penal_code;

} Legal_System;

typedef struct Gold_Deposit_tag {

	__int64 id;
	__int64 deposit_date;
	__int64 gold_microgram_value;

} Gold_Deposit;

typedef struct Vault_tag {

	Gold_Deposit* gold_deposits;

} Vault;

typedef struct Simp_Queue_tag {

	__int64 data;

	Simp_Queue_tag* next;

} Simp_Queue;

typedef struct SATSolver_tag {

	__int64 n_parm;
	__int64 k_parm;

	__int64 chops;

	__int64 leading_trues;

	bool* Z;				// current state of advancement through search space

	__int64* lst_l_parm;
	__int64* lst_r_parm;

	bool* is_f;
	bool* is_t;

} SATSolver;

Article_V_Option* simp_article_v_option_vector_create(__int64 init_sz);
Article_V_Option* simp_article_v_option_vector_read(Article_V_Option** v, __int64 vtop, __int64 vcap, __int64 loc);
void simp_article_v_option_vector_append(Article_V_Option*** v, __int64* vtop, __int64* vcap, Article_V_Option* data);
Voucher* simp_voucher_vector_create(__int64 init_sz);
Voucher* simp_voucher_vector_read(Voucher** v, __int64 vtop, __int64 vcap, __int64 loc);
void simp_voucher_vector_append(Voucher*** v, __int64* vtop, __int64* vcap, Voucher* data);
Offer* simp_offer_vector_create(__int64 init_sz);
Offer* simp_offer_vector_read(Offer** v, __int64 vtop, __int64 vcap, __int64 loc);
void simp_offer_vector_append(Offer*** v, __int64* vtop, __int64* vcap, Offer* data);
Bill* simp_bill_vector_create(__int64 init_sz);
Bill* simp_bill_vector_read(Bill** v, __int64 vtop, __int64 vcap, __int64 loc);
void simp_bill_vector_append(Bill*** v, __int64* vtop, __int64* vcap, Bill* data);
Law* simp_law_vector_create(__int64 init_sz);
Law* simp_law_vector_read(Law** v, __int64 vtop, __int64 vcap, __int64 loc);
void simp_law_vector_append(Law*** v, __int64* vtop, __int64* vcap, Law* data);
Gold_Deposit* simp_gold_deposit_vector_create(__int64 init_sz);
Gold_Deposit* simp_gold_deposit_vector_read(Gold_Deposit** v, __int64 vtop, __int64 vcap, __int64 loc);
void simp_gold_deposit_vector_append(Gold_Deposit*** v, __int64* vtop, __int64* vcap, Gold_Deposit* data);
char* simp_char_vector_create(__int64 init_sz);
char simp_char_vector_read(char* v, __int64 vtop, __int64 vcap, __int64 loc);
void simp_char_vector_append(char** v, __int64* vtop, __int64* vcap, char data);
__int64* simp_vector_create(__int64 init_sz);
__int64 simp_vector_read(__int64* v, __int64 vtop, __int64 vcap, __int64 loc);
void simp_vector_append(__int64** v, __int64* vtop, __int64* vcap, __int64 data);
void simp_queue_enqueue(Simp_Queue* queue, Simp_Queue* parm);
Simp_Queue* simp_queue_dequeue(Simp_Queue* queue);
bool* SATSolver_create_boundary(bool begin, __int64 chop, __int64 offs, __int64 n, __int64 leading_trues);
void SATSolver_create(SATSolver* s, __int64* lst_l_parm, __int64* lst_r_parm, __int64 k_parm, __int64 n_parm, bool* is_f, bool* is_t, __int64 chops, __int64 chop, __int64 leading_trues);
void SATSolver_destroy(SATSolver* s);
bool SATSolver_isSat(SATSolver* s, bool* sln);
void thread_2SAT(bool* arr, bool* is_sat, __int64* lst_l_parm, __int64* lst_r_parm, __int64 k_parm, __int64 n_parm, bool* is_f, bool* is_t, __int64 chops, __int64 chop, __int64 leading_trues);
bool SATSolver_threads(bool* arr, bool* is_sat, __int64* lst_l_parm, __int64* lst_r_parm, __int64 k_parm, __int64 n_parm, bool* is_f, bool* is_t, __int64 chops, __int64 chop, __int64 leading_trues);



#endif