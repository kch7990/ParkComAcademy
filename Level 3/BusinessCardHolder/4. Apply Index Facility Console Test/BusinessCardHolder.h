// BusinessCardHolder.h

#ifndef _BUSINESSCARDHOLDER_H
#define _BUSINESSCARDHOLDER_H

#include "LinkedList.h"

typedef signed long int Long;

typedef struct _personal
{
	char name[11];
	char telephoneNumber[64];
	char emailAddress[64];
	char position[11];
} Personal;

typedef struct _company
{
	char name[11];
	char address[64];
	char telephoneNumber[64];
	char faxNumber[12];
	char url[64];
} Company;

typedef struct _businessCard BusinessCard;

typedef struct _businessCard
{
	Personal personal;
	Company company;
} BusinessCard;

typedef struct _businessCardHolder
{
	LinkedList businessCards;
	Long length;
	BusinessCard *current;
} BusinessCardHolder;

void BusinessCardHolder_Create(BusinessCardHolder *businessCardHolder);
Long Load(BusinessCardHolder* businessCardHolder);
BusinessCard* PutIn(BusinessCardHolder *businessCardHolder, BusinessCard businessCard);
void Find(BusinessCardHolder *businessCardHolder, char(*name), BusinessCard* *(*indexes), Long *count);
BusinessCard* FindByCompanyName(BusinessCardHolder *businessCardHolder, char(*companyName));
BusinessCard PutOut(BusinessCardHolder *businessCardHolder, BusinessCard *index);
BusinessCard* BusinessCardHolder_First(BusinessCardHolder *businessCardHolder);
BusinessCard* BusinessCardHolder_Previous(BusinessCardHolder *businessCardHolder);
BusinessCard* BusinessCardHolder_Next(BusinessCardHolder *businessCardHolder);
BusinessCard* BusinessCardHolder_Last(BusinessCardHolder *businessCardHolder);
BusinessCard* BusinessCardHolder_Move(BusinessCardHolder *businessCardHolder, BusinessCard *index);
Long Save(BusinessCardHolder* businessCardHolder);
void BusinessCardHolder_Destroy(BusinessCardHolder *businessCardHolder);
int ComparePersonalNames(void *one, void *other);
int CompareCompanyNames(void *one, void *other);
int CompareBusinessCardLinks(void *one, void *other);

#endif //_BUSINESSCARDHOLDER_H
