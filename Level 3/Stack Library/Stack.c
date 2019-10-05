#include "Stack.h"
#include <stdlib.h>
#include <memory.h>

void Stack_Create(Stack *stack, Long capacity, size_t size) {
	stack->front = calloc(capacity, size);
	stack->capacity = capacity;
	stack->length = 0;
	stack->top = 0;
}
Long Push(Stack *stack, void *object, size_t size) {
	void(*objects);
	Long i;

	if (stack->length >= stack->capacity) {
		objects = calloc(stack->capacity + 1, size);
		i = 0;
		while (i < stack->length) {
			memcpy(((char(*))objects) + (i*size), ((char(*))stack->front) + (i*size), size);
			i++;
		}
		if (stack->front != NULL) {
			free(stack->front);
		}
		stack->front = objects;
		stack->capacity++;
		stack->top = stack->length;
	}
	memcpy(((char(*))stack->front) + ((stack->top) * size), object, size);
	stack->length++;
	stack->top++;

	return stack->top;
}
Long Pop(Stack *stack) {
	stack->top--;
	stack->length--;

	return -1;
}
void Top(Stack *stack, void *object, size_t size) {
	memcpy(object, ((char(*))stack->front) + ((stack->top - 1) * size), size);
}
void Stack_Empty(Stack *stack) {
	stack->top = 0;
	stack->length = 0;
}
void Stack_Destroy(Stack *stack) {
	if (stack->front != NULL) {
		free(stack->front); 
	}
}
Boolean Stack_IsEmpty(Stack *stack) {
	Boolean ret;
	if (stack->length == 0) {
		ret = TRUE;
	}
	else {
		ret = FALSE;
	}
	return ret;
}