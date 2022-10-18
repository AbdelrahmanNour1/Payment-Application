#include "server.h"

ST_accountsDB_t accountsDB[255] = {
{2000.0, RUNNING, "8989374615436851"},
{1000.0, RUNNING, "8655528868743589"},
{20000.0, RUNNING, "3563265054334620"},
{15000.0, RUNNING, "7430146671520005"},
{3000.0, RUNNING, "2509644955896265"},
{12000.0, RUNNING, "2261720121476435"},
{50000.0, RUNNING, "7083316739255270"},
{23000.0, RUNNING, "0830510118542554"},
{22000.0, BLOCKED, "0631250670916654"},
{5000.0, BLOCKED, "5168279500002554"},
};
ST_transaction_t transDB[255] = { {{"Mohamed Abdelmoniem Amr","8989374615436851","02/25" }, {1000, 10000, "02/05/2026"},APPROVED,1 }
,{ { "Mohamed Mostafa Ahmed","5168279500002554","06/28" }, { 12000, 10000, "01/11/2030" }, APPROVED, 2 }};
int index = 2;
int check = 0;

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	struct ST_cardData_t c = transData->cardHolderData;
	struct ST_cardData_t* cptr = &c;
	struct ST_terminalData_t t = transData->terminalData;
	struct ST_terminalData_t* tptr = &t;
	struct ST_accountsDB_t p = { 0,RUNNING,"" };
	struct ST_accountsDB_t* pptr = &p;
	EN_serverError_t x,y,z;
	y = isValidAccount(cptr, pptr);
	if (y == ACCOUNT_NOT_FOUND)
	{
		printf("FRAUD_CARD\n");
		return FRAUD_CARD;
	}
	z = isBlockedAccount(pptr);
	if (z == BLOCKED_ACCOUNT)
	{
		printf("DECLINED_STOLEN_CARD\n");
		return DECLINED_STOLEN_CARD;
	}
	x = isAmountAvailable(tptr, pptr);
	if (x == LOW_BALANCE)
	{

		printf("DECLINED_INSUFFECIENT_FUND\n");
		return DECLINED_INSUFFECIENT_FUND;
	}
	if (index == 254)
	{

		printf("INTERNAL_SERVER_ERROR\n");
		return INTERNAL_SERVER_ERROR;
	}
	else
	{
		pptr->balance = pptr->balance - tptr->transAmount;
		printf("APPROVED\n");
		return APPROVED;
	}
	





}
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
	int length = sizeof(accountsDB) / sizeof(accountsDB[0]);
	int flag = 0;
	for (int i = 0; i < length; i++) {
		if (strcmp(cardData->primaryAccountNumber, accountsDB[i].primaryAccountNumber) == 0) {
			flag++;
			check = i;
		}
	}
	if (flag == 1) {
		printf("SERVER_OK\n");
		*accountRefrence = accountsDB[check];
		return SERVER_OK;
	}
	else {
		printf("ACCOUNT_NOT_FOUND\n");
		accountRefrence = NULL;
		return ACCOUNT_NOT_FOUND;
		
	}
}
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
	if(accountRefrence->state == RUNNING)
	{
		printf("SERVER_OK\n");
		return SERVER_OK;
	}
	else
	{
		printf("BLOCKED_ACCOUNT\n");
		return BLOCKED_ACCOUNT;
	}
}
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence)
{
	if (termData->transAmount <= accountRefrence->balance)
	{
		printf("SERVER_OK\n");
		return SERVER_OK;
	}
	else
	{
		printf("LOW_BALANCE\n");
		return LOW_BALANCE;
	}
}
EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	int n = index++;
	transDB[n].cardHolderData = transData->cardHolderData;
	transDB[n].terminalData = transData->terminalData;
	transDB[n].transState = recieveTransactionData(transData);
	transDB[n].transactionSequenceNumber = n + 1;
	printf("SERVER_OK\n");
	return SERVER_OK;


}
void listSavedTransactions(void)
{
	for (int i = 0; i < index; i++)
	{
		printf("#########################\n");
		printf("Transaction Sequence Number: \n");
		printf("%d\n", transDB[i].transactionSequenceNumber);
		printf("Transaction Date: \n");
		printf("%s\n", transDB[i].terminalData.transactionDate);
		printf("Transaction Amount: \n");
		printf("%f\n", transDB[i].terminalData.transAmount);
		printf("Transaction State: \n");
		if (transDB[i].transState == INTERNAL_SERVER_ERROR)
		{
			printf("INTERNAL_SERVER_ERROR\n");
		}
		else if (transDB[i].transState == FRAUD_CARD)
		{
			printf("FRAUD_CARD\n");
		}
		else if (transDB[i].transState == DECLINED_STOLEN_CARD)
		{
			printf("DECLINED_STOLEN_CARD\n");
		}
		else if (transDB[i].transState == DECLINED_INSUFFECIENT_FUND)
		{
			printf("DECLINED_INSUFFECIENT_FUND\n");
		}
		else
		{
			printf("APPROVED\n");
		}
		printf("Terminal Max Amount: \n");
		printf("%f\n", transDB[i].terminalData.maxTransAmount);
		printf("Cardholder Name: \n");
		printf("%s\n", transDB[i].cardHolderData.cardHolderName);
		printf("PAN: \n");
		printf("%s\n", transDB[i].cardHolderData.primaryAccountNumber);
		printf("Card Expiration Date: \n");
		printf("%s\n", transDB[i].cardHolderData.cardExpirationDate);
		printf("#########################\n");
	}
}

