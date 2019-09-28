/*
파일명: FillNumbers2.c
기  능: 수를 세면서 거꾸로 된 ㄴ자를 계속해서 그리는 형태의 수들 배열을 만든다.
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
기  능: 수를 세면서 거꾸로 된 ㄴ자를 계속해서 그리는 형태의 수들 배열을 만든다.
입  력: 없음
출  력: 수들
*/
void FillNumbers(Long(*numbers)[COLUMNS]) {
	Long number = 1;
	Long row;
	Long column;
	Long i;
	Long remainder;

	for (i = 0; i < ROWS; i++) {
		remainder = i % 2;
		if (remainder == 0) {
			row = 0;
			column = i;
			while (row <= column) {
				numbers[row][column] = number;
				number++;
				row++;
			}
			row = i;
			column = i - 1;
			while (column >= 0) {
				numbers[row][column] = number;
				number++;
				column--;
			}
		}
		else {
			column = 0;
			row = i;
			while (column <= row) {
				numbers[row][column] = number;
				number++;
				column++;
			}
			column = i;
			row = i - 1;
			while (row >= 0) {
				numbers[row][column] = number;
				number++;
				row--;
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
			printf("%2d ", numbers[row][column]);
		}
		printf("\n");
	}
}