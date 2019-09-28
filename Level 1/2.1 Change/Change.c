/*
파일명: Change.c
기  능: 물건값을 입력받아 거스름돈을 어떻게 줘야 할지 구하여 출력한다.
작성자: 김찬형
작성일: 19.1.21
*/
#include<stdio.h>
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//선언부
int main(int argc, char* argv[]);
ULong Input();
void Change(ULong price, ULong *count500, ULong *count100, ULong *count50, ULong *count10);
void Output(ULong count500, ULong count100, ULong count50, ULong count10);

//정의부
int main(int argc, char* argv[]) {
	ULong price;
	ULong count500;
	ULong count100;
	ULong count50;
	ULong count10;
	//호출
	price = Input();
	Change(price, &count500, &count100, &count50, &count10);
	Output(count500, count100, count50, count10);

	return 0;
}
/*
함수명: Input
기  능: 가격을 외부입력받는다.
입  력: 없음
출  력: 가격
*/
ULong Input() {
	ULong price;
	scanf("%d", &price);
	return price;
}
/*
함수명: Change
기  능: 거스름돈을 어떻게 줘야 하는지 동전별로 개수를 구한다.
입  력: 가격
출  력: 500원개수, 100원개수, 50원개수, 10원개수
*/
void Change(ULong price, ULong *count500, ULong *count100, ULong *count50, ULong *count10) {
	ULong change;
	ULong money = 0;
	*count500 = 0;
	*count100 = 0;
	*count50 = 0;
	*count10 = 0;
	
	while (money < price) {
		money += 1000;
	}change = money - price;
	while (change >= 500) {
		*count500= *count500 +1;
		change -= 500;
	}
	while (change >= 100) {
		*count100 = *count100 + 1;
		change -= 100;
	}
	while (change >= 50) {
		*count50 = *count50 + 1;
		change -= 50;
	}
	while (change > 0) {
		*count10 = *count10 + 1;
		change -= 10;
	}
}
/*
함수명: Output
기  능: 동전별 개수를 모니터에 출력한다.
입  력: 500원개수, 100원개수, 50원개수, 10원개수
출  력: 없음
*/
void Output(ULong count500, ULong count100, ULong count50, ULong count10) {
	printf("500원 개수: %d\n100원 개수: %d\n50원 개수: %d\n10원 개수: %d\n", count500, count100, count50, count10);
}