void isValidAccountTest(void)
{
	struct ST_cardData_t c = { "", "8989374615436851", "" };
	struct ST_cardData_t* cptr = &c;
	struct ST_accountsDB_t p = { 0,RUNNING,"" };
	struct ST_accountsDB_t* pptr = &p;
	printf("Tester Name: Abdelrahman Mohamed Nour\n");
	printf("Function Name: isCardExpried\n");
	printf("Test Case 1:\n");
	printf("Input Data: PAN Is 8989374615436851 which is present in the database");
	printf("Expected Result: SERVER_OK\n");
	printf("Actual Result: ");
	isValidAccount(cptr, pptr);
	printf("\n");
	struct ST_cardData_t k = { "", "8989374615436811", "" };
	struct ST_cardData_t* kptr = &k;
	struct ST_accountsDB_t y = { 0,RUNNING,"" };
	struct ST_accountsDB_t* yptr = &y;
	printf("Test Case 2:\n");
	printf("Input Data: PAN Is 8989374615436811 which is not in the database\n");
	printf("Expected Result: ACCOUNT_NOT_FOUND\n");
	printf("Actual Result: ");
	isValidAccount(kptr, yptr);
	printf("\n");
}
void isBlockedAccountTest(void)
{
	struct ST_accountsDB_t p = { 0,RUNNING,"" };
	struct ST_accountsDB_t* pptr = &p;
	printf("Tester Name: Abdelrahman Mohamed Nour\n");
	printf("Function Name: isBlockedAccount\n");
	printf("Test Case 1:\n");
	printf("Input Data: Account state is running\n");
	printf("Expected Result: SERVER_OK\n");
	printf("Actual Result: ");
	isBlockedAccount(pptr);
	printf("\n");
	struct ST_accountsDB_t y = { 0,BLOCKED,"" };
	struct ST_accountsDB_t* yptr = &y;
	printf("Test Case 2:\n");
	printf("Input Data: account state is blocked\n");
	printf("Expected Result: BLOCKED_ACCOUNT\n");
	printf("Actual Result: ");
	isBlockedAccount(yptr);
	printf("\n");
}
void isAmountAvailableTest(void)
{
	struct ST_accountsDB_t p = { 1000,RUNNING,"" };
	struct ST_accountsDB_t* pptr = &p;
	struct ST_terminalData_t c = { 500,1000,"" };
	struct ST_terminalData_t* cptr = &c;
	printf("Tester Name: Abdelrahman Mohamed Nour\n");
	printf("Function Name: isAmountAvailable\n");
	printf("Test Case 1:\n");
	printf("Input Data: transaction amount is lower than balance\n");
	printf("Expected Result: SERVER_OK\n");
	printf("Actual Result: ");
	isAmountAvailable(cptr,pptr);
	printf("\n");
	struct ST_accountsDB_t y = { 1000,RUNNING,"" };
	struct ST_accountsDB_t* yptr = &y;
	struct ST_terminalData_t t = { 2000,1000,"" };
	struct ST_terminalData_t* tptr = &t;
	printf("Test Case 2:\n");
	printf("Input Data: transaction amount is higher than balance\n");
	printf("Expected Result: LOW_BALANCE\n");
	printf("Actual Result: ");
	isAmountAvailable(tptr, yptr);
	printf("\n");
}
void recieveTransactionDataTest(void) 
{
	ST_transaction_t trans = { {"","8989374615436851","" }, {0, 0, ""},APPROVED,0 };
	ST_transaction_t* transptr = &trans;
	printf("Tester Name: Abdelrahman Mohamed Nour\n");
	printf("Function Name: recieveTransactionData\n");
	printf("Test Case 1:\n");
	printf("Input Data: Account is valid and running and amount is correct\n");
	printf("Expected Result: APPROVED\n");
	printf("Actual Result: ");
	recieveTransactionData(transptr);
	printf("\n");
	ST_transaction_t p = { {"","5168279500002554","" }, {0, 0, ""},APPROVED,0 };
	ST_transaction_t* pptr = &p;
	printf("Test Case 2:\n");
	printf("Input Data: account is valid but it's stolen\n");
	printf("Expected Result: DECLINED_STOLEN_CARD\n");
	printf("Actual Result: ");
	recieveTransactionData(pptr);
	printf("\n");
}
void saveTransactionTest(void)
{
	ST_transaction_t trans = { { "Mohamed Mostafa Ahmed","8989374615436851","06/28" }
	, { 2000, 10000, "01/11/2030" }
	, APPROVED
		, 0 };
	ST_transaction_t* transptr = &trans;
	printf("Tester Name: Abdelrahman Mohamed Nour\n");
	printf("Function Name: saveTransaction\n");
	printf("Test Case 1:\n");
	printf("Input Data: Account is valid and running and amount is correct\n");
	printf("Expected Result: SERVER_OK\n");
	printf("Actual Result: ");
	saveTransaction(transptr);
	printf("\n");
}
void listSavedTransactionsTest(void)
{
	printf("Tester Name: Abdelrahman Mohamed Nour\n");
	printf("Function Name: listSavedTransactionsn");
	printf("Test Case 1:\n");
	printf("Input Data: I put random 2 transactions to print");
	printf("Expected Result: printed succesfully\n");
	printf("Actual Result: ");
	listSavedTransactions();
}