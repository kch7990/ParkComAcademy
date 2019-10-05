#ifndef _COMPANY_H
#define _COMPANY_H

#include <string>
using namespace std;
class Company {
public:
	Company();
	Company(string name, string address, string telephoneNumber, string faxNumber, string url);
	Company(const Company& source);
	~Company();
	bool IsEqual(const Company& other);
	bool IsNotEqual(const Company& other);
	bool operator ==(const Company& other);
	bool operator !=(const Company& other);
	Company& operator =(const Company& source);
	
	string& GetName() const;
	string& GetAddress() const;
	string& GetTelephoneNumber() const;
	string& GetFaxNumber() const;
	string& GetUrl() const;
private:
	string name;
	string address;
	string telephoneNumber;
	string faxNumber;
	string url;
};
inline string& Company::GetName() const {
	return const_cast<string&>(this->name);
}
inline string& Company::GetAddress() const {
	return const_cast<string&>(this->address);
}
inline string& Company::GetTelephoneNumber() const {
	return const_cast<string&>(this->telephoneNumber);
}
inline string& Company::GetFaxNumber() const {
	return const_cast<string&>(this->faxNumber);
}
inline string& Company::GetUrl() const {
	return const_cast<string&>(this->url);
}

#endif //_COMPANY_H