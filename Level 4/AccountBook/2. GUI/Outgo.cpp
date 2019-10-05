#include "Outgo.h"

Outgo::Outgo()
{

}

Outgo::Outgo(Date date, string content, Currency amount, Currency balance, string note)
	:Account(date, content, amount, balance, note)
{

}

Outgo::Outgo(const Outgo& source)
	: Account(source)
{

}

Outgo::~Outgo()
{

}

Outgo& Outgo::operator=(const Outgo& source)
{
	Account::operator=(source);

	return *this;
}
