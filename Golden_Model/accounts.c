#include "accounts.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//account_t *Accounts_DB[DB_SIZE] ;
void readAccounts(account_t ** Accounts_DB,uint8_t DB_SIZE)
{
	FILE *filepointer = fopen("DataBase.txt", "r");
	for (int i = 0; i < DB_SIZE; i++){
		Accounts_DB[i] = (account_t *) malloc(sizeof(account_t));
		fscanf(filepointer, "%f,%s,%s", &(Accounts_DB[i]->Balance), Accounts_DB[i]->primaryAccountNumber,Accounts_DB[i]->PIN);
	}

	// fclose(filepointer);
	// filepointer = fopen("Declined_accounts.txt","r");
	// for(int i = 0;i<DB_SIZE||filepointer==EOF;i++){
	// 	Declined_Accouns[i] = (account_t*) malloc(sizeof(account_t));
	// 	fscanf(filepointer, "%s", Declined_Accouns[i]->primaryAccountNumber);
	// }
	fclose(filepointer);
}
/*****************************/
void updateAccounts(account_t ** Accounts_DB,uint8_t DB_SIZE)
{
	FILE *filepointer = fopen("DataBase.txt", "w");
	for (int i = 0; i < DB_SIZE; i++)
	{
		fprintf(filepointer, "%f,%s\n", Accounts_DB[i]->Balance, Accounts_DB[i]->primaryAccountNumber,Accounts_DB[i]->PIN);
	}
	fclose(filepointer);
}

uint8_t findAccount(account_t **Accounts_DB,uint8_t DB_SIZE,account_t *rat){
	uint8_t *PAN = rat->PIN;
	for(uint8_t i=0;i<DB_SIZE;i++)
	{
		if(!strcmp(Accounts_DB[i]->primaryAccountNumber,PAN))
			return i;
	}
	return -1;
}