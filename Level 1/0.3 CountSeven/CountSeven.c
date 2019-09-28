/*
파일명: CountSeven
기  능: 1부터 10000까지 7의 개수를 세어 출력한다.
작성자: 김찬형
작성일: 19.1.17
*/
#include<stdio.h>
#define MAX 10000
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//선언부
int main(int argc, char* argv[]);
ULong CountSeven();
void Output(ULong countSeven);

//정의부
int main(int argc, char* argv[]) {
	ULong countSeven;
	//함수 호출
	countSeven = CountSeven();
	Output(countSeven);

	return 0;
}
/*
함수명: CountSeven
기  능: 1부터 10000까지 7의 개수를 세어 출력한다.
입  력: 없음
출  력: 7의 개수
*/
ULong CountSeven() {
	ULong countSeven = 0;
	ULong number;
	ULong digitNumber;
	ULong dividend;

	for (number = 1; number <= MAX; number++) {
		dividend = number;
		while (dividend > 0) {
			digitNumber = dividend % 10;
			if (digitNumber == 7) {
				countSeven++;
			}
			dividend /= 10;
		}
	}
	return countSeven;
}
/*
함수명: Output
기  능: 7의 개수를 모니터에 출력한다.
입  력: 7의 개수
출  력: 없음
*/
void Output(ULong countSeven) {
	printf("1부터 %d까지 7의 개수는 %d개이다.\n", MAX, countSeven);
}
