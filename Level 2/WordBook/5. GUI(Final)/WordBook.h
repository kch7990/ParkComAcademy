#ifndef _WORDBOOK_H
#define _WORDBOOK_H //Guard

#include "Array.h"

//자료구조도
typedef signed long int Long;
typedef struct _englishWord {
	char word[64];
	char wordClass[11];
	char meaning[64];
	char example[128];
}EnglishWord;
typedef struct _wordBook {
	Array englishWords;
	Long capacity;
	Long length;
}WordBook;

//시스템 다이어그램
void WordBook_Create(WordBook *wordBook, Long capacity);
Long Record(WordBook *wordBook, char(*word), char(*wordClass), char(*meaning), char(*example));
void Find(WordBook *wordBook, char(*word), Long* (*indexes), Long *count);
Long Correct(WordBook *wordBook, Long index, char(*wordClass), char(*meaning), char(*example));
Long Erase(WordBook *wordBook, Long index);
void Arrange(WordBook *wordBook);
void WordBook_Destroy(WordBook *wordBook);
Long Load(WordBook *wordBook);
Long Save(WordBook *wordBook);
EnglishWord WordBook_GetAt(WordBook *wordBook, Long index);
int CompareWords(void* one, void* other);
int CompareEnglishWords(void* one, void* other);

#endif //_WORDBOOK_H
