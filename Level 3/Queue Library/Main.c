#include "Queue.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
	Queue queue;
	QueueNode *node;
	Long object;
	Long ret;
	Boolean isEmpty;

	//1. 큐를 만들다.
	Queue_Create(&queue);
	//2. 100을 넣다.
	object = 100;
	Put(&queue, &object, sizeof(Long));
	//3. 마지막을 확인하다.
	Rear(&queue, &ret, sizeof(Long));
	printf("%d\n", ret);
	//4. 200을 넣다.
	object = 200;
	Put(&queue, &object, sizeof(Long));
	//5. 마지막을 확인하다.
	Rear(&queue, &ret, sizeof(Long));
	printf("%d\n", ret);
	//6. 비어있는지 확인하다.
	isEmpty = Queue_IsEmpty(&queue);
	if (isEmpty == TRUE) {
		printf("비어있다.\n");
	}
	else {
		printf("비어있지 않다\n");
	}
	//7. 비우다.
	Queue_Empty(&queue);
	//8. 비어있는지 확인하다.
	isEmpty = Queue_IsEmpty(&queue);
	if (isEmpty == TRUE) {
		printf("비어있다.\n");
	}
	else {
		printf("비어있지 않다\n");
	}
	//9. 300을 넣다.
	object = 300;
	Put(&queue, &object, sizeof(Long));
	//10. 50을 넣다.
	object = 50;
	Put(&queue, &object, sizeof(Long));
	//11. 처음을 구하다.
	Front(&queue, &ret, sizeof(Long));
	printf("%d\n", ret);
	//12. 빼다.
	node = Get(&queue);
	if (node == NULL) {
		printf("지워졌다.\n");
	}
	//13. 큐를 지우다.
	Queue_Destroy(&queue);

	return 0;
}