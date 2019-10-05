#ifndef _ARRAY_H
#define _ARRAY_H


#include <stddef.h> //size_t

typedef signed long int Long;

typedef struct _array {
	void (*front);
	Long capacity;
	Long length;
}Array;

void Array_Create(Array *array, Long capacity, size_t size);
Long Array_Store(Array *array, Long index, void *object, size_t size);
Long Array_Insert(Array *array, Long index, void *object, size_t size);
Long Array_AppendFromFront(Array *array, void *object, size_t size);
Long Array_AppendFromRear(Array *array, void *object, size_t size);
Long Array_Delete(Array *array, Long index, size_t size);
Long Array_DeleteFromFront(Array *array, size_t size);
Long Array_DeleteFromRear(Array *array, size_t size);
void Array_Clear(Array *array);
Long Array_Modify(Array *array, Long index, void *object, size_t size);
Long Array_LinearSearchUnique(Array *array, void *key, size_t size, int(*compare)(void*, void*));
void Array_LinearSearchDuplicate(Array *array, void *key, Long* (*indexes), Long *count, size_t size, int(*compare)(void*, void*));
Long Array_BinerySearchUnique(Array *array, void *key, size_t size, int(*compare)(void*, void*));
void Array_BinerySearchDuplicate(Array *array, void *key, Long* (*indexes), Long *count, size_t size, int(*compare)(void*, void*));
void Array_BubbleSort(Array *array, size_t size, int(*compare)(void*, void*));
void Array_SelectionSort(Array *array, size_t size, int(*compare)(void*, void*));
void Array_InsertionSort(Array *array, size_t size, int(*compare)(void*, void*));
void Array_Merge(Array *array, Array one, Array other, size_t size, int(*compare)(void*, void*));
void Array_Destroy(Array *array);
void Array_GetAt(Array *array, Long index, void *object, size_t size);

#endif //_ARRAY_H