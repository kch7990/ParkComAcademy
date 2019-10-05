//AddressBook.h
#ifndef _ADDRESSBOOK_H
#define _ADDRESSBOOK_H //Guard

#define MAX 6

typedef signed long int Long;

typedef struct _personal {
	char name[11];
	char address[64];
	char telephoneNumber[12];
	char emailAddress[64];
} Personal;

typedef struct _addressBook {
	Personal personals[MAX];
	Long capacity;
	Long length;
} AddressBook;

Long Record(AddressBook *addressBook, char(*name), char(*address), char(*telephoneNumber), char(*emailAddress));
void Find(AddressBook *addressBook, char(*name), Long(*indexes), Long *count);
Long Correct(AddressBook *addressBook, Long index, char(*address), char(*telephoneNumber), char(*emailAddress));
Long Erase(AddressBook *addressBook, Long index);
void Arrange(AddressBook *addressBook);

#endif //_ADDRESSBOOK_H
