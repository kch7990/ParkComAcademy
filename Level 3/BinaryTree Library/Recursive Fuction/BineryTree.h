#ifndef _BINERYTREE_H
#define _BINERYTREE_H

#include <stddef.h>

typedef signed long int Long;
typedef struct _bineryNode BineryNode;
typedef struct _bineryNode {
	BineryNode *left;
	BineryNode *right;
}BineryNode;
typedef struct _bineryTree {
	BineryNode *root;
	Long length;
	Long balance;
}BineryTree;

void Create(BineryTree *bineryTree);
BineryNode* Insert(BineryTree *bineryTree, void *key, size_t size, int(*compare)(void*, void*));
BineryNode* Delete(BineryTree *bineryTree, void *key, int(*compare)(void*, void*));
BineryNode* Search(BineryTree *bineryTree, void *key, int(*compare)(void*, void*));
void GetAt(BineryTree *bineryTree, BineryNode *index, void *key, size_t size);
void MakeBalance(BineryTree *bineryTree, size_t size);
void MakeKeys(BineryTree *bineryTree, void* (*keys), Long *count, size_t size);
void Node_MakeKeys(BineryNode *node, void(*keys), Long *count, Long *i, size_t size);
void DeleteAllItems(BineryTree *bineryTree);
void Node_DeleteAllItems(BineryNode *node);
void MakeTree(BineryTree *bineryTree, void(*keys), Long count, size_t size);
BineryNode* Node_MakeTree(void(*keys), Long first, Long last, size_t size);
void Destroy(BineryTree *bineryTree);
void Node_Destroy(BineryNode *node);

#endif //_BINERYTREE_H