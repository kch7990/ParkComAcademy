// BusinessCard.cpp
#include "BusinessCard.h"

BusinessCard::BusinessCard()
{

}

BusinessCard::BusinessCard(string companyName, string address, string companyTelephoneNumber, string faxNumber, string url,
	string personalName, string personalTelephoneNumber, string emailAddress, string position)
	:company(companyName, address, companyTelephoneNumber, faxNumber, url),
	personal(personalName, personalTelephoneNumber, emailAddress, position)
{

}

BusinessCard::BusinessCard(const BusinessCard& source)
	:company(source.company), personal(source.personal)
{

}

BusinessCard::~BusinessCard()
{

}

bool BusinessCard::IsEqual(const BusinessCard& other)
{
	bool ret = false;

	if (this->company.IsEqual(other.company) && this->personal.IsEqual(other.personal))
	{
		ret = true;
	}

	return ret;
}

bool BusinessCard::IsNotEqual(const BusinessCard& other)
{
	bool ret = false;

	if (this->company.IsNotEqual(other.company) || this->personal.IsNotEqual(other.personal))
	{
		ret = true;
	}

	return ret;
}

bool BusinessCard::operator ==(const BusinessCard& other)
{
	bool ret = false;

	if (this->company == other.company && this->personal == other.personal)
	{
		ret = true;
	}

	return ret;
}

bool BusinessCard::operator !=(const BusinessCard& other)
{
	bool ret = false;

	if (this->company != other.company || this->personal != other.personal)
	{
		ret = true;
	}

	return ret;
}

BusinessCard& BusinessCard::operator =(const BusinessCard& source)
{
	this->company = source.company;
	this->personal = source.personal;

	return *this;
}
