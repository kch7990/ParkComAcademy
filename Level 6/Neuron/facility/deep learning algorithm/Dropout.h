#ifndef _DROPOUT_H
#define _DROPOUT_H

#include "Layer.h"

class Dropout : public Layer {
public:
	Dropout(Long capacity = 256, double ratio = 0.2);
	Dropout(const Dropout& source);
	virtual ~Dropout();

	virtual Array<double> Forward(Array<double>& signals, bool isTraining);
	virtual Array<Array<double>> BatchForward(Array<Array<double>>& signals, bool isTraining);
	virtual Array<double> Backward(Array<double>& signals);
	virtual Array<Array<double>> BatchBackward(Array<Array<double>>& signals);
	virtual void MakeNodes(Long inputCount, Long outputCount);
	virtual Long Save(fstream *fs);
	virtual Long Load(fstream *fs);

	virtual string GetType();

	virtual Neuron* Clone();

	double GetRatio() const;

	Dropout& operator =(const Dropout& source);
private:
	double ratio;
};

inline double Dropout::GetRatio() const {
	return this->ratio;
}
#endif //_DROPOUT_H