/*
파일명: GetBiggestNumber
기  능: 수를 입력받아 그 수의 자릿수의 조합으로 만들 수 있는 가장 큰 수를 구하여 출력한다.
작성자: 김찬형
작성일: 19.1.17
*/
#include<stdio.h>
#pragma warning(disable:4996)

typedef signed long int Long;

//선언부
int main(int argc, char* argv[]);
Long Input();
Long GetBiggestNumber(Long number);
void Output(Long biggestNumber);

//정의부
int main(int argc, char* argv[]) {
	Long number;
	Long biggestNumber;
	//호출
	number = Input();
	biggestNumber = GetBiggestNumber(number);
	Output(biggestNumber);

	return 0;
}
/*
함수명: Input
기  능: 수를 외부입력받는다.
입  력: 없음
출  력: 수
*/
Long Input() {
	Long number;
	scanf("%d", &number);
	return number;
}
/*
함수명: GetBiggestNumber
기  능: 입력받은 수의 자릿수의 조합으로 만들 수 있는 가장 큰 수를 구하여 출력한다.
입  력: 수
출  력: 가장 큰 수
*/
Long GetBiggestNumber(Long number) {
	Long biggestNumber = 0;
	Long digit;
	Long count = 0;
	Long dividend;
	Long digitNumber;

	for (digit = 9; digit >= 0; digit--) {
		dividend = number;
		while (dividend > 0) {
			digitNumber = dividend % 10;
			if (digitNumber == digit) {
				count++;
			}
			dividend /= 10;
		}
		while (count > 0) {
			biggestNumber = biggestNumber * 10 + digit;
			count--;
		}
	}
	return biggestNumber;
}
/*
함수명: Output
기  능: 가장 큰 수를 모니터에 출력한다.
입  력: 가장 큰 수
출  력: 없음
*/
void Output(Long biggestNumber) {
	printf("가장 큰 수 : %d\n", biggestNumber);
}
