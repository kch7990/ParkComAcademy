#ifndef _RELU_H
#define _RELU_H

#include "Layer.h"

class ReLU : public Layer {
public:
	ReLU(Long capacity = 32);
	ReLU(const ReLU& source);
	virtual ~ReLU();

	virtual Array<double> Forward(Array<double>& signals);
	virtual Array<Array<double>> BatchForward(Array<Array<double>>& signals);
	virtual Array<double> Backward(Array<double>& signals);
	virtual Array<Array<double>> BatchBackward(Array<Array<double>>& signals);
	virtual void MakeNodes(Long iQnputCount, Long outputCount);
	virtual Long Save(fstream *fs);
	virtual Long Load(fstream *fs);

	virtual string GetType();

	virtual Neuron* Clone();

	ReLU& operator =(const ReLU& source);
};

#endif //_RELU_H