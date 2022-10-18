#include "app.h"

void appStart(void)
{
	struct ST_cardData_t c = { "", "", "" };
	struct ST_cardData_t* cptr = &c;
	struct ST_terminalData_t t = { 0,10000, "" };
	struct ST_terminalData_t* tptr = &t;
	struct ST_accountsDB_t p = { 0,RUNNING,"" };
	struct ST_accountsDB_t* pptr = &p;
	getCardHolderName(cptr);
	getCardExpiryDate(cptr);
	getCardPAN(cptr);
	getTransactionDate(tptr);
	EN_terminalError_t x = isCardExpired(cptr, tptr);
	if (x == EXPIRED_CARD) {
		return;
	}
	getTransactionAmount(tptr);
	EN_terminalError_t y = isBelowMaxAmount(tptr);
	if (y == EXCEED_MAX_AMOUNT)
	{
		return;
	}
	struct ST_transaction_t trans = { { "","","" }	, { 0, 10000, "" }, APPROVED, 0 };
	struct ST_transaction_t* transptr = &trans;
	trans.cardHolderData = c;
	trans.terminalData = t;
	saveTransaction(transptr);
	return;

}

int main()
{
	appStart();
	return;
}