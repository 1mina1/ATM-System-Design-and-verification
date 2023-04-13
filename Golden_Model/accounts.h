typedef unsigned char uint8_t;
typedef unsigned int uint32_t; 
typedef unsigned short uint16_t;

typedef struct account_t
{
	double Balance;
	uint8_t primaryAccountNumber[21];
    uint8_t PIN[4];
}account_t;
//Accounts_DB is an array of pointers each one points to a struct of type account_t in the heap
//DB_SIZE is the number of accounts in the database
//rat is a pointer to in structure of type account in the heap.



void readAccounts(account_t**Accounts_DB,uint8_t DB_SIZE);
void updateAccounts(account_t**Accounts_DB,uint8_tDB_SIZE);

//returns the index of the required account in the database.
//returns -1 if account notfound.
uint8_t findAccount(account_t **Accounts_DB,uint8_t DB_SIZE,account_t *rat);