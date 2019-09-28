/*
파일명: Wage.c
기  능: 사원들의 정보로 임금을 계산한다.
작성자: 김찬형
작성일: 19.1.29
*/
#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef unsigned long int ULong;
typedef struct _worker {
	char name[11];
	ULong time;
	ULong code;
	ULong wage;
}Worker;
//선언부
int main(int argc, char* argv[]);
void Load(Worker*(*workers), ULong *count);
void Wage(Worker(*workers), ULong count);
void Save(Worker(*workers), ULong count);

//정의부
int main(int argc, char* argv[]) {
	Worker(*workers);
	ULong count;
	//호출
	Load(&workers, &count);
	Wage(workers, count);
	Save(workers, count);

	if (workers != NULL) {
		free(workers);
	}
	return 0;
}
/*
함수명: Load
기  능: 사원들 디스크 파일을 적재한다.
입  력: 없음
출  력: 사원들, 개수
*/
void Load(Worker*(*workers), ULong *count) {
	Worker worker;
	ULong i = 0;
	FILE* file = fopen("Workers.txt", "rt");
	*count = 0;
	if (file != NULL) {
		fscanf(file, "%s %d %d", worker.name, &worker.time, &worker.code);
		while (!feof(file)) {
			(*count)++;
			fscanf(file, "%s %d %d", worker.name, &worker.time, &worker.code);
		}
		if (*count > 0) {
			*workers = (Worker(*))calloc(*count, sizeof(Worker));
		}
		fseek(file, 0L, SEEK_SET);
		fscanf(file, "%s %d %d", worker.name, &worker.time, &worker.code);
		while (!feof(file)) {
			(*workers)[i] = worker;
			i++;
			fscanf(file, "%s %d %d", worker.name, &worker.time, &worker.code);
		}
		fclose(file);
	}
}
/*
함수명: Wage
기  능: 사원들을 입력받아 임금을 계산한다.
입  력: 사원들, 개수
출  력: 사원들
*/
void Wage(Worker(*workers), ULong count){
	ULong hourWage;
	ULong i = 0;

	while (i < count) {
		if (workers[i].code >= 1 && workers[i].code <= 4) {
			switch (workers[i].code) {
			case 1: hourWage = 2000; break;
			case 2: hourWage = 2500; break;
			case 3: hourWage = 3000; break;
			case 4: hourWage = 4000; break;
			default:break;
			}
		}
		else {
			hourWage = 0;
		}
		workers[i].wage = workers[i].time*hourWage;
		i++;
	}
}
/*
함수명: Save
기  능: 사원들 디스크 파일을 저장한다.
입  력: 사원들, 개수
출  력: 없음
*/
void Save(Worker(*workers), ULong count) {
	ULong i = 0;
	FILE* file = fopen("Workers.txt", "wt");
	if (file != NULL) {
		fprintf(file, "===============================\n");
		fprintf(file, "성명\t작업시간\t코드\t임금\n");
		fprintf(file, "-------------------------------\n");
		while (i < count) {
			fprintf(file, "%s\t%d\t%d\t%d\n", workers[i].name, workers[i].time, workers[i].code, workers[i].wage);
			i++;
		}
		fclose(file);
	}
}
