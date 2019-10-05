#ifndef _INDEXHOLDER_H
#define _INDEXHOLDER_H

#include "BineryTree.h"

typedef struct _businessCard BusinessCard;
typedef struct _index Index;
typedef struct _indexHolder {
	BineryTree indexes;
	Long length;
}IndexHolder;

void IndexHolder_Create(IndexHolder *indexHolder);
Index* IndexHolder_PutIn(IndexHolder *indexHolder, BusinessCard *businessCardLink);
Index* IndexHolder_PutOut(IndexHolder *indexHolder, char(*companyName), BusinessCard *businessCardLink);
Index* IndexHolder_Find(IndexHolder *indexHolder, char(*companyName));
void IndexHolder_MakeList(IndexHolder *indexHolder, Index* (*indexes), Long *count);
void IndexHolder_Arrange(IndexHolder *indexHolder);
void IndexHolder_Node_Array_Arrange(BineryNode *node);
void IndexHolder_Destroy(IndexHolder *indexHolder);
void IndexHolder_Node_Array_Destroy(BineryNode *node);
int CompareIndexes(void *one, void *other);

#endif //_INDEXHOLDER_H