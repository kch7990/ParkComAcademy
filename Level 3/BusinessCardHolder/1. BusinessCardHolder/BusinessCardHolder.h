#ifndef _BUSINESSCARDHOLDER_H
#define _BUSINESSCARDHOLDER_H

typedef signed long int Long;

typedef struct _personal {
	char name[11];
	char telephoneNumber[12];
	char emailAddress[64];
	char position[16];
}Personal;
typedef struct _company {
	char name[64];
	char address[64];
	char telephoneNumber[12];
	char faxNumber[12];
	char url[64];
}Company;
typedef struct _businessCard BusinessCard;
typedef struct _businessCard {
	Company company;
	Personal personal;
	BusinessCard *next;
}BusinessCard;
typedef struct _businessCardHolder {
	BusinessCard *first;
	Long length;
	BusinessCard *current;
}BusinessCardHolder;

void Create(BusinessCardHolder *businessCardHolder);
BusinessCard* PutIn(BusinessCardHolder *businessCardHolder, BusinessCard businessCard);
void Find(BusinessCardHolder *businessCardHolder, char(*name), BusinessCard** (*indexes), Long *count);
BusinessCard PutOut(BusinessCardHolder *businessCardHolder, BusinessCard *index);
BusinessCard* First(BusinessCardHolder *businessCardHolder);
BusinessCard* Previous(BusinessCardHolder *businessCardHolder);
BusinessCard* Next(BusinessCardHolder *businessCardHolder);
BusinessCard* Last(BusinessCardHolder *businessCardHolder);
void Arrange(BusinessCardHolder *businessCardHolder);
void Destroy(BusinessCardHolder *businessCardHolder);
BusinessCard* Move(BusinessCardHolder *businessCardHolder, BusinessCard *index);
BusinessCard* FindByCompanyName(BusinessCardHolder *businessCardHolder, char(*companyName));

#endif //_BUSINESSCARDHOLDER_H