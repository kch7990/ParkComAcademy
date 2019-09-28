/*
파일명: WageRecord.c
기  능: 사원들의 성명, 작업시간, 코드를 입력받아 임금을 계산해 출력한다.
작성자: 김찬형
작성일: 19.1.28
*/
#include<stdio.h>
#define MAX 5
#pragma warning(disable:4996)

typedef unsigned long int ULong;
typedef struct _worker {
	char name[11];
	ULong time;
	ULong code;
	ULong wage;
} Worker;

//선언부
int main(int argc, char* argv[]);
void Load(Worker (*workers));
void Wage(Worker (*workers));
void Save(Worker (*workers));

//정의부
int main(int argc, char* argv[]) {
	Worker workers[MAX];
	//호출
	Load(workers);
	Wage(workers);
	Save(workers);

	return 0;
}
/*
함수명: Load
기  능: 디스크 파일 Workers.txt를 읽는다.
입  력: 없음
출  력: 사원들
*/
void Load(Worker(*workers)) {
	Worker worker;
	ULong i=0;

	FILE* file;
	file = fopen("Workers.txt", "rt");
	if (file != NULL) {
		fscanf(file, "%s %d %d", worker.name, &worker.time, &worker.code);
		while (!feof(file)) {
			workers[i] = worker;
			i++;
			fscanf(file, "%s %d %d", worker.name, &worker.time, &worker.code);
		}
	}
}
/*
함수명: Wage
기  능: 입력받은 정보들로 임금을 계산한다.
입  력: 사원들
출  력: 사원들
*/
void Wage(Worker (*workers)) {
	ULong hourWage;
	ULong i;

	for (i = 0; i < MAX; i++) {
		if (workers[i].code >= 1 && workers[i].code <= 4) {
			switch (workers[i].code) {
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
		workers[i].wage = workers[i].time * hourWage;
	}
}
/*
함수명: Save
기  능: 사원들을 디스크 파일에 저장한다.
입  력: 사원들
출  력: 없음
*/
void Save(Worker(*workers)) {
	ULong i;
	FILE* file;

	file = fopen("Workers.txt", "wt");
	if (file != NULL) {
		fprintf(file, "%s", "=============================\n");
		fprintf(file, "%s", "성명\t작업시간\t코드\t임금\t\n");
		fprintf(file, "%s", "-----------------------------\n");
		for (i = 0; i < MAX; i++) {
			fprintf(file, "%s\t%d\t%d\t%d\n", workers[i].name, workers[i].time, workers[i].code, workers[i].wage);
		}
		fprintf(file, "%s", "=============================\n");
		fclose(file);
	}
}