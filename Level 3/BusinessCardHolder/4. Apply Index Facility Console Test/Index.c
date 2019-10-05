#include "Index.h"
#include "BusinessCardHolder.h"
#include <string.h>

void Index_Create(Index *index, Long capacity) {
	Array_Create(&index->businessCards, capacity, sizeof(BusinessCard*));
	index->capacity = capacity;
	index->length = 0;
}
Long Index_PutIn(Index *index, BusinessCard *businessCardLink) {
	Long location;

	if (index->length < index->capacity) {
		location = index->length;
		location = Array_Store(&index->businessCards, location, &businessCardLink, sizeof(BusinessCard*));
	}
	else {
		location = Array_AppendFromRear(&index->businessCards, &businessCardLink, sizeof(BusinessCard*));
		index->capacity++;
	}
	index->length++;

	return location;
}
Long Index_Find(Index *index, BusinessCard *businessCardLink) {
	Long location;

	location = Array_LinearSearchUnique(&index->businessCards, businessCardLink, sizeof(BusinessCard*), Index_CompareBusinessCardLinks);

	return location;
}
Long Index_PutOut(Index *index, Long location) {
	location = Array_Delete(&index->businessCards, location, sizeof(BusinessCard*));
	index->capacity--;
	index->length--;

	return location;
}
void Index_Arrange(Index *index) {
	Array_SelectionSort(&index->businessCards, sizeof(BusinessCard*), Index_ComparePersonalNames);
}
BusinessCard* Index_GetAt(Index *index, Long location) {
	BusinessCard *businessCardLink;

	Array_GetAt(&index->businessCards, location, &businessCardLink, sizeof(BusinessCard*));

	return businessCardLink;
}
void Index_Destroy(Index *index) {
	Array_Destroy(&index->businessCards);
}
int Index_CompareBusinessCardLinks(void *one, void *other) {
	BusinessCard* *one_ = (BusinessCard**)one;
	int ret;

	if ((*one_) > other) {
		ret = 1;
	}
	else if ((*one_) == other) {
		ret = 0;
	}
	else if ((*one_) < other) {
		ret = -1;
	}

	return ret;
}
int Index_ComparePersonalNames(void *one, void *other) {
	BusinessCard* *one_ = (BusinessCard**)one;
	BusinessCard* *other_ = (BusinessCard**)other;

	return strcmp((*one_)->personal.name, (*other_)->personal.name);
}