#ifndef _ACCOUNTBOOK_H
#define _ACCOUNTBOOK_H

#include "Date.h"
#include "Array.h"
#include <string>

typedef double Currency;
typedef signed long int Long;

using namespace std;

class Account;
class AccountBook
{
public:
	AccountBook(Long capacity = 256);
	AccountBook(const AccountBook& source);
	~AccountBook();
	Long Record(Date date, string content, Currency amount, string note);
	Long Correct(Long index, Currency amount, string note);
	void Find(const Date& date, Long *(*indexes), Long *count);
	void Find(string content, Long *(*indexes), Long *count);
	void Find(const Date& startDate, const Date& endDate, Long *(*indexes), Long *count);
	void Find(string content, const Date& startDate, const Date& endDate, Long *(*indexes), Long *count);
	void Calculate(const Date& startDate, const Date& endDate, Currency *sumOfIncome, Currency *sumOfOutgo, Currency *difference);
	Account* GetAt(Long index);

	AccountBook& operator =(const AccountBook& source);
	Account* operator [](Long index);

	Long GetCapacity() const;
	Long GetLength() const;
private:
	Array<Account*> accounts;
	Long capacity;
	Long length;
};
inline Long AccountBook::GetCapacity() const
{
	return this->capacity;
}
inline Long AccountBook::GetLength() const
{
	return this->length;
}
int CompareDates(void *one, void *other);
int CompareContents(void *one, void *other);

#endif //_ACCOUNTBOOK_H