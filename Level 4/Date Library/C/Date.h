//C
#ifndef _DATE_H
#define _DATE_H

typedef signed long int Long;
typedef enum _boolean { FALSE = 0, TRUE=1 }Boolean;
typedef enum _month {JAN =1, FEB =2, MAR=3, APR=4, MAY=5, JUN=6, JUL=7,
					AUG=8, SEP=9, OCT=10, NOV=11, DEC=12}Month;
typedef enum _weekDay{SUN=0, MON=1, TUE=2, WEN=3, THU=4, FRI=5, SAT=6}WeekDay;
typedef struct _date Date; // 전방선언
typedef struct _date {
	Long year;
	Month month;
	Long day;
	WeekDay weekDay;
	Date(*Today)(Date*);
	Date(*Yesterday)(Date*);
	Date(*Tomorrow)(Date*);
	Date(*PreviousDate)(Date*, Long);
	Date(*NextDate)(Date*, Long);
	Boolean(*IsEqual)(Date*, Date*);
	Boolean(*IsNotEqual)(Date*, Date*);
	Boolean(*IsLesserThan)(Date*, Date*);
	Boolean(*IsGreaterThan)(Date*, Date*);
}Date;

void Create(Date *date);
Date Today(Date *date);
Date Yesterday(Date *date);
Date Tomorrow(Date *date);
Date PreviousDate(Date *date, Long days);
Date NextDate(Date *date, Long days);
Boolean IsEqual(Date *date, Date *other);
Boolean IsNotEqul(Date *date, Date *other);
Boolean IsLesserThan(Date *date, Date *other);
Boolean IsGraterThan(Date *date, Date *other);
void Destroy(Date *date);








#endif //_DATE_H