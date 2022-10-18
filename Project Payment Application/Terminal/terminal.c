#include "terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	int length;
	char s[11];
	printf("Please enter your transaction date:\n");
	scanf("%[^\n]%*c", s);
	length = strlen(s);
	if (s == NULL || length < 10 || s[2] != '/' || s[5] != '/' || s[3] > '1' || (s[3] == '1' && s[4] > '2'))
	{
		printf("WRONG_DATE\n");
		return WRONG_DATE;
	}
	else {

		strcpy(termData->transactionDate, s);
		printf("TERMINAL_OK\n");
		return TERMINAL_OK;
	}

}
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
	if (cardData->cardExpirationDate[3] < termData->transactionDate[8] || (cardData->cardExpirationDate[3] == termData->transactionDate[8]
		&& cardData->cardExpirationDate[4] < termData->transactionDate[9]) || (cardData->cardExpirationDate[3] == termData->transactionDate[8]
			&& cardData->cardExpirationDate[4] == termData->transactionDate[9] && cardData->cardExpirationDate[0] < termData->transactionDate[3])
		|| (cardData->cardExpirationDate[3] == termData->transactionDate[8] && cardData->cardExpirationDate[4] == termData->transactionDate[9]
			&& cardData->cardExpirationDate[0] == termData->transactionDate[3] && cardData->cardExpirationDate[1] < termData->transactionDate[4]))
	{

		printf("EXPIRED_CARD\n");
		return EXPIRED_CARD;
	}
	else {

		printf("TERMINAL_OK\n");
		return TERMINAL_OK;
	}


}
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	float i = 0;
	printf("Please enter your transaction amount:\n");
	scanf("%f", &i);
	if (i <= 0)
	{
		printf("INVALID_AMOUNT\n");
		return INVALID_AMOUNT;
	}
	else {

		termData->transAmount = i;
		printf("TERMINAL_OK\n");
		return TERMINAL_OK;
	}


}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if (termData->transAmount > termData->maxTransAmount)
	{
		printf("EXCEED_MAX_AMOUNT\n");
		return EXCEED_MAX_AMOUNT;
	}
	else {
		printf("TERMINAL_OK\n");
		return TERMINAL_OK;
	}
}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount)
{
	printf("Enter maximum allowed transaction amount:\n");
	scanf("%f", &maxAmount);
	if (maxAmount <= 0)
	{
		printf("INVALID_MAX_AMOUNT\n");
		return INVALID_MAX_AMOUNT;
	}
	else {

		termData->maxTransAmount = maxAmount;
		printf("TERMINAL_OK\n");
		return TERMINAL_OK;
	}
}

