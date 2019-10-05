#include "LinkedList.h"
#include <stdlib.h>
#include <stdio.h>

int Compare(void *one, void *other);
int main(int argc, char* argv[]) {
	LinkedList linkedList;
	Node *index;
	Node* (*indexes);
	Long count;
	Long object;
	Long key;
	Long ret;
	Long i;
	Node *previous;

	//1. 연결 리스트를 생성한다.
	Create(&linkedList);
	//2. 100을 맨 뒤에 추가한다.	100`
	object = 100;
	index = AppendFromTail(&linkedList, &object, sizeof(Long));
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	previous = NULL;
	linkedList.current = linkedList.head;
	//3. 200을 맨 앞에 추가한다.	200` 100
	object = 200;
	index = AppendFromHead(&linkedList, &object, sizeof(Long));
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	//4. 다음으로 이동한다.			200 100`
	index = Next(&linkedList);
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	//5. 300을 100 앞에 삽입한다.	200 300` 100
	object = 300;
	index = InsertBefore(&linkedList, index, &object, sizeof(Long));
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	//6. 처음으로 이동한다.			200` 300 100
	index = First(&linkedList);
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	//7. 400을 200 뒤에 삽입한다.	200 400` 300 100
	object = 400;
	index = InsertAfter(&linkedList, index, &object, sizeof(Long));
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	//8. 300을 선형검색하다.		200 400 300` 100
	key = 300;
	index = LinearSearchUnique(&linkedList, &key, Compare);
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	//9. 300을 삭제하다.			200 400 100`
	index = Delete(&linkedList, index);
	if (index == NULL) {
		printf("지워졌습니다\n");
	}
	//10. 100의 이전으로 이동한다.	200 400` 100
	index = Previous(&linkedList);
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	//11. 200을 맨 뒤에 추가한다.	200 400 100 200`
	object = 200;
	index = AppendFromTail(&linkedList, &object, sizeof(Long));
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	//12. 200을 선형검색하다.		200 400 100 200`
	key = 200;
	LinearSearchDuplicate(&linkedList, &key, &indexes, &count, Compare);
	i = 0;
	while (i < count) {
		index = indexes[i];
		GetAt(&linkedList, index, &ret, sizeof(Long));
		printf("%d\n", ret);
		i++;
	}
	//13. 처음 200으로 이동한다.	200` 400 100 200
	index = indexes[0];
	index = Move(&linkedList, index);
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	//14. 맨 뒤를 삭제하다.			200 400 100`
	index = DeleteFromTail(&linkedList);
	if (index == NULL) {
		printf("지워졌습니다\n");
	}
	
	//15. 맨 앞을 삭제하다.			400` 100
	index = DeleteFromHead(&linkedList);
	if (index == NULL) {
		printf("지워졌습니다\n");
	}
	//16. 맨 뒤로 이동한다.			400 100`
	index = Last(&linkedList);
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	//17. 전부 삭제한다.			-
	DeleteAllItems(&linkedList);
	if (linkedList.length == 0) {
		printf("전부 지워졌습니다\n");
	}
	//18. 500을 맨 뒤에 추가한다.	500`
	object = 500;
	index = AppendFromTail(&linkedList, &object, sizeof(Long));
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	//19. 100을 500 앞에 삽입한다.	100` 500
	object = 100;
	index = InsertBefore(&linkedList, index, &object, sizeof(Long));
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	//20. 연결리스트를 없앤다.		-
	Destroy(&linkedList);

	return 0;
}
int Compare(void *one, void *other) {
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