#ifndef _OUTGO_H
#define _OUTGO_H

#include "Account.h"

class Outgo :public Account
{
public:
	Outgo();
	Outgo(Date date, string content, Currency amount, Currency balance, string note);
	Outgo(const Outgo& source);
	virtual ~Outgo();

	Outgo& operator =(const Outgo& source);
};

#endif // !_OUTGO_H
