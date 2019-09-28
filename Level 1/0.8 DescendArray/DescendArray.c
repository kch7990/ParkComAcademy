/*
파일명: DescendArray.c
기  능: 수 세개를 입력받아 내림차순으로 정렬하여 출력한다.
작성자: 김찬형
작성일: 19.1.22
*/
#include<stdio.h>
#define MAX 3
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//선언부
int main(int argc, char* argv[]);
void Input(ULong(*numbers));
void DescendArray(ULong(*numbers));
void Output(ULong(*numbers));

//정의부
int main(int argc, char* argv[]) {
	ULong numbers[MAX];
	//호출
	Input(numbers);
	DescendArray(numbers);
	Output(numbers);

	return 0;
}
/*
함수명: Input
기  능: 수 세개를 외부입력받는다.
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
함수명: DescendArray
기  능: 수들을 내림차순으로 정렬한다.
입  력: 수들
출  력: 수들
*/
void DescendArray(ULong(*numbers)) {
	ULong i;
	ULong j;
	ULong temp;

	for (i = 0; i < MAX - 1; i++) {
		j = i + 1;
		while (j < MAX) {
			if (numbers[i] < numbers[j]) {
				temp = numbers[i];
				numbers[i] = numbers[j];
				numbers[j] = temp;
			}
			j++;
		}
	}
}
/*
함수명: Output
기  능: 수들을 모니터에 출력한다.
입  력: 수들
출  력: 없음
*/
void Output(ULong(*numbers)) {
	ULong i;
	for (i = 0; i < MAX; i++) {
		printf("%d ", numbers[i]);
	}
}