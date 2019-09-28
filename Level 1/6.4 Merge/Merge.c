/*
함수명: Merge.c
기  능: 오름차순으로 정렬된 두 배열을 입력받아 오름차순으로 병합해 출력한다.
작성자: 김찬형
작성일: 19.1.24
*/
#include<stdio.h>
#define MAX 10
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//선언부
int main(int argc, char* argv[]);
void Input(ULong(*firstNumbers), ULong(*secondNumbers));
void Merge(ULong(*firstNumbers), ULong(*secondNumbers), ULong(*mergedNumbers));
void Output(ULong(*mergedNumbers));

//정의부
int main(int argc, char* argv[]) {
	ULong firstNumbers[MAX];
	ULong secondNumbers[MAX];
	ULong mergedNumbers[MAX*2];
	//호출
	Input(firstNumbers, secondNumbers);
	Merge(firstNumbers, secondNumbers, mergedNumbers);
	Output(mergedNumbers);

	return 0;
}
/*
함수명: Input
기  능: 첫번째수들, 두번째수들을 외부입력받는다.
입  력: 없음
출  력: 첫번째수들, 두번째수들
*/
void Input(ULong(*firstNumbers), ULong(*secondNumbers)) {
	ULong i;
	for (i = 0; i < MAX; i++) {
		scanf("%d", firstNumbers + i);
	}
	for (i = 0; i < MAX; i++) {
		scanf("%d", secondNumbers + i);
	}
}
/*
함수명: Merge
기  능: 첫번째수들, 두번째수들을 오름차순으로 병합하여 출력한다.
입  력: 첫번째수들, 두번째수들
출  력: 병합된수들
*/
void Merge(ULong(*firstNumbers), ULong(*secondNumbers), ULong(*mergedNumbers)) {
	ULong i = 0;
	ULong j = 0;
	ULong k = 0;

	while (i < MAX && j < MAX) {
		if (firstNumbers[i] < secondNumbers[j]) {
			mergedNumbers[k] = firstNumbers[i];
			k++;
			i++;
		}
		else {
			mergedNumbers[k] = secondNumbers[j];
			k++;
			j++;
		}
	}
	while (i < MAX) {
		mergedNumbers[k] = firstNumbers[i];
		k++;
		i++;
	}
	while (j < MAX) {
		mergedNumbers[k] = secondNumbers[j];
		k++;
		j++;
	}
}
/*
함수명: Output
기  능: 병합된 수들을 모니터에 출력한다.
입  력: 병합된 수들
출  력: 없음
*/
void Output(ULong(*mergedNumbers)) {
	ULong k;
	for (k = 0; k < MAX*2; k++) {
		printf("%d ", mergedNumbers[k]);
	}
}