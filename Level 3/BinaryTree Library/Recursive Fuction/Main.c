#include "BineryTree.h"
#include <stdio.h>

int CompareKeys(void *one, void *other);

int main(int argc, char* argv[]) {
	BineryTree bineryTree;
	BineryNode *node;
	Long key;
	Long ret;

	//1. 이분검색트리를 만든다.
	Create(&bineryTree);
	//2. 100을 삽입한다.
	key = 100;
	node = Insert(&bineryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&bineryTree, node, &ret, sizeof(Long));
	printf("%d\n", ret);
	//3. 50을 삽입한다.
	key = 50;
	node = Insert(&bineryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&bineryTree, node, &ret, sizeof(Long));
	printf("%d\n", ret);
	//4. 200을 삽입한다.
	key = 200;
	node = Insert(&bineryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&bineryTree, node, &ret, sizeof(Long));
	printf("%d\n", ret);
	//5. 50을 찾는다.
	key = 50;
	node = Search(&bineryTree, &key, CompareKeys);
	GetAt(&bineryTree, node, &ret, sizeof(Long));
	printf("%d\n", ret);
	//6. 50을 삭제한다.
	node = Delete(&bineryTree, &key, CompareKeys);
	if (node == NULL) {
		printf("지워졌습니다.\n");
	}
	//7. 150을 삽입한다.
	key = 150;
	node = Insert(&bineryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&bineryTree, node, &ret, sizeof(Long));
	printf("%d\n", ret);
	//8. 균형을 맞춘다.
	MakeBalance(&bineryTree, sizeof(Long));
	//9. 이분검색트리를 없앤다.
	Destroy(&bineryTree);

	return 0;
}
int CompareKeys(void *one, void *other) {
	Long *one_ = (Long*)one;
	Long *other_ = (Long*)other;
	int ret;

	if (*one_ > *other_) {
		ret = 1;
	}
	else if (*one_ == *other_) {
		ret = 0;
	}
	else if (*one_ < *other_) {
		ret = -1;
	}
	return ret;
}