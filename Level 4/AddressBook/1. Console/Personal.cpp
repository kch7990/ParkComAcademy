#include "Personal.h"

Personal::Personal()
	:name(""), address(""), telephoneNumber(""), emailAddress("") {
}
Personal::Personal(string name, string address, string telephoneNumber, string emailAddress)
	:name(name), address(address), telephoneNumber(telephoneNumber), emailAddress(emailAddress){
}
Personal::Personal(const Personal& source)
	:name(source.name), address(source.address), telephoneNumber(source.telephoneNumber), emailAddress(source.emailAddress){
}
Personal::~Personal() {
}
bool Personal::IsEqual(const Personal& other) {
	bool ret = false;

	if (this->name.compare(other.name) == 0 && this->address.compare(other.address) == 0 &&
		this->telephoneNumber.compare(other.telephoneNumber) == 0 && this->emailAddress.compare(other.emailAddress) == 0) {
		ret = true;
	}

	return ret;
}
bool Personal::IsNotEqual(const Personal& other) {
	bool ret = false;

	if (this->name.compare(other.name) != 0 || this->address.compare(other.address) != 0
		|| this->telephoneNumber.compare(other.telephoneNumber) != 0 || this->emailAddress.compare(other.emailAddress) != 0) {
		ret = true;
	}

	return ret;
}
bool Personal::operator ==(const Personal& other) {
	bool ret = false;
	
	if (this->name.compare(other.name) == 0 && this->address.compare(other.address) == 0 &&
		this->telephoneNumber.compare(other.telephoneNumber) == 0 && this->emailAddress.compare(other.emailAddress) == 0) {
		ret = true;
	}

	return ret;
}
bool Personal::operator !=(const Personal& other) {
	bool ret = false;

	if (this->name.compare(other.name) != 0 || this->address.compare(other.address) != 0
		|| this->telephoneNumber.compare(other.telephoneNumber) != 0 || this->emailAddress.compare(other.emailAddress) != 0) {
		ret = true;
	}

	return ret;
}
Personal& Personal::operator =(const Personal& source) {
	this->name = source.name;
	this->address = source.address;
	this->telephoneNumber = source.telephoneNumber;
	this->emailAddress = source.emailAddress;

	return *this;
}
#if 0
#include <iostream>

using namespace std;
int main(int argc, char* argv[]) {
	//디폴트 생성자
	Personal me;
	cout << me.GetName() << "/" << me.GetAddress() << "/" << me.GetTelephoneNumber() << "/" << me.GetEmailAddress() << endl;
	//매개변수를 갖는 생성자
	Personal somebody("홍길동", "서울시 마포구", "0101111", "hong@");
	cout << somebody.GetName() << "/" << somebody.GetAddress() << "/" << somebody.GetTelephoneNumber() << "/" << somebody.GetEmailAddress() << endl;
	//복사 생성자
	Personal somesomebody(somebody);
	cout << somesomebody.GetName() << "/" << somebody.GetAddress() << "/" << somebody.GetTelephoneNumber() << "/" << somebody.GetEmailAddress() << endl;
	//IsEqual 연산 함수
	bool ret = somesomebody.IsEqual(somebody);
	if (ret == true) {
		cout << "같은 사람" << endl;
	}
	//==연산자 함수
	if (somesomebody == somebody) {
		cout << "같은 사람" << endl;
	}

	Personal meme("김길동", "서울시 서대문구", "0102222", "kim@");
	cout << meme.GetName() << "/" << meme.GetAddress() << "/" << meme.GetTelephoneNumber() << "/" << meme.GetEmailAddress() << endl;
	//치환 연산자 함수
	me = meme;
	cout << me.GetName() << "/" << me.GetAddress() << "/" << me.GetTelephoneNumber() << "/" << me.GetEmailAddress() << endl;
	//IsNotEqual 연산 함수
	ret = me.IsNotEqual(somebody);
	if (ret == true) {
		cout << "다른 사람" << endl;
	}
	//!=연산자 함수
	if (me != somebody) {
		cout << "다른 사람" << endl;
	}

	return 0;
}
#endif