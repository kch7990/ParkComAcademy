#include "Date.h"
#include <ctime>
#include <cstdio>

Date::Date() {
	this->year = 1900;
	this->month = JAN;
	this->day = 1;
	this->weekDay = MON;
}
Date::Date(Short year, Month month, Short day) {
	struct tm date = { 0, };

	date.tm_year = year - 1900;
	date.tm_mon = month - 1;
	date.tm_mday = day;

	mktime(&date);

	this->year = date.tm_year + 1900;
	this->month = static_cast<Month>(date.tm_mon + 1);
	this->day = date.tm_mday;
	this->weekDay = static_cast<WeekDay>(date.tm_wday);
}
Date::Date(const char(*date)) {
	struct tm _date = { 0, };

	sscanf(date, "%4d%2d%2d", &this->year, &this->month, &this->day);

	_date.tm_year = this->year - 1900;
	_date.tm_mon = this->month - 1;
	_date.tm_mday = this->day;

	mktime(&_date);

	this->year = _date.tm_year + 1900;
	this->month = static_cast<Month>(_date.tm_mon + 1);
	this->day = _date.tm_mday;
	this->weekDay = static_cast<WeekDay>(_date.tm_wday);
}
Date::Date(const Date& source) {
	this->year = source.year;
	this->month = source.month;
	this->day = source.day;
	this->weekDay = source.weekDay;
}
Date::~Date() {
}
Date Date::Today() {
	time_t timer;
	struct tm *today;
	Date today_; //Date()

	time(&timer);
	today = localtime(&timer);

	today_.year = today->tm_year + 1900;
	today_.month = static_cast<Month>(today->tm_mon + 1);
	today_.day = today->tm_mday;
	today_.weekDay = static_cast<WeekDay>(today->tm_wday);

	return today_;
}
Date Date::Yesterday() {
	struct tm yesterday = { 0, };
	Date yesterday_;

	yesterday.tm_year = this->year - 1900;
	yesterday.tm_mon = this->month - 1;
	yesterday.tm_mday = this->day - 1;

	mktime(&yesterday);

	yesterday_.year = yesterday.tm_year + 1900;
	yesterday_.month = static_cast<Month>(yesterday.tm_mon + 1);
	yesterday_.day = yesterday.tm_mday;
	yesterday_.weekDay = static_cast<WeekDay>(yesterday.tm_wday);

	return yesterday_;
}
Date Date::Tomorrow() {
	struct tm tomorrow = { 0, };
	Date tomorrow_;

	tomorrow.tm_year = this->year - 1900;
	tomorrow.tm_mon = this->month - 1;
	tomorrow.tm_mday = this->day + 1;

	mktime(&tomorrow);

	tomorrow_.year = tomorrow.tm_year + 1900;
	tomorrow_.month = static_cast<Month>(tomorrow.tm_mon + 1);
	tomorrow_.day = tomorrow.tm_mday;
	tomorrow_.weekDay = static_cast<WeekDay>(tomorrow.tm_wday);

	return tomorrow_;
}
Date Date::PreviousDate(Short days) {
	struct tm previousDate = { 0, };
	Date previousDate_;

	previousDate.tm_year = this->year - 1900;
	previousDate.tm_mon = this->month - 1;
	previousDate.tm_mday = this->day - days;

	mktime(&previousDate);

	previousDate_.year = previousDate.tm_year + 1900;
	previousDate_.month = static_cast<Month>(previousDate.tm_mon + 1);
	previousDate_.day = previousDate.tm_mday;
	previousDate_.weekDay = static_cast<WeekDay>(previousDate.tm_wday);

	return previousDate_;
}
Date Date::NextDate(Short days) {
	struct tm nextDate = { 0, };
	Date nextDate_;

	nextDate.tm_year = this->year - 1900;
	nextDate.tm_mon = this->month - 1;
	nextDate.tm_mday = this->day + days;

	mktime(&nextDate);

	nextDate_.year = nextDate.tm_year + 1900;
	nextDate_.month = static_cast<Month>(nextDate.tm_mon + 1);
	nextDate_.day = nextDate.tm_mday;
	nextDate_.weekDay = static_cast<WeekDay>(nextDate.tm_wday);

	return nextDate_;
}
bool Date::IsEqual(const Date& other) {
	bool ret = false;

	if (this->year == other.year && this->month == other.month && this->day == other.day) {
		ret = true;
	}

	return ret;
}
bool Date::IsNotEqual(const Date& other) {
	bool ret = false;

	if (this->year != other.year || this->month != other.month || this->day != other.day) {
		ret = true;
	}

	return ret;
}
bool Date::IsLesserThan(const Date& other) {
	bool ret = false;

	if (this->year < other.year) {
		ret = true;
	}
	else if (this->year == other.year && this->month < other.month) {
		ret = true;
	}
	else if (this->year == other.year&& this->month == other.month && this->day < other.day) {
		ret = true;
	}

	return ret;
}
bool Date::IsGreaterThan(const Date& other) {
	bool ret = false;

	if (this->year > other.year) {
		ret = true;
	}
	else if (this->year == other.year && this->month > other.month) {
		ret = true;
	}
	else if (this->year == other.year && this->month == other.month && this->day > other.day) {
		ret = true;
	}

	return ret;
}
Date::operator char*() {
	static char buffer[9];

	sprintf(buffer, "%4d%02d%02d", this->year, this->month, this->day);

	return buffer;
}
Date& Date::operator --() {
	struct tm date = { 0, };

	date.tm_year = this->year - 1900;
	date.tm_mon = this->month - 1;
	date.tm_mday = this->day - 1;

	mktime(&date);

	this->year = date.tm_year + 1900;
	this->month = static_cast<Month>(date.tm_mon + 1);
	this->day = date.tm_mday;
	this->weekDay = static_cast<WeekDay>(date.tm_wday);

	return *this;
}
Date Date::operator --(int) {
	Date date_(*this); //복사 생성자
	struct tm date = { 0, };

	date.tm_year = this->year - 1900;
	date.tm_mon = this->month - 1;
	date.tm_mday = this->day - 1;

	mktime(&date);

	this->year = date.tm_year + 1900;
	this->month = static_cast<Month>(date.tm_mon + 1);
	this->day = date.tm_mday;
	this->weekDay = static_cast<WeekDay>(date.tm_wday);

	return date_;
}
Date& Date::operator ++() {
	struct tm date = { 0, };

	date.tm_year = this->year - 1900;
	date.tm_mon = this->month - 1;
	date.tm_mday = this->day + 1;

	mktime(&date);

	this->year = date.tm_year + 1900;
	this->month = static_cast<Month>(date.tm_mon + 1);
	this->day = date.tm_mday;
	this->weekDay = static_cast<WeekDay>(date.tm_wday);

	return *this;
}
Date Date::operator ++(int) {
	Date date_(*this);
	struct tm date = { 0, };

	date.tm_year = this->year - 1900;
	date.tm_mon = this->month - 1;
	date.tm_mday = this->day + 1;

	mktime(&date);

	this->year = date.tm_year + 1900;
	this->month = static_cast<Month>(date.tm_mon + 1);
	this->day = date.tm_mday;
	this->weekDay = static_cast<WeekDay>(date.tm_wday);

	return date_;
}
Date Date::operator -(Short days) {
	Date date_;
	struct tm date = { 0, };

	date.tm_year = this->year - 1900;
	date.tm_mon = this->month - 1;
	date.tm_mday = this->day - days;

	mktime(&date);

	date_.year = date.tm_year + 1900;
	date_.month = static_cast<Month>(date.tm_mon + 1);
	date_.day = date.tm_mday;
	date_.weekDay = static_cast<WeekDay>(date.tm_wday);

	return date_;
}
Date Date::operator +(Short days) {
	Date date_;
	struct tm date = { 0, };

	date.tm_year = this->year - 1900;
	date.tm_mon = this->month - 1;
	date.tm_mday = this->day + days;

	mktime(&date);

	date_.year = date.tm_year + 1900;
	date_.month = static_cast<Month>(date.tm_mon + 1);
	date_.day = date.tm_mday;
	date_.weekDay = static_cast<WeekDay>(date.tm_wday);

	return date_;
}
bool Date::operator ==(const Date& other) {
	bool ret = false;
	
	if (this->year == other.year && this->month == other.month && this->day == other.day) {
		ret = true;
	}

	return ret;
}
bool Date::operator !=(const Date& other) {
	bool ret = false;

	if (this->year != other.year || this->month != other.month || this->day != other.day) {
		ret = true;
	}

	return ret;
}
bool Date::operator <(const Date& other) {
	bool ret = false;

	if (this->year < other.year) {
		ret = true;
	}
	else if (this->year == other.year && this->month < other.month) {
		ret = true;
	}
	else if (this->year == other.year && this->month == other.month && this->day < other.day) {
		ret = true;
	}

	return ret;
}
bool Date::operator <=(const Date& other) {
	bool ret = false;

	if (this->year < other.year) {
		ret = true;
	}
	else if (this->year == other.year && this->month < other.month) {
		ret = true;
	}
	else if (this->year == other.year && this->month == other.month && this->day < other.day) {
		ret = true;
	}
	else if (this->year == other.year && this->month == other.month && this->day == other.day) {
		ret = true;
	}

	
	return ret;
}
bool Date::operator >(const Date& other) {
	bool ret = false;

	if (this->year > other.year) {
		ret = true;
	}
	else if (this->year == other.year && this->month > other.month) {
		ret = true;
	}
	else if (this->year == other.year && this->month == other.month && this->day > other.day) {
		ret = true;
	}
	
	return ret;
}
bool Date::operator >=(const Date& other) {
	bool ret = false;

	if (this->year > other.year) {
		ret = true;
	}
	else if (this->year == other.year && this->month > other.month) {
		ret = true;
	}
	else if (this->year == other.year && this->month == other.month && this->day > other.day) {
		ret = true;
	}
	else if (this->year == other.year&&this->month == other.month&& this->day == other.day) {
		ret = true;
	}

	return ret;
}
Date& Date::operator =(const Date& source) {
	this->year = source.year;
	this->month = source.month;
	this->day = source.day;
	this->weekDay = source.weekDay;

	return *this;
}

