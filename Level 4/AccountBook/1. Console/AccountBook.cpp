#include "AccountBook.h"
#include "Account.h"
#include "Income.h"
#include "Outgo.h"


AccountBook::AccountBook(Long capacity)
	: accounts(capacity)
{
	this->capacity = capacity;
	this->length = 0;
}
AccountBook::AccountBook(const AccountBook& source)
	: accounts(source.capacity)
{
	Account *account;
	Long i = 0;
	while (i < source.length)
	{
		account = (const_cast<AccountBook&>(source)).accounts[i]; //const_cast OFF(toggle)
		if (dynamic_cast<Income*>(account))
		{
			account = new Income(*(dynamic_cast<Income*>(account)));
		}
		else if (dynamic_cast<Outgo*>(account))
		{
			account = new Outgo(*(dynamic_cast<Outgo*>(account)));
		}
		this->accounts.Store(i, account);
		i++;
	}
	this->length = source.length;
}
AccountBook::~AccountBook()
{
	Long i = 0;
	while (i < this->length)
	{
		delete this->accounts[i];
		i++;
	}
}
Long AccountBook::Record(Date date, string content, Currency amount, string note)
{
	Account *account;
	Long index;
	Currency balance = 0;
	if (this->length > 0)
	{
		balance = this->accounts.GetAt(this->length - 1)->GetBalance();
	}
	balance += amount;
	if (amount >= 0)
	{
		account = new Income(date, content, amount, balance, note);
	}
	else
	{
		account = new Outgo(date, content, -amount, balance, note);
	}

	if (this->length < this->capacity)
	{
		index = this->accounts.Store(this->length, account);
	}
	else
	{
		index = this->accounts.AppendFromRear(account);
		this->capacity++;
	}
	this->length++;

	return index;
}
Long AccountBook::Correct(Long index, Currency amount, string note)
{
	Account *account = this->accounts[index];
	Date date = account->GetDate();
	string content = account->GetContent();
	Currency balance = account->GetBalance();

	Currency amountOfAccount = account->GetAmount();
	Currency difference;
	Account *temp;
	if (dynamic_cast<Income*>(account))
	{
		difference = amount - amountOfAccount;
		balance += difference;
		temp = new Income(date, content, amount, balance, note);
	}
	else if (dynamic_cast<Outgo*>(account))
	{
		difference = amount + amountOfAccount;
		balance += difference;
		temp = new Outgo(date, content, -amount, balance, note);
	}
	if (account != 0)
	{
		delete account;
	}
	index = this->accounts.Modify(index, temp);

	Long i = index + 1;
	while (i < this->length)
	{
		account = this->accounts[i];
		date = account->GetDate();
		content = account->GetContent();
		amount = account->GetAmount();
		balance = account->GetBalance() + difference;
		note = account->GetNote();

		if (dynamic_cast<Income*>(account))
		{
			temp = new Income(date, content, amount, balance, note);
		}
		else if (dynamic_cast<Outgo*>(account))
		{
			temp = new Outgo(date, content, amount, balance, note);
		}
		if (account != 0)
		{
			delete account;
		}
		this->accounts.Modify(i, temp);
		i++;
	}

	return index;
}
void AccountBook::Find(const Date& date, Long *(*indexes), Long *count)
{
	this->accounts.BinarySearchDuplicate(&const_cast<Date&>(date), indexes, count, CompareDates);
}
void AccountBook::Find(string content, Long *(*indexes), Long *count)
{
	this->accounts.LinearSearchDuplicate(&content, indexes, count, CompareContents);
}
void AccountBook::Find(const Date& startDate, const Date& endDate, Long *(*indexes), Long *count)
{
	Long i;
	Long j = 0;
	Long(*dateIndexes);
	Long countDate;

	*indexes = new Long[this->length];
	*count = 0;
	Date date = startDate;
	while (date <= endDate)
	{
		this->accounts.BinarySearchDuplicate(&date, &dateIndexes, &countDate, CompareDates);
		i = 0;
		while (i<countDate)
		{
			(*indexes)[j++] = dateIndexes[i];
			(*count)++;
			i++;
		}
		if (dateIndexes != 0)
		{
			delete[] dateIndexes;
		}
		date++;
	}
}
void AccountBook::Find(string content, const Date& startDate, const Date& endDate, Long *(*indexes), Long *count)
{
	Long i;
	Long j = 0;
	Long(*dateIndexes);
	Long countDate;

	*indexes = new Long[this->length];
	*count = 0;
	Date date = startDate;
	while (date <= endDate)
	{
		this->accounts.BinarySearchDuplicate(&date, &dateIndexes, &countDate, CompareDates);
		i = 0;
		while (i < countDate)
		{
			if (content.compare(this->accounts.GetAt(dateIndexes[i])->GetContent()) == 0)
			{
				(*indexes)[j++] = dateIndexes[i];
				(*count)++;
			}
			i++;
		}
		if (dateIndexes != 0)
		{
			delete[] dateIndexes;
		}
		date++;
	}
}
void AccountBook::Calculate(const Date& startDate, const Date& endDate, Currency *sumOfIncome, Currency *sumOfOutgo, Currency *difference)
{
	Long(*indexes);
	Long count;
	Account *account;
	Currency amount;
	Long i;
	*sumOfIncome = 0;
	*sumOfOutgo = 0;
	*difference = 0;
	Date date = startDate;
	while (date <= endDate)
	{
		this->accounts.BinarySearchDuplicate(&date, &indexes, &count, CompareDates);
		i = 0;
		while (i < count)
		{
			account = this->accounts.GetAt(indexes[i]);
			amount = account->GetAmount();
			if (dynamic_cast<Income*>(account))
			{
				*sumOfIncome += amount;
			}
			else if (dynamic_cast<Outgo*>(account))
			{
				*sumOfOutgo += amount;
			}
			i++;
		}
		if (indexes != 0)
		{
			delete[] indexes;
		}
		date++;
	}
	*difference = *sumOfIncome - *sumOfOutgo;
}
Account* AccountBook::GetAt(Long index) {
	return this->accounts.GetAt(index);
}

