/*
파일명: SumDigit.c
기  능: 수를 입력받아 자릿수의 합을 구하여 출력한다.
작성자: 김찬형
작성일: 19.1.17
*/
//전처리부
#include<stdio.h>
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//선언부
int main(int argc, char* argv[]);
ULong Input();
ULong SumDigit(ULong number);
void Output(ULong sum);

//정의부
int main(int argc, char* argv[]) {
	ULong number;
	ULong sum;
	//함수 호출
	number = Input();
	sum = SumDigit(number);
	Output(sum);

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
함수명: SumDigit
기  능: 수를 입력받아 자릿수의 합을 구하여 출력한다.
입  력: 수
출  력: 합
*/
ULong SumDigit(ULong number) {
	ULong sum = 0;
	ULong digitNumber;
	ULong dividend;

	dividend = number;
	while (dividend > 0) {
		digitNumber = dividend % 10;
		sum += digitNumber;
		dividend /= 10;
	}
	return sum;
}
/*
함수명: Output
기  능: 모니터에 합을 출력한다.
입  력: 합
출  력: 없음
*/
void Output(ULong sum) {
	printf("자릿수 합: %d\n", sum);
}