#include <iostream>

using namespace std;
int main(int argc, char* argv[]) {
	Date today;
	Date yesterday;
	Date tomorrow;
	Date previousDate;
	Date nextDate;
	bool isEqual;
	bool isNotEqual;
	bool isLesserThan;
	bool isGreaterThan;

	today = Date::Today();
	cout << today.GetYear() << "-" << today.GetMonth() << "-" << today.GetDay() << endl;
	
	previousDate = today.PreviousDate(static_cast<Short>(3));
	cout << previousDate.GetYear() << "-" << previousDate.GetMonth() << "-" << previousDate.GetDay() << endl;
	
	isGreaterThan = today.IsGreaterThan(previousDate);
	if (isGreaterThan == true) {
		cout << "더 큽니다" << endl;
	}
	
	yesterday = today.Yesterday();
	cout << yesterday.GetYear() << "-" << yesterday.GetMonth() << "-" << yesterday.GetDay() << endl;
	
	previousDate = today.PreviousDate(static_cast<Short>(1));
	cout << previousDate.GetYear() << "-" << previousDate.GetMonth() << "-" << previousDate.GetDay() << endl;
	
	isEqual = yesterday.IsEqual(previousDate);
	if (isEqual == true) {
		cout << "같습니다" << endl;
	}
	
	tomorrow = today.Tomorrow();
	cout << tomorrow.GetYear() << "-" << tomorrow.GetMonth() << "-" << tomorrow.GetDay() << endl;
	
	nextDate = today.NextDate(static_cast<Short>(2));
	cout << nextDate.GetYear() << "-" << nextDate.GetMonth() << "-" << nextDate.GetDay() << endl;
	
	isLesserThan = tomorrow.IsLesserThan(nextDate);
	if (isLesserThan == true) {
		cout << "더 작습니다" << endl;
	}
	
	cout << today.GetYear() << "-" << today.GetMonth() << "-" << today.GetDay() << endl;
	cout << nextDate.GetYear() << "-" << nextDate.GetMonth() << "-" << nextDate.GetDay() << endl;
	isNotEqual = today.IsNotEqual(nextDate);
	if (isNotEqual == true) {
		cout << "다릅니다" << endl;
	}

	//형변환함수
	cout << static_cast<char*>(today) << endl;

	//매개변수(문자열)를 갖는 생성자
	Date birthday("20190818");
	cout << birthday.GetYear() << "-" << birthday.GetMonth() << "-" << birthday.GetDay() << endl;

	//복사 생성자
	Date another(birthday);
	cout << another.GetYear() << "-" << another.GetMonth() << "-" << another.GetDay() << endl;

	Date prefix;
	Date postfix;
	//전위 증가 연산자 함수
	prefix = ++birthday + static_cast<Short>(3);
	//후위 증가 연산자 함수
	postfix = another++ + static_cast<Short>(3);
	cout << birthday.GetYear() << "-" << birthday.GetMonth() << "-" << birthday.GetDay() << endl;
	cout << prefix.GetYear() << "-" << prefix.GetMonth() << "-" << prefix.GetDay() << endl;
	cout << another.GetYear() << "-" << another.GetMonth() << "-" << another.GetDay() << endl;
	cout << postfix.GetYear() << "-" << postfix.GetMonth() << "-" << postfix.GetDay() << endl;

	//!= 연산자 함수
	if (prefix != postfix) {
		cout << "같지 않다" << endl;
	}

	//>연산자 함수
	if (prefix > postfix) {
		cout << "크다" << endl;
	}

	//치환 연산자
	another = birthday;
	if (birthday == another) {
		cout << "같다" << endl;
	}

	//전위 감소 연산자
	prefix = --birthday - static_cast<Short>(3);
	//후위 감소 연산자
	postfix = another-- - static_cast<Short>(3);
	cout << birthday.GetYear() << "-" << birthday.GetMonth() << "-" << birthday.GetDay() << endl;
	cout << prefix.GetYear() << "-" << prefix.GetMonth() << "-" << prefix.GetDay() << endl;
	cout << another.GetYear() << "-" << another.GetMonth() << "-" << another.GetDay() << endl;
	cout << postfix.GetYear() << "-" << postfix.GetMonth() << "-" << postfix.GetDay() << endl;

	//<연산자함수
	if (prefix < postfix) {
		cout << "작다" << endl;
	}

	//매개변수를 갖는 생성자
	Date christmas(2019, DEC, 25);
	cout << christmas.GetYear() << "-" << christmas.GetMonth() << "-" << christmas.GetDay() << endl;

	//-연산자
	another = christmas - static_cast<Short>(1);
	cout << another.GetYear() << "-" << another.GetMonth() << "-" << another.GetDay() << endl;

	//>=연산자 함수
	if (christmas >= another) {
		cout << "크거나 같다" << endl;
	}

	//+연산자 함수
	another = christmas + static_cast<Short>(7);
	cout << another.GetYear() << "-" << another.GetMonth() << "-" << another.GetDay() << endl;

	//<=연산자 함수
	if (christmas <= another) {
		cout << "작거나 같다" << endl;
	}

	return 0;
}