/*
파일명: FindKey.c
기  능: 수들과 찾고자 하는 값을 입력받아 그 값의 위치들을 찾아서 출력한다.
작성자: 김찬형
작성일: 19.1.22
*/
#include<stdio.h>
#define MAX 10
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//선언부
int main(int argc, char* argv[]);
void Input(ULong(*numbers), ULong *key);
void FindKey(ULong(*numbers), ULong key, ULong(*indexes), ULong *count);
void Output(ULong(*indexes), ULong count);

//정의부
int main(int argc, char* argv[]) {
	ULong numbers[MAX];
	ULong key;
	ULong indexes[MAX];
	ULong count;
	//호출
	Input(numbers, &key);
	FindKey(numbers, key, indexes, &count);
	Output(indexes, count);

	return 0;
}
/*
함수명: Input
기  능: 수들과 키를 외부입력받는다.
입  력: 없음
출  력: 수들, 키
*/
void Input(ULong(*numbers), ULong *key) {
	ULong i;
	printf("수들\n");
	for (i = 0; i < MAX; i++) {
		scanf("%d", numbers + i);
	}
	printf("키 ");
	scanf("%d", key);
}
/*
함수명: FindKey
기  능: 수들 중에 키의 위치들을 찾아서 출력한다.
입  력: 수들, 키
출  력: 위치들, 개수(사용량)
*/
void FindKey(ULong(*numbers), ULong key, ULong(*indexes), ULong *count) {
	ULong i;
	ULong j = 0;
	*count = 0;

	for (i = 0; i < MAX; i++) {
		if (numbers[i] == key) {
			indexes[j] = i;
			j++;
			(*count)++;
		}
	}
}
/*
함수명: Output
기  능: 위치들을 모니터에 출력한다.
입  력: 위치들, 개수(사용량)
출  력: 없음
*/
void Output(ULong(*indexes), ULong count) {
	ULong j = 0;
	printf("위치들\n");
	while (j < count) {
		printf("%d ", indexes[j] + 1);
		j++;
	}
	if (count == 0) {
		printf("찾고자 하는 값이 없다.\n");
	}
}
