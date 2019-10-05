#include "BineryTree.h"
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

void BineryTree_Create(BineryTree *bineryTree) {
	bineryTree->root = NULL;
	bineryTree->length = 0;
	bineryTree->balance = 0;
}
BineryNode* BineryTree_Insert(BineryTree *bineryTree, void *key, size_t size, int(*compare)(void*, void*)) {
	BineryNode *index;
	BineryNode *parent = NULL;
	index = bineryTree->root;
	while (index != NULL) {
		parent = index;
		if (compare(index + 1, key) > 0) {
			index = index->left;
		}
		else {
			index = index->right;
		}
	}
	index = (BineryNode*)malloc(sizeof(BineryNode) + size);
	memcpy(index + 1, key, size);
	index->left = NULL;
	index->right = NULL;
	if (parent != NULL) {
		if (compare(parent + 1, key) > 0) {
			parent->left = index;
		}
		else {
			parent->right = index;
		}
		if (compare(bineryTree->root + 1, key) > 0) {
			bineryTree->balance--;
		}
		else {
			bineryTree->balance++;
		}
	}
	else {
		bineryTree->root = index;
	}
	bineryTree->length++;

	return index;
}
BineryNode* BineryTree_Delete(BineryTree *bineryTree, void *key, int(*compare)(void*, void*)) {
	BineryNode *index;
	BineryNode *deleteNode;
	BineryNode *parentofDelete = NULL;
	BineryNode *changeNode = NULL;
	BineryNode *parentofChange = NULL;

	deleteNode = bineryTree->root;
	while (deleteNode != NULL && compare(deleteNode + 1, key) != 0) {
		parentofDelete = deleteNode;
		if (compare(deleteNode + 1, key) > 0) {
			deleteNode = deleteNode->left;
		}
		else {
			deleteNode = deleteNode->right;
		}
	}
	index = deleteNode->right;
	while (index != NULL) {
		parentofChange = changeNode;
		changeNode = index;
		index = index->left;
	}
	if (deleteNode->right == NULL) {
		index = deleteNode->left;
	}
	while (index != NULL) {
		parentofChange = changeNode;
		changeNode = index;
		index = index->right;
	}
	if (changeNode != NULL && parentofChange == NULL) {
		parentofChange = deleteNode;
	}
	if (changeNode != NULL) {
		if (changeNode->left != NULL || changeNode->right != NULL) {
			if (parentofChange != deleteNode) {
				if (changeNode->left != NULL) {
					parentofChange->right = changeNode->left;
				}
				else {
					parentofChange->left = changeNode->right;
				}
			}
			else {
				if (changeNode->left != NULL) {
					parentofChange->left = changeNode->left;
				}
				else {
					parentofChange->right = changeNode->right;
				}
			}
		}
		else {
			if (parentofChange->left == changeNode) {
				parentofChange->left = NULL;
			}
			else {
				parentofChange->right = NULL;
			}
		}
		changeNode->left = deleteNode->left;
		changeNode->right = deleteNode->right;
		if (parentofDelete != NULL) {
			if (parentofDelete->left == deleteNode) {
				parentofDelete->left = changeNode;
			}
			else {
				parentofDelete->right = changeNode;
			}
		}
		else {
			bineryTree->root = changeNode;
		}
	}
	else {
		if (parentofDelete != NULL) {
			if (parentofDelete->left == deleteNode) {
				parentofDelete->left = NULL;
			}
			else {
				parentofDelete->right = NULL;
			}
		}
		else {
			bineryTree->root = NULL;
		}
	}
	if (deleteNode != NULL) {
		free(deleteNode);
	}
	bineryTree->length--;
	if (bineryTree->root != NULL) {
		if (parentofDelete != NULL) {
			if (compare(bineryTree->root + 1, key) > 0) {
				bineryTree->balance++;
			}
			else {
				bineryTree->balance--;
			}
		}
		else {
			if (compare(bineryTree->root + 1, key) < 0) {
				bineryTree->balance++;
			}
			else {
				bineryTree->balance--;
			}
		}
	}
	return NULL;
}
BineryNode* Search(BineryTree *bineryTree, void *key, int(*compare)(void*, void*)) {
	BineryNode *index;
	
	index = bineryTree->root;
	while (index != NULL && compare(index + 1, key) != 0) {
		if (compare(index + 1, key) > 0) {
			index = index->left;
		}
		else {
			index = index->right;
		}
	}
	
	return index;
}
void BineryTree_GetAt(BineryTree *bineryTree, BineryNode *index, void *key, size_t size) {
	memcpy(key, index + 1, size);
}
void MakeBalance(BineryTree *bineryTree, size_t size) {
	void(*keys);
	Long count;

	MakeKeys(bineryTree, &keys, &count, size);
	BineryTree_DeleteAllItems(bineryTree);
	MakeTree(bineryTree, keys, count, size);
	if (keys != NULL) {
		free(keys);
	}
}
void MakeKeys(BineryTree *bineryTree, void *(*keys), Long *count, size_t size) {
	Long i = 0;
	*count = 0;
	
	*keys = calloc(bineryTree->length, size);
	Node_MakeKeys(bineryTree->root, *keys, count, &i, size);
}
void Node_MakeKeys(BineryNode *node, void(*keys), Long *count, Long *i, size_t size) {
	if (node != NULL) {
		Node_MakeKeys(node->left, keys, count, i, size);
		memcpy(((char(*))keys) + ((*i)*size), node + 1, size);
		(*i)++;
		(*count)++;
		Node_MakeKeys(node->right, keys, count, i, size);
	}
}
void BineryTree_DeleteAllItems(BineryTree *bineryTree) {
	BineryTree_Node_DeleteAllItems(bineryTree->root);
	bineryTree->root = NULL;
	bineryTree->length = 0;
	bineryTree->balance = 0;
}
void BineryTree_Node_DeleteAllItems(BineryNode *node) {
	if (node != NULL) {
		BineryTree_Node_DeleteAllItems(node->left);
		BineryTree_Node_DeleteAllItems(node->right);
		free(node);
	}
}
void MakeTree(BineryTree *bineryTree, void(*keys), Long count, size_t size) {
	Long remainder;

	bineryTree->root = Node_MakeTree(keys, 0, count - 1, size);
	bineryTree->length = count;
	remainder = count % 2;
	if (remainder == 0) {
		bineryTree->balance = 1;
	}
}
BineryNode* Node_MakeTree(void(*keys), Long first, Long last, size_t size) {
	BineryNode *node = NULL;
	Long mid;

	if (first <= last) {
		node = (BineryNode*)malloc(sizeof(BineryNode) + size);
		mid = (first + last) / 2;
		memcpy(node + 1, ((char(*))keys) + (mid*size), size);
		node->left = Node_MakeTree(keys, first, mid - 1, size);
		node->right = Node_MakeTree(keys, mid + 1, last, size);
	}

	return node;
}
void BineryTree_Destroy(BineryTree *bineryTree) {
	BineryTree_Node_Destroy(bineryTree->root);
}
void BineryTree_Node_Destroy(BineryNode *node) {
	if (node != NULL) {
		BineryTree_Node_Destroy(node->left);
		BineryTree_Node_Destroy(node->right);
		free(node);
	}
}