/*
파일명: Dice.c
기  능: 주사위 눈의 합을 입력받고 그 눈의 합이 되는 주사위 두 개 눈의 조합을 구하여 출력한다.
작성자: 김찬형
작성일: 19.1.23
*/
#include<stdio.h>
#define MAX 6
#pragma warning(disable:4996)

typedef signed long int Long;

//선언부
int main(int argc, char* argv[]);
Long Input();
void Dice(Long pipSum, Long(*firstPips), Long(*secondPips), Long *count);
void Output(Long(*firstPips), Long(*secondPips), Long count);

//정의부
int main(int argc, char* argv[]) {
	Long pipSum;
	Long firstPips[MAX];
	Long secondPips[MAX];
	Long count;
	//호출
	pipSum = Input();
	Dice(pipSum, firstPips, secondPips, &count);
	Output(firstPips, secondPips, count);

	return 0;
}
/*
함수명: Input
기  능: 눈의합을 외부입력받는다.
입  력: 없음
출  력: 눈의합
*/
Long Input() {
	Long pipSum;
	scanf("%d", &pipSum);
	return pipSum;
}
/*
함수명: Dice
기  능: 눈의 합에 대해 주사위 두 개로 만들 수 있는 눈들의 조합을 모두 구하여 출력한다.
입  력: 눈의합
출  력: 첫번째눈들, 두번째눈들, 개수
*/
void Dice(Long pipSum, Long(*firstPips), Long(*secondPips), Long *count) {
	Long dice1 = 1;
	Long dice2;
	Long i = 0;
	*count = 0;

	while (dice1 <= MAX && dice1 < pipSum) {
		dice2 = pipSum - dice1;
		if (dice2 >= 1 && dice2 <= MAX) {
			firstPips[i] = dice1;
			secondPips[i] = dice2;
			i++;
			(*count)++; 
		}
		dice1++;
	}
}
/*
함수명: Output
기  능: 첫번째 눈들, 두번째 눈들을 모니터에 출력한다.
입  력: 첫번째 눈들, 두번째 눈들, 개수
출  력: 없음
*/
void Output(Long(*firstPips), Long(*secondPips), Long count) {
	Long i = 0;
	while (i < count) {
		printf("%d %d\n", firstPips[i], secondPips[i]);
		i++;
	}
}