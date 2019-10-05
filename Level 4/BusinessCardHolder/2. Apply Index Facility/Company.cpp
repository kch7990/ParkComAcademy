#include "Company.h"

Company::Company()
	: name(""), address(""), telephoneNumber(""), faxNumber(""), url("") {
}
Company::Company(string name, string address, string telephoneNumber, string faxNumber, string url)
	: name(name), address(address), telephoneNumber(telephoneNumber), faxNumber(faxNumber), url(url) {
}
Company::Company(const Company& source)
	: name(source.name), address(source.address), telephoneNumber(source.telephoneNumber), faxNumber(source.faxNumber), url(source.url) {
}
Company::~Company() {
}
bool Company::IsEqual(const Company& other) {
	bool ret = false;
	if (this->name.compare(other.name) == 0 &&
		this->address.compare(other.address) == 0 &&
		this->telephoneNumber.compare(other.telephoneNumber) == 0 &&
		this->faxNumber.compare(other.faxNumber) == 0 &&
		this->url.compare(other.url) == 0) {
		ret = true;
	}

	return ret;
}
bool Company::IsNotEqual(const Company& other) {
	bool ret = false;
	if (this->name.compare(other.name) != 0 ||
		this->address.compare(other.address) != 0 ||
		this->telephoneNumber.compare(other.telephoneNumber) != 0 ||
		this->faxNumber.compare(other.faxNumber) != 0 ||
		this->url.compare(other.url) != 0) {
		ret = true;
	}

	return ret;
}
bool Company::operator ==(const Company& other) {
	bool ret = false;
	if (this->name.compare(other.name) == 0 &&
		this->address.compare(other.address) == 0 &&
		this->telephoneNumber.compare(other.telephoneNumber) == 0 &&
		this->faxNumber.compare(other.faxNumber) == 0 &&
		this->url.compare(other.url) == 0) {
		ret = true;
	}

	return ret;
}
bool Company::operator !=(const Company& other) {
	bool ret = false;
	if (this->name.compare(other.name) != 0 ||
		this->address.compare(other.address) != 0 ||
		this->telephoneNumber.compare(other.telephoneNumber) != 0 ||
		this->faxNumber.compare(other.faxNumber) != 0 ||
		this->url.compare(other.url) != 0) {
		ret = true;
	}

	return ret;
}
Company& Company::operator =(const Company& source) {
	this->name = source.name;
	this->address = source.address;
	this->telephoneNumber = source.telephoneNumber;
	this->faxNumber = source.faxNumber;
	this->url = source.url;

	return *this;
}