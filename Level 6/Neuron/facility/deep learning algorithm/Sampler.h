#ifndef _SAMPLER_H
#define _SAMPLER_H

#include "Array.h"

class Sampler{
public:
	Sampler();
	Sampler(const Sampler& source);
	~Sampler();
	Array<double> Forward(Array<double> &image, Array<double> &sampleRows, Array<double> &sampleColumns);
	Array<Array<double>> BatchForward(Array<Array<double>> &batchImage, Array<Array<double>> &batchSampleRows, Array<Array<double>> &batchSampleColumns);
	void Backward(Array<double> &image, Array<double> &backSignals, Array<double> *rowGradients, Array<double> *columnGradients, Array<double> *imageGradients);
	void BatchBackward(Array<Array<double>> &batchImage, Array<Array<double>> &batchBackSignals, Array<Array<double>> *batchRowGradients, 
		Array<Array<double>> *batchColumnGradients, Array<Array<double>> *batchImageGradients);
	Sampler& operator=(const Sampler& source);

private: 
	Array<double> rows;
	Array<double> columns;
	Array<Array<double>> batchRows;
	Array<Array<double>> batchColumns;
};

#endif
