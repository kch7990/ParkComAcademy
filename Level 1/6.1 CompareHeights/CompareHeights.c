/*
파일명: CompareHeights
기  능: 키들을 입력받아 가장 큰 키와 두번째로 큰 키를 구하여 출력한다.
작성자: 김찬형
작성일: 19.1.23
*/
#include<stdio.h>
#define MAX 7
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//선언부
int main(int argc, char* argv[]);
void Input(ULong(*heights));
void CompareHeights(ULong(*heights), ULong *first, ULong *second);
void Output(ULong first, ULong second);

//정의부
int main(int argc, char* argv[]) {
	ULong heights[MAX];
	ULong first;
	ULong second;
	//호출
	Input(heights);
	CompareHeights(heights, &first, &second);
	Output(first, second);

	return 0;
}
/*
함수명: Input
기  능: 키들을 외부입력받는다.
입  력: 없음
출  력: 키들
*/
void Input(ULong(*heights)) {
	ULong i;
	for (i = 0; i < MAX; i++) {
		scanf("%d", heights + i);
	}
}
/*
함수명: CompareHeights
기  능: 키들 중 가장 큰 키와 두번째로 큰 키를 구하여 출력한다.
입  력: 키들
출  력: 가장큰키, 두번째큰키
*/
void CompareHeights(ULong(*heights), ULong *first, ULong *second) {
	ULong i;
	*first = 0;

	for (i = 0; i < MAX; i++) {
		if (heights[i] > *first) {
			*second = *first;
			*first = heights[i];
		}
		else if (heights[i] > *second) {
			*second = heights[i];
		}
	}
}
/*
함수명: Output
기  능: 가장 큰 키와 두번째로 큰 키를 모니터에 출력한다.
입  력: 가장큰키, 두번째큰키
출  력: 없음
*/
void Output(ULong first, ULong second) {
	printf("가장 큰 키: %d\n두번째 큰 키: %d\n", first, second);
}