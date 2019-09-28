/*
파일명: Average.c
기  능: 학생들의 성명, 3과목 점수를 입력받아 개인평균과 반평균을 구한다.
작성자: 김찬형
작성일: 19.1.25
*/
#include<stdio.h>
#define STUDENTS 5
#define SUBJECTS 3
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//선언부
int main(int argc, char* argv[]);
void Input(char(*names)[11], ULong(*scores)[SUBJECTS]);
void Average(char(*names)[11], ULong(*scores)[SUBJECTS], float(*averages), float *classAverage);
void Output(char(*names)[11], ULong(*scores)[SUBJECTS], float(*averages), float classAverage);

//정의부
int main(int argc, char* argv[]) {
	char names[STUDENTS][11];
	ULong scores[STUDENTS][SUBJECTS];
	float averages[STUDENTS];
	float classAverage;
	//호출
	Input(names, scores);
	Average(names, scores, averages, &classAverage);
	Output(names, scores, averages, classAverage);

	return 0;
}
/*
함수명: Input
기  능: 성명들, 점수들을 외부입력받는다.
입  력: 없음
출  력: 성명들, 점수들
*/
void Input(char(*names)[11], ULong(*scores)[SUBJECTS]) {
	ULong i;

	for (i = 0; i < STUDENTS; i++) {
		scanf("%s %d %d %d", names[i], scores[i] + 0, scores[i] + 1, scores[i] + 2);
	}
}
/*
함수명: Average
기  능: 학생들의 3과목 점수로 개인평균을 구하고 반평균까지 구하여 출력한다.
입  력: 성명들, 점수들
출  력: 평균들, 반평균
*/
void Average(char(*names)[11], ULong(*scores)[SUBJECTS], float(*averages), float *classAverage) {
	ULong i;
	ULong j;
	ULong sum;
	ULong classSum = 0;

	for (i = 0; i < STUDENTS; i++) {
		sum = 0;
		for (j = 0; j < SUBJECTS; j++) {
			sum += scores[i][j];
			classSum += scores[i][j];
		}
		averages[i] = sum / (SUBJECTS*1.0F);
	}
	*classAverage = classSum / (STUDENTS*SUBJECTS*1.0F);
}
/*
함수명: Output
기  능: 성명들, 점수들, 평균들, 반평균을 모니터에 출력한다.
입  력: 성명들, 점수들, 평균들, 반평균
출  력: 없음
*/
void Output(char(*names)[11], ULong(*scores)[SUBJECTS], float(*averages), float classAverage) {
	ULong i;

	for (i = 0; i < STUDENTS; i++) {
		printf("%s %d %d %d %.1f\n", names[i], scores[i][0], scores[i][1], scores[i][2], averages[i]);
	}
	printf("%.1f\n", classAverage);
}