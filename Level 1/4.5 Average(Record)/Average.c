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
typedef struct _student {
	char name[11];
	ULong scores[SUBJECTS];
	float average;
}Student;

//선언부
int main(int argc, char* argv[]);
void Load(Student(*students));
void Average(Student(*students), float *classAverage);
void Save(Student(*students), float classAverage);

//정의부
int main(int argc, char* argv[]) {
	Student students[STUDENTS];
	float classAverage;
	//호출
	Load(students);
	Average(students, &classAverage);
	Save(students, classAverage);

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
	ULong i=0;

	FILE* file;
	file = fopen("Students.txt", "rt");
	if (file != NULL) {
		fscanf(file, "%s %d %d %d", student.name, &student.scores[0], &student.scores[1], &student.scores[2]);
		while (!feof(file)) {
			students[i] = student;
			i++;
			fscanf(file, "%s %d %d %d", student.name, &student.scores[0], &student.scores[1], &student.scores[2]);
		}
		fclose(file);
	}
}
/*
함수명: Average
기  능: 학생들의 3과목 점수로 개인평균을 구하고 반평균까지 구하여 출력한다.
입  력: 학생들
출  력: 학생들, 반평균
*/
void Average(Student (*students), float *classAverage) {
	ULong i;
	ULong j;
	ULong sum;
	ULong classSum = 0;

	for (i = 0; i < STUDENTS; i++) {
		sum = 0;
		for (j = 0; j < SUBJECTS; j++) {
			sum += students[i].scores[j];
			classSum += students[i].scores[j];
		}
		students[i].average = sum / (SUBJECTS*1.0F);
	}
	*classAverage = classSum / (STUDENTS*SUBJECTS*1.0F);
}
/*
함수명: Save
기  능: 학생들, 반평균을 디스크 파일에 저장한다.
입  력: 학생들, 반평균
출  력: 없음
*/
void Save(Student(*students), float classAverage) {
	ULong i;

	FILE* file;
	file = fopen("Students.txt", "wt");
	if (file != NULL) {
		fprintf(file, "=====================================\n");
		fprintf(file, "성명\t점수들\t\t\t평균\n");
		fprintf(file, "-------------------------------------\n");
		for (i = 0; i < STUDENTS; i++) {
			fprintf(file, "%s\t%d\t%d\t%d\t%.1f\n", students[i].name, students[i].scores[0], students[i].scores[1], students[i].scores[2], students[i].average);
		}
		fprintf(file, "-------------------------------------\n");
		fprintf(file, "반평균: %.1f\n", classAverage);
		fclose(file);
	}
}