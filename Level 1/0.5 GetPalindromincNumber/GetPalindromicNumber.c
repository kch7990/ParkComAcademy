/*
파일명: GetPalindromicNumber.c
기  능: 수를 입력받아 회문수를 구하여 출력한다.
작성자: 김찬형
작성일: 19.1.17
*/
#include<stdio.h>
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//선언부
int main(int argc, char* argv[]);
ULong Input();
ULong GetPalindromicNumber(ULong number);
void Output(ULong number);

//정의부
int main(int argc, char* argv[]) {
	ULong number;
	//함수 호출
	number = Input();
	number = GetPalindromicNumber(number);
	Output(number);

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
함수명: GetPalindromicNumber
기  능: 수를 입력받아 회문수를 구하여 출력한다.
입  력: 수
출  력: 수(회문)
*/
ULong GetPalindromicNumber(ULong number) {
	ULong reversedNumber=0;
	ULong dividend;
	ULong digitNumber;

	while (reversedNumber != number) {
		number += reversedNumber;
		reversedNumber = 0;
		dividend = number;
		while (dividend > 0) {
			digitNumber = dividend % 10;
			reversedNumber = reversedNumber * 10 + digitNumber;
			dividend /= 10;
		}
	}
	return number;
}
/*
함수명: Output
기  능: 수(회문)을 모니터에 출력한다.
입  력: 수
출  력: 없음
*/
void Output(ULong number) {
	printf("구해지는 회문수: %d\n", number);
}
