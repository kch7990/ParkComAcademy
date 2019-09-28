/*
파일명: PutTiles.c
기  능: 방의 가로, 세로의 길이를 입력받아 8*8타일을 깔 때, 온전한 타일 수와 잘라쓴 타일 수를 구하여 출력한다.
작성자: 김찬형
작성일: 19.1.21
*/
#include<stdio.h>
#define TILE 8
#pragma warning (disable:4996)

typedef unsigned long int ULong;

//선언부
int main(int argc, char* argv[]);
void Input(ULong *width, ULong *height);
void PutTiles(ULong width, ULong height, ULong *tiles, ULong *cutTiles);
void Output(ULong tiles, ULong cutTiles);

//정의부
int main(int argc, char* argv[]) {
	ULong width;
	ULong height;
	ULong tiles;
	ULong cutTiles;
	//호출
	Input(&width, &height);
	PutTiles(width, height, &tiles, &cutTiles);
	Output(tiles, cutTiles);

	return 0;
}
/*
함수명: Input
기  능: 방의 가로와 세로 길이를 외부입력받는다.
입  력: 없음
출  력: 가로, 세로
*/
void Input(ULong *width, ULong *height) {
	scanf("%d %d", width, height);
}
/*
함수명: PutTiles
기  능: 방에 타일을 깔 때 사용한 온전한 타일 수와 잘라쓴 타일 수를 구하여 출력한다.
입  력: 가로, 세로
출  력: 온전한 타일 수, 잘라쓴 타일 수
*/
void PutTiles(ULong width, ULong height, ULong *tiles, ULong *cutTiles) {
	ULong rowTiles;
	ULong lineTiles;
	ULong emptyRow;
	ULong emptyLine;

	rowTiles = width / TILE;
	lineTiles = height / TILE;
	*tiles = rowTiles * lineTiles;
	emptyRow = width % TILE;
	emptyLine = height % TILE;
	if (emptyRow != 0 && emptyLine != 0) {
		*cutTiles = rowTiles + lineTiles + 1;
	}
	else if (emptyRow != 0) {
		*cutTiles = lineTiles;
	}
	else if (emptyLine != 0) {
		*cutTiles = rowTiles;
	}
	else {
		*cutTiles = 0;
	}
}
/*
함수명: Output
기  능: 온전한 타일 수와 잘라쓴 타일 수를 모니터에 출력한다.
입  력: 온전한 타일 수, 잘라쓴 타일 수
출  력: 없음
*/
void Output(ULong tiles, ULong cutTiles) {
	printf("온전한 타일 수: %d\n잘라쓴 타일 수: %d\n", tiles, cutTiles);
}
