/*
파일명: Clap.c
기  능: 마지막 수까지 수를 세면서 3의 배수이거나 3이 들어가는 수면 박수를 치는 369게임을 한다.
작성자: 김찬형
작성일: 19.1.23
*/
#include<stdio.h>
#define MAX 1000
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//선언부
int main(int argc, char* argv[]);
ULong Input();
void Clap(ULong lastNumber, ULong(*numbers), ULong(*clapNumbers));
void Output(ULong lastNumber, ULong(*numbers), ULong(*clapNumbers));

//정의부
int main(int argc, char* argv[]) {
	ULong lastNumber;
	ULong numbers[MAX];
	ULong clapNumbers[MAX];
	//호출
	lastNumber = Input();
	Clap(lastNumber, numbers, clapNumbers);
	Output(lastNumber, numbers, clapNumbers);

	return 0;
}
/*
함수명: Input
기  능: 마지막 수를 외부입력받는다.
입  력: 없음
출  력: 마지막수
*/
ULong Input() {
	ULong lastNumber;
	scanf("%d", &lastNumber);
	return lastNumber;
}
/*
함수명: Clap
기  능: 마지막 수까지 수를 세면서 수들과 박수칠 수들을 구하여 출력한다.
입  력: 마지막수
출  력: 수들, 박수칠수들
*/
void Clap(ULong lastNumber, ULong(*numbers), ULong(*clapNumbers)) {
	ULong remainder;
	ULong digitNumber;
	ULong number = 1;
	ULong i = 0;
	ULong j = 0;
	ULong countDigit;
	ULong dividend;

	while (number <= lastNumber) {
		remainder = number % 3;
		if (remainder == 0) {
			clapNumbers[i] = number;
			i++;
		}
		else {
			countDigit = 0;
			dividend = number;
			while (dividend > 0) {
				digitNumber = dividend % 10;
				if (digitNumber == 3) {
					countDigit++;
				}
				dividend /= 10;
			}
			if (countDigit >= 1) {
				clapNumbers[i] = number;
				i++;
			}
			else {
				numbers[j] = number;
				j++;
			}
		}
		number++;
	}
}
/*
함수명: Output
기  능: 수를 세며 박수친다.
입  력: 마지막수, 수들, 박수칠수들
출  력: 없음
*/
void Output(ULong lastNumber, ULong(*numbers), ULong(*clapNumbers)) {
	ULong number = 1;
	ULong i = 0;
	ULong j = 0;
	while (number <= lastNumber) {
		if (number == clapNumbers[i]) {
			printf("Clap ");
			i++;
		}
		else {
			printf("%d ", numbers[j]);
			j++;
		}
		number++;
	}
}