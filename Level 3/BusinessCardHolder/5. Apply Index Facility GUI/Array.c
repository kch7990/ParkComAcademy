#include "Array.h"
#include <stdlib.h> //calloc, free
#include <memory.h> //memcpy

void Array_Create(Array *array, Long capacity, size_t size) {
	array->front = calloc(capacity, size);
	array->capacity = capacity;
	array->length = 0;
}
Long Array_Store(Array *array, Long index, void *object, size_t size) {
	memcpy(((char(*))array->front) + (index*size), object, size);
	(array->length)++;

	return index;
}
Long Array_Insert(Array *array, Long index, void *object, size_t size) {
	Long i = 0;
	Long j = 0;
	void(*objects);

	objects = calloc(array->capacity + 1, size);
	while (i < index) {
		memcpy(((char(*))objects) + (j*size), ((char(*))array->front) + (i*size), size);
		j++;
		i++;
	}
	j++;
	while(i < array->length){
		memcpy(((char(*))objects) + (j*size), ((char(*))array->front) + (i*size), size);
		j++;
		i++;
	}
	if (array->front != NULL) {
		free(array->front);
	}
	array->front = objects;
	(array->capacity)++;
	memcpy(((char(*))array->front) + (index*size), object, size);
	(array->length)++;

	return index;
}
Long Array_AppendFromFront(Array *array, void *object, size_t size) {
	Long index;
	void(*objects);
	Long i = 0;

	objects = calloc(array->capacity + 1, size);
	while (i < array->length) {
		memcpy(((char(*))objects) + ((i + 1)*size), ((char(*))array->front) + (i*size), size);
		i++;
	}
	if (array->front != NULL) {
		free(array->front);
	}
	array->front = objects;
	(array->capacity)++;
	index = 0;
	memcpy(((char(*))array->front) + (index*size), object, size);
	(array->length)++;

	return index;
}
Long Array_AppendFromRear(Array *array, void *object, size_t size) {
	Long index;
	void(*objects);
	Long i = 0;

	objects = calloc(array->capacity + 1, size);
	while (i < array->length) {
		memcpy(((char(*))objects) + (i*size), ((char(*))array->front) + (i*size), size);
		i++;
	}
	if (array->front != NULL) {
		free(array->front);
	}
	array->front = objects;
	(array->capacity)++;
	index = array->capacity - 1;
	memcpy(((char(*))array->front) + (index*size), object, size);
	(array->length)++;

	return index;
}
Long Array_Delete(Array *array, Long index, size_t size) {
	void(*objects);
	Long i = 0;
	Long j = 0;

	objects = calloc(array->capacity - 1, size);
	while (i < array->length) {
		if (i != index) {
			memcpy(((char(*))objects) + (j*size), ((char(*))array->front) + (i*size), size);
			j++;
		}
		i++;
	}
	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	array->front = objects;
	(array->capacity)--;
	(array->length)--;
	index = -1;

	return index;
}
Long Array_DeleteFromFront(Array *array, size_t size) {
	Long index;
	void(*objects) = NULL;
	Long i = 1;

	if (array->capacity > 1) {
		objects = calloc(array->capacity - 1, size);
	}
	while (i < array->length) {
		memcpy(((char(*))objects) + (i*size), ((char(*))array->front) + ((i + 1)*size), size);
		i++;
	}
	if (array->front != NULL) {
		free(array->front);
	}
	array->front = objects;
	(array->capacity)--;
	(array->length)--;
	index = -1;

	return index;
}
Long Array_DeleteFromRear(Array *array, size_t size) {
	Long index;
	void(*objects)=NULL;
	Long i = 0;

	if (array->capacity > 1) {
		objects = calloc(array->capacity + 1, size);
	}
	while (i < array->length - 1) {
		memcpy(((char(*))objects) + (i*size), ((char(*))array->front) + (i*size), size);
		i++;
	}
	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	if (array->capacity > 1) {
		array->front = objects;
	}
	(array->capacity)--;
	(array->length)--;
	index = -1;

	return index;
}
void Array_Clear(Array *array) {
	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	array->capacity = 0;
	array->length = 0;
}
Long Array_Modify(Array *array, Long index, void *object, size_t size) {
	memcpy(((char(*))array->front) + (index*size), object, size);

	return index;
}
Long Array_LinearSearchUnique(Array *array, void *key, size_t size, int(*compare)(void*, void*)) {
	Long index = -1;
	Long i = 0;

	while (i < array->length && compare(((char(*))array->front) + (i*size), key) != 0) {
		i++;
	}
	if (i < array->length) {
		index = i;
	}

	return index;
}
void Array_LinearSearchDuplicate(Array *array, void *key, Long* (*indexes), Long *count, size_t size, int(*compare)(void*, void*)) {
	Long i = 0;
	Long j = 0;
	*count = 0;

	*indexes = (Long(*))calloc(array->length, sizeof(Long));
	while (i < array->length) {
		if (compare(((char(*))array->front) + (i*size), key) == 0) {
			(*indexes)[j] = i;
			j++;
			(*count)++;
		}
		i++;
	}
}
Long Array_BinerySearchUnique(Array *array, void *key, size_t size, int(*compare)(void*, void*)) {
	Long index = -1;
	Long start = 0;
	Long end;
	Long searchIndex;

	end = array->length - 1;
	searchIndex = (start + end) / 2;
	while (start <= end && compare(((char(*))array->front) + (searchIndex*size), key) != 0) {
		if (compare(((char(*))array->front) + (searchIndex*size), key) < 0) {
			start = searchIndex + 1;
		}
		else {
			end = searchIndex - 1;
		}
		searchIndex = (start + end) / 2;
	}
	if (start <= end) {
		index = searchIndex;
	}

	return index;
}
void Array_BinerySearchDuplicate(Array *array, void *key, Long* (*indexes), Long *count, size_t size, int(*compare)(void*, void*)) {
	Long start = 0;
	Long end;
	Long searchIndex;
	Long i;
	Long j = 0;
	*count = 0;

	*indexes = (Long(*))calloc(array->length, sizeof(Long));
	end = array->length - 1;
	searchIndex = (start + end) / 2;
	while (start <= end && compare(((char(*))array->front) + (searchIndex*size), key) != 0) {
		if (compare(((char(*))array->front) + (searchIndex*size), key) < 0) {
			start = searchIndex + 1;
		}
		else {
			end = searchIndex - 1;
		}
		searchIndex = (start + end) / 2;
	}
	i = searchIndex - 1;
	while (i >= start && compare(((char(*))array->front) + (i*size), key) == 0) {
		i--;
	}
	start = i + 1;
	i = start;
	while (i <= end && compare(((char(*))array->front) + (i*size), key) == 0) {
		(*indexes)[j] = i;
		j++;
		(*count)++;
		i++;
	}
}
void Array_BubbleSort(Array *array, size_t size, int(*compare)(void*, void*)) {
	Long i = 0;
	Long j;
	void *temp;
	Long check = 1;

	temp = malloc(size);
	
	while (i < array->length - 1 && check==1) {
		check = 0;
		j = 0;
		while (j < array->length - i - 1) {
			if (compare(((char(*))array->front) + (j*size), ((char(*))array->front) + ((j + 1)*size)) > 0) {
				memcpy(temp, ((char(*))array->front) + (j*size), size);
				memcpy(((char(*))array->front) + (j*size), ((char(*))array->front) + ((j + 1)*size), size);
				memcpy(((char(*))array->front) + ((j + 1)*size), temp, size);
				check = 1;
			}
			j++;
		}
		i++;
	}

	if (temp != NULL) {
		free(temp);
	}
}
void Array_SelectionSort(Array *array, size_t size, int(*compare)(void*, void*)) {
	Long index;
	Long i = 0;
	Long j;
	void *temp;

	temp = malloc(size);

	while (i < array->length - 1) {
		index = i;
		j = i + 1;
		while (j < array->length) {
			if (compare(((char(*))array->front) + (j*size), ((char(*))array->front) + (index*size)) < 0) {
				index = j;
			}
			j++;
		}
		memcpy(temp, ((char(*))array->front) + (i*size), size);
		memcpy(((char(*))array->front) + (i*size), ((char(*))array->front) + (index*size), size);
		memcpy(((char(*))array->front) + (index*size), temp, size);
		i++;
	}

	if (temp != NULL) {
		free(temp);
	}
}
void Array_InsertionSort(Array *array, size_t size, int(*compare)(void*, void*)) {
	Long i = 1;
	Long j;
	void *temp;

	temp = malloc(size);

	while (i < array->length) {
		memcpy(temp, ((char(*))array->front) + (i*size), size);
		j = i - 1;
		while (j >= 0 && compare(((char(*))array->front) + (j*size), temp) > 0) {
			memcpy(((char(*))array->front) + ((j + 1)*size), ((char(*))array->front) + (j*size), size);
			j--;
		}
		memcpy(((char(*))array->front) + ((j + 1)*size), temp, size);
		i++;
	}

	if (temp != NULL) {
		free(temp);
	}
}
void Array_Merge(Array *array, Array one, Array other, size_t size, int(*compare)(void*, void*)) {
	Long i = 0;
	Long j = 0;
	Long k = 0;

	if (array->front != NULL) {
		free(array->front);
	}
	array->front = calloc(one.length + other.length, size);
	array->capacity = one.length + other.length;
	array->length = 0;
	while (i < one.length && j < other.length) {
		if (compare(((char(*))one.front) + (i*size), ((char(*))other.front) + (j*size)) < 0) {
			memcpy(((char(*))array->front) + (k*size), ((char(*))one.front) + (i*size), size);
			k++;
			(array->length)++;
			i++;
		}
		else {
			memcpy(((char(*))array->front) + (k*size), ((char(*))other.front) + (j*size), size);
			k++;
			(array->length)++;
			j++;
		}
	}
	while (i < one.length) {
		memcpy(((char(*))array->front) + (k*size), ((char(*))one.front) + (i*size), size);
		k++;
		(array->length)++;
		i++;
	}
	while (j < other.length) {
		memcpy(((char(*))array->front) + (k*size), ((char(*))other.front) + (j*size), size);
		k++;
		(array->length)++;
		j++;
	}
}
void Array_Destroy(Array *array) {
	if (array->front != NULL) {
		free(array->front);
	}
}
void Array_GetAt(Array *array, Long index, void *object, size_t size) {
	memcpy(object, ((char(*))array->front) + (index*size), size);
}