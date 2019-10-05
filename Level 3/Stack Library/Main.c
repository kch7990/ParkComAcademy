#include "Stack.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
	Stack stack;
	Long object;
	Long index;
	Long ret;
	Boolean isEmpty;
	
	//1. 스택을 만들다.
	Stack_Create(&stack, 2, sizeof(Long));
	//2. 100을 넣다.
	object = 100;
	Push(&stack, &object, sizeof(Long));
	Top(&stack, &ret, sizeof(Long));
	printf("%d\n", ret);
	//3. 200을 넣다.
	object = 200;
	Push(&stack, &object, sizeof(Long));
	Top(&stack, &ret, sizeof(Long));
	printf("%d\n", ret);
	//4. 50을 넣다.
	object = 50;
	Push(&stack, &object, sizeof(Long));
	Top(&stack, &ret, sizeof(Long));
	printf("%d\n", ret);
	//5. 꺼내다.
	index = Pop(&stack);
	if (index == -1) {
		printf("지웠다.\n");
	}
	//비어있는지 확인한다.
	isEmpty = Stack_IsEmpty(&stack);
	if (isEmpty == TRUE) {
		printf("비어있다.\n");
	}
	else {
		printf("비어있지 않다.\n");
	}
	//6. 비우다.
	Stack_Empty(&stack);
	if (stack.top == 0) {
		printf("모두 지웠다.\n");
	}
	//비어있는지 확인한다.
	isEmpty = Stack_IsEmpty(&stack);
	if (isEmpty == TRUE) {
		printf("비어있다.\n");
	}
	else {
		printf("비어있지 않다.\n");
	}
	//7. 20을 넣다.
	object = 20;
	Push(&stack, &object, sizeof(Long));
	Top(&stack, &ret, sizeof(Long));
	printf("%d\n", ret);
	//8. 스택을 지우다.
	Stack_Destroy(&stack);

	return 0;
}