void getTransactionDateTest(void)
{
	struct ST_terminalData_t c = { 0, 0, "" };
	struct ST_terminalData_t* cptr = &c;
	printf("Tester Name: Abdelrahman Mohamed Nour\n");
	printf("Function Name: getTransactionDate\n");
	printf("Test Case 1:\n");
	printf("Input Data: 05/02/2022\n");
	printf("Expected Result: TERMINAL_OK\n");
	printf("Actual Result: ");
	getTransactionDate(cptr);
	printf("\n");
	printf("Test Case 2:\n");
	printf("Input Data: 02/30/2025\n");
	printf("Expected Result: WRONG_DATE\n");
	printf("Actual Result: ");
	getTransactionDate(cptr);
	printf("\n");
	printf("Test Case 3:\n");
	printf("Input Data:\n");
	printf("Expected Result: WRONG_DATE\n");
	printf("Actual Result: ");
	getTransactionDate(cptr);
	printf("\n");
}
void isCardExpriedTest(void)
{
	struct ST_cardData_t c = { "", "", "05/25" };
	struct ST_cardData_t* cptr = &c;
	struct ST_terminalData_t t = { 0, 0,"03/11/2022"};
	struct ST_terminalData_t* tptr = &t;
	printf("Tester Name: Abdelrahman Mohamed Nour\n");
	printf("Function Name: isCardExpried\n");
	printf("Test Case 1:\n");
	printf("Input Data: Expiry date 05/25 , Transaction date 03/11/2022\n");
	printf("Expected Result: TERMINAL_OK\n");
	printf("Actual Result: ");
	isCardExpired(cptr,tptr);
	printf("\n");
	struct ST_cardData_t k = { "", "", "02/22" };
	struct ST_cardData_t* kptr = &k;
	struct ST_terminalData_t y = { 0, 0,"25/12/2023" };
	struct ST_terminalData_t* yptr = &y;
	printf("Test Case 2:\n");
	printf("Input Data: Expiry date 02/23 , Transaction date 30/02/2025\n");
	printf("Expected Result: EXPIRED_CARD\n");
	printf("Actual Result: ");
	isCardExpired(kptr, yptr);
	printf("\n");

}
void getTransactionAmountTest(void)
{
	struct ST_terminalData_t c = { 0, 0, "" };
	struct ST_terminalData_t* cptr = &c;
	printf("Tester Name: Abdelrahman Mohamed Nour\n");
	printf("Function Name: getTransactionAmount\n");
	printf("Test Case 1:\n");
	printf("Input Data: 10000\n");
	printf("Expected Result: TERMINAL_OK\n");
	printf("Actual Result: ");
	getTransactionAmount(cptr);
	printf("\n");
	printf("Test Case 2:\n");
	printf("Input Data: -1000\n");
	printf("Expected Result: INVALID_AMOUNT\n");
	printf("Actual Result: ");
	getTransactionAmount(cptr);
	printf("\n");
	printf("Test Case 3:\n");
	printf("Input Data: 0\n");
	printf("Expected Result: INVALID_AMOUNT\n");
	printf("Actual Result: ");
	getTransactionAmount(cptr);
	printf("\n");
}
void isBelowMaxAmountTest(void)
{
	struct ST_terminalData_t t = { 1000, 10000,"" };
	struct ST_terminalData_t* tptr = &t;
	printf("Tester Name: Abdelrahman Mohamed Nour\n");
	printf("Function Name: isBelowMaxAmount\n");
	printf("Test Case 1:\n");
	printf("Input Data: Transaction amount is 1000 and max amount is 10000\n");
	printf("Expected Result: TERMINAL_OK\n");
	printf("Actual Result: ");
	isBelowMaxAmount(tptr);
	printf("\n");
	struct ST_terminalData_t y = { 10000, 1000,"" };
	struct ST_terminalData_t* yptr = &y;
	printf("Test Case 2:\n");
	printf("Input Data: Transaction amount is 10000 and max amount is 1000\n");
	printf("Expected Result: EXCEED_MAX_AMOUNT\n");
	printf("Actual Result: ");
	isBelowMaxAmount(yptr);
	printf("\n");
}
void setMaxAmountTest(void)
{
	float i = 0;
	struct ST_terminalData_t c = { 0, 0, "" };
	struct ST_terminalData_t* cptr = &c;
	printf("Tester Name: Abdelrahman Mohamed Nour\n");
	printf("Function Name: setMaxAmount\n");
	printf("Test Case 1:\n");
	printf("Input Data: 10000\n");
	printf("Expected Result: TERMINAL_OK\n");
	printf("Actual Result: ");
	setMaxAmount(cptr,i);
	printf("\n");
	printf("Test Case 2:\n");
	printf("Input Data: -1000\n");
	printf("Expected Result: INVALID_MAX_AMOUNT\n");
	printf("Actual Result: ");
	setMaxAmount(cptr,i);
	printf("\n");
	printf("Test Case 3:\n");
	printf("Input Data: 0\n");
	printf("Expected Result: INVALID_MAX_AMOUNT\n");
	printf("Actual Result: ");
	setMaxAmount(cptr,i);
	printf("\n");
}