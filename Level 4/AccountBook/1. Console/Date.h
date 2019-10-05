#ifndef _DATE_H
#define _DATE_H

typedef signed short int Short;
enum Month { JAN = 1, FEB = 2, MAR = 3, APR = 4, MAY = 5, JUN = 6, JUL = 7, AUG = 8, SEP = 9, OCT = 10, NOV = 11, DEC = 12 };
enum WeekDay { SUN = 0, MON = 1, TUE = 2, WED = 3, THU = 4, FRI = 5, SAT = 6 };
class Date {
public:
	Date(); //디폴트 생성자 Default Constructor
	Date(Short year, Month month, Short day); //매개변수를 갖는 생성자 Constructor with parameters
	Date(const char(*date)); //매개변수를 갖는 생성자 Constructor with parameters
	Date(const Date& source); //복사 생성자 Copy Constructor
	~Date(); //소멸자 Destructor
	static Date Today(); //static 연산
	Date Yesterday();
	Date Tomorrow();
	Date PreviousDate(Short days);
	Date NextDate(Short days);
	bool IsEqual(const Date& other);
	bool IsNotEqual(const Date& other);
	bool IsLesserThan(const Date& other);
	bool IsGreaterThan(const Date& other);
	operator char*(); //형 변환 함수
	Date& operator --(); //전위 감소 연산자 함수
	Date operator --(int); //후위 감소 연산자 함수
	Date& operator ++(); //전위 증가 연산자 함수
	Date operator ++(int); //후위 증가 연산자 함수
	Date operator -(Short days); // 빼기 연산자 함수
	Date operator +(Short days); // 더하기 연산자 함수
	bool operator ==(const Date& other); // == 연산자 함수
	bool operator !=(const Date& other); // != 연산자 함수
	bool operator <(const Date& other); // < 연산자 함수
	bool operator <=(const Date& other); // <= 연산자 함수
	bool operator >(const Date& other); // > 연산자 함수
	bool operator >=(const Date& other); // >= 연산자 함수
	Date& operator =(const Date& source); //치환 연산자 함수

	Short GetYear() const;
	Short GetMonth() const;
	Short GetDay() const;
	Short GetWeekDay() const;
private:
	Short year;
	Month month;
	Short day;
	WeekDay weekDay;
};
inline Short Date::GetYear() const {
	return this->year;
}
inline Short Date::GetMonth() const {
	return this->month;
}
inline Short Date::GetDay() const {
	return this->day;
}
inline Short Date::GetWeekDay() const {
	return this->weekDay;
}

#endif //_DATE_H