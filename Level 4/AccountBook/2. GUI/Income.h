#ifndef _INCOME_H
#define _INCOME_H

#include "Account.h"

class Income :public Account
{
public:
	Income();
	Income(Date date, string content, Currency amount, Currency balance, string note);
	Income(const Income& source);
	virtual ~Income();

	Income& operator =(const Income& source);
};

#endif // !_INCOME_H
