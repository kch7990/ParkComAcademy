// BusinessCardHolder.c

#include "BusinessCardHolder.h"
#include "Index.h"
#include "IndexHolder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable : 4996)

int main(int argc, char* argv[]) {
	BusinessCardHolder businessCardHolder;
	BusinessCard businessCard1 = { {"홍길동", "01011111111", "hong@", "사원"}, {"홍컴", "서울 강동구", "0211111111", "0211111110", "hong.com" } };
	BusinessCard businessCard2 = { {"정길동", "01022222222", "go@", "이사"}, {"고컴", "대전 강서구", "04222222222", "04222222220", "go.com" } };
	BusinessCard businessCard3 = { {"고길동", "01033333333", "jung@", "부장"}, {"고컴", "대구 강남구", "05333333333", "05333333330", "jung.com" } };
	BusinessCard businessCard4 = { {"이길동", "01044444444", "gil@", "차장"}, {"홍컴", "부산 강북구", "05144444444", "05144444440", "gil.com" } };

	Long count;
	BusinessCard businessCard;
	BusinessCard *businessCardLink;
	BusinessCard* (*businessCardLinks);
	BusinessCard* previous = NULL;

	Long i;
	IndexHolder indexHolder;
	Long location;
	Long j;
	Index *indexLink;
	Index(*indexLinks);
	Long indexLinkCount;
	BusinessCard *current;

	// 1. 명함첩을 만든다.
	BusinessCardHolder_Create(&businessCardHolder);

	// 색인첩을 만들다.
	IndexHolder_Create(&indexHolder);
	
	// 적재하다.
	count = Load(&businessCardHolder);
	if (count > 1) {
		businessCardLink = BusinessCardHolder_First(&businessCardHolder);
		while (businessCardLink != previous)
		{
			previous = businessCardLink;

			indexLink = IndexHolder_PutIn(&indexHolder, businessCardLink);
			printf("%s\n", indexLink->name);

			j = 0;
			while (j < indexLink->length)
			{
				current = Index_GetAt(indexLink, j);
				printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", current->personal.name, current->personal.telephoneNumber, current->personal.emailAddress, current->personal.position,
					current->company.name, current->company.address, current->company.telephoneNumber, current->company.faxNumber, current->company.url);
				j++;
			}

			businessCardLink = BusinessCardHolder_Next(&businessCardHolder);
		}
	}
	
	// 2. 명함 1을 끼운다.
	businessCardLink = PutIn(&businessCardHolder, businessCard1);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", businessCardLink->personal.name, businessCardLink->personal.telephoneNumber, businessCardLink->personal.emailAddress, businessCardLink->personal.position,
		businessCardLink->company.name, businessCardLink->company.address, businessCardLink->company.telephoneNumber, businessCardLink->company.faxNumber, businessCardLink->company.url);
	
	// 색인을 끼운다.
	indexLink = IndexHolder_PutIn(&indexHolder, businessCardLink);
	printf("%s\n", indexLink->name);

	location = Index_Find(indexLink, businessCardLink);
	businessCardLink = Index_GetAt(indexLink, location);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", businessCardLink->personal.name, businessCardLink->personal.telephoneNumber, businessCardLink->personal.emailAddress, businessCardLink->personal.position,
		businessCardLink->company.name, businessCardLink->company.address, businessCardLink->company.telephoneNumber, businessCardLink->company.faxNumber, businessCardLink->company.url);
	
	// 3. 명함 2을 끼운다.
	businessCardLink = PutIn(&businessCardHolder, businessCard2);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", businessCardLink->personal.name, businessCardLink->personal.telephoneNumber, businessCardLink->personal.emailAddress, businessCardLink->personal.position,
		businessCardLink->company.name, businessCardLink->company.address, businessCardLink->company.telephoneNumber, businessCardLink->company.faxNumber, businessCardLink->company.url);

	// 색인을 끼운다.
	indexLink = IndexHolder_PutIn(&indexHolder, businessCardLink);
	printf("%s\n", indexLink->name);

	location = Index_Find(indexLink, businessCardLink);
	businessCardLink = Index_GetAt(indexLink, location);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", businessCardLink->personal.name, businessCardLink->personal.telephoneNumber, businessCardLink->personal.emailAddress, businessCardLink->personal.position,
		businessCardLink->company.name, businessCardLink->company.address, businessCardLink->company.telephoneNumber, businessCardLink->company.faxNumber, businessCardLink->company.url);
	
	// 4. 명함 3을 끼운다.
	businessCardLink = PutIn(&businessCardHolder, businessCard3);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", businessCardLink->personal.name, businessCardLink->personal.telephoneNumber, businessCardLink->personal.emailAddress, businessCardLink->personal.position,
		businessCardLink->company.name, businessCardLink->company.address, businessCardLink->company.telephoneNumber, businessCardLink->company.faxNumber, businessCardLink->company.url);

	// 색인을 끼운다.
	indexLink = IndexHolder_PutIn(&indexHolder, businessCardLink);
	printf("%s\n", indexLink->name);

	location = Index_Find(indexLink, businessCardLink);
	businessCardLink = Index_GetAt(indexLink, location);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", businessCardLink->personal.name, businessCardLink->personal.telephoneNumber, businessCardLink->personal.emailAddress, businessCardLink->personal.position,
		businessCardLink->company.name, businessCardLink->company.address, businessCardLink->company.telephoneNumber, businessCardLink->company.faxNumber, businessCardLink->company.url);
	
	// 5. 명함 4을 끼운다.
	businessCardLink = PutIn(&businessCardHolder, businessCard4);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", businessCardLink->personal.name, businessCardLink->personal.telephoneNumber, businessCardLink->personal.emailAddress, businessCardLink->personal.position,
		businessCardLink->company.name, businessCardLink->company.address, businessCardLink->company.telephoneNumber, businessCardLink->company.faxNumber, businessCardLink->company.url);

	// 색인을 끼운다.
	indexLink = IndexHolder_PutIn(&indexHolder, businessCardLink);
	printf("%s\n", indexLink->name);

	location = Index_Find(indexLink, businessCardLink);
	businessCardLink = Index_GetAt(indexLink, location);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", businessCardLink->personal.name, businessCardLink->personal.telephoneNumber, businessCardLink->personal.emailAddress, businessCardLink->personal.position,
		businessCardLink->company.name, businessCardLink->company.address, businessCardLink->company.telephoneNumber, businessCardLink->company.faxNumber, businessCardLink->company.url);
	
	// 6. "홍길동"의 명함을 찾는다.
	Find(&businessCardHolder, "홍길동", &businessCardLinks, &count);

	i = 0;
	while (i < count)
	{
		businessCardLink = businessCardLinks[i];
		printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", businessCardLink->personal.name, businessCardLink->personal.telephoneNumber, businessCardLink->personal.emailAddress, businessCardLink->personal.position,
			businessCardLink->company.name, businessCardLink->company.address, businessCardLink->company.telephoneNumber, businessCardLink->company.faxNumber, businessCardLink->company.url);
		i++;
	}
	businessCard = PutOut(&businessCardHolder, businessCardLinks[0]);

	indexLink = IndexHolder_PutOut(&indexHolder, businessCard.company.name, businessCardLinks[0]);

	if (businessCardLinks != NULL)
	{
		free(businessCardLinks);
	}

	if (indexLink == NULL)
	{
		printf("색인이 삭제되었습니다.\n");
	}
	else
	{
		printf("%s\n", indexLink->name);
	}
	
	// 6. "이길동"의 명함을 찾는다.
	Find(&businessCardHolder, "이길동", &businessCardLinks, &count);

	i = 0;
	while (i < count)
	{
		businessCardLink = businessCardLinks[i];
		printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", businessCardLink->personal.name, businessCardLink->personal.telephoneNumber, businessCardLink->personal.emailAddress, businessCardLink->personal.position,
			businessCardLink->company.name, businessCardLink->company.address, businessCardLink->company.telephoneNumber, businessCardLink->company.faxNumber, businessCardLink->company.url);
		i++;
	}
	businessCard = PutOut(&businessCardHolder, businessCardLinks[0]);

	indexLink = IndexHolder_PutOut(&indexHolder, businessCard.company.name, businessCardLinks[0]);

	if (businessCardLinks != NULL)
	{
		free(businessCardLinks);
	}

	if (indexLink == NULL)
	{
		printf("색인이 삭제되었습니다\n");
	}
	else
	{
		printf("%s\n", indexLink->name);
	}

	IndexHolder_Arrange(&indexHolder);
	IndexHolder_MakeList(&indexHolder, &indexLinks, &indexLinkCount);
	i = 0;
	while (i < indexLinkCount) {
		indexLink = indexLinks + i;
		printf("%s\n", indexLink->name);
		j = 0;
		while (j < indexLink->length) {
			businessCardLink = Index_GetAt(indexLink, j);
			printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", businessCardLink->personal.name, businessCardLink->personal.telephoneNumber, businessCardLink->personal.emailAddress, businessCardLink->personal.position,
				businessCardLink->company.name, businessCardLink->company.address, businessCardLink->company.telephoneNumber, businessCardLink->company.faxNumber, businessCardLink->company.url);
			j++;
		}
		i++;
	}
	if (indexLinks != NULL) {
		free(indexLinks);
	}

	// 14. 명함첩을 저장한다.
	Save(&businessCardHolder);

	// 색인첩을 지운다.
	IndexHolder_Destroy(&indexHolder);

	// 15. 명함첩을 지운다.
	BusinessCardHolder_Destroy(&businessCardHolder);
	
	return 0;
}

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
