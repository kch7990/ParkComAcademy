#ifndef _AFFINE_H
#define _AFFINE_H

#include "Layer.h"
#include <fstream>

class Affine : public Layer {
public:
	Affine(Long capacity = 32, Long inputCount = 784, double deviation = 0.01);
	Affine(const Affine& source);
	virtual ~Affine();

	virtual Array<double> Forward(Array<double>& signals);
	virtual Array<Array<double>> BatchForward(Array<Array<double>>& signals);
	virtual Array<double> Backward(Array<double>& signals);
	virtual Array<Array<double>> BatchBackward(Array<Array<double>>& signals);
	virtual void Update(double learningRate);
	virtual void Update(double updatedLearningRate, double beta1, double beta2);
	virtual void MakeNodes(Long inputCount, Long outputCount, double deviation);
	virtual Long Save(fstream *fs);
	virtual Long Load(fstream *fs);

	virtual Array<double> GetWeights();
	virtual Array<double> GetWeightGradients();
	virtual string GetType();
	virtual Neuron* Clone();

	double GetDeviation() const;

	Affine& operator=(const Affine& source);
private:
	double deviation;
};

inline double Affine::GetDeviation() const {
	return this->deviation;
}

#endif //_AFFINE_H
