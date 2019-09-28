/*
파일명: FillNumbers3.c
기  능: 중간으로 갈 수록 높은 수를 저장하는 수들을 만들어 출력한다.
작성자: 김찬형
작성일: 19.1.24
*/
#include<stdio.h>
#define ROWS 5
#define COLUMNS 5
#pragma warning(disable:4996)

typedef signed long int Long;

//선언부
int main(int argc, char* argv[]);
void FillNumbers(Long(*numbers)[COLUMNS]);
void Output(Long(*numbers)[COLUMNS]);

//정의부
int main(int argc, char* argv[]) {
	Long numbers[ROWS][COLUMNS];
	//호출
	FillNumbers(numbers);
	Output(numbers);

	return 0;
}
/*
함수명: FillNumbers
기  능: 중간으로 갈 수록 높은 수를 저장하는 수들을 만든다.
입  력: 없음
출  력: 수들
*/
void FillNumbers(Long(*numbers)[COLUMNS]) {
	Long number;
	Long row;
	Long column;
	Long middle;
	Long pairIndex;

	middle = ROWS / 2;
	for (row = 0; row < ROWS; row++) {
		pairIndex = (ROWS - 1) - row;
		for (column = 0; column < COLUMNS; column++) {
			if ((column < middle - row || column > middle + row) || (column < middle - pairIndex || column > middle + pairIndex)) {
				number = 0;
				numbers[row][column] = number;
			}
			else if (column <= middle) {
				number++;
				numbers[row][column] = number;
			}
			else {
				number--;
				numbers[row][column] = number;
			}
		}
	}
}
/*
함수명: Output
기  능: 수들을 모니터에 출력한다.
입  력: 수들
출  력: 없음
*/
void Output(Long(*numbers)[COLUMNS]) {
	Long row;
	Long column;

	for (row = 0; row < ROWS; row++) {
		for (column = 0; column < COLUMNS; column++) {
			printf("%d ", numbers[row][column]);
		}
		printf("\n");
	}
}