AccountBook& AccountBook::operator =(const AccountBook& source) {
	Long i = 0;
	Account *account;
	while (i < this->length) {
		delete this->accounts[i];
		i++;
	}
	this->accounts = source.accounts;
	this->capacity = source.capacity;
	this->length = 0;
	i = 0;
	while (i < source.length) {
		account = (const_cast<AccountBook&>(source).accounts[i]);
		if (dynamic_cast<Income*>(account)) {
			account = new Income(*(dynamic_cast<Income*>(account)));
		}
		else if (dynamic_cast<Outgo*>(account)) {
			account = new Outgo(*(dynamic_cast<Outgo*>(account)));
		}
		this->accounts.Modify(i, account);
		i++;
	}
	this->length = source.length;
	return *this;

}
Account* AccountBook::operator[](Long index) {
	return this->accounts[index];
}

int CompareDates(void *one, void *other) {
	Account **one_ = static_cast<Account**>(one);
	Date *other_ = static_cast<Date*>(other);
	int ret;
	if ((*one_)->GetDate() < *other_) {
		ret = -1;
	}
	else if ((*one_)->GetDate() == *other_) {
		ret = 0;
	}
	else if ((*one_)->GetDate() > *other_) {
		ret = 1;
	}
	return ret;
}

int CompareContents(void *one, void *other) {
	Account **one_ = static_cast<Account**>(one);
	string *other_ = static_cast<string*>(other);

	return (*one_)->GetContent().compare(*other_);
}

