/*
파일명: ReverseArray.c
기  능: 수들을 입력받아 거꾸로 출력한다.
작성자: 김찬형
작성일: 19.1.22
*/
#include<stdio.h>
#define MAX 1000
#pragma warning(disable:4996)

typedef signed long int Long;

//선언부
int main(int argc, char* argv[]);
void Input(Long *countNumber, Long(*numbers));
void ReverseArray(Long countNumber, Long(*numbers));
void Output(Long countNumber, Long(*numbers));

//정의부
int main(int argc, char* argv[]) {
	Long countNumber;
	Long numbers[MAX];
	//호출
	Input(&countNumber, numbers);
	ReverseArray(countNumber, numbers);
	Output(countNumber, numbers);

	return 0;
}
/*
함수명: Input
기  능: 수의 개수와 그 개수만큼의 수들을 외부입력받는다.
입  력: 없음
출  력: 수의 개수, 수들
*/
void Input(Long *countNumber, Long(*numbers)) {
	Long i = 0;
	printf("수의 개수: ");
	scanf("%d", countNumber);
	printf("수들\n");
	while (i < *countNumber) {
		scanf("%d", numbers + i);
		i++;
	}
}
/*
함수명: ReverseArray
기  능: 수들을 거꾸로 정렬해서 출력한다.
입  력: 수의개수, 수들
출  력: 수들
*/
void ReverseArray(Long countNumber, Long(*numbers)) {
	Long i = 0;
	Long j;
	Long temp;
	j = countNumber-1;

	while (i < (countNumber / 2)) {
		temp = numbers[i];
		numbers[i] = numbers[j];
		numbers[j] = temp;
		j--;
		i++;
	}
}
/*
함수명: Output
기  능: 수들을 모니터에 출력한다.
입  력: 수의개수, 수들
출  력: 없음
*/
void Output(Long countNumber, Long(*numbers)) {
	Long i = 0;
	while (i < countNumber) {
		printf("%d ", numbers[i]);
		i++;
	}
}
