#ifndef _GRIDGENERATOR_H
#define _GRIDGENERATOR_H

#include "Array.h"

typedef signed long int Long;

class GridGenerator {
public:
	GridGenerator();
	GridGenerator(const GridGenerator& source);
	~GridGenerator();

	void Forward(Array<double>& theta, Array<double> *sampleRows, Array<double> *sampleColumns);
	Array<double> Backward(Array<double>& sampleRowGradients, Array<double>& sampleColumnGradients);

	GridGenerator& operator=(const GridGenerator& source);
};

#endif //_GRIDGENERATOR_H