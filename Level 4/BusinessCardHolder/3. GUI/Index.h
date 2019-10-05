#ifndef _INDEX_H
#define _INDEX_H

#include "BinaryTree.h"
#include "Array.h"
#include <string>

using namespace std;

class BusinessCard;
class Index {
public:
	Index(Long capacity = 256);
	Index(string name, Long capacity = 256);
	Index(const Index& source);
	~Index();
	Long PutIn(BusinessCard *businessCardLink);
	Long Find(BusinessCard *businessCardLink);
	Long PutOut(Long location);
	void Arrange(BinaryTree<Index>::Node *node);
	BusinessCard* GetAt(Long location);

	Index& operator =(const Index& source);
	BusinessCard* operator [](Long i);

	string& GetName() const;
	Long GetCapacity() const;
	Long GetLength() const;
private:
	string name;
	Array<BusinessCard*> businessCards;
	Long capacity;
	Long length;
};
inline string& Index::GetName() const {
	return const_cast<string&>(this->name);
}
inline Long Index::GetCapacity() const {
	return this->capacity;
}
inline Long Index::GetLength() const {
	return this->length;
}
int CompareBusinessCardLinksinIndex(void *one, void *other);
int CompareBusinessCardPersonalNames(void *one, void *other);

#endif //_INDEX_H