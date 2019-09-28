/*
파일명: Wage.c
기  능: 사원들의 성명, 작업시간, 코드를 입력받아 임금을 계산해 출력한다.
작성자: 김찬형
작성일: 19.1.25
*/
#include<stdio.h>
#define MAX 5
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//선언부
int main(int argc, char* argv[]);
void Input(char(*names)[11], ULong(*times), ULong(*codes));
void Wage(char(*names)[11], ULong(*times), ULong(*codes), ULong(*wages));
void Output(char(*names)[11], ULong(*times), ULong(*codes), ULong(*wages));

//정의부
int main(int argc, char* argv[]) {
	char names[MAX][11];
	ULong times[MAX];
	ULong codes[MAX];
	ULong wages[MAX];
	//호출
	Input(names, times, codes);
	Wage(names, times, codes, wages);
	Output(names, times, codes, wages);

	return 0;
}
/*
함수명: Input
기  능: 성명들, 작업시간들, 코드들을 외부입력받는다.
입  력: 없음
출  력: 성명들, 작업시간들, 코드들
*/
void Input(char(*names)[11], ULong(*times), ULong(*codes)) {
	ULong i;
	for (i = 0; i < MAX; i++) {
		scanf("%s %d %d", names[i], times + i, codes + i);
	}
}
/*
함수명: Wage
기  능: 입력받은 정보들로 임금을 계산한다.
입  력: 성명들, 작업시간들, 코드들
출  력: 임금들
*/
void Wage(char(*names)[11], ULong(*times), ULong(*codes), ULong(*wages)) {
	ULong hourWage;
	ULong i;

	for (i = 0; i < MAX; i++) {
		if (codes[i] >= 1 && codes[i] <= 4) {
			switch (codes[i]) {
			case 1: hourWage = 2000; break;
			case 2: hourWage = 2500; break;
			case 3: hourWage = 3000; break;
			case 4: hourWage = 4000; break;
			default: break;
			}
		}
		else {
			hourWage = 0;
		}
		wages[i] = times[i] * hourWage;
	}
}
/*
함수명: Output
기  능: 성명들, 작업시간들, 코드들, 임금들을 모니터에 출력한다.
입  력: 성명들, 작업시간들, 코드들, 임금들
출  력: 없음
*/
void Output(char(*names)[11], ULong(*times), ULong(*codes), ULong(*wages)) {
	ULong i;
	for (i = 0; i < MAX; i++) {
		printf("%s %d %d %d\n", names[i], times[i], codes[i], wages[i]);
	}
}