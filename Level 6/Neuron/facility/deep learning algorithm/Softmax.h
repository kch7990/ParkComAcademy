#ifndef _SOFTMAX_H
#define _SOFTMAX_H

#include "Layer.h"

class Softmax : public Layer {
public:
	Softmax(Long capacity = 32);
	Softmax(const Softmax& source);
	virtual ~Softmax();

	virtual Array<double> Forward(Array<double>& signals);
	virtual Array<Array<double>> BatchForward(Array<Array<double>>& signals);
	virtual Array<double> Backward(Array<double>& signals);
	virtual Array<Array<double>> BatchBackward(Array<Array<double>>& signals);
	virtual void MakeNodes(Long inutCount, Long outputCount);
	virtual Long Save(fstream *fs);
	virtual Long Load(fstream *fs);

	virtual string GetType();
	virtual Neuron* Clone();

	Softmax& operator =(const Softmax& source);
};

int Compare(void *one, void *other);

#endif // !_SOFTAMX_H
