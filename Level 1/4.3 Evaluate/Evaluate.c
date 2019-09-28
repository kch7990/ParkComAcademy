/*
파일명: Evaluate.c
기  능: 학생들의 3과목 점수를 입력받아 총점, 평균, 평가를 구하고 과목별 평균 또한 구한다.
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
void Input(char(*names)[11], ULong(*koreanScores), ULong(*englishScores), ULong(*mathScores));
void Evaluate(char(*names)[11], ULong(*koreanScores), ULong(*englishScores), ULong(*mathScores), ULong(*sums), float(*averages),
	char* (*evaluations), float *koreanAverage, float *englishAverage, float *mathAverage);
void Output(char (*names)[11], ULong(*koreanScores), ULong(*englishScores), ULong(*mathScores), ULong(*sums), float(*averages),
	char* (*evaluations), float koreanAverage, float englishAverage, float mathAverage);

//정의부
int main(int argc, char* argv[]) {
	char names[STUDENTS][11];
	ULong koreanScores[STUDENTS];
	ULong englishScores[STUDENTS];
	ULong mathScores[STUDENTS];
	ULong sums[STUDENTS];
	float averages[STUDENTS];
	char* evaluations[STUDENTS];
	float koreanAverage;
	float englishAverage;
	float mathAverage;
	//호출
	Input(names, koreanScores, englishScores, mathScores);
	Evaluate(names, koreanScores, englishScores, mathScores, sums, averages, evaluations, &koreanAverage, &englishAverage, &mathAverage);
	Output(names, koreanScores, englishScores, mathScores, sums, averages, evaluations, koreanAverage, englishAverage, mathAverage);

	return 0;
}
/*
함수명: Input
기  능: 성명들, 국어점수들, 영어점수들, 수학점수들을 외부입력받는다.
입  력: 없음
출  력: 성명들, 국어점수들, 영어점수들, 수학점수들
*/
void Input(char(*names)[11], ULong(*koreanScores), ULong(*englishScores), ULong(*mathScores)) {
	ULong i;
	for (i = 0; i < STUDENTS; i++) {
		scanf("%s %d %d %d", names[i], koreanScores + i, englishScores + i, mathScores + i);
	}
}
/*
함수명: Evaluate
기  능: 입력받은 정보에 대해 총점, 평균, 평가를 구하고 과목별로 평균을 구하여 출력한다.
입  력: 성명들, 국어점수들, 영어점수들, 수학점수들
출  력: 총점들, 평균들, 평가들, 국어평균, 영어평균, 수학평균
*/
void Evaluate(char(*names)[11], ULong(*koreanScores), ULong(*englishScores), ULong(*mathScores), ULong(*sums), float(*averages),
	char* (*evaluations), float *koreanAverage, float *englishAverage, float *mathAverage) {
	ULong koreanSum = 0;
	ULong englishSum = 0;
	ULong mathSum = 0;
	ULong i;

	for (i = 0; i < STUDENTS; i++) {
		sums[i] = koreanScores[i] + englishScores[i] + mathScores[i];
		averages[i] = sums[i] / (SUBJECTS*1.0F);
		if (averages[i] >= 90.0F) {
			evaluations[i] = "EXCELLENT";
		}
		else if (averages[i] < 60.0F) {
			evaluations[i] = "FAIL";
		}
		else {
			evaluations[i] = "";
		}
		koreanSum += koreanScores[i];
		englishSum += englishScores[i];
		mathSum += mathScores[i];
	}
	*koreanAverage = koreanSum / (STUDENTS*1.0F);
	*englishAverage = englishSum / (STUDENTS*1.0F);
	*mathAverage = mathSum / (STUDENTS*1.0F);
}
/*
함수명: Output
기  능: 성명들, 국어점수들, 영어점수들, 수학점수들, 총점들, 평균들, 평가들, 국어평균, 영어평균, 수학평균을 모니터에 출력한다.
입  력: 성명들, 국어점수들, 영어점수들, 수학점수들, 총점들, 평균들, 평가들, 국어평균, 영어평균, 수학평균
출  력: 없음
*/
void Output(char(*names)[11], ULong(*koreanScores), ULong(*englishScores), ULong(*mathScores), ULong(*sums), float(*averages),
	char* (*evaluations), float koreanAverage, float englishAverage, float mathAverage) {
	ULong i;
	for (i = 0; i < STUDENTS; i++) {
		printf("%s %d %d %d %d %.1f %s\n", names[i], koreanScores[i], englishScores[i], mathScores[i], sums[i], averages[i], evaluations[i]);
	}
	printf("국어평균:%.1f\n영어평균:%.1f\n수학평균:%.1f\n", koreanAverage, englishAverage, mathAverage);
}