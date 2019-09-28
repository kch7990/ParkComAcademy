/*
파일 명칭: Escape.c
기능: 우물의 높이를 입력받아 그 우물을 달팽이가 탈출하는 데 걸리는 일수를 구한다.
작성자: 김찬형
작성일자: 19.01.16
*/
#include<stdio.h>
#define UP 3
#define DOWN 2

//자료형 선언
typedef unsigned long int ULong;

//선언부
int main(int argc, char* argv[]);
ULong Input();
ULong Escape(ULong wellHeight);
void Output(ULong wellHeight, ULong day);

//정의부
int main(int argc, char* argv[]) {
	ULong wellHeight;
	ULong day;

	//함수 호출
	wellHeight = Input();
	day = Escape(wellHeight);
	Output(wellHeight, day);

	return 0;
}
/*
함수 명칭: Input
기능: 우물의 높이를 입력받는다.
입력: 없음
출력: 우물의 높이
*/
ULong Input() {
	ULong wellHeight;
	scanf("%d", &wellHeight);
	return wellHeight;
}
/*
함수 명칭: Escape
기능: 우물의 높이를 입력받아 달팽이가 그 우물을 탈출하는데 걸리는 일수를 구하여 출력한다.
입력: 우물의 높이
출력: 일수
*/
ULong Escape(ULong wellHeight) {
	ULong day = 1;
	ULong upHeight = UP;
	ULong downHeight;

	while (upHeight < wellHeight) {
		downHeight = upHeight - DOWN;
		day++;
		upHeight = downHeight + UP;
	}
	return day;
}
/*
함수 명칭: Output
기능: 달팽이가 우물을 탈출한 데 걸린 일수를 모니터에 출력한다.
입력: 우물의 높이, 일수
출력: 없음
*/
void Output(ULong wellHeight, ULong day) {
	printf("%dm의 우물을 %d일 후 탈출했다.\n", wellHeight, day);
}