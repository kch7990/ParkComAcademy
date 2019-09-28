/*
파일명: Average.c
기  능: 학생 정보를 입력받아 개인평균과 반평균을 계산한다.
작성자: 김찬형
작성일: 19.1.30
*/
#include<stdio.h>
#include<stdlib.h>
#define SUBJECTS 3
#pragma warning(disable:4996)

typedef unsigned long int ULong;
typedef struct _student {
	char name[11];
	ULong scores[SUBJECTS];
	ULong sum;
	float average;
}Student;
//선언부
int main(int argc, char* argv[]);
void Load(Student*(*students), ULong *count);
void Average(Student(*students), ULong count, float *classAverage);
void Save(Student(*students), ULong count, float classAverage);

//정의부
int main(int argc, char* argv[]) {
	Student(*students);
	ULong count;
	float classAverage;
	//호출
	Load(&students, &count);
	Average(students, count, &classAverage);
	Save(students, count, classAverage);
	if (students != NULL) {
		free(students);
	}
	return 0;
}
/*
함수명: Load
기  능: 학생들 디스크 파일을 적재한다
입  력: 없음
출  력: 학생들, 개수
*/
void Load(Student*(*students), ULong *count) {
	Student student;
	ULong i = 0;

	FILE* file = fopen("Students.txt", "rt");
	*count = 0;
	if (file != NULL) {
		fscanf(file, "%s %d %d %d", student.name, student.scores + 0, student.scores + 1, student.scores + 2);
		while (!feof(file)) {
			(*count)++;
			fscanf(file, "%s %d %d %d", student.name, student.scores + 0, student.scores + 1, student.scores + 2);
		}
		if (*count > 0) {
			*students = (Student(*))calloc(*count, sizeof(Student));
		}
		fseek(file, 0L, SEEK_SET);
		fscanf(file, "%s %d %d %d", student.name, student.scores + 0, student.scores + 1, student.scores + 2);
		while (!feof(file)) {
			(*students)[i] = student;
			i++;
			fscanf(file, "%s %d %d %d", student.name, student.scores + 0, student.scores + 1, student.scores + 2);
		}
		fclose(file);
	}
}
/*
함수명: Average
기  능: 학생들 정보를 입력받아 개인평균과 반평균을 계산한다.
입  력: 학생들, 개수
출  력: 학생들, 반평균
*/
void Average(Student(*students), ULong count, float *classAverage) {
	ULong i = 0;
	ULong j;
	ULong classSum = 0;

	while (i < count) {
		students[i].sum = 0;
		for (j = 0; j < SUBJECTS; j++) {
			students[i].sum += students[i].scores[j];
			classSum += students[i].scores[j];
		}
		students[i].average = students[i].sum / (SUBJECTS + 1.0F);
		i++;
	}
	*classAverage = classSum / (count*SUBJECTS*1.0F);
}
/*
함수명: Save
기  능: 학생들 디스크 파일을 저장하다.
입  력: 학생들, 개수, 반평균
출  력: 없음
*/
void Save(Student(*students), ULong count, float classAverage) {
	ULong i = 0;

	FILE* file = fopen("Students.txt", "wt");
	if (file != NULL) {
		fprintf(file, "=====================================\n");
		fprintf(file, "성명\t점수들\t\t\t총점\t평균\n");
		fprintf(file, "-------------------------------------\n");
		while (i < count) {
			fprintf(file, "%s\t%d\t%d\t%d\t%d\t%.1f\n", students[i].name, students[i].scores[0], students[i].scores[1], students[i].scores[2], students[i].sum, students[i].average);
			i++;
		}
		fprintf(file, "-------------------------------------\n");
		fprintf(file, "반평균: %.1f\n", classAverage);
	}
}