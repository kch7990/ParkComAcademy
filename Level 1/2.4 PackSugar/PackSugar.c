/*
파일명: PackSugar
기  능: 설탕의 무게를 입력받아 5kg 상자와 3kg상자에 담을 수 있을 때 모두 포장하는 최소 상자수와 5kg상자 수, 3kg상자 수를 구하여 출력한다.
작성자: 김찬형
작성일: 19.1.21
*/
#include<stdio.h>
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//선언부
int main(int argc, char* argv[]);
ULong Input();
void PackSugar(ULong weight, ULong *leastBoxes, ULong *boxes3, ULong *boxes5);
void Output(ULong leastBoxes, ULong boxes3, ULong boxes5);

//정의부
int main(int argc, char* argv[]) {
	ULong weight;
	ULong leastBoxes;
	ULong boxes3;
	ULong boxes5;
	//호출
	weight = Input();
	PackSugar(weight, &leastBoxes, &boxes3, &boxes5);
	Output(leastBoxes, boxes3, boxes5);

	return 0;
}
/*
함수명: Input
기  능: 설탕의 무게를 외부입력받는다.
입  력: 없음
출  력: 무게
*/
ULong Input() {
	ULong weight;
	scanf("%d", &weight);
	return weight;
}
/*
함수명: PackSugar
기  능: 무게에 대해 5kg상자, 3kg상자에 포장할 때 남김없이 포장하되 상자를 최소한으로 쓰려면 몇 개의 상자를 써야 하는지 구하여 출력한다.
입  력: 무게
출  력: 최소상자수, 5kg상자수, 3kg상자수
*/
void PackSugar(ULong weight, ULong *leastBoxes, ULong *boxes5, ULong *boxes3) {
	ULong leftWeight;

	*boxes5 = weight / 5;
	leftWeight = weight - (*boxes5 * 5);
	*boxes3 = leftWeight / 3;
	leftWeight = leftWeight - (*boxes3 * 3);
	while ((leftWeight > 0 && leftWeight < 3) && *boxes5 > 0) {
		(*boxes5)--;
		leftWeight = weight - (*boxes5 * 5);
		*boxes3 = leftWeight / 3;
		leftWeight = leftWeight - (*boxes3 * 3);
	}
	if (leftWeight == 0) {
		*leastBoxes = *boxes5 + *boxes3;
	}
	else {
		*leastBoxes = 0;
	}
}
/*
함수명: Output
기  능: 최소상자수, 5kg상자수, 3kg상자수를 모니터에 출력한다.
입  력: 최소상자수, 5kg상자수, 3kg상자수
출  력: 없음
*/
void Output(ULong leastBoxes, ULong boxes5, ULong boxes3) {
	if (leastBoxes != 0) {
		printf("%d\n%d %d\n", leastBoxes, boxes5, boxes3);
	}
	else {
		printf("-1\n");
	}
}