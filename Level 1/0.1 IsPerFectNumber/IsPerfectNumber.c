/*
파일 명칭: IsPerfectNumber.c
기능: 수를 입력받아 완전수인지 판별하다.
작성자: 김찬형
작성일자: 19.01.16.
*/
#include<stdio.h>
typedef enum _boolean {FALSE=0, TRUE=1} Boolean;
typedef unsigned long int ULong;
//선언부
int main(int argc, char* argv[]);
ULong Input();
Boolean IsPerfectNumber(ULong number);
void Output(ULong numeber, Boolean IsPerfectNumber);
//정의부
int main(int argc, char* argv[]) {
	ULong number;
	Boolean isPerfectNumber;
	//함수 호출
	number = Input();
	isPerfectNumber = IsPerfectNumber(number);
	Output(number, isPerfectNumber);

	return 0;
}
/*
함수 명칭: Input
기능: 수를 입력받는다.
입력: 없음
출력: 수
*/
ULong Input() {
	ULong number;
	scanf("%d", &number);
	return number;
}
/*
함수 명칭: IsPerfectNumber
기능: 수의 완전수여부를 판별한다.
입력: 수
출력: 완전수여부
*/
Boolean IsPerfectNumber(ULong number) {
	Boolean isPerfectNumber;
	ULong factor = 0;
	ULong sum = 0;
	ULong i = 1;
	ULong remainder;

	while (i < number) {
		factor++;
		remainder = number % factor;
		if (remainder == 0) {
			sum += factor;
		}
		i++;
	}
	if (sum == number) {
		isPerfectNumber = TRUE;
	}
	else {
		isPerfectNumber = FALSE;
	}
	return isPerfectNumber;
}
/*
함수 명칭: Output
기능: 완전수를 판별한 결과를 모니터에 출력한다.
입력: 수, 완전수여부
출력: 없음
*/
void Output(ULong number, Boolean isPerfectNumber) {
	if (isPerfectNumber == TRUE) {
		printf("%d는 완전수입니다.\n", number);
	}
	else {
		printf("%d는 완전수가 아닙니다.\n", number);
	}
}
