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

typedef struct Article_V_Convention_tag {

	char* source;
	char* title;
	char* description;
	char* media_url;
	__int64 interval;
	__int64 votes_for;
	__int64 votes_against;
	__int64 gold_microgram_value_for;
	__int64 gold_microgram_value_against;

} Article_V_Convention ;

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

	char* title;
	char* description;
	char* media_url;
	__int64 interval;
	__int64 votes_for;
	__int64 votes_against;
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

	char* title;
	char* description;
	char* media_url;
	__int64 valid_start;
	__int64 valid_end;

} Law;

typedef struct Code_tag {

	Law* laws;

} Code;

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

	__int64 n;
	__int64 k;

	__int64 chops;

	__int64 leading_trues;

	bool* Z;				// current state of advancement through search space

	__int64* inopcell_l;	// instance operation cell left
	__int64* inopcell_m;	// instance operation cell middle
	__int64* inopcell_r;	// instance operation cell right

	__int64** cdopcelll_f;	// encoding operation cell left, false
	__int64** cdopcellr_f;	// encoding operation cell right, false

	__int64* cdol_vtop_f;	// vector top, left, false
	__int64* cdol_vcap_f;	// vector capacity, left, false

	__int64* cdor_vtop_f;	// vector top, right, false
	__int64* cdor_vcap_f;	// vector capacity, right, false

	__int64** cdopcelll_t;	// encoding operation cell right, true
	__int64** cdopcellr_t;	// encoding operation cell right, true

	__int64* cdol_vtop_t;	// vector top, left, true
	__int64* cdol_vcap_t;	// vector capacity, left, true

	__int64* cdor_vtop_t;	// vector top, right, true
	__int64* cdor_vcap_t;	// vector capacity, right, true

	__int64* cd_sizes_f;	// sizes of encodings, false
	__int64* cd_sizes_t;	// sizes of encodings, true

} SATSolver;

char* simp_char_vector_create(__int64 init_sz);
char simp_char_vector_read(char* v, __int64 vtop, __int64 vcap, __int64 loc);
void simp_char_vector_append(char** v, __int64* vtop, __int64* vcap, __int64 data);
__int64* simp_vector_create(__int64 init_sz);
__int64 simp_vector_read(__int64* v, __int64 vtop, __int64 vcap, __int64 loc);
void simp_vector_append(__int64** v, __int64* vtop, __int64* vcap, __int64 data);
void simp_queue_enqueue(Simp_Queue* queue, Simp_Queue* parm);
Simp_Queue* simp_queue_dequeue(Simp_Queue* queue);
void SATSolver_create(SATSolver* s, __int64** lst, __int64 k, __int64 n, __int64 chops, __int64 chop, __int64 leading_trues);
void SATSolver_destroy(SATSolver* s);
bool SATSolver_isSat(SATSolver* s, bool* sln);
void thread_2SAT(bool* arr, bool* is_sat, __int64** lst, __int64 k_parm, __int64 n_parm, __int64 chops, __int64 chop, __int64 leading_trues);
bool SATSolver_threads(__int64** lst, __int64 k_parm, __int64 n_parm, bool* arr, __int64 leading_trues);



#endif