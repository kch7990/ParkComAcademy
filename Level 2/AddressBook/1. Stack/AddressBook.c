//AddressBook.c
/*
파일명: AddressBook.c
기  능: 기재하고 찾고 고치고 지우고 정리할 수 있는 주소록 프로그램
작성자: 김찬형
작성일: 19.2.1.
*/
#include"AddressBook.h"
#include<stdio.h>
#include<string.h>
#pragma warning(disable: 28719)
int main(int argc, char* argv[]) {
	AddressBook addressBook = { {{"","","",""},{"","","",""},{"","","",""},{"","","",""},{"","","",""},{"","","",""}},MAX,0 };
	Long indexes[MAX];
	Long count;
	Long index;
	Long i;
	//호출
	//1. 기재하다
	index = Record(&addressBook, "홍길동", "서울시", "0101111", "hong@");
	printf("%s\t%s\t%s\t%s\n", addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
	index = Record(&addressBook, "고길동", "대전시", "0102222", "ko@");
	printf("%s\t%s\t%s\t%s\n", addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
	index = Record(&addressBook, "정길동", "대구시", "0103333", "jung@");
	printf("%s\t%s\t%s\t%s\n", addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
	index = Record(&addressBook, "홍길동", "부산시", "0104444", "hongd@");
	printf("%s\t%s\t%s\t%s\n", addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
	printf("\n");
	//2. 찾다
	Find(&addressBook, "홍길동", indexes, &count);
	i = 0;
	while (i < count) {
		index = indexes[i];
		printf("%s\t%s\t%s\t%s\n", addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
		i++;
	}
	printf("\n");
	//3. 고치다
	index = Correct(&addressBook, 2, "제주도", "0103333", "jung@");
	printf("%s\t%s\t%s\t%s\n", addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
	printf("\n");
	//4. 지우다
	index = Erase(&addressBook, 1);
	if (index == -1) {
		printf("지워졌다!\n");
	}
	printf("\n");
	//5. 정리하다
	Arrange(&addressBook);
	i = 0;
	while (i < addressBook.length) {
		printf("%s\t%s\t%s\t%s\n", addressBook.personals[i].name, addressBook.personals[i].address, addressBook.personals[i].telephoneNumber, addressBook.personals[i].emailAddress);
		i++;
	}
	return 0;
}
/*
함수명: Record
기  능: 주소록에 성명, 주소, 전화번호, 이메일주소를 기재한다.
입  력: 성명, 주소, 전화번호, 이메일주소
출  력: 위치
*/
Long Record(AddressBook *addressBook, char(*name), char(*address), char(*telephoneNumber), char(*emailAddress)) {
	Long index = -1;
	Long i = 0;
	while (i < addressBook->capacity && strcmp(addressBook->personals[i].name, "") != 0) {
		i++;
	}
	if (i < addressBook->capacity) {
		index = i;
		strcpy(addressBook->personals[index].name, name);
		strcpy(addressBook->personals[index].address, address);
		strcpy(addressBook->personals[index].telephoneNumber, telephoneNumber);
		strcpy(addressBook->personals[index].emailAddress, emailAddress);
		(addressBook->length)++;
	}
	return index;
}
/*
함수명: Find
기  능: 성명을 입력받아 그 위치를 찾는다.
입  력: 성명
출  력: 위치들, 개수
*/
void Find(AddressBook *addressBook, char(*name), Long(*indexes), Long *count) {
	Long i = 0;
	Long j = 0;
	*count = 0;
	while (i < addressBook->length) {
		if (strcmp(addressBook->personals[i].name, name) == 0) {
			indexes[j] = i;
			j++;
			(*count)++;
		}
		i++;
	}
}
/*
함수명: Correct
기  능: 어떤 위치의 주소, 전화번호, 이메일주소를 고친다.
입  력: 위치, 주소, 전화번호, 이메일주소
출  력: 위치
*/
Long Correct(AddressBook *addressBook, Long index, char(*address), char(*telephoneNumber), char(*emailAddress)) {
	strcpy(addressBook->personals[index].address, address);
	strcpy(addressBook->personals[index].telephoneNumber, telephoneNumber);
	strcpy(addressBook->personals[index].emailAddress, emailAddress);

	return index;
}
/*
함수명: Erase
기  능: 어떤 위치의 성명을 지운다.
입  력: 위치
출  력; 위치
*/
Long Erase(AddressBook *addressBook, Long index) {
	strcpy(addressBook->personals[index].name, "X");
	index = -1;

	return index;
}
/*
함수명: Arrange
기  능: 정리한다.
입  력: 없음
출  력: 없음
*/
void Arrange(AddressBook *addressBook) {
	Personal personal;
	Long i = 0;
	Long j;
	while (i < (addressBook->length) - 1) {
		j = i + 1;
		while (j < addressBook->length) {
			if (strcmp(addressBook->personals[i].name, addressBook->personals[j].name) < 0) {
				personal = addressBook->personals[i];
				addressBook->personals[i] = addressBook->personals[j];
				addressBook->personals[j] = personal;
			}
			j++;
		}
		i++;
	}
	i = (addressBook->length) - 1;
	while (i >= 0 && strcmp(addressBook->personals[i].name, "X") == 0) {
		i--; 
	}
	j = 0;
	while (j < i) {
		personal = addressBook->personals[j];
		addressBook->personals[j] = addressBook->personals[i];
		addressBook->personals[i] = personal;
		i--;
		j++;
	}
}