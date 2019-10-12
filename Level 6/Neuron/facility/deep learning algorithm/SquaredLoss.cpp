#include "SquaredLoss.h"

SquaredLoss::SquaredLoss() {

}

SquaredLoss::SquaredLoss(const SquaredLoss& source) {

}

SquaredLoss::~SquaredLoss() {

}

double SquaredLoss::Forward(Array<double> results, Array<double> targets) {
	double loss = -1;
	double sum = 0;
	Long i = 0;
	while (i < results.GetLength()) {
		sum += (results[i] - targets[i])*(results[i] - targets[i]);
		i++;
	}
	
	if (sum != 0) {
		loss = sum * 0.5;
	}
	return loss;
}

double SquaredLoss::BatchForward(Array<Array<double>> &results, Array<Array<double>> &targets) {
	double loss = 0;
	double sum;
	double totalValue = 0;

	Long j = 0;
	while (j < results.GetLength()) {
		sum = 0;
		Long i = 0;
		while (i < results[j].GetLength()) {
			sum += (results[j][i] - targets[j][i])*(results[j][i] - targets[j][i]);
			i++;
		}
		totalValue += sum * 0.5;
		j++;
	}
	loss = totalValue / results.GetLength();

	return loss;
}

Array<double> SquaredLoss::Backward(Array<double> results, Array<double> targets) {
	Array<double> backSignals(results.GetLength());
	Long i = 0;
	while (i < results.GetLength()) {
		backSignals.Store(i, results[i] - targets[i]);
		i++;
	}

	return backSignals;
}

Array<Array<double>> SquaredLoss::BatchBackward(Array<Array<double>> &results, Array<Array<double>> &targets) {
	Array<Array<double>> backSignals(results);

	Long j = 0;
	while (j < results.GetLength()) {
		Long i = 0;
		while (i < results[j].GetLength()) {
			backSignals[j][i] = (results[j][i] - targets[j][i]) / results.GetLength();
			i++;
		}
		j++;
	}
	return backSignals;
}

SquaredLoss& SquaredLoss::operator=(const SquaredLoss& source) {
	return *this;
}