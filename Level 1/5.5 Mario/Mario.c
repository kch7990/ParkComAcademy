/*
파일명: Mario.c
기  능: 마리오가 버섯 10개를 집는 게임을 할 때 100점에 가능한 한 가까운 점수를 얻도록 하는 프로그램
작성자: 김찬형
작성일: 19.1.23
*/
#include<stdio.h>
#define MAX 10
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//선언부
int main(int argc, char* argv[]);
void Input(ULong(*mushrooms));
ULong Mario(ULong(*mushrooms));
void Output(ULong score);

//정의부
int main(int argc, char* argv[]) {
	ULong mushrooms[MAX];
	ULong score;
	//호출
	Input(mushrooms);
	score = Mario(mushrooms);
	Output(score);

	return 0;
}
/*
함수명: Input
기  능: 버섯들을 외부입력받는다.
입  력: 없음
출  력: 버섯들
*/
void Input(ULong(*mushrooms)) {
	ULong i;
	for (i = 0; i < MAX; i++) {
		scanf("%d", mushrooms + i);
	}
}
/*
함수명: Mario
기  능: 마리오가 얻어야 할 점수를 구하여 출력한다.
입  력: 버섯들
출  력: 점수
*/
ULong Mario(ULong(*mushrooms)) {
	ULong score = 0;
	ULong beforeScore;
	ULong afterScore;
	ULong beforeGap;
	ULong afterGap;
	ULong i;

	for (i = 0; i < MAX; i++) {
		beforeScore = score;
		afterScore = beforeScore + mushrooms[i];
		if (beforeScore < 100) {
			beforeGap = 100 - beforeScore;
		}
		else {
			beforeGap = beforeScore - 100;
		}
		if (afterScore < 100) {
			afterGap = 100 - afterScore;
		}
		else {
			afterGap = afterScore - 100;
		}
		if (afterGap <= beforeGap) {
			score = afterScore;
		}
	}
	return score;
}
/*
함수명: Output
기  능: 점수를 모니터에 출력한다.
입  력: 점수
출  력: 없음
*/
void Output(ULong score) {
	printf("%d\n", score);
}
