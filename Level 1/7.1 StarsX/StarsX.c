/*
파일명: StarsX.c
기  능: 별들로 X모양을 만들어 출력한다.
작성자: 김찬형
작성일: 19.1.24
*/
#include<stdio.h>
#define ROWS 5
#define COLUMNS 5
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//선언부
int main(int argc, char* argv[]);
void Stars(char(*stars)[COLUMNS]);
void Output(char(*stars)[COLUMNS]);

//정의부
int main(int argc, char* argv[]) {
	char stars[ROWS][COLUMNS];
	//호출
	Stars(stars);
	Output(stars);

	return 0;
}
/*
함수명: Stars
기  능: 별들로 X모양을 만든다.
입  력: 없음
출  력: 별들
*/
void Stars(char(*stars)[COLUMNS]) {
	ULong row;
	ULong column;
	ULong pairIndex;

	for (row = 0; row < ROWS; row++) {
		pairIndex = (ROWS - 1) - row;
		for (column = 0; column < COLUMNS; column++) {
			if (column == row) {
				stars[row][column] = '*';
			}
			else if (column == pairIndex) {
				stars[row][column] = '*';
			}
			else {
				stars[row][column] = ' ';
			}
		}
	}
}
/*
함수명: Output
기  능: 별들을 모니터에 출력한다.
입  력: 별들
출  력: 없음
*/
void Output(char(*stars)[COLUMNS]) {
	ULong row;
	ULong column;

	for (row = 0; row < ROWS; row++) {
		for (column = 0; column < COLUMNS; column++) {
			printf("%c", stars[row][column]);
		}
		printf("\n");
	}
}