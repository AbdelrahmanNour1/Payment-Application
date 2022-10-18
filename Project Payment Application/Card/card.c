#include "card.h"

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	int length;
	char s[50];
	printf("Please enter your name:\n");
	scanf("%[^\n]%*c", s);
	length = strlen(s);
	if (s == NULL || length < 20 || length > 24)
	{
		printf("WRONG_NAME\n");
		return WRONG_NAME;
	}
	else {

		strcpy(cardData->cardHolderName, s);
		printf("CARD_OK\n");
		return CARD_OK;
	}
}
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	int length;
	char s[15];
	printf("Please enter your card expiry date:\n");
	scanf("%[^\n]%*c", s);
	length = strlen(s);
	if (s == NULL || length < 5 || length > 5 || s[2] != '/' || s[0] > '1' || (s[0] == '1' && s[1] > '2') || (s[0] == '0' && s[1] == '0'))
	{
		printf("WRONG_EXP_DATE\n");
		return WRONG_EXP_DATE;
	}
	else {

		strcpy(cardData->cardExpirationDate, s);
		printf("CARD_OK\n");
		return CARD_OK;
	}


}
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	int length;
	char s[30];
	printf("Please enter your Primary Account Number:\n");
	scanf("%[^\n]%*c", s);
	length = strlen(s);
	if (s == NULL || length < 16 || length > 19)
	{
		printf("WRONG_PAN\n");
		return WRONG_PAN;
	}
	else {

		strcpy(cardData->primaryAccountNumber, s);
		printf("CARD_OK\n");
		return CARD_OK;
	}


}
void getCardHolderNameTest(void)
{
	struct ST_cardData_t c = { "", "", "" };
	struct ST_cardData_t* cptr = &c;
	printf("Tester Name: Abdelrahman Mohamed Nour\n");
	printf("Function Name: getCardHolderName\n");
	printf("Test Case 1:\n");
	printf("Input Data: Mohamed Mostafa Ahmed\n");
	printf("Expected Result: CARD_OK\n");
	printf("Actual Result: ");
	getCardHolderName(cptr);
	printf("\n");
	printf("Test Case 2:\n");
	printf("Input Data: Mohamed Mostafa\n");
	printf("Expected Result: WRONG_NAME\n");
	printf("Actual Result: ");
	getCardHolderName(cptr);
	printf("\n");
	printf("Test Case 3:\n");
	printf("Input Data:\n");
	printf("Expected Result: WRONG_NAME\n");
	printf("Actual Result: ");
	getCardHolderName(cptr);
	printf("\n");

}
void getCardExpiryDateTest(void) 
{
	struct ST_cardData_t c = { "", "", "" };
	struct ST_cardData_t* cptr = &c;
	printf("Tester Name: Abdelrahman Mohamed Nour\n");
	printf("Function Name: getCardExpiryDate\n");
	printf("Test Case 1:\n");
	printf("Input Data: 05/02\n");
	printf("Expected Result: CARD_OK\n");
	printf("Actual Result: ");
	getCardExpiryDate(cptr);
	printf("\n");
	printf("Test Case 2:\n");
	printf("Input Data: 30/02\n");
	printf("Expected Result: WRONG_EXP_DATE\n");
	printf("Actual Result: ");
	getCardExpiryDate(cptr);
	printf("\n");
	printf("Test Case 3:\n");
	printf("Input Data: 00/00\n");
	printf("Expected Result: WRONG_EXP_DATE\n");
	printf("Actual Result: ");
	getCardExpiryDate(cptr);
	printf("\n");
	printf("Test Case 4:\n");
	printf("Input Data: 55/22\n");
	printf("Expected Result: WRONG_EXP_DATE\n");
	printf("Actual Result: ");
	getCardExpiryDate(cptr);
	printf("\n");
	printf("Test Case 5:\n");
	printf("Input Data: \n");
	printf("Expected Result: WRONG_EXP_DATE\n");
	printf("Actual Result: ");
	getCardExpiryDate(cptr);
	printf("\n");
}
void getCardPANTest(void)
{
	struct ST_cardData_t c = { "", "", "" };
	struct ST_cardData_t* cptr = &c;
	printf("Tester Name: Abdelrahman Mohamed Nour\n");
	printf("Function Name: getCardPAN\n");
	printf("Test Case 1:\n");
	printf("Input Data: 012345678910111213\n");
	printf("Expected Result: CARD_OK\n");
	printf("Actual Result: ");
	getCardPAN(cptr);
	printf("\n");
	printf("Test Case 2:\n");
	printf("Input Data: 0123456789\n");
	printf("Expected Result: WRONG_PAN\n");
	printf("Actual Result: ");
	getCardPAN(cptr);
	printf("\n");
	printf("Test Case 3:\n");
	printf("Input Data:\n");
	printf("Expected Result: WRONG_PAN\n");
	printf("Actual Result: ");
	getCardPAN(cptr);
	printf("\n");
}