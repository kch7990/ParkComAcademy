/*
파일명: HitandBlow.c
기  능: 정답수 4개와 답안수 4개를 입력받아 값과 위치가 같을 때 Hit, 값은 같지만 위치가 다를 때 Blow로 판정해 그 개수를 세어 출력한다.
작성자: 김찬형
작성일: 19.1.22
*/
#include<stdio.h>
#define MAX 4
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//선언부
int main(int argc, char* argv[]);
void Input(ULong(*rightAnswers), ULong(*answers));
void HitandBlow(ULong(*rightAnswers), ULong(*answers), ULong *countHit, ULong *countBlow);
void Output(ULong countHit, ULong countBlow);

//정의부
int main(int argc, char* argv[]) {
	ULong rightAnswers[MAX];
	ULong answers[MAX];
	ULong countHit;
	ULong countBlow;
	//호출
	Input(rightAnswers, answers);
	HitandBlow(rightAnswers, answers, &countHit, &countBlow);
	Output(countHit, countBlow);

	return 0;
}
/*
함수명: Input
기  능: 정답수들과 답안수들을 외부입력받는다.
입  력: 없음
출  력: 정답수들, 답안수들
*/
void Input(ULong(*rightAnswers), ULong(*answers)) {
	ULong i;
	printf("정답수들: ");
	for (i = 0; i < MAX; i++) {
		scanf("%d", rightAnswers + i);
	}
	printf("답안수들: ");
	for (i = 0; i < MAX; i++) {
		scanf("%d", answers + i);
	}
}
/*
함수명: HitandBlow
기  능: 정답수들과 답안수들을 비교해서 값과 위치가 같으면 Hit, 값만 같으면 Blow로 판정해 개수를 센다.
입  력: 정답수들, 답안수들
출  력: 히트개수, 블로개수
*/
void HitandBlow(ULong(*rightAnswers), ULong(*answers), ULong *countHit, ULong *countBlow) {
	ULong i;
	ULong j;
	*countHit = 0;
	*countBlow = 0;

	for (i = 0; i < MAX; i++) {
		for (j = 0; j < MAX; j++) {
			if (answers[i] == rightAnswers[j]) {
				if (i == j) {
					(*countHit)++;
				}
				else {
					(*countBlow)++;
				}
			}
		}
	}
}
/*
함수명: Output
기  능: 히트개수와 블로개수를 모니터에 출력한다.
입  력: 히트개수, 블로개수
출  력: 없음
*/
void Output(ULong countHit, ULong countBlow) {
	printf("Hit개수: %d Blow개수: %d\n", countHit, countBlow);
}
