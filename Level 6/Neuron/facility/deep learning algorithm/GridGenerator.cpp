#include "GridGenerator.h"
#include <cmath>

GridGenerator::GridGenerator() {
}

GridGenerator::GridGenerator(const GridGenerator& source) {
}

GridGenerator::~GridGenerator() {
}

void GridGenerator::Forward(Array<double>& theta, Array<double> *sampleRows, Array<double> *sampleColumns) {
	Long inputSize = sqrt(sampleRows->GetCapacity());
	Long k = 0;
	Long i = 0;
	while (i < inputSize) {
		Long j = 0;
		while (j < inputSize) {
			sampleColumns->Store(k, theta[0] * j + theta[1] * i + theta[2] * 1);
			sampleRows->Store(k, theta[3] * j + theta[4] * i + theta[5] * 1);
			k++;
			j++;
		}
		i++;
	}
}

Array<double> GridGenerator::Backward(Array<double>& sampleRowGradients, Array<double>& sampleColumnGradients) {
	Long inputSize = sqrt(sampleRowGradients.GetCapacity());
	Array<double> thetaGradients(6);
	Long i = 0;
	while (i < thetaGradients.GetCapacity()) {
		thetaGradients.Store(i, 0.0);
		i++;
	}

	Long k = 0;
	i = 0;
	while (i < inputSize) {
		Long j = 0;
		while (j < inputSize) {
			thetaGradients.Modify(0, thetaGradients[0] + sampleColumnGradients[k] * j);
			thetaGradients.Modify(1, thetaGradients[1] + sampleColumnGradients[k] * i);
			thetaGradients.Modify(2, thetaGradients[2] + sampleColumnGradients[k] * 1);
			thetaGradients.Modify(3, thetaGradients[3] + sampleRowGradients[k] * j);
			thetaGradients.Modify(4, thetaGradients[4] + sampleRowGradients[k] * i);
			thetaGradients.Modify(5, thetaGradients[5] + sampleRowGradients[k] * 1);
			k++;
			j++;
		}
		i++;
	}
	return thetaGradients;
}

GridGenerator& GridGenerator::operator=(const GridGenerator& source) {
	return *this;
}