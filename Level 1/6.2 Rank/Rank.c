/*
파일명: Rank.c
기  능: 학생들의 점수가 번호순으로 입력될 때 개인 석차를 구하여 번호, 점수, 석차 순으로 출력한다.
작성자: 김찬형
작성일: 19.1.23
*/
#include<stdio.h>
#define MAX 10
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//선언부
int main(int argc, char* argv[]);
void Input(ULong(*scores));
void Rank(ULong(*scores), ULong(*ranks));
void Output(ULong(*scores), ULong(*ranks));

//정의부
int main(int argc, char* argv[]) {
	ULong scores[MAX];
	ULong ranks[MAX];
	//호출
	Input(scores);
	Rank(scores, ranks);
	Output(scores, ranks);

	return 0;
}
/*
함수명: Input
기  능: 점수들을 외부입력받는다.
입  력: 없음
출  력: 점수들
*/
void Input(ULong(*scores)) {
	ULong i;
	for (i = 0; i < MAX; i++) {
		scanf("%d", scores + i);
	}
}
/*
함수명: Rank
기  능: 점수들에 대해 개인 석차를 구한다.
입  력: 점수들
출  력: 석차들
*/
void Rank(ULong(*scores), ULong(*ranks)) {
	ULong rank;
	ULong i;
	ULong j;

	for (i = 0; i < MAX; i++) {
		rank = 1;
		for (j = 0; j < MAX; j++) {
			if (scores[i] < scores[j]) {
				rank++;
			}
		}
		ranks[i] = rank;
	}
}
/*
함수명: Output
기  능: 번호별로 점수와 석차를 모니터에 출력한다.
입  력: 점수들, 석차들
출  력: 없음
*/
void Output(ULong(*scores), ULong(*ranks)) {
	ULong i;
	for (i = 0; i < MAX; i++) {
		printf("%d %d %d\n", i + 1, scores[i], ranks[i]);
	}
}
