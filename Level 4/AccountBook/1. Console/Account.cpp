#include "Account.h"

Account::Account()
	:date(Date::Today()), content(""), note("")
{
	this->amount = 0;
	this->balance = 0;
}

Account::Account(Date date, string content, Currency amount, Currency balance, string note)
	: date(date), content(content), note(note)
{
	this->amount = amount;
	this->balance = balance;
}

Account::Account(const Account& source)
	:date(source.date), content(source.content), note(source.note)
{
	this->amount = source.amount;
	this->balance = source.balance;
}

Account::~Account()
{

}

bool Account::IsEqual(const Account& other)
{
	bool ret = false;

	if (this->date == other.date && this->content.compare(other.content) == 0 && this->amount == other.amount
		&& this->balance == other.balance && this->note.compare(other.note) == 0)
	{
		ret = true;
	}

	return ret;
}

bool Account::IsNotEqual(const Account& other)
{
	bool ret = false;

	if (this->date != other.date || this->content.compare(other.content) != 0 || this->amount != other.amount
		|| this->balance != other.balance || this->note.compare(other.note) != 0)
	{
		ret = true;
	}

	return ret;
}

bool Account::operator==(const Account& other)
{
	bool ret = false;

	if (this->date == other.date && this->content.compare(other.content) == 0 && this->amount == other.amount
		&& this->balance == other.balance && this->note.compare(other.note) == 0)
	{
		ret = true;
	}

	return ret;
}

bool Account::operator!=(const Account& other)
{
	bool ret = false;

	if (this->date != other.date || this->content.compare(other.content) != 0 || this->amount != other.amount
		|| this->balance != other.balance || this->note.compare(other.note) != 0)
	{
		ret = true;
	}

	return ret;
}

Account& Account::operator=(const Account& source)
{
	this->date = source.date;
	this->content = source.content;
	this->amount = source.amount;
	this->balance = source.balance;
	this->note = source.note;

	return *this;
}
