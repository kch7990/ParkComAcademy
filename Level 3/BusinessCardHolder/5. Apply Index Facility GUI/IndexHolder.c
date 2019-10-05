#include "IndexHolder.h"
#include "Index.h"
#include "BusinessCardHolder.h"
#include <string.h>

void IndexHolder_Create(IndexHolder *indexHolder) {
	BineryTree_Create(&indexHolder->indexes);
	indexHolder->length = 0;
}
Index* IndexHolder_PutIn(IndexHolder *indexHolder, BusinessCard *businessCardLink) {
	Index index;
	Index *indexLink;
	BineryNode *node;

	strcpy(index.name, businessCardLink->company.name);
	node = Search(&indexHolder->indexes, &index, CompareIndexes);
	if (node == NULL) {
		Index_Create(&index, 100);
		node = BineryTree_Insert(&indexHolder->indexes, &index, sizeof(Index), CompareIndexes);
		indexHolder->length++;
	}
	indexLink = (Index*)(node + 1);
	Index_PutIn(indexLink, businessCardLink);

	return indexLink;
}
Index* IndexHolder_PutOut(IndexHolder *indexHolder, char(*companyName), BusinessCard *businessCardLink) {
	Index index;
	BineryNode *node;
	Index *indexLink;
	Long location;

	strcpy(index.name, companyName);
	node = Search(&indexHolder->indexes, &index, CompareIndexes);
	indexLink = (Index*)(node + 1);
	location = Index_Find(indexLink, businessCardLink);
	Index_PutOut(indexLink, location);
	if (indexLink->length == 0) {
		Index_Destroy(indexLink);
		node = BineryTree_Delete(&indexHolder->indexes, &index, CompareIndexes);
		indexHolder->length--;
		indexLink = NULL;
	}

	return indexLink;
}
Index* IndexHolder_Find(IndexHolder *indexHolder, char(*companyName)) {
	Index index;
	BineryNode *node;
	Index *indexLink = NULL;
	
	strcpy(index.name, companyName);
	node = Search(&indexHolder->indexes, &index, CompareIndexes);
	if (node != NULL) {
		indexLink = (Index*)(node + 1);
	}

	return indexLink;
}
void IndexHolder_MakeList(IndexHolder *indexHolder, Index* (*indexes), Long *count) {
	MakeKeys(&indexHolder->indexes, indexes, count, sizeof(Index));
}
void IndexHolder_Arrange(IndexHolder *indexHolder) {
	IndexHolder_Node_Array_Arrange(indexHolder->indexes.root);
	MakeBalance(&indexHolder->indexes, sizeof(Index));
}
void IndexHolder_Node_Array_Arrange(BineryNode *node) {
	Index *indexLink;

	if (node != NULL) {
		IndexHolder_Node_Array_Arrange(node->left);
		IndexHolder_Node_Array_Arrange(node->right);
		indexLink = (Index*)(node + 1);
		Index_Arrange(indexLink);
	}
}
void IndexHolder_Destroy(IndexHolder *indexHolder) {
	IndexHolder_Node_Array_Destroy(indexHolder->indexes.root);
	BineryTree_Destroy(&indexHolder->indexes);
}
void IndexHolder_Node_Array_Destroy(BineryNode *node) {
	Index *indexLink;

	if (node != NULL) {
		IndexHolder_Node_Array_Destroy(node->left);
		IndexHolder_Node_Array_Destroy(node->right);
		indexLink = (Index*)(node + 1);
		Index_Destroy(indexLink);
	}
}
int CompareIndexes(void *one, void *other) {
	Index *one_ = (Index*)one;
	Index *other_ = (Index*)other;

	return strcmp(one_->name, other_->name);
}