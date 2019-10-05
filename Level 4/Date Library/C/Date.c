#include"date.h"
#include<time.h>

void Create(Date *date) {
	date->year = 1900;
	date->month = JAN;
	date->day = 1;
	date->weekDay = MON;
	date->Today = Today;
	date->Yesterday = Yesterday;
	date->Tomorrow = Tomorrow;
	date->PreviousDate = PreviousDate;
	date->NextDate = NextDate;
	date->IsEqual = IsEqual;
	date->IsNotEqual = IsNotEqul;
	date->IsLesserThan = IsLesserThan;
	date->IsGreaterThan = IsGraterThan;
}
Date Today(Date *date) {
	time_t timer;
	struct tm *today;
	Date today_;

	Create(&today_);

	time(&timer);
	today = localtime(&timer);

	today_.year = today->tm_year + 1900;
	today_.month = (Month)(today->tm_mon + 1);
	today_.day = today->tm_mday;
	today_.weekDay = (WeekDay)(today->tm_wday);

	Destroy(&today_);
	return today_;
}
Date Yesterday(Date *date) {
	struct tm yesterday = { 0, };
	Date yesterday_;

	Create(&yesterday_);
	yesterday.tm_year = date->year - 1900;
	yesterday.tm_mon = date->month - 1;
	yesterday.tm_mday = date->day - 1;

	mktime(&yesterday);

	yesterday_.year = yesterday.tm_year + 1900;
	yesterday_.month = (Month)(yesterday.tm_mon + 1);
	yesterday_.day = yesterday.tm_mday;
	yesterday_.weekDay = (WeekDay)(yesterday.tm_wday);

	Destroy(&yesterday_);
	return yesterday_;
}
Date Tomorrow(Date *date) {
	struct tm tomorrow = { 0, };
	Date tomorrow_;

	Create(&tomorrow_);
	tomorrow.tm_year = date->year - 1900;
	tomorrow.tm_mon = date->month - 1;
	tomorrow.tm_mday = date->day + 1;

	mktime(&tomorrow);

	tomorrow_.year = tomorrow.tm_year + 1900;
	tomorrow_.month = (Month)(tomorrow.tm_mon + 1);
	tomorrow_.day = tomorrow.tm_mday;
	tomorrow_.weekDay = (WeekDay)(tomorrow.tm_wday);

	Destroy(&tomorrow_);
	return tomorrow_;
}
Date PreviousDate(Date *date, Long days) {
	struct tm previousDate = { 0, };
	Date previousDate_;

	Create(&previousDate_);
	previousDate.tm_year = date->year - 1900;
	previousDate.tm_mon = date->month - 1;
	previousDate.tm_mday = date->day - days;

	mktime(&previousDate);

	previousDate_.year = previousDate.tm_year + 1900;
	previousDate_.month = (Month)(previousDate.tm_mon + 1);
	previousDate_.day = previousDate.tm_mday;
	previousDate_.weekDay = (WeekDay)(previousDate.tm_wday);

	Destroy(&previousDate_);
	return previousDate_;
}
Date NextDate(Date *date, Long days) {
	struct tm nextDate = { 0, };
	Date nextDate_;

	Create(&nextDate_);
	nextDate.tm_year = date->year - 1900;
	nextDate.tm_mon = date->month - 1;
	nextDate.tm_mday = date->day + days;

	mktime(&nextDate);

	nextDate_.year = nextDate.tm_year + 1900;
	nextDate_.month = (Month)(nextDate.tm_mon + 1);
	nextDate_.day = nextDate.tm_mday;
	nextDate_.weekDay = (WeekDay)(nextDate.tm_wday);

	Destroy(&nextDate_);
	return nextDate_;
}
Boolean IsEqual(Date *date, Date *other) {
	Boolean ret = FALSE;
	if (date->year == other->year &&
		date->month == other->month &&
		date->day == other->day) {
		ret = TRUE;
	}
	return ret;
}
Boolean IsNotEqul(Date *date, Date *other) {
	Boolean ret = FALSE;
	if (date->year != other->year ||
		date->month != other->month ||
		date->day != other->day) {
		ret = TRUE;
	}
	return ret;
}
Boolean IsLesserThan(Date *date, Date *other) {
	Boolean ret = FALSE;
	if (date->year < other->year) {
		ret = TRUE;
	}
	else if (date->year == other->year &&
		date->month < other->month) {
		ret = TRUE;
	}
	else if (date->year == other->year &&
		date->month == other->month &&
		date->day < other->day) {
		ret = TRUE;
	}

	return ret;
}
Boolean IsGraterThan(Date *date, Date *other) {
	Boolean ret = FALSE;
	if (date->year > other->year) {
		ret = TRUE;
	}
	else if (date->year == other->year &&
		date->month > other->month) {
		ret = TRUE;
	}
	else if (date->year == other->year &&
		date->month == other->month &&
		date->day > other->day) {
		ret = TRUE;
	}

	return ret;
}
void Destroy(Date *date) {

}

#include <stdio.h>

int main(int argc, char *argv[]) {
	Date date;
	Date today;
	Date yesterday;
	Date tomorrow;
	Date previousDate;
	Date nextDate;
	Boolean ret;

	Create(&date);
	Create(&today);
	Create(&yesterday);
	Create(&tomorrow);
	Create(&previousDate);
	Create(&nextDate);

	today = date.Today(&date);
	printf("%4d-%02d-%02d\n", today.year, today.month, today.day);
	previousDate = today.PreviousDate(&today, 3);
	printf("%4d-%02d-%02d\n", previousDate.year, previousDate.month, previousDate.day);
	ret = today.IsGreaterThan(&today, &previousDate);
	if (ret == TRUE) {
		printf("더 큰 날짜 입니다.\n");
	}
	yesterday = today.Yesterday(&today);
	printf("%4d-%02d-%02d\n", yesterday.year, yesterday.month, yesterday.day);
	previousDate = today.PreviousDate(&today, 1);
	printf("%4d-%02d-%02d\n", previousDate.year, previousDate.month, previousDate.day);
	ret = yesterday.IsEqual(&yesterday, &previousDate);
	if (ret == TRUE) {
		printf("같은 날짜입니다.\n");
	}
	tomorrow = today.Tomorrow(&today);
	printf("%4d-%02d-%02d\n", tomorrow.year, tomorrow.month, tomorrow.day);
	nextDate = today.NextDate(&today, 2);
	printf("%4d-%02d-%02d\n", nextDate.year, nextDate.month, nextDate.day);
	ret = tomorrow.IsLesserThan(&tomorrow, &nextDate);
	if (ret == TRUE) {
		printf("더 작은 날짜입니다.\n");
	}
	ret = today.IsNotEqual(&today, &nextDate);
	if (ret == TRUE) {
		printf("다른 날짜 입니다.\n");
	}

	Destroy(&date);
	Destroy(&today);
	Destroy(&yesterday);
	Destroy(&tomorrow);
	Destroy(&previousDate);
	Destroy(&nextDate);

	return 0;
}