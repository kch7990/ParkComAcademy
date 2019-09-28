/*
파일명: CountAnimals.c
기  능: 총 동물의 머리 수와 다리 수를 입력받아 그 중 강아지와 병아리가 각각 몇 마리인지 구한다.
작성자: 김찬형
작성일: 19.1.19
*/
#include<stdio.h>
#pragma warning(disable:4996)

typedef signed long int ULong;

//선언부
int main(int argc, char* argv[]);
void Input(ULong *heads, ULong *legs);
void CountAnimals(ULong heads, ULong legs, ULong *countDogs, ULong *countChicks);
void Output(ULong countDogs, ULong countChicks);

//정의부
int main(int argc, char* argv[]) {
	ULong heads;
	ULong legs;
	ULong countDogs;
	ULong countChicks;
	//호출
	Input(&heads, &legs);
	CountAnimals(heads, legs, &countDogs, &countChicks);
	Output(countDogs, countChicks);

	return 0;
}
/*
함수명: Input
기  능: 머리 수와 다리 수를 외부입력받는다.
입  력: 없음
출  력: 머리 수, 다리 수
*/
void Input(ULong *heads, ULong *legs) {
	scanf("%d %d", heads, legs);
}
/*
함수명: CountAnimals
기  능: 입력받은 머리 수와 다리 수에 맞는 강아지와 병아리 수를 구한다.
입  력: 머리 수, 다리 수
출  력: 강아지 수, 병아리 수
*/
void CountAnimals(ULong heads, ULong legs, ULong *countDogs, ULong *countChicks){
	ULong legSum;
	*countDogs = 0;
	*countChicks = heads - *countDogs;
	legSum = *countDogs * 4 + *countChicks * 2;
	while (legSum < legs) {
		(*countDogs)++;
		*countChicks = heads - *countDogs;
		legSum = *countDogs * 4 + *countChicks * 2;
	}
	if (*countDogs > heads) {
		*countDogs = 0;
		*countChicks = 0;
	}
}
/*
함수명: Output
기  능: 강아지와 병아리 수를 모니터에 출력한다.
입  력: 강아지 수, 병아리 수, 다리 합, 다리 수
출  력: 없음
*/
void Output(ULong countDogs, ULong countChicks) {
	if(countDogs!=0 || countChicks!=0){
		printf("강아지 수: %d 병아리 수: %d\n", countDogs, countChicks);
	}
	else {
		printf("0\n");
	}
}