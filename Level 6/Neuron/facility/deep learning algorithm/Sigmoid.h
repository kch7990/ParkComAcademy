#ifndef _SIGMOID_H
#define _SIGMOID_H

#include "Layer.h"

class Sigmoid : public Layer {
public:
	Sigmoid(Long capacity = 32);
	Sigmoid(const Sigmoid& source);
	virtual ~Sigmoid();

	virtual Array<double> Forward(Array<double>& signals);
	virtual Array<Array<double>> BatchForward(Array<Array<double>>& signals);
	virtual Array<double> Backward(Array<double>& signals);
	virtual Array<Array<double>> BatchBackward(Array<Array<double>>& signals);
	virtual void MakeNodes(Long inputCount, Long outputCount);
	virtual Long Save(fstream *fs);
	virtual Long Load(fstream *fs);


	virtual string GetType();

	virtual Neuron* Clone();

	Sigmoid& operator =(const Sigmoid& source);
};

#endif //_SIGMOID_H