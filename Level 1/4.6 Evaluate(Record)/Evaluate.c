/*
파일명: Evaluate.c
기  능: 학생들의 3과목 점수를 입력받아 총점, 평균, 평가를 구하고 과목별 평균 또한 구한다.
작성자: 김찬형
작성일: 19.1.28
*/
#include<stdio.h>
#define STUDENTS 5
#define SUBJECTS 3
#pragma warning(disable:4996)

typedef unsigned long int ULong;
typedef struct _student {
	char name[11];
	ULong koreanScore;
	ULong englishScore;
	ULong mathScore;
	ULong sum;
	float average;
	char* evaluation;
}Student;

//선언부
int main(int argc, char* argv[]);
void Load(Student(*students));
void Evaluate(Student(*students), float *koreanAverage, float *englishAverage, float *mathAverage);
void Save(Student(*students), float koreanAverage, float englishAverage, float mathAverage);

//정의부
int main(int argc, char* argv[]) {
	Student students[STUDENTS];
	float koreanAverage;
	float englishAverage;
	float mathAverage;
	//호출
	Load(students);
	Evaluate(students, &koreanAverage, &englishAverage, &mathAverage);
	Save(students, koreanAverage, englishAverage, mathAverage);

	return 0;
}
/*
함수명: Load
기  능: 학생 디스크 파일을 적재한다.
입  력: 없음
출  력: 학생들
*/
void Load(Student(*students)) {
	Student student;
	ULong i = 0;

	FILE* file;
	file = fopen("Students.txt", "rt");
	if (file != NULL) {
		fscanf(file, "%s %d %d %d", student.name, &student.koreanScore, &student.englishScore, &student.mathScore);
		while (!feof(file)) {
			students[i] = student;
			i++;
			fscanf(file, "%s %d %d %d", student.name, &student.koreanScore, &student.englishScore, &student.mathScore);
		}
		fclose(file);
	}
}
/*
함수명: Evaluate
기  능: 입력받은 정보에 대해 총점, 평균, 평가를 구하고 과목별로 평균을 구하여 출력한다.
입  력: 학생들
출  력: 학생들, 국어평균, 영어평균, 수학평균
*/
void Evaluate(Student (*students), float *koreanAverage, float *englishAverage, float *mathAverage) {
	ULong koreanSum = 0;
	ULong englishSum = 0;
	ULong mathSum = 0;
	ULong i;

	for (i = 0; i < STUDENTS; i++) {
		students[i].sum = students[i].koreanScore + students[i].englishScore + students[i].mathScore;
		students[i].average = students[i].sum / (SUBJECTS*1.0F);
		if (students[i].average >= 90.0F) {
			students[i].evaluation = "EXCELLENT";
		}
		else if (students[i].average < 60.0F) {
			students[i].evaluation = "FAIL";
		}
		else {
			students[i].evaluation = "";
		}
		koreanSum += students[i].koreanScore;
		englishSum += students[i].englishScore;
		mathSum += students[i].mathScore;
	}
	*koreanAverage = koreanSum / (STUDENTS*1.0F);
	*englishAverage = englishSum / (STUDENTS*1.0F);
	*mathAverage = mathSum / (STUDENTS*1.0F);
}
/*
함수명: Save
기  능: 학생들과 국어평균, 영어평균, 수학평균을 디스크 파일에 저장한다.
입  력: 학생들, 국어평균, 영어평균, 수학평균
출  력: 없음
*/
void Save(Student(*students), float koreanAverage, float englishAverage, float mathAverage) {
	ULong i;

	FILE* file;
	file = fopen("Students.txt", "wt");
	if (file != NULL) {
		fprintf(file, "=====================================================================\n");
		fprintf(file, "성명\t국어점수\t영어점수\t수학점수\t총점\t평균\t평가\n");
		fprintf(file, "---------------------------------------------------------------------\n");
		for (i = 0; i < STUDENTS; i++) {
			fprintf(file, "%s\t%d\t%d\t%d\t%d\t%.1f\t%s\n", students[i].name, students[i].koreanScore, students[i].englishScore, students[i].mathScore,
				students[i].sum, students[i].average, students[i].evaluation);
		}
		fprintf(file, "---------------------------------------------------------------------\n");
		fprintf(file, "국어평균: %.1f\n영어평균: %.1f\n수학평균: %.1f\n", koreanAverage, englishAverage, mathAverage);
		fclose(file);
	}
}