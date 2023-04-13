typedef unsigned char uint8_t;
typedef unsigned int uint32_t; 
typedef unsigned short uint16_t;

typedef struct account_t
{
	double Balance;
	uint8_t primaryAccountNumber[21];
    uint8_t PIN[4];
}account_t;

void readAccounts(account_t**,uint8_t);
void updateAccounts(account_t**,uint8_t);
