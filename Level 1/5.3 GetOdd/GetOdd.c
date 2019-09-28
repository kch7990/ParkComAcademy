/*
파일명: GetOdd.c
기  능: 수들을 입력받아 그 중 홀수들의 합과 최소 홀수를 구하여 출력한다.
작성자: 김찬형
작성일: 19.1.23
*/
#include<stdio.h>
#define MAX 7
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//선언부
int main(int argc, char* argv[]);
void Input(ULong(*numbers));
void GetOdd(ULong(*numbers), ULong *sum, ULong *smallest);
void Output(ULong sum, ULong smallest);

//정의부
int main(int argc, char* argv[]) {
	ULong numbers[MAX];
	ULong sum;
	ULong smallest;
	//호출
	Input(numbers);
	GetOdd(numbers, &sum, &smallest);
	Output(sum, smallest);

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
함수명: GetOdd
기  능: 수들 중 홀수들의 합과 최소홀수를 구하여 출력한다.
입  력: 수들
출  력: 합, 최솟값
*/
void GetOdd(ULong(*numbers), ULong *sum, ULong *smallest) {
	ULong i;
	ULong remainder;
	*sum = 0;
	*smallest = 0;

	for (i = 0; i < MAX; i++) {
		remainder = numbers[i] % 2;
		if (remainder == 1) {
			(*sum) += numbers[i];
			if (numbers[i] < *smallest || *smallest == 0) {
				*smallest = numbers[i];
			}
		}
	}
}
/*
함수명: Output
기  능: 합과 최솟값을 모니터에 출력한다.
입  력: 합, 최솟값
출  력: 없음
*/
void Output(ULong sum, ULong smallest) {
	printf("합: %d 최솟값: %d\n", sum, smallest);
}
