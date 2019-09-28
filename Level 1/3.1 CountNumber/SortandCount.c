/*
파일명: SortandCount.c
기  능: 수들을 입력받아 양수, 음수, 짝수, 홀수의 개수를 구하여 출력한다.
작성자: 김찬형
작성일: 19.1.22
*/
#include<stdio.h>
#define MAX 5
#pragma warning(disable:4996)

typedef signed long int Long;

//선언부
int main(int argc, char* argv[]);
void Input(Long(*numbers));
void SortandCount(Long(*numbers), Long *positive, Long *negative, Long *even, Long *odd);
void Output(Long positive, Long negative, Long even, Long odd);

//정의부
int main(int argc, char* argv[]) {
	Long numbers[MAX];
	Long positive;
	Long negative;
	Long even;
	Long odd;
	//호출
	Input(numbers);
	SortandCount(numbers, &positive, &negative, &even, &odd);
	Output(positive, negative, even, odd);

	return 0;
}
/*
함수명: Input
기  능: 수 100개를 외부입력받는다.
입  력: 없음
출  력: 수들
*/
void Input(Long(*numbers)) {
	Long i;
	for (i = 0; i < MAX; i++) {
		scanf("%d", numbers + i);
	}
}
/*
함수명: SortandCount
기  능: 수들 중에 양수, 음수, 짝수, 홀수의 개수를 센다.
입  력: 수들
출  력: 양수개수, 음수개수, 짝수개수, 홀수개수
*/
void SortandCount(Long(*numbers), Long *positive, Long *negative, Long *even, Long *odd) {
	Long remainder;
	Long i;
	*positive = 0;
	*negative = 0;
	*even = 0;
	*odd = 0;

	for (i = 0; i < MAX; i++) {
		if (numbers[i] > 0) {
			(*positive)++;
			remainder = numbers[i] % 2;
			if (remainder == 0) {
				(*even)++;
			}
			else {
				(*odd)++;
			}
		}
		else if (numbers[i] < 0) {
			(*negative)++;
		}
	}
}
/*
함수명: Output
기  능: 양수, 음수, 짝수, 홀수의 개수를 모니터에 출력한다.
입  력: 양수개수, 음수개수, 짝수개수, 홀수개수
출  력: 없음
*/
void Output(Long positive, Long negative, Long even, Long odd) {
	printf("양수:%d개 음수:%d개 짝수:%d개 홀수:%d개\n", positive, negative, even, odd);
}