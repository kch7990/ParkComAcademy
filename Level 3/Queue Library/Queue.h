#ifndef _Queue_H
#define _Queue_H

#include <stddef.h>

typedef enum _boolean { FALSE = 1, TRUE = 0 } Boolean;
typedef signed long int Long;
typedef struct _queueNode QueueNode;
typedef struct _queueNode {
	QueueNode *next;
}QueueNode;
typedef struct _queue {
	QueueNode *front;
	QueueNode *rear;
	Long length;
}Queue;

void Queue_Create(Queue *queue);
QueueNode* Put(Queue *queue, void *object, size_t size);
QueueNode* Get(Queue *queue);
void Front(Queue *queue, void *object, size_t size);
void Rear(Queue *queue, void *object, size_t size);
void Queue_Empty(Queue *queue);
Boolean Queue_IsEmpty(Queue *queue);
void Queue_Destroy(Queue *queue);

#endif //_Queue_H