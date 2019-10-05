#include "Index.h"
#include "BusinessCard.h"

Index::Index(Long capacity)
	: name(""), businessCards(capacity) {
	this->capacity = capacity;
	this->length = 0;
}
Index::Index(string name, Long capacity)
	: name(name), businessCards(capacity) {
	this->capacity = capacity;
	this->length = 0;
}
Index::Index(const Index& source)
	: name(source.name), businessCards(source.businessCards) {
	this->capacity = source.capacity;
	this->length = source.length;
}
Index::~Index() {

}
Long Index::PutIn(BusinessCard *businessCardLink) {
	Long location;
	if (this->length < this->capacity) {
		location = this->businessCards.Store(this->length, businessCardLink);
	}
	else {
		location = this->businessCards.AppendFromRear(businessCardLink);
		this->capacity++;
	}
	this->length++;

	return location;
}
Long Index::Find(BusinessCard *businessCardLink) {
	Long location;
	location = this->businessCards.LinearSearchUnique(businessCardLink, CompareBusinessCardLinksinIndex);

	return location;
}
Long Index::PutOut(Long location) {
	location = this->businessCards.Delete(location);
	this->capacity--;
	this->length--;

	return location;
}
void Index::Arrange(BinaryTree<Index>::Node *node) {
	this->businessCards.SelectionSort(CompareBusinessCardPersonalNames);
	Index *key;
	BinaryTree<Index>::Node *left = node->GetLeft();
	if (left != 0) {
		key = &left->GetKey();
		key->Arrange(left);
	}
	BinaryTree<Index>::Node *right = node->GetRight();
	if (right != 0) {
		key = &right->GetKey();
		key->Arrange(right);
	}
}
BusinessCard* Index::GetAt(Long location) {
	return this->businessCards.GetAt(location);
}
Index& Index::operator =(const Index& source) {
	this->name = source.name;
	this->businessCards = source.businessCards;
	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}
BusinessCard* Index::operator [](Long i) {
	return this->businessCards[i];
}
int CompareBusinessCardLinksinIndex(void *one, void *other) {
	BusinessCard* *one_ = static_cast<BusinessCard**>(one);
	int ret;

	if (*one_ < other) {
		ret = -1;
	}
	else if (*one_ == other) {
		ret = 0;
	}
	else if (*one_ > other) {
		ret = 1;
	}

	return ret;
}
int CompareBusinessCardPersonalNames(void *one, void *other) {
	BusinessCard* *one_ = static_cast<BusinessCard**>(one);
	BusinessCard* *other_ = static_cast<BusinessCard**>(other);

	return (*one_)->GetPersonalName().compare((*other_)->GetPersonalName());
}