#include "BusinessCardHolder.h"

BusinessCardHolder::BusinessCardHolder()
{
	this->length = 0;
	this->current = 0;
}

BusinessCardHolder::BusinessCardHolder(const BusinessCardHolder& source)
	:businessCards(source.businessCards)
{
	this->length = source.length;
	this->current = &this->businessCards.GetCurrent()->GetObject();
}

BusinessCard* BusinessCardHolder::PutIn(BusinessCard businessCard)
{
	LinkedList<BusinessCard>::Node *node;
	node = this->businessCards.AppendFromTail(businessCard);
	this->length++;
	this->current = &(node->GetObject());

	return this->current;
}

void BusinessCardHolder::Find(string name, BusinessCard* *(*indexes), Long *count)
{
	*indexes= new BusinessCard*[this->GetLength()];
	LinkedList<BusinessCard>::Node* (*nodes);
	this->businessCards.LinearSearchDuplicate(&name, &nodes, count, ComparePersonalNames);

	Long i = 0;
	while (i < *count)
	{
		(*indexes)[i] = &(nodes[i]->GetObject());
		i++;
	}

	if (nodes != 0)
	{
		delete[] nodes;
	}
}

BusinessCard* BusinessCardHolder::FindByCompanyName(string companyName)
{
	LinkedList<BusinessCard>::Node *node;
	node = this->businessCards.LinearSearchUnique(&companyName, CompareCompanyNames);
	BusinessCard *index = 0;

	if (node != 0)
	{
		index = &(node->GetObject());
	}

	return index;
}

BusinessCard BusinessCardHolder::PutOut(BusinessCard *index)
{
	LinkedList<BusinessCard>::Node *node;
	node = this->businessCards.LinearSearchUnique(index, CompareBusinessCardLinks);
	BusinessCard businessCard = node->GetObject();
	this->businessCards.Delete(node);
	this->length--;
	LinkedList<BusinessCard>::Node *current;
	current = this->businessCards.GetCurrent();

	if (current != 0)
	{
		this->current = &current->GetObject();
	}
	else
	{
		this->current = 0;
	}

	return businessCard;
}

BusinessCard* BusinessCardHolder::First()
{
	LinkedList<BusinessCard>::Node *node;
	node = this->businessCards.First();
	this->current = &node->GetObject();

	return this->current;
}

BusinessCard* BusinessCardHolder::Previous()
{
	LinkedList<BusinessCard>::Node *node;
	node = this->businessCards.Previous();
	this->current = &node->GetObject();

	return this->current;
}

BusinessCard* BusinessCardHolder::Next()
{
	LinkedList<BusinessCard>::Node *node;
	node = this->businessCards.Next();
	this->current = &node->GetObject();

	return this->current;
}

BusinessCard* BusinessCardHolder::Last()
{
	LinkedList<BusinessCard>::Node *node;
	node = this->businessCards.Last();
	this->current = &node->GetObject();

	return this->current;
}

BusinessCard* BusinessCardHolder::Move(BusinessCard* index)
{
	LinkedList<BusinessCard>::Node *node;
	node = this->businessCards.LinearSearchUnique(index, CompareBusinessCardLinks);
	node = this->businessCards.Move(node);
	this->current = &node->GetObject();

	return this->current;
}

BusinessCardHolder& BusinessCardHolder::operator=(const BusinessCardHolder& source)
{
	this->businessCards = source.businessCards;
	this->length = source.length;
	this->current = &this->businessCards.GetCurrent()->GetObject();

	return *this;
}

BusinessCard& BusinessCardHolder::operator[](Long index)
{
	return this->businessCards[index];
}


