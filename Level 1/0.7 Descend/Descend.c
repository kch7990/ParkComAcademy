/*
파일명: Descend.c
기  능: 수 세개를 입력받아 내림차순으로 출력한다.
작성자: 김찬형
작성일: 19.1.21
*/
#include<stdio.h>
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//선언부
int main(int argc, char* argv[]);
void Input(ULong *number1, ULong *number2, ULong *number3);
void Descend(ULong number1, ULong number2, ULong number3, ULong *biggest, ULong *middle, ULong *smallest);
void Output(ULong biggest, ULong middle, ULong smallest);

//정의부
int main(int argc, char* argv[]) {
	ULong number1;
	ULong number2;
	ULong number3;
	ULong biggest;
	ULong middle;
	ULong smallest;
	//호출
	Input(&number1, &number2, &number3);
	Descend(number1, number2, number3, &biggest, &middle, &smallest);
	Output(biggest, middle, smallest);

	return 0;
}
/*
함수명: Input
기  능: 수 세개를 외부입력받는다.
입  력: 없음
출  력: 수1, 수2, 수3
*/
void Input(ULong *number1, ULong *number2, ULong *number3) {
	scanf("%d %d %d", number1, number2, number3);
}
/*
함수명: Descend
기  능: 세 수를 내림차순으로 정렬한다.
입  력: 수1, 수2, 수3
출  력: 큰수, 중간수, 작은수
*/
void Descend(ULong number1, ULong number2, ULong number3, ULong *biggest, ULong *middle, ULong *smallest) {
	if (number1 > number2) {
		if (number1 > number3) {
			if (number2 > number3) {
				*biggest = number1;
				*middle = number2;
				*smallest = number3;
			}
			else {
				*biggest = number1;
				*middle = number3;
				*smallest = number2;
			}
		}
		else {
			*biggest = number3;
			*middle = number1;
			*smallest = number2;
		}
	}
	else {
		if (number2 > number3) {
			if (number1 > number3) {
				*biggest = number2;
				*middle = number1;
				*smallest = number3;
			}
			else {
				*biggest = number2;
				*middle = number3;
				*smallest = number1;
			}
		}
		else {
			*biggest = number3;
			*middle = number2;
			*smallest = number1;
		}
	}
}
/*
함수명: Output
기  능: 큰 수, 중간수, 작은수를 모니터에 출력한다.
입  력: 큰수, 중간수, 작은수
출  력: 없음
*/
void Output(ULong biggest, ULong middle, ULong smallest) {
	printf("%d %d %d\n", biggest, middle, smallest);
}
