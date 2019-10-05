// BusinessCardHolder.c

#include "BusinessCardHolder.h"
#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable : 4996)

void BusinessCardHolder_Create(BusinessCardHolder *businessCardHolder)
{
	Create(&businessCardHolder->businessCards);

	businessCardHolder->length = 0;
	businessCardHolder->current = NULL;
}

Long Load(BusinessCardHolder* businessCardHolder)
{
	Long index;
	Personal personal;
	Company company;
	BusinessCard businessCard;
	Node *node;
	FILE *companiesFile;
	FILE *personalsFile;
	size_t companiesFlag;
	size_t personalsFlag;
	Long i;

	personalsFile = fopen("Personals.dat", "rb");
	companiesFile = fopen("Companies.dat", "rb");

	if (personalsFile != NULL && companiesFile != NULL)
	{
		personalsFlag = fread(&index, sizeof(Long), 1, personalsFile);
		personalsFlag = fread(&personal, sizeof(Personal), 1, personalsFile);
		while (!feof(personalsFile) && personalsFlag != 0)
		{
			fseek(companiesFile, 0L, SEEK_SET);
			i = 1;
			companiesFlag = fread(&company, sizeof(Company), 1, companiesFile);

			while (!feof(companiesFile) && companiesFlag != 0 && i < index)
			{
				i++;
				companiesFlag = fread(&company, sizeof(Company), 1, companiesFile);
			}

			businessCard.company = company;
			businessCard.personal = personal;

			node = AppendFromTail(&businessCardHolder->businessCards, &businessCard, sizeof(BusinessCard));
			businessCardHolder->length++;

			businessCardHolder->current = (BusinessCard*)(node + 1);

			personalsFlag = fread(&index, sizeof(Long), 1, personalsFile);
			personalsFlag = fread(&personal, sizeof(Personal), 1, personalsFile);
		}
		fclose(companiesFile);
		fclose(personalsFile);

	}

	return businessCardHolder->length;
}

BusinessCard* PutIn(BusinessCardHolder *businessCardHolder, BusinessCard businessCard)
{
	Node *node;

	node = AppendFromTail(&businessCardHolder->businessCards, &businessCard, sizeof(BusinessCard));
	businessCardHolder->length++;
	businessCardHolder->current = (BusinessCard*)(node + 1);

	return businessCardHolder->current;
}

void Find(BusinessCardHolder *businessCardHolder, char(*name), BusinessCard* *(*indexes), Long *count)
{
	Node* (*nodes);
	Long i;

	*indexes = (BusinessCard*(*))calloc(businessCardHolder->length, sizeof(BusinessCard*));

	LinearSearchDuplicate(&businessCardHolder->businessCards, name, &nodes, count, ComparePersonalNames);

	i = 0;
	while (i < *count)
	{
		(*indexes)[i] = (BusinessCard*)(nodes[i] + 1);
		i++;
	}

	if (nodes != NULL)
	{
		free(nodes);
	}
}

BusinessCard* FindByCompanyName(BusinessCardHolder *businessCardHolder, char(*companyName))
{
	Node *node;
	BusinessCard *index = NULL;

	node = LinearSearchUnique(&businessCardHolder->businessCards, companyName, CompareCompanyNames);

	if (node != NULL)
	{
		index = (BusinessCard*)(node + 1);
	}

	return index;
}

BusinessCard PutOut(BusinessCardHolder *businessCardHolder, BusinessCard *index)
{
	BusinessCard businessCard;
	Node *node;

	node = LinearSearchUnique(&businessCardHolder->businessCards, index, CompareBusinessCardLinks);
	GetAt(&businessCardHolder->businessCards, node, &businessCard, sizeof(BusinessCard));
	Delete(&businessCardHolder->businessCards, node);
	businessCardHolder->length--;
	if (businessCardHolder->businessCards.current != NULL)
	{
		businessCardHolder->current = (BusinessCard*)(businessCardHolder->businessCards.current + 1);
	}
	else
	{
		businessCardHolder->current = NULL;
	}

	return businessCard;
}

BusinessCard* BusinessCardHolder_First(BusinessCardHolder *businessCardHolder)
{
	Node *node;

	node = First(&businessCardHolder->businessCards);
	businessCardHolder->current = (BusinessCard*)(node + 1);

	return businessCardHolder->current;
}


BusinessCard* BusinessCardHolder_Previous(BusinessCardHolder *businessCardHolder)
{
	Node *node;

	node = Previous(&businessCardHolder->businessCards);
	businessCardHolder->current = (BusinessCard*)(node + 1);

	return businessCardHolder->current;
}

BusinessCard* BusinessCardHolder_Next(BusinessCardHolder *businessCardHolder)
{
	Node *node;

	node = Next(&businessCardHolder->businessCards);
	businessCardHolder->current = (BusinessCard*)(node + 1);

	return businessCardHolder->current;
}

BusinessCard* BusinessCardHolder_Last(BusinessCardHolder *businessCardHolder)
{
	Node *node;

	node = Last(&businessCardHolder->businessCards);
	businessCardHolder->current = (BusinessCard*)(node + 1);

	return businessCardHolder->current;
}

BusinessCard* BusinessCardHolder_Move(BusinessCardHolder *businessCardHolder, BusinessCard *index)
{
	Node *node;

	node = LinearSearchUnique(&businessCardHolder->businessCards, index, CompareBusinessCardLinks);
	node = Move(&businessCardHolder->businessCards, node);
	businessCardHolder->current = (BusinessCard*)(node + 1);

	return businessCardHolder->current;
}

Long Save(BusinessCardHolder* businessCardHolder)
{
	Node *node;
	Node *previous = NULL;
	BusinessCard businessCard;
	Company company;
	Long count = 0;
	Long i;
	FILE *companiesFile;
	FILE *personalsFile;
	size_t flag;

	personalsFile = fopen("Personals.dat", "wb");
	companiesFile = fopen("Companies.dat", "wb+");
	if (personalsFile != NULL && companiesFile != NULL)
	{
		node = First(&businessCardHolder->businessCards);

		while (node != previous)
		{
			GetAt(&businessCardHolder->businessCards, node, &businessCard, sizeof(BusinessCard));
			i = 1;
			fseek(companiesFile, 0L, SEEK_SET);
			flag = fread(&company, sizeof(Company), 1, companiesFile);

			while (!feof(companiesFile) && flag != 0 && strcmp(businessCard.company.name, company.name) != 0)
			{
				i++;
				flag = fread(&company, sizeof(Company), 1, companiesFile);
			}

			if (flag == 0)
			{
				fwrite(&businessCard.company, sizeof(Company), 1, companiesFile);
			}

			fwrite(&i, sizeof(Long), 1, personalsFile);
			fwrite(&businessCard.personal, sizeof(Personal), 1, personalsFile);
			count++;
			previous = node;
			node = Next(&businessCardHolder->businessCards);
		}

		fclose(companiesFile);
		fclose(personalsFile);
	}

	return count;
}

void BusinessCardHolder_Destroy(BusinessCardHolder *businessCardHolder)
{
	Destroy(&businessCardHolder->businessCards);
}

int ComparePersonalNames(void *one, void *other)
{
	BusinessCard *one_ = (BusinessCard*)one;
	char(*other_) = (char*)other;

	return strcmp(one_->personal.name, other);
}

int CompareCompanyNames(void *one, void *other)
{
	BusinessCard *one_ = (BusinessCard*)one;
	char(*other_) = (char*)other;

	return strcmp(one_->company.name, other_);
}

int CompareBusinessCardLinks(void *one, void *other)
{
	Node *one_ = one;
	BusinessCard *other_ = other;
	int ret;

	if ((BusinessCard*)(one_) > other_)
	{
		ret = 1;
	}
	else if ((BusinessCard*)(one_) == other_)
	{
		ret = 0;
	}
	else if ((BusinessCard*)(one_) < other_)
	{
		ret = -1;
	}

	return ret;
}
