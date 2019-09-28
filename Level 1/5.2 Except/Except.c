/*
파일명: Except.c
기  능: 수들을 입력받아 중복되지 않은 수들만 골라 출력한다.
작성자: 김찬형
작성일: 19.1.23
*/
#include<stdio.h>
#define MAX 10
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//선언부
int main(int argc, char* argv[]);
void Input(ULong(*numbers));
void Except(ULong(*numbers), ULong(*excepts), ULong *length);
void Output(ULong(*excepts), ULong length);

//정의부
int main(int argc, char* argv[]) {
	ULong numbers[MAX];
	ULong excepts[MAX];
	ULong length;
	//호출
	Input(numbers);
	Except(numbers, excepts, &length);
	Output(excepts, length);

	return 0;
}
/*
함수명: Input
기  능: 수들을 외부입력받는다.
입  력: 없음
출  력: 수들
*/
void Input(ULong(*numbers)) {
	ULong i;
	for (i = 0; i < MAX; i++) {
		scanf("%d", numbers + i);
	}
}
/*
함수명: Except
기  능: 수들 중 중복되지 않은 수들만 골라 출력한다.
입  력: 수들
출  력: 중복안된수들, 개수
*/
void Except(ULong(*numbers), ULong(*excepts), ULong *length) {
	ULong i;
	ULong j;
	ULong k = 0;
	ULong count;
	*length = 0;

	for (i = 0; i < MAX; i++) {
		count = 0;
		for (j = 0; j < MAX; j++) {
			if (numbers[i] == numbers[j]) {
				count++;
			}
		}
		if (count == 1) {
			excepts[k] = numbers[i];
			k++;
			(*length)++;
		}
	}
}
/*
함수명: Output
기  능: 중복안된수들을 모니터에 출력한다.
입  력: 중복안된수들, 개수
출  력: 없음
*/
void Output(ULong(*excepts), ULong length) {
	ULong k = 0;
	while (k < length) {
		printf("%d ", excepts[k]);
		k++;
	}
}