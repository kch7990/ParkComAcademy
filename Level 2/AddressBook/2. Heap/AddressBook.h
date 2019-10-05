#ifndef _ADDRESSBOOK_H
#define _ADDRESSBOOK_H

typedef signed long int Long;
typedef struct _personal {
	char name[11];
	char address[64];
	char telephoneNumber[12];
	char emailAddress[64];
}Personal;
typedef struct _addressBook {
	Personal(*personals);
	Long capacity;
	Long length;
}AddressBook;

//함수 선언
void Create(AddressBook *addressBook, Long capacity);
Long Record(AddressBook *addressBook, char(*name), char(*address), char(*telephoneNumber), char(*emailAddress));
void Find(AddressBook *addressBook, char(*name), Long* (*indexes), Long *count);
Long Correct(AddressBook *addressBook, Long index, char(*address), char(*telephoneNumber), char(*emailAddress));
Long Erase(AddressBook *addressBook, Long index);
void Arrange(AddressBook *addressBook);
void Destroy(AddressBook *addressBook);

#endif