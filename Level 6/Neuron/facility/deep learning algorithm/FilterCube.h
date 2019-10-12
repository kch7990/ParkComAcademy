#ifndef _FILTERCUBE_H
#define _FILTERCUBE_H

#include "CompositeNeuron.h"

class FilterCube : public CompositeNeuron {
public:
	FilterCube(Long capacity = 32, double bias = 0.0, double biasMomentum = 0.0, double biasVelocity = 0.0);
	FilterCube(const FilterCube& source);
	virtual ~FilterCube();

	Array<double> Flow(Array<double>& inputs, Long inputsSize, Long stride, Long pad);
	Array<double> BackFlow(Array<double>& inputs, Array<double>& signals, Long stride, Long pad);
	Array<double> BatchBackFlow(Array<double>& inputs, Array<double>& signals, Long stride, Long pad); //입력 기울기
	void BatchBackFlow(Array<Array<double>>& inputs, Array<Array<double>>& signals, Long stride, Long pad); //가중치, 편향 기울기
	virtual void Update(double learningRate);
	virtual void Update(double updatedLearningRate, double beta1, double beta2);

	virtual Neuron* Clone();
	FilterCube& operator =(const FilterCube& source);

	double GetBias() const;
	double GetBiasGradient() const;
	double GetBiasMomentum() const;
	double GetBiasVelocity() const;

private:
	double bias;
	double biasGradient;
	double biasMomentum;
	double biasVelocity;
};

inline double FilterCube::GetBias() const {
	return this->bias;
}

inline double FilterCube::GetBiasGradient() const {
	return this->biasGradient;
}

inline double FilterCube::GetBiasMomentum() const {
	return this->biasMomentum;
}

inline double FilterCube::GetBiasVelocity() const {
	return this->biasVelocity;
}

#endif //_FILTERCUBE_H