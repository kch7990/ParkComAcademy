#ifndef _ACCOUNT_H
#define _ACCOUNT_H

#include "Date.h"
#include <string>

typedef double Currency;

using namespace std;

class Account
{
public:
	Account();
	Account(Date date, string content, Currency amount, Currency balance, string node);
	Account(const Account& source);
	virtual ~Account() = 0;

	bool IsEqual(const Account& other);
	bool IsNotEqual(const Account& other);
	bool operator ==(const Account& other);
	bool operator !=(const Account& other);
	Account& operator =(const Account& source);

	Date& GetDate() const;
	string& GetContent() const;
	Currency GetAmount() const;
	Currency GetBalance() const;
	string& GetNote() const;

private:
	Date date;
	string content;
	Currency amount;
	Currency balance;
	string note;
};

inline Date& Account::GetDate() const
{
	return const_cast<Date&>(this->date);
}

inline string& Account::GetContent() const
{
	return const_cast<string&>(this->content);
}

inline Currency Account::GetAmount() const
{
	return this->amount;
}

inline Currency Account::GetBalance() const
{
	return this->balance;
}

inline string& Account::GetNote() const
{
	return const_cast<string&>(this->note);
}

#endif // !_ACCOUNT_H
