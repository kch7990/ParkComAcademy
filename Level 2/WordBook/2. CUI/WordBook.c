/*
파일명: WordBook.c
기  능: 기재하고 찾고 고치고 지우고 정리할 수 있는 단어장 프로그램
작성자: 김찬형
작성일: 19.2.8.
*/
#include "WordBook.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//정의부

int main(int argc, char* argv[]) {
	WordBook wordBook;
	Long index;
	Long(*indexes);
	Long count;
	Long i;

	//테스트 시나리오
	Create(&wordBook, 3);
	/*
	index = Record(&wordBook, "eat", "동사", "먹다", "I eat banana.");
	printf("%s\t%s\t%s\t%s\n", wordBook.englishWords[index].word, wordBook.englishWords[index].wordClass, wordBook.englishWords[index].meaning, wordBook.englishWords[index].example);
	index = Record(&wordBook, "apple", "명사", "사과", "I like apple");
	printf("%s\t%s\t%s\t%s\n", wordBook.englishWords[index].word, wordBook.englishWords[index].wordClass, wordBook.englishWords[index].meaning, wordBook.englishWords[index].example);
	index = Record(&wordBook, "pretty", "형용사", "예쁜", "You are pretty.");
	printf("%s\t%s\t%s\t%s\n", wordBook.englishWords[index].word, wordBook.englishWords[index].wordClass, wordBook.englishWords[index].meaning, wordBook.englishWords[index].example);
	index = Record(&wordBook, "where", "접속사", "어디에", "Where are you going?");
	printf("%s\t%s\t%s\t%s\n", wordBook.englishWords[index].word, wordBook.englishWords[index].wordClass, wordBook.englishWords[index].meaning, wordBook.englishWords[index].example);
	index = Record(&wordBook, "pretty", "부사", "꽤", "This shirt is pretty nice.");
	printf("%s\t%s\t%s\t%s\n", wordBook.englishWords[index].word, wordBook.englishWords[index].wordClass, wordBook.englishWords[index].meaning, wordBook.englishWords[index].example);
	printf("\n");

	Find(&wordBook, "pretty", &indexes, &count);
	i = 0;
	while (i < count) {
		index = indexes[i];
		printf("%s\t%s\t%s\t%s\n", wordBook.englishWords[index].word, wordBook.englishWords[index].wordClass, wordBook.englishWords[index].meaning, wordBook.englishWords[index].example);
		i++;
	}
	if (indexes != NULL) {
		free(indexes);
	}
	printf("\n");

	index = Correct(&wordBook, 2, "부사", "꽤", "This shirt is pretty nice.");
	printf("%s\t%s\t%s\t%s\n", wordBook.englishWords[index].word, wordBook.englishWords[index].wordClass, wordBook.englishWords[index].meaning, wordBook.englishWords[index].example);
	printf("\n");

	index = Erase(&wordBook, 4);
	if (index == -1) {
		printf("지워졌다!\n");
	}
	printf("\n");

	Arrange(&wordBook);
	i = 0;
	while (i < wordBook.length) {
		index = i;
		printf("%s\t%s\t%s\t%s\n", wordBook.englishWords[index].word, wordBook.englishWords[index].wordClass, wordBook.englishWords[index].meaning, wordBook.englishWords[index].example);
		i++;
	}
	printf("\n");
	*/
	Destroy(&wordBook);

	return 0;
}

