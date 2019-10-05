#ifndef _INDEX_H
#define _INDEX_H

#include "Array.h"

typedef struct _businessCard BusinessCard;
typedef struct _index {
	char name[64];
	Array businessCards;
	Long capacity;
	Long length;
}Index;

void Index_Create(Index *index, Long capacity);
Long Index_PutIn(Index *index, BusinessCard *businessCardLink);
Long Index_Find(Index *index, BusinessCard *businessCardLink);
Long Index_PutOut(Index *index, Long location);
void Index_Arrange(Index *index);
BusinessCard* Index_GetAt(Index *index, Long location);
void Index_Destroy(Index *index);
int Index_CompareBusinessCardLinks(void *one, void *other);
int Index_ComparePersonalNames(void *one, void *other);

#endif //_INDEX_H