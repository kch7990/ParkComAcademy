#ifndef _LAYER_H
#define _LAYER_H

#include "CompositeNeuron.h"
#include <string>

using namespace std;

class Layer : public CompositeNeuron {
public:
	Layer(Long capacity = 32);
	Layer(const Layer& source);
	virtual ~Layer() = 0;

	virtual Array<double> Forward(Array<double>& signals);
	virtual Array<double> Forward(Array<double>& signals, bool isTraining); //dropout
	virtual Array<double> Backward(Array<double>& signals) = 0;
	virtual void MakeNodes(Long inputCount, Long outputCount);
	virtual void MakeNodes(Long inputCount, Long outputCount, double deviation); //affine
	virtual void MakeFilters(Long channel, Long filterCount);
	virtual void MakeFilters(Long channel, Long filterCount, double deviation);

	virtual Array<Array<double>> BatchForward(Array<Array<double>>& signals);
	virtual Array<Array<double>> BatchForward(Array<Array<double>>& signals, bool isTraining);
	virtual Array<Array<double>> BatchBackward(Array<Array<double>>& signals);


	//virtual string GetType() = 0; //CompositeNeuron으로 올림
	virtual Array<double> GetWeights();
	virtual Array<double> GetWeightGradients();
	virtual Array<double> GetResults();

	double GetInputGradient(Long index) const;
	double GetInput(Long index) const;
	Long GetInputCount() const;

	Layer& operator =(const Layer& source);
protected:
	Array<double> inputGradients;
	Array<double> inputs;
	Long inputCount;
	Array<Array<double>> batchInputs;
};

inline double Layer::GetInputGradient(Long index) const {
	return const_cast<Array<double>&>(this->inputGradients)[index];
}
inline double Layer::GetInput(Long index) const {
	return const_cast<Array<double>&>(this->inputs)[index];
}
inline Long Layer::GetInputCount() const {
	return this->inputCount;
}

#endif //_LAYER_H