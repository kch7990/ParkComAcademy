#include "Personal.h"

Personal::Personal()
	: name(""), telephoneNumber(""), emailAddress(""), position("") {
}
Personal::Personal(string name, string telephoneNumber, string emailAddress, string position)
	: name(name), telephoneNumber(telephoneNumber), emailAddress(emailAddress), position(position) {
}
Personal::Personal(const Personal& source)
	: name(source.name), telephoneNumber(source.telephoneNumber), emailAddress(source.emailAddress), position(source.position) {
}
Personal::~Personal() {
}
bool Personal::IsEqual(const Personal& other) {
	bool ret = false;
	if (this->name.compare(other.name) == 0 &&
		this->telephoneNumber.compare(other.telephoneNumber) == 0 &&
		this->emailAddress.compare(other.emailAddress) == 0 &&
		this->position.compare(other.position) == 0) {
		ret = true;
	}

	return ret;
}
bool Personal::IsNotEqual(const Personal& other) {
	bool ret = false;
	if (this->name.compare(other.name) != 0 ||
		this->telephoneNumber.compare(other.telephoneNumber) != 0 ||
		this->emailAddress.compare(other.emailAddress) != 0 ||
		this->position.compare(other.position) != 0) {
		ret = true;
	}

	return ret;
}
bool Personal::operator ==(const Personal& other) {
	bool ret = false;
	if (this->name.compare(other.name) == 0 &&
		this->telephoneNumber.compare(other.telephoneNumber) == 0 &&
		this->emailAddress.compare(other.emailAddress) == 0 &&
		this->position.compare(other.position) == 0) {
		ret = true;
	}

	return ret;
}
bool Personal::operator !=(const Personal& other) {
	bool ret = false;
	if (this->name.compare(other.name) != 0 ||
		this->telephoneNumber.compare(other.telephoneNumber) != 0 ||
		this->emailAddress.compare(other.emailAddress) != 0 ||
		this->position.compare(other.position) != 0) {
		ret = true;
	}

	return ret;
}
Personal& Personal::operator =(const Personal& source) {
	this->name = source.name;
	this->telephoneNumber = source.telephoneNumber;
	this->emailAddress = source.emailAddress;
	this->position = source.position;

	return *this;
}