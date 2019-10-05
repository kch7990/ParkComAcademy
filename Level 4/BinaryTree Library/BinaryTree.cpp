#include "BinaryTree.h"
#include <iostream>
using namespace std;

int CompareKeys(void *one, void *other);

int main(int argc, char *argv[]) {
	BinaryTree<Long> binaryTree;
	BinaryTree<Long>::Node *node;

	node = binaryTree.Insert(100, CompareKeys);
	cout << node->GetKey() << endl;

	node = binaryTree.Insert(50, CompareKeys);
	cout << node->GetKey() << endl;

	node = binaryTree.Insert(200, CompareKeys);
	cout << node->GetKey() << endl;

	node = binaryTree.Search(50, CompareKeys);
	if (node != 0) {
		cout << node->GetKey() << endl;
	}

	node = binaryTree.Delete(50, CompareKeys);
	if (node == 0) {
		cout << "삭제됐습니다." << endl;
	}

	node = binaryTree.Insert(150, CompareKeys);
	cout << node->GetKey() << endl;

	binaryTree.MakeBalance();
	cout << binaryTree.GetBalance() << endl;
#if 0
	BinaryTree<Long> another(binaryTree);
	Long (*keys);
	Long count;
	another.MakeKeys(&keys, &count);
	Long i = 0;
	while (i < count) {
		cout << keys[i] << " ";
		i++;
	}
	cout << endl;
	if (keys != 0) {
		delete[] keys;
	}

	another.Delete(200, CompareKeys);
	binaryTree = another;
	binaryTree.MakeKeys(&keys, &count);
	i = 0;
	while (i < count) {
		cout << keys[i] << " ";
		i++;
	}
	cout << endl;
	if (keys != 0) {
		delete[] keys;
	}
#endif
	return 0;
}
int CompareKeys(void *one, void *other) {
	Long *one_ = static_cast<Long *>(one);
	Long *other_ = static_cast<Long *>(other);
	int ret;
	if (*one_ < *other_) {
		ret = -1;
	}
	else if (*one_ == *other_) {
		ret = 0;
	}
	else if (*one_>*other_) {
		ret = 1;
	}
	return ret;
}