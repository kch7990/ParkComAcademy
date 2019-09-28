/*
파일명: Divide.c
기  능: 두 자연수를 입력받아 앞의 수를 뒤의 수로 나눴을 때 몫과 나머지를 구한다.
작성자: 김찬형
작성일: 2019.1.19
*/
#include<stdio.h>
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//선언부
int main(int argc, char* argv[]);
void Input(ULong *number1, ULong *number2);
void Divide(ULong number1, ULong number2, ULong *quotient, ULong *remainder);
void Output(ULong quotient, ULong remainder);

//정의부
int main(int argc, char* argv[]) {
	ULong number1;
	ULong number2;
	ULong quotient;
	ULong remainder;
	//함수 호출
	Input(&number1, &number2);
	Divide(number1, number2, &quotient, &remainder);
	Output(quotient, remainder);

	return 0;
}
/*
함수명: Input
기  능: 두 자연수를 외부입력받는다.
입  력: 없음
출  력: 수1, 수2
*/
void Input(ULong *number1, ULong *number2) {
	scanf("%d %d", number1, number2);
}
/*
함수명: Divide
기  능: 입력받은 두 수를 서로 나눠 몫과 나머지를 구한다.
입  력: 수1, 수2
출  력: 몫, 나머지
*/
void Divide(ULong number1, ULong number2, ULong *quotient, ULong *remainder) {
	*quotient = number1 / number2;
	*remainder = number1 % number2;
}
/*
함수명: Output
기  능: 몫과 나머지를 모니터에 출력한다.
입  력: 몫, 나머지
출  력: 없음
*/
void Output(ULong quotient, ULong remainder) {
	printf("몫: %d, 나머지: %d\n", quotient, remainder);
}
