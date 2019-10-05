#ifndef _PERSONAL_H
#define _PERSONAL_H

#include <string>

using namespace std;
class Personal {
public:
	Personal();
	Personal(string name, string telephoneNumber, string emailAddress, string position);
	Personal(const Personal& source);
	~Personal();
	bool IsEqual(const Personal& other);
	bool IsNotEqual(const Personal& other);
	bool operator ==(const Personal& other);
	bool operator !=(const Personal& other);
	Personal& operator =(const Personal& source);

	string& GetName() const;
	string& GetTelephoneNumber() const;
	string& GetEmailAddress() const;
	string& GetPosition() const;
private:
	string name;
	string telephoneNumber;
	string emailAddress;
	string position;
};
inline string& Personal::GetName() const {
	return const_cast<string&>(this->name);
}
inline string& Personal::GetTelephoneNumber() const {
	return const_cast<string&>(this->telephoneNumber);
}
inline string& Personal::GetEmailAddress() const {
	return const_cast<string&>(this->emailAddress);
}
inline string& Personal::GetPosition() const {
	return const_cast<string&>(this->position);
}

#endif //_PERSONAL_H