#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
	
	BusinessCardHolder businessCardHolder;
	
	BusinessCard businessCard1("홍컴", "서울시 마포구", "021111", "021110", "hong.com", "홍길동", "0101111", "hong@", "사장");
	BusinessCard businessCard2("고컴", "대전시 유성구", "0432222", "0432220", "ko.com", "고길동", "0102222", "ko@", "과장");
	BusinessCard businessCard3("이컴", "대구시 달서구", "0523333", "0523330", "lee.com", "홍길동", "0103333", "gil@", "사원");
	BusinessCard businessCard4("홍컴", "서울시 마포구", "021111", "021110", "hong.com", "정길동", "0104444", "jung@", "대리");
	BusinessCard *index;

	index = businessCardHolder.PutIn(businessCard1);
	cout << index->GetCompanyName() << " " << index->GetAddress() << " " << index->GetCompanyTelephoneNumber() << " " << index->GetFaxNumber() << " " << index->GetUrl() << " "
		<< index->GetPersonalName() << " " << index->GetPersonalTelephoneNumber() << " " << index->GetEmailAddress() << " " << index->GetPosition() << endl;

	index = businessCardHolder.PutIn(businessCard2);
	cout << index->GetCompanyName() << " " << index->GetAddress() << " " << index->GetCompanyTelephoneNumber() << " " << index->GetFaxNumber() << " " << index->GetUrl() << " "
		<< index->GetPersonalName() << " " << index->GetPersonalTelephoneNumber() << " " << index->GetEmailAddress() << " " << index->GetPosition() << endl;

	index = businessCardHolder.PutIn(businessCard3);
	cout << index->GetCompanyName() << " " << index->GetAddress() << " " << index->GetCompanyTelephoneNumber() << " " << index->GetFaxNumber() << " " << index->GetUrl() << " "
		<< index->GetPersonalName() << " " << index->GetPersonalTelephoneNumber() << " " << index->GetEmailAddress() << " " << index->GetPosition() << endl;
	
	index = businessCardHolder.PutIn(businessCard4);
	cout << index->GetCompanyName() << " " << index->GetAddress() << " " << index->GetCompanyTelephoneNumber() << " " << index->GetFaxNumber() << " " << index->GetUrl() << " "
		<< index->GetPersonalName() << " " << index->GetPersonalTelephoneNumber() << " " << index->GetEmailAddress() << " " << index->GetPosition() << endl;

	index = businessCardHolder.First();
	cout << index->GetCompanyName() << " " << index->GetAddress() << " " << index->GetCompanyTelephoneNumber() << " " << index->GetFaxNumber() << " " << index->GetUrl() << " "
		<< index->GetPersonalName() << " " << index->GetPersonalTelephoneNumber() << " " << index->GetEmailAddress() << " " << index->GetPosition() << endl;

	index = businessCardHolder.Next();
	cout << index->GetCompanyName() << " " << index->GetAddress() << " " << index->GetCompanyTelephoneNumber() << " " << index->GetFaxNumber() << " " << index->GetUrl() << " "
		<< index->GetPersonalName() << " " << index->GetPersonalTelephoneNumber() << " " << index->GetEmailAddress() << " " << index->GetPosition() << endl;

	BusinessCard businessCard = businessCardHolder.PutOut(index);
	cout << businessCard.GetCompanyName() << " " << businessCard.GetAddress() << " " << businessCard.GetCompanyTelephoneNumber() << " " << businessCard.GetFaxNumber() << " " << businessCard.GetUrl() << " "
		<< businessCard.GetPersonalName() << " " << businessCard.GetPersonalTelephoneNumber() << " " << businessCard.GetEmailAddress() << " " << businessCard.GetPosition() << endl;

	index = businessCardHolder.PutIn(businessCard);
	cout << index->GetCompanyName() << " " << index->GetAddress() << " " << index->GetCompanyTelephoneNumber() << " " << index->GetFaxNumber() << " " << index->GetUrl() << " "
		<< index->GetPersonalName() << " " << index->GetPersonalTelephoneNumber() << " " << index->GetEmailAddress() << " " << index->GetPosition() << endl;

	BusinessCard* (*indexes);
	Long count;
	businessCardHolder.Find("홍길동", &indexes, &count);
	Long i = 0;
	while (i < count) {
		cout << indexes[i]->GetCompanyName() << " " << indexes[i]->GetAddress() << " " << indexes[i]->GetCompanyTelephoneNumber() << " " << indexes[i]->GetFaxNumber() << " " << indexes[i]->GetUrl() << " "
			<< indexes[i]->GetPersonalName() << " " << indexes[i]->GetPersonalTelephoneNumber() << " " << indexes[i]->GetEmailAddress() << " " << indexes[i]->GetPosition() << endl;
		i++;
	}

	index = businessCardHolder.Last();
	cout << index->GetCompanyName() << " " << index->GetAddress() << " " << index->GetCompanyTelephoneNumber() << " " << index->GetFaxNumber() << " " << index->GetUrl() << " "
		<< index->GetPersonalName() << " " << index->GetPersonalTelephoneNumber() << " " << index->GetEmailAddress() << " " << index->GetPosition() << endl;

	index = businessCardHolder.Previous();
	cout << index->GetCompanyName() << " " << index->GetAddress() << " " << index->GetCompanyTelephoneNumber() << " " << index->GetFaxNumber() << " " << index->GetUrl() << " "
		<< index->GetPersonalName() << " " << index->GetPersonalTelephoneNumber() << " " << index->GetEmailAddress() << " " << index->GetPosition() << endl;

	index = businessCardHolder.FindByCompanyName("홍컴");
	cout << index->GetCompanyName() << " " << index->GetAddress() << " " << index->GetCompanyTelephoneNumber() << " " << index->GetFaxNumber() << " " << index->GetUrl() << " "
		<< index->GetPersonalName() << " " << index->GetPersonalTelephoneNumber() << " " << index->GetEmailAddress() << " " << index->GetPosition() << endl;

	index = businessCardHolder.Move(indexes[0]);
	cout << index->GetCompanyName() << " " << index->GetAddress() << " " << index->GetCompanyTelephoneNumber() << " " << index->GetFaxNumber() << " " << index->GetUrl() << " "
		<< index->GetPersonalName() << " " << index->GetPersonalTelephoneNumber() << " " << index->GetEmailAddress() << " " << index->GetPosition() << endl;

	BusinessCardHolder another(businessCardHolder);
	BusinessCard *previous = 0;
	index = another.First();
	while (index != previous) {
		cout << index->GetCompanyName() << " " << index->GetAddress() << " " << index->GetCompanyTelephoneNumber() << " " << index->GetFaxNumber() << " " << index->GetUrl() << " "
			<< index->GetPersonalName() << " " << index->GetPersonalTelephoneNumber() << " " << index->GetEmailAddress() << " " << index->GetPosition() << endl;
		previous = index;
		index = another.Next();
	}

	businessCard = another.PutOut(index);
	businessCardHolder = another;
	i = 0;
	while (i < businessCardHolder.GetLength()) {
		cout << businessCardHolder[i].GetCompanyName() << " " << businessCardHolder[i].GetAddress() << " " << businessCardHolder[i].GetCompanyTelephoneNumber() << " " << businessCardHolder[i].GetFaxNumber() << " " << businessCardHolder[i].GetUrl() << " "
			<< businessCardHolder[i].GetPersonalName() << " " << businessCardHolder[i].GetPersonalTelephoneNumber() << " " << businessCardHolder[i].GetEmailAddress() << " " << businessCardHolder[i].GetPosition() << endl;
		i++;
	}

	if (indexes != 0) {
		delete[] indexes;
	}

	return 0;
}

int ComparePersonalNames(void *one, void *other) {
	BusinessCard *one_ = static_cast<BusinessCard*>(one);
	string *other_ = static_cast<string*>(other);

	return one_->GetPersonalName().compare(*other_);
}
int CompareCompanyNames(void *one, void *other) {
	BusinessCard *one_ = static_cast<BusinessCard*>(one);
	string *other_ = static_cast<string*>(other);

	return one_->GetCompanyName().compare(*other_);
}
int CompareBusinessCardLinks(void *one, void *other) {
	int ret;
	if (one < other) {
		ret = -1;
	}
	else if (one == other) {
		ret = 0;
	}
	else if (one > other) {
		ret = 1;
	}
	return ret;
}