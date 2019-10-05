#include "Income.h"

Income::Income()
{

}

Income::Income(Date date, string content, Currency amount, Currency balance, string note)
	:Account(date, content, amount, balance, note)
{

}

Income::Income(const Income& source)
	: Account(source)
{

}

Income::~Income()
{

}

Income& Income::operator=(const Income& source)
{
	Account::operator=(source);

	return *this;
}
