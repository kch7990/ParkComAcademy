// BusinessCardHolder.h

#ifndef _BUSINESSCARDHOLDER_H
#define _BUSINESSCARDHOLDER_H

#include "BusinessCard.h"
#include "LinkedList.h"
#include <string>

using namespace std;

class BusinessCardHolder
{
public:
	BusinessCardHolder();
	BusinessCardHolder(const BusinessCardHolder& source);
	BusinessCard* PutIn(BusinessCard businessCard);
	void Find(string name, BusinessCard* *(*indexes), Long *count);
	BusinessCard* FindByCompanyName(string companyName);
	BusinessCard PutOut(BusinessCard *index);
	BusinessCard* First();
	BusinessCard* Previous();
	BusinessCard* Next();
	BusinessCard* Last();
	BusinessCard* Move(BusinessCard* index);
	BusinessCardHolder& operator=(const BusinessCardHolder& source);
	BusinessCard& operator[](Long index);
	Long GetLength() const;
	BusinessCard* GetCurrent() const;

private:
	LinkedList<BusinessCard> businessCards;
	Long length;
	BusinessCard* current;
};

inline Long BusinessCardHolder::GetLength() const
{
	return this->length;
}

inline BusinessCard* BusinessCardHolder::GetCurrent() const
{
	return const_cast<BusinessCard*>(this->current);
}

int ComparePersonalNames(void *one, void *other);
int CompareCompanyNames(void *one, void *other);
int CompareBusinessCardLinks(void *one, void *other);

#endif //_BUSINESSCARDHOLDER_H
