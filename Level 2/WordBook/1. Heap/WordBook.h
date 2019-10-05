#ifndef _ADDRESSBOOK_H
#define _ADDRESSBOOK_H //Guard

//자료구조도
typedef signed long int Long;
typedef struct _englishWord {
	char word[64];
	char wordClass[11];
	char meaning[64];
	char example[128];
}EnglishWord;
typedef struct _wordBook {
	EnglishWord(*englishWords);
	Long capacity;
	Long length;
}WordBook;

//시스템 다이어그램
void Create(WordBook *wordBook, Long capacity);
Long Record(WordBook *wordBook, char(*word), char(*wordClass), char(*meaning), char(*example));
void Find(WordBook *wordBook, char(*word), Long* (*indexes), Long *count);
Long Correct(WordBook *wordBook, Long index, char(*wordClass), char(*meaning), char(*example));
Long Erase(WordBook *wordBook, Long index);
void Arrange(WordBook *wordBook);
void Destroy(WordBook *wordBook);

#endif //_ADDRESSBOOK_H