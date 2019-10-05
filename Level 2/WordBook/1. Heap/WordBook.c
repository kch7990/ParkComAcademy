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
	
	Destroy(&wordBook);

	return 0;
}
/*
함수명: Create
기  능: 힙에 영단어 배열을 할당한다.
입  력: 할당량
출  력: 없음
*/
void Create(WordBook *wordBook, Long capacity) {
	wordBook->englishWords = (EnglishWord(*))calloc(capacity, sizeof(EnglishWord));
	wordBook->capacity = capacity;
	wordBook->length = 0;
}
/*
함수명: Record
기  능: 단어장에 기재한다.
입  력: 단어, 품사, 뜻, 예문
출  력: 위치
*/
Long Record(WordBook *wordBook, char(*word), char(*wordClass), char(*meaning), char(*example)) {
	Long index;
	EnglishWord(*englishWords);
	Long i;

	if (wordBook->length >= wordBook->capacity) {
		englishWords = (EnglishWord(*))calloc(wordBook->capacity + 1, sizeof(EnglishWord));
		i = 0;
		while (i < wordBook->length) {
			englishWords[i] = wordBook->englishWords[i];
			i++;
		}
		if (wordBook->englishWords != NULL) {
			free(wordBook->englishWords);
		}
		wordBook->englishWords = englishWords;
		(wordBook->capacity)++;
	}
	index = wordBook->length;
	strcpy(wordBook->englishWords[index].word, word);
	strcpy(wordBook->englishWords[index].wordClass, wordClass);
	strcpy(wordBook->englishWords[index].meaning, meaning);
	strcpy(wordBook->englishWords[index].example, example);
	(wordBook->length)++;

	return index;
}
/*
함수명: Find
기  능: 단어을 입력받아 그 정보를 찾는다.
입  력: 단어
출  력: 위치들, 개수
*/
void Find(WordBook *wordBook, char(*word), Long* (*indexes), Long *count) {
	Long i = 0;
	Long j = 0;
	*count = 0;

	*indexes = (Long(*))calloc(wordBook->length, sizeof(Long));
	while (i < wordBook->length) {
		if (strcmp(wordBook->englishWords[i].word, word) == 0) {
			(*indexes)[j] = i;
			j++;
			(*count)++;
		}
		i++;
	}
}
/*
함수명: Correct
기  능: 위치에 대한 정보를 고친다.
입  력: 위치, 품사, 뜻, 예문
출  력: 위치
*/
Long Correct(WordBook *wordBook, Long index, char(*wordClass), char(*meaning), char(*example)) {
	strcpy(wordBook->englishWords[index].wordClass, wordClass);
	strcpy(wordBook->englishWords[index].meaning, meaning);
	strcpy(wordBook->englishWords[index].example, example);

	return index;
}
/*
함수명: Erase
기  능: 위치에 대한 정보를 지운다.
입  력: 위치
출  력: 위치
*/
Long Erase(WordBook *wordBook, Long index) {
	EnglishWord(*englishWords);
	Long i = 0;
	Long j = 0;

	if (wordBook->capacity > 1) {
		englishWords = (EnglishWord(*))calloc(wordBook->capacity - 1, sizeof(EnglishWord));
	}
	while(i < wordBook->length){
		if (i != index) {
			englishWords[j] = wordBook->englishWords[i];
			j++;
		}
		i++;
	}
	if (wordBook->englishWords != NULL) {
		free(wordBook->englishWords);
		wordBook->englishWords = NULL;
	}
	if (wordBook->capacity > 1) {
		wordBook->englishWords = englishWords;
	}
	(wordBook->capacity)--;
	(wordBook->length)--;
	index = -1;

	return index;
}
/*
함수명: Arrange
기  능: 단어장을 오름차순으로 정리한다.
입  력: 없음
출  력: 없음
*/
void Arrange(WordBook *wordBook) {
	EnglishWord englishWord;
	Long i = 1;
	Long j;

	while (i < wordBook->length) {
		englishWord = wordBook->englishWords[i];
		j = i - 1;
		while (j >= 0 && strcmp(englishWord.word, wordBook->englishWords[j].word) < 0) {
			wordBook->englishWords[j + 1] = wordBook->englishWords[j];
			j--;
		}
		wordBook->englishWords[j + 1] = englishWord;
		i++;
	}
}
/*
함수명: Destroy
기  능: 단어장을 없앤다.
입  력: 없음
출  력: 없음
*/
void Destroy(WordBook *wordBook) {
	if (wordBook->englishWords != NULL) {
		free(wordBook->englishWords);
	}
}