/*
파일명: SumPrime.c
기  능: 두 수를 입력받아 그 사이의 수 중 소수들의 합을 구하여 출력한다.
작성자: 김찬형
작성일: 19.1.21
*/
#include<stdio.h>
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//선언부
int main(int argc, char* argv[]);
void Input(ULong *number1, ULong *number2);
ULong SumPrime(ULong number1, ULong number2);
void Output(ULong sum);

//정의부
int main(int argc, char* argv[]) {
	ULong number1;
	ULong number2;
	ULong sum;
	//호출
	Input(&number1, &number2);
	sum = SumPrime(number1, number2);
	Output(sum);

	return 0;
}
/*
함수명: Input
기  능: 두 수를 외부입력받는다.
입  력: 없음
출  력: 수1, 수2
*/
void Input(ULong *number1, ULong *number2) {
	scanf("%d %d", number1, number2);
}
/*
함수명: SumPrime
기  능: 두 수 사이의 수 중 소수의 합을 구하여 출력한다.
입  력: 수1, 수2
출  력: 합
*/
ULong SumPrime(ULong number1, ULong number2) {
	ULong sum = 0;
	ULong i;
	ULong j;
	ULong count;
	ULong remainder;

	i = number1;
	while (i <= number2) {
		count = 0;
		j = 2;
		while (j < i) {
			remainder = i % j;
			if (remainder == 0) {
				count++;
			}
			j++;
		}
		if (count == 0) {
			sum += i;
		}
		i++;
	}
	return sum;
}
/*
함수명: Output
기  능: 합을 모니터에 출력한다.
입  력: 합
출  력: 없음
*/
void Output(ULong sum) {
	printf("소수의 합:%d\n", sum);
}

