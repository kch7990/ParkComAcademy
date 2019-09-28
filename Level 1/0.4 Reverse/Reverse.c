/*
파일명: Reverse.c
기  능: 수를 입력받아 그 수를 뒤집은수를 구하여 출력한다.
작성자: 김찬형
작성일: 19.1.17
*/
#include<stdio.h>
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//선언부
int main(int argc, char* argv[]);
ULong Input();
ULong Reverse(ULong number);
void Output(ULong reversedNumber);

//정의부
int main(int argc, char* argv[]) {
	ULong number;
	ULong reversedNumber;
	//함수 호출
	number = Input();
	reversedNumber = Reverse(number);
	Output(reversedNumber);

	return 0;
}
/*
함수명: Input
기  능: 수를 외부입력받는다.
입  력: 없음
출  력: 수
*/
ULong Input() {
	ULong number;
	scanf("%d", &number);
	return number;
}
/*
함수명: Reverse
기  능: 수를 입력받아 뒤집은 수를 구하여 출력한다.
입  력: 수
출  력: 뒤집은 수
*/
ULong Reverse(ULong number) {
	ULong reversedNumber = 0;
	ULong digitNumber;
	ULong dividend;

	dividend = number;
	while (dividend > 0) {
		digitNumber = dividend % 10;
		reversedNumber = reversedNumber * 10 + digitNumber;
		dividend /= 10;
	}
	return reversedNumber;
}
/*
함수명: Output
기  능: 뒤집은 수를 모니터에 출력한다.
입  력: 뒤집은 수
출  력: 없음
*/
void Output(ULong reversedNumber) {
	printf("뒤집은 수: %d\n", reversedNumber);
}
