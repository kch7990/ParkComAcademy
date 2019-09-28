/*
파일명: InsertAscend.c
기  능: 수들을 오름차순으로 정렬하여 정렬 전 수들과 정렬 후 수들을 함께 출력한다.
작성자: 김찬형
작성일: 19.1.24
*/
#include<stdio.h>
#define MAX 10
#pragma warning(disable:4996)

typedef signed long int Long;

//선언부
int main(int argc, char* argv[]);
void Input(Long(*numbers));
void Ascend(Long(*numbers), Long(*ascends));
void Output(Long(*numbers), Long(*ascends));

//정의부
int main(int argc, char* argv[]) {
	Long numbers[MAX];
	Long ascends[MAX];
	//호출
	Input(numbers);
	Ascend(numbers, ascends);
	Output(numbers, ascends);

	return 0;
}
/*
함수명: Input
기  능: 수들을 외부입력받는다.
입  력: 없음
출  력: 수들
*/
void Input(Long(*numbers)) {
	Long i;
	for (i = 0; i < MAX; i++) {
		scanf("%d", numbers + i);
	}
}
/*
함수명: Ascend
기  능: 수들을 오름차순 정렬한 오름차순들을 구해 출력한다.
입  력: 수들
출  력: 오름차순들
*/
void Ascend(Long(*numbers), Long(*ascends)) {
	Long i;
	Long j;
	Long temp;

	for (i = 0; i < MAX; i++) {
		ascends[i] = numbers[i];
	}
	for (i = 1; i < MAX; i++) {
		temp = ascends[i];
		j = i - 1;
		while (j >= 0 && temp < ascends[j]) {
			ascends[j + 1] = ascends[j];
			j--;
		}
		ascends[j + 1] = temp;
	}
}
/*
함수명: Output
기  능: 수들과 오름차순들을 모니터에 출력한다.
입  력: 수들, 오름차순들
출  력: 없음
*/
void Output(Long(*numbers), Long(*ascends)) {
	Long i;
	for (i = 0; i < MAX; i++) {
		printf("%d ", numbers[i]);
	}printf("\n");
	for (i = 0; i < MAX; i++) {
		printf("%d ", ascends[i]);
	}
}