#ifndef _AXIS_H
#define _AXIS_H

#include "Array.h"
typedef signed long int Long;

class Axis {
public:
	Axis();
	Axis(const Axis& source);
	~Axis();
	void ConvertToHist(Array<double>& weights, Array<double> *axisX, Array<Long> *axisY);
	Axis& operator =(const Axis& source);
};

int CompareFloat(void *one, void *other);

#endif //_AXIS_H