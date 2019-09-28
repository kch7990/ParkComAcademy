/*
파일명: Convert.c
기  능: 온도 단위와 수치를 입력받아 섭씨면 화씨로, 화씨면 섭씨로 변환하여 출력한다.
작성자: 김찬형
작성일: 19.1.19
*/
#include<stdio.h>
#pragma warning(disable:4996)

//선언부
int main(int argc, char* argv[]);
void Input(char *unit, float *value);
void Convert(char unit, float value, char *convertUnit, float *convertValue);
void Output(char convertUnit, float convertValue);

//정의부
int main(int argc, char* argv[]) {
	char unit;
	float value;
	char convertUnit;
	float convertValue;
	//호출
	Input(&unit, &value);
	Convert(unit, value, &convertUnit, &convertValue);
	Output(convertUnit, convertValue);

	return 0;
}
/*
함수명: Input
기  능: 온도 단위와 온도 수치를 외부입력받는다.
입  력: 없음
출  력: 온도 단위, 온도 수치
*/
void Input(char *unit, float *value) {
	scanf("%c %f", unit, value);
}
/*
함수명: Convert
기  능: 섭씨면 화씨로, 화씨면 섭씨로 변환하여 출력한다.
입  력: 온도 단위, 온도 수치
출  력: 변환 온도 단위, 변환 온도 수치
*/
void Convert(char unit, float value, char *convertUnit, float *convertValue) {
	if (unit == 'C' || unit == 'c') {
		*convertUnit = 'F';
		*convertValue = value * 1.8F + 32.0F;
	}
	else if (unit == 'F' || unit == 'f') {
		*convertUnit = 'C';
		*convertValue = (value - 32.0F) / 1.8F;
	}
	else {
		*convertUnit = 'E';
		*convertValue = 0.0F;
	}
}
/*
함수명: Output
기  능: 변환한 온도 단위와 수치를 모니터에 출력한다.
입  력: 변환 온도 단위, 변환 온도 수치
출  력: 없음
*/
void Output(char convertUnit, float convertValue) {
	if (convertUnit!='E') {
		printf("변환 결과: %.1f %c\n", convertValue, convertUnit);
	}
	else {
		printf("ERROR DATA = %.1f\n", convertValue);
	}
}