#include <iostream>
using namespace std;
int main(int argc, char *argv[]) {
	AccountBook accountBook;
	Long index = accountBook.Record(Date(2019, APR, 1), "용돈", 300000.0, "어머니");
	Account *account = accountBook.GetAt(index);
	cout << static_cast<char*>(account->GetDate()) << " " << account->GetContent() << " "
		<< account->GetAmount() << " " << account->GetBalance() << " " << account->GetNote() << endl;

	index = accountBook.Record(Date(2019, APR, 1), "식사", -10000.0, "");
	account = accountBook.GetAt(index);
	cout << static_cast<char*>(account->GetDate()) << " " << account->GetContent() << " "
		<< account->GetAmount() << " " << account->GetBalance() << " " << account->GetNote() << endl;

	index = accountBook.Record(Date(2019, APR, 1), "교통카드", -50000.0, "");
	account = accountBook.GetAt(index);
	cout << static_cast<char*>(account->GetDate()) << " " << account->GetContent() << " "
		<< account->GetAmount() << " " << account->GetBalance() << " " << account->GetNote() << endl;

	index = accountBook.Record(Date(2019, APR, 2), "식사", -10000.0, "");
	account = accountBook.GetAt(index);
	cout << static_cast<char*>(account->GetDate()) << " " << account->GetContent() << " "
		<< account->GetAmount() << " " << account->GetBalance() << " " << account->GetNote() << endl;

	index = accountBook.Record(Date(2019, APR, 3), "간식", -10000.0, "");
	account = accountBook.GetAt(index);
	cout << static_cast<char*>(account->GetDate()) << " " << account->GetContent() << " "
		<< account->GetAmount() << " " << account->GetBalance() << " " << account->GetNote() << endl;

	cout << "고치기" << endl;
	index = accountBook.Correct(0, 350000.0, "어머니");
	account = accountBook.GetAt(index);
	cout << static_cast<char*>(account->GetDate()) << " " << account->GetContent() << " "
		<< account->GetAmount() << " " << account->GetBalance() << " " << account->GetNote() << endl;
	cout << "전체 출력" << endl;
	Long i = 0;
	while (i < accountBook.GetLength()) {
		account = accountBook.GetAt(i);
		cout << static_cast<char*>(account->GetDate()) << " " << account->GetContent() << " "
			<< account->GetAmount() << " " << account->GetBalance() << " " << account->GetNote() << endl;
		i++;
	}

	cout << "날짜로 찾기" << endl;
	Long(*indexes);
	Long count;
	accountBook.Find(Date(2019, APR, 1), &indexes, &count);
	i = 0;
	while (i < count) {
		account = accountBook.GetAt(indexes[i]);
		cout << static_cast<char*>(account->GetDate()) << " " << account->GetContent() << " "
			<< account->GetAmount() << " " << account->GetBalance() << " " << account->GetNote() << endl;
		i++;
	}
	if (indexes != 0) {
		delete[] indexes;
	}

	cout << "기간 별 찾기" << endl;
	accountBook.Find(Date(2019, APR, 1), Date(2019, APR, 2), &indexes, &count);

	i = 0;
	while (i < count) {
		account = accountBook.GetAt(indexes[i]);
		cout << static_cast<char*>(account->GetDate()) << " " << account->GetContent() << " "
			<< account->GetAmount() << " " << account->GetBalance() << " " << account->GetNote() << endl;
		i++;
	}
	if (indexes != 0) {
		delete[] indexes;
	}

	cout << "적요로 찾기" << endl;
	accountBook.Find(string("식사"), &indexes, &count);
	//string("식사") 이렇게 하지않으면 Date로만 찾는 find와 인수목록이 겹쳐버림
	i = 0;
	while (i < count) {
		account = accountBook.GetAt(indexes[i]);
		cout << static_cast<char*>(account->GetDate()) << " " << account->GetContent() << " "
			<< account->GetAmount() << " " << account->GetBalance() << " " << account->GetNote() << endl;
		i++;
	}
	if (indexes != 0) {
		delete[] indexes;
	}
	
	cout << "적요와 기간별 찾기" << endl;
	accountBook.Find(string("식사"), Date(2019, APR, 1), Date(2019, APR, 3), &indexes, &count);
	i = 0;
	while (i < count) {
		account = accountBook.GetAt(indexes[i]);
		cout << static_cast<char*>(account->GetDate()) << " " << account->GetContent() << " "
			<< account->GetAmount() << " " << account->GetBalance() << " " << account->GetNote() << endl;
		i++;
	}

	Currency sumOfIncome;
	Currency sumOfOutgo;
	Currency difference;
	accountBook.Calculate(Date(2019, APR, 1), Date(2019, APR, 2), &sumOfIncome, &sumOfOutgo, &difference);
	cout << "총수입: " << sumOfIncome << " " << "총지출: " << sumOfOutgo << " " << "차액: " << difference << endl;

	AccountBook another(accountBook);
	i = 0;
	while (i < another.GetLength()) {
		cout << static_cast<char*>(another[i]->GetDate()) << " " << another[i]->GetContent() << " "
			<< another[i]->GetAmount() << " " << another[i]->GetBalance() << " " << another[i]->GetNote() << endl;
		i++;
	}

	cout << "고치고 치환연산자" << endl;

	index = another.Correct(2, -55000.0, "");

	accountBook = another;
	i = 0;
	while (i < accountBook.GetLength()) {
		cout << static_cast<char*>(accountBook[i]->GetDate()) << " " << accountBook[i]->GetContent() << " "
			<< accountBook[i]->GetAmount() << " " << accountBook[i]->GetBalance() << " " << accountBook[i]->GetNote() << endl;
		i++;
	}

	return 0;
}