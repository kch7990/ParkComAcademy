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
/*
int main(int argc, char* argv[]) {
	WordBook wordBook;
	Long index;
	Long(*indexes);
	Long count;
	Long i;
	EnglishWord englishWord;

	//1. 생성하다
	WordBook_Create(&wordBook, 3);
	
	//2. 적재하다
	
	count = Load(&wordBook);
	i = 0;
	while (i < count) {
		englishWord = WordBook_GetAt(&wordBook, i);
		printf("%s\t%s\t%s\t%s\n", englishWord.word, englishWord.wordClass, englishWord.meaning, englishWord.example);
		i++;
	}
	printf("\n");
	
	//3. 기재하다
	index = Record(&wordBook, "eat", "동사", "먹다", "I eat banana.");
	englishWord = WordBook_GetAt(&wordBook, index);
	printf("%s\t%s\t%s\t%s\n", englishWord.word, englishWord.wordClass, englishWord.meaning, englishWord.example);
	
	index = Record(&wordBook, "apple", "명사", "사과", "I like apple");
	englishWord = WordBook_GetAt(&wordBook, index);
	printf("%s\t%s\t%s\t%s\n", englishWord.word, englishWord.wordClass, englishWord.meaning, englishWord.example);

	index = Record(&wordBook, "pretty", "형용사", "예쁜", "You are pretty.");
	englishWord = WordBook_GetAt(&wordBook, index);
	printf("%s\t%s\t%s\t%s\n", englishWord.word, englishWord.wordClass, englishWord.meaning, englishWord.example);

	index = Record(&wordBook, "where", "접속사", "어디에", "Where are you going?");
	englishWord = WordBook_GetAt(&wordBook, index);
	printf("%s\t%s\t%s\t%s\n", englishWord.word, englishWord.wordClass, englishWord.meaning, englishWord.example);

	index = Record(&wordBook, "pretty", "부사", "꽤", "This shirt is pretty nice.");
	englishWord = WordBook_GetAt(&wordBook, index);
	printf("%s\t%s\t%s\t%s\n", englishWord.word, englishWord.wordClass, englishWord.meaning, englishWord.example);

	printf("\n");

	//4. 찾다
	Find(&wordBook, "pretty", &indexes, &count);
	i = 0;
	while (i < count) {
		index = indexes[i];
		englishWord = WordBook_GetAt(&wordBook, index);
		printf("%s\t%s\t%s\t%s\n", englishWord.word, englishWord.wordClass, englishWord.meaning, englishWord.example);
		i++;
	}
	if (indexes != NULL) {
		free(indexes);
	}
	printf("\n");
	
	//5. 고치다
	index = Correct(&wordBook, 2, "부사", "꽤", "This shirt is pretty nice.");
	englishWord = WordBook_GetAt(&wordBook, index);
	printf("%s\t%s\t%s\t%s\n", englishWord.word, englishWord.wordClass, englishWord.meaning, englishWord.example);
	printf("\n");
	
	//6. 지우다
	index = Erase(&wordBook, 4);
	if (index == -1) {
		printf("지워졌다!\n");
	}
	printf("\n");
	
	//7. 정리하다
	Arrange(&wordBook);
	i = 0;
	while (i < wordBook.length) {
		index = i;
		englishWord = WordBook_GetAt(&wordBook, index);
		printf("%s\t%s\t%s\t%s\n", englishWord.word, englishWord.wordClass, englishWord.meaning, englishWord.example);
		i++;
	}
	printf("\n");
	
	//8. 저장하다
	Save(&wordBook);

	//9. 없애다
	WordBook_Destroy(&wordBook);

	return 0;
}
*/
void WordBook_Create(WordBook *wordBook, Long capacity) {
	Create(&wordBook->englishWords, capacity, sizeof(EnglishWord));
	wordBook->capacity = capacity;
	wordBook->length = 0;
}
Long Load(WordBook *wordBook) {
	EnglishWord englishWord;
	size_t flag;

	FILE* file = fopen("WordBook.dat", "rb");
	if (file != NULL) {
		flag = fread(&englishWord, sizeof(EnglishWord), 1, file);
		while (!feof(file) && flag != 0) {
			if (wordBook->length < wordBook->capacity) {
				Store(&wordBook->englishWords, wordBook->length, &englishWord, sizeof(EnglishWord));
			}
			else {
				AppendFromRear(&wordBook->englishWords, &englishWord, sizeof(EnglishWord));
				wordBook->capacity++;
			}
			wordBook->length++;
			flag = fread(&englishWord, sizeof(EnglishWord), 1, file);
		}
		fclose(file);
	}
	return wordBook->length;
}
Long Record(WordBook *wordBook, char(*word), char(*wordClass), char(*meaning), char(*example)) {
	EnglishWord englishWord;
	Long index;

	strcpy(englishWord.word, word);
	strcpy(englishWord.wordClass, wordClass);
	strcpy(englishWord.meaning, meaning);
	strcpy(englishWord.example, example);
	if (wordBook->length < wordBook->capacity) {
		index = Store(&wordBook->englishWords, wordBook->length, &englishWord, sizeof(EnglishWord));
	}
	else {
		index = AppendFromRear(&wordBook->englishWords, &englishWord, sizeof(EnglishWord));
		wordBook->capacity++;
	}
	wordBook->length++;

	return index;
}
void Find(WordBook *wordBook, char(*word), Long* (*indexes), Long *count) {
	LinearSearchDuplicate(&wordBook->englishWords, word, indexes, count, sizeof(EnglishWord), CompareWords);
}
Long Correct(WordBook *wordBook, Long index, char(*wordClass), char(*meaning), char(*example)) {
	EnglishWord englishWord;

	GetAt(&wordBook->englishWords, index, &englishWord, sizeof(EnglishWord));
	strcpy(englishWord.wordClass, wordClass);
	strcpy(englishWord.meaning, meaning);
	strcpy(englishWord.example, example);
	index = Modify(&wordBook->englishWords, index, &englishWord, sizeof(EnglishWord));

	return index;
}
Long Erase(WordBook *wordBook, Long index) {
	index = Delete(&wordBook->englishWords, index, sizeof(EnglishWord));
	wordBook->capacity--;
	wordBook->length--;

	return index;
}
void Arrange(WordBook *wordBook) {
	InsertionSort(&wordBook->englishWords, sizeof(EnglishWord), CompareEnglishWords);
}
Long Save(WordBook *wordBook) {
	EnglishWord englishWord;
	Long i;

	FILE* file = fopen("WordBook.dat", "wb");
	if (file != NULL) {
		i = 0;
		while (i < wordBook->length) {
			GetAt(&wordBook->englishWords, i, &englishWord, sizeof(EnglishWord));
			fwrite(&englishWord, sizeof(EnglishWord), 1, file);
			i++;
		}
		fclose(file);
	}
	return wordBook->length;
}
void WordBook_Destroy(WordBook *wordBook) {
	Destroy(&wordBook->englishWords);
}
EnglishWord WordBook_GetAt(WordBook *wordBook, Long index) {
	EnglishWord englishWord;

	GetAt(&wordBook->englishWords, index, &englishWord, sizeof(EnglishWord));

	return englishWord;
}
int CompareWords(void* one, void* other) {
	EnglishWord *one_ = (EnglishWord*)one;
	char(*other_) = (char(*))other;

	return strcmp(one_->word, other_);
}
int CompareEnglishWords(void* one, void* other) {
	EnglishWord *one_ = (EnglishWord*)one;
	EnglishWord *other_ = (EnglishWord*)other;

	return strcmp(one_->word, other_->word);
}