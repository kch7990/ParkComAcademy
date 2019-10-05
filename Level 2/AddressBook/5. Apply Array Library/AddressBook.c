#include "AddressBook.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
	AddressBook addressBook;
	Long index;
	Long(*indexes);
	Long count;
	Long i;
	Personal personal;

	//1. 생성하다
	AddressBook_Create(&addressBook, 4);
	
	//2. 적재하다.
	count = Load(&addressBook);
	i = 0;
	while (i < count) {
		personal = AddressBook_GetAt(&addressBook, i);
		printf("%s\t%s\t%s\t%s\n", personal.name, personal.address, personal.telephoneNumber, personal.emailAddress);
		i++;
	}
	
	//3. 기재하다
	index = Record(&addressBook, "홍길동", "서울시", "01011111111", "hong@");
	personal = AddressBook_GetAt(&addressBook, index);
	printf("%s\t%s\t%s\t%s\n", personal.name, personal.address, personal.telephoneNumber, personal.emailAddress);
	
	index = Record(&addressBook, "고길동", "대전시", "01022222222", "ko@");
	personal = AddressBook_GetAt(&addressBook, index);
	printf("%s\t%s\t%s\t%s\n", personal.name, personal.address, personal.telephoneNumber, personal.emailAddress);

	index = Record(&addressBook, "홍길동", "부산시", "01044444444", "hong@");
	personal = AddressBook_GetAt(&addressBook, index);
	printf("%s\t%s\t%s\t%s\n", personal.name, personal.address, personal.telephoneNumber, personal.emailAddress);

	printf("\n");
	
	//4. 찾다
	Find(&addressBook, "홍길동", &indexes, &count);
	i = 0;
	while (i < count) {
		index = indexes[i];
		personal = AddressBook_GetAt(&addressBook, index);
		printf("%s\t%s\t%s\t%s\n", personal.name, personal.address, personal.telephoneNumber, personal.emailAddress);
		i++;
	}
	if (indexes != NULL) {
		free(indexes);
	}
	printf("\n");
	
	//5. 고치다
	index = Correct(&addressBook, 2, "제주시", "01033333333", "jung@");
	personal = AddressBook_GetAt(&addressBook, index);
	printf("%s\t%s\t%s\t%s\n", personal.name, personal.address, personal.telephoneNumber, personal.emailAddress);
	printf("\n");
	
	//6. 지우다
	index = Erase(&addressBook, 1);
	if (index == -1) {
		printf("지워졌다!\n");
	}
	printf("\n");
	
	//7. 정리하다
	Arrange(&addressBook);
	i = 0;
	while (i < addressBook.length) {
		personal = AddressBook_GetAt(&addressBook, i);
		printf("%s\t%s\t%s\t%s\n", personal.name, personal.address, personal.telephoneNumber, personal.emailAddress);
		i++;
	}
	printf("\n");
	
	//8. 저장하다
	Save(&addressBook);
	
	//9. 없애다
	AddressBook_Destroy(&addressBook);
	
	return 0;
}
void AddressBook_Create(AddressBook *addressBook, Long capacity) {
	Create(&addressBook->personals, capacity, sizeof(Personal));
	addressBook->capacity = capacity;
	addressBook->length = 0;
}
Long Load(AddressBook *addressBook) {
	Personal personal;
	size_t flag;

	FILE *file = fopen("AddressBook.dat", "rb");
	if (file != NULL) {
		flag = fread(&personal, sizeof(Personal), 1, file);
		while (!feof(file) && flag != 0) {
			if (addressBook->length < addressBook->capacity) {
				Store(&addressBook->personals, addressBook->length, &personal, sizeof(Personal));
			}
			else {
				AppendFromRear(&addressBook->personals, &personal, sizeof(Personal));
				addressBook->capacity++;
			}
			addressBook->length++;
			flag = fread(&personal, sizeof(Personal), 1, file);
		}
		fclose(file);
	}
	return addressBook->length;
}
Long Record(AddressBook *addressBook, char(*name), char(*address), char(*telephoneNumber), char(*emailAddress)) {
	Long index;
	Personal personal;

	strcpy(personal.name, name);
	strcpy(personal.address, address);
	strcpy(personal.telephoneNumber, telephoneNumber);
	strcpy(personal.emailAddress, emailAddress);
	if (addressBook->length < addressBook->capacity) {
		index = Store(&addressBook->personals, addressBook->length, &personal, sizeof(Personal));
	}
	else {
		index = AppendFromRear(&addressBook->personals, &personal, sizeof(Personal));
		addressBook->capacity++;
	}
	addressBook->length++;
	return index;
}
void Find(AddressBook *addressBook, char(*name), Long* (*indexes), Long *count) {
	LinearSearchDuplicate(&addressBook->personals, name, indexes, count, sizeof(Personal), CompareNames);
}
Long Correct(AddressBook *addressBook, Long index, char(*address), char(*telephoneNumber), char(*emailAddress)) {
	Personal personal;

	GetAt(&addressBook->personals, index, &personal, sizeof(Personal));
	strcpy(personal.address, address);
	strcpy(personal.telephoneNumber, telephoneNumber);
	strcpy(personal.emailAddress, emailAddress);
	index = Modify(&addressBook->personals, index, &personal, sizeof(Personal));

	return index;
}
Long Erase(AddressBook *addressBook, Long index) {
	index = Delete(&addressBook->personals, index, sizeof(Personal));
	addressBook->capacity--;
	addressBook->length--;

	return index;
}
void Arrange(AddressBook *addressBook) {
	SelectionSort(&addressBook->personals, sizeof(Personal), ComparePersonals);
}
Long Save(AddressBook *addressBook) {
	Personal personal;
	Long i;

	FILE *file = fopen("AddressBook.dat", "wb");
	if (file != NULL) {
		i = 0;
		while (i < addressBook->length) {
			GetAt(&addressBook->personals, i, &personal, sizeof(Personal));
			fwrite(&personal, sizeof(Personal), 1, file);
			i++;
		}
		fclose(file);
	}

	return addressBook->length;
}
void AddressBook_Destroy(AddressBook *addressBook) {
	Destroy(&addressBook->personals);
}
Personal AddressBook_GetAt(AddressBook *addressBook, Long index) {
	Personal personal;

	GetAt(&addressBook->personals, index, &personal, sizeof(Personal));

	return personal;
}
int CompareNames(void* one, void* other) {
	Personal *one_ = (Personal*)one;
	char(*other_) = (char(*))other;

	return strcmp(one_->name, other_);
}
int ComparePersonals(void* one, void* other) {
	Personal *one_ = (Personal*)one;
	Personal *other_ = (Personal*)other;

	return strcmp(one_->name, other_->name);
}