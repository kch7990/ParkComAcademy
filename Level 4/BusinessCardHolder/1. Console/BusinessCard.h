// BusinessCard.h
#ifndef _BUSINESSCARD_H
#define _BUSINESSCARD_H

#include "Company.h"
#include "Personal.h"
#include <string>

using namespace std;

class BusinessCard
{
public:
	BusinessCard();
	BusinessCard(string companyName, string address, string companyTelephoneNumber, string faxNumber, string url,
		string personalName, string personalTelephoneNumber, string emailAddress, string position);
	BusinessCard(const BusinessCard& source);
	~BusinessCard();

	bool IsEqual(const BusinessCard& other);
	bool IsNotEqual(const BusinessCard& other);

	bool operator ==(const BusinessCard& other);
	bool operator !=(const BusinessCard& other);
	BusinessCard& operator =(const BusinessCard& source);

	string& GetCompanyName() const;
	string& GetAddress() const;
	string& GetCompanyTelephoneNumber() const;
	string& GetFaxNumber() const;
	string& GetUrl() const;
	string& GetPersonalName() const;
	string& GetPersonalTelephoneNumber() const;
	string& GetEmailAddress() const;
	string& GetPosition() const;

private:
	Company company;
	Personal personal;
};

inline string& BusinessCard::GetCompanyName() const
{
	return const_cast<string&>(this->company.GetName());
}

inline string& BusinessCard::GetAddress() const
{
	return const_cast<string&>(this->company.GetAddress());
}

inline string& BusinessCard::GetCompanyTelephoneNumber() const
{
	return const_cast<string&>(this->company.GetTelephoneNumber());
}
inline string& BusinessCard::GetFaxNumber() const
{
	return const_cast<string&>(this->company.GetFaxNumber());
}
inline string& BusinessCard::GetUrl() const
{
	return const_cast<string&>(this->company.GetUrl());
}
inline string& BusinessCard::GetPersonalName() const
{
	return const_cast<string&>(this->personal.GetName());
}
inline string& BusinessCard::GetPersonalTelephoneNumber() const
{
	return const_cast<string&>(this->personal.GetTelephoneNumber());
}
inline string& BusinessCard::GetEmailAddress() const
{
	return const_cast<string&>(this->personal.GetEmailAddress());
}
inline string& BusinessCard::GetPosition() const
{
	return const_cast<string&>(this->personal.GetPosition());
}

#endif //_BUSINESSCARD_H
