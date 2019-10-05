#include "Array.h"
#include <stdio.h> //printf
#include <stdlib.h> //free

int Compare(void* one, void* other);

int main(int argc, char* argv[]) {
	Array array;
	Long index; //Long 반환 함수의 출력
	Long object; //입력
	Long key; //입력
	Long(*indexes); //~SearchDuplicate 출력
	Long count; //~SearchDuplicate 출력
	Array one;
	Array other;
	Long ret; //GetAt 출력
	Long i; //반복제어변수

	//1. 배열을 3만큼 할당하다.
	Create(&array, 3, sizeof(Long));

	//2. 숫자 30을 위치 1에 저장하다.
	object = 30;
	index = Store(&array, 0, &object, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);							//30
	
	//3. 숫자 10을 위치 2에 저장하다.
	object = 10;
	index = Store(&array, 1, &object, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);							//30 10

	//4. 숫자 20을 위치 3에 저장하다.
	object = 20;
	index = Store(&array, 2, &object, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);							//30 10 20

	//5. 숫자 20을 위치 2에 삽입하다.
	object = 20;
	index = Insert(&array, 1, &object, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);							//30 20 10 20

	//6. 20을 선형검색하다.
	key = 20;
	LinearSearchDuplicate(&array, &key, &indexes, &count, sizeof(Long), Compare);
	i = 0;
	while (i < count) {
		index = indexes[i];
		GetAt(&array, index, &ret, sizeof(Long));
		printf("%d ", ret);
		i++;
	}printf("\n");
	if (indexes != NULL) {
		free(indexes);
	}
	
	//7. 맨 뒤의 배열요소를 삭제하다.
	index = DeleteFromRear(&array, sizeof(Long));
	if (index == -1) {
		printf("지워졌습니다.\n");
	}												//30 20 10

	//8. 맨 앞에 숫자 50을 추가하다.
	object = 50;
	index = AppendFromFront(&array, &object, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);							//50 30 20 10

	//9. 10을 선형검색하다.
	key = 10;
	index = LinearSearchUnique(&array, &key, sizeof(Long), Compare);
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	//10. 거품 정렬하다.
	BubbleSort(&array, sizeof(Long), Compare);
	i = 0;
	while (i < array.length) {
		GetAt(&array, i, &ret, sizeof(Long));
		printf("%d ", ret);
		i++;
	}printf("\n");									//10 20 30 50

	//11. 클리어하다.
	Clear(&array);
	if (array.front == NULL) {
		printf("클리어했습니다.\n");
	}

	//12. one 배열을 2만큼 생성하다.
	Create(&one, 2, sizeof(Long));

	//13. 숫자 50을 one의 위치 1에 저장하다.
	object = 50;
	index = Store(&one, 0, &object, sizeof(Long));
	GetAt(&one, index, &ret, sizeof(Long));
	printf("%d\n", ret);							//50

	//14. 숫자 90을 one의 위치 2에 저장하다.
	object = 90;
	index = Store(&one, 1, &object, sizeof(Long));
	GetAt(&one, index, &ret, sizeof(Long));
	printf("%d\n", ret);							//50 90

	//15. other 배열을 3만큼 생성하다.
	Create(&other, 3, sizeof(Long));

	//16. 숫자 60을 other의 위치 1에 저장하다.
	object = 60;
	index = Store(&other, 0, &object, sizeof(Long));
	GetAt(&other, index, &ret, sizeof(Long));
	printf("%d\n", ret);							//60

	//17. 숫자 70을 other의 위치 2에 저장하다.
	object = 70;
	index = Store(&other, 1, &object, sizeof(Long));
	GetAt(&other, index, &ret, sizeof(Long));
	printf("%d\n", ret);							//60 70

	//18. 숫자 80을 other의 위치 3에 저장하다.
	object = 80;
	index = Store(&other, 2, &object, sizeof(Long));
	GetAt(&other, index, &ret, sizeof(Long));
	printf("%d\n", ret);							//60 70 80

	//19. one과 other를 병합하다.
	Merge(&array, one, other, sizeof(Long), Compare);
	i = 0;
	while (i < array.length) {
		GetAt(&array, i, &ret, sizeof(Long));
		printf("%d ", ret);
		i++;
	}printf("\n");									//50 60 70 80 90 

	//20. 위치 4의 배열요소를 삭제하다.
	index = Delete(&array, 3, sizeof(Long));
	if (index == -1) {
		printf("지워졌습니다.\n");					//50 60 70 90
	}

	//21. 70을 이분검색하다.
	key = 70;
	index = BinerySearchUnique(&array, &key, sizeof(Long), Compare);
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	//22. 맨 뒤에 숫자 40을 추가하다.
	object = 40;
	index = AppendFromRear(&array, &object, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);							//50 60 70 90 40

	//23. 선택 정렬하다.
	SelectionSort(&array, sizeof(Long), Compare);
	i = 0;
	while (i < array.length) {	
		GetAt(&array, i, &ret, sizeof(Long));
		printf("%d ", ret);
		i++;
	}printf("\n");									//40 50 60 70 90

	//24. 맨 앞의 배열요소를 삭제하다.
	index = DeleteFromFront(&array, sizeof(Long));
	if (index == -1) {
		printf("지워졌습니다.\n");
	}												//50 60 70 90
	
	//25. 위치 1의 배열요소를 숫자 90으로 수정하다.
	object = 90;
	index = Modify(&array, 0, &object, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);							//90 60 70 90

	//26. 삽입 정렬하다.
	InsertionSort(&array, sizeof(Long), Compare);
	i = 0;
	while (i < array.length) {
		GetAt(&array, i, &ret, sizeof(Long));
		printf("%d ", ret);
		i++;
	}printf("\n");									//60 70 90 90

	//27. 90을 이분 검색하다.
	key = 90;
	BinerySearchDuplicate(&array, &key, &indexes, &count, sizeof(Long), Compare);
	i = 0;
	while (i < count) {
		index = indexes[i];
		GetAt(&array, index, &ret, sizeof(Long));
		printf("%d ", ret);
		i++;
	}printf("\n");
	if (indexes != NULL) {
		free(indexes);
	}

	//28. other를 없애다.
	Destroy(&other);

	//29. one을 없애다.
	Destroy(&one);

	//30. 배열을 없애다.
	Destroy(&array);

	return 0;
}
int Compare(void* one, void* other) {
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