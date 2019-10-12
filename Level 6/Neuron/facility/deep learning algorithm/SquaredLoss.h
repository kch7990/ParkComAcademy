#ifndef _SQUAREDLOSS_H
#define _SQUAREDLOSS_H

#include "Array.h"

class SquaredLoss {
public:
	SquaredLoss();
	SquaredLoss(const SquaredLoss& source);
	~SquaredLoss();
	double Forward(Array<double> results, Array<double> targets);
	double BatchForward(Array<Array<double>> &results, Array<Array<double>> &targets);

	Array<double> Backward(Array<double> results, Array<double> targets);
	Array<Array<double>> BatchBackward(Array<Array<double>> &results, Array<Array<double>> &targets);

	SquaredLoss& operator=(const SquaredLoss& source);
};




#endif