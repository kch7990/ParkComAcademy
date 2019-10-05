#include "Queue.h"
#include <stdlib.h>
#include <memory.h>

void Queue_Create(Queue *queue) {
	queue->front = NULL;
	queue->rear = NULL;
	queue->length = 0;
}
QueueNode* Put(Queue *queue, void *object, size_t size) {
	QueueNode *node;

	node = (QueueNode*)malloc(sizeof(QueueNode) + size);
	memcpy(node + 1, object, size);
	node->next = NULL;
	if (queue->rear != NULL) {
		queue->rear->next = node;
	}
	else {
		queue->front = node;
	}
	queue->rear = node;
	queue->length++;

	return queue->rear;
}
QueueNode* Get(Queue *queue) {
	QueueNode *node;

	node = queue->front->next;
	if (queue->front != NULL) {
		free(queue->front);
	}
	if (node == NULL) {
		queue->rear = NULL;
	}
	queue->front = node;
	queue->length--;

	return NULL;
}
void Front(Queue *queue, void *object, size_t size) {
	memcpy(object, queue->front + 1, size);
}
void Rear(Queue *queue, void *object, size_t size) {
	memcpy(object, queue->rear + 1, size);
}
void Queue_Empty(Queue *queue) {
	QueueNode *node;

	node = queue->front;
	while (node != NULL) {
		queue->front = queue->front->next;
		free(node);
		node = queue->front;
	}
	queue->rear = NULL;
	queue->length = 0;
}
Boolean Queue_IsEmpty(Queue *queue) {
	Boolean ret;

	if (queue->length == 0) {
		ret = TRUE;
	}
	else {
		ret = FALSE;
	}

	return ret;
}
void Queue_Destroy(Queue *queue) {
	QueueNode *node;

	node = queue->front;
	while (node != NULL) {
		queue->front = queue->front->next;
		free(node);
		node = queue->front;
	}
}