#ifndef _NEURON_H
#define _NEURON_H

#include "Array.h"
#include <fstream>

typedef signed long int Long;

using namespace std;

class Neuron {
public:
	Neuron();
	Neuron(const Neuron& source);
	virtual ~Neuron() = 0;
	virtual Long Add(Neuron *neuron);
	virtual Long Add(Long index, Neuron *neuron);
	virtual Long Remove(Long index);
	virtual Long Move(Long index);
	virtual void ReSynchronization();
	virtual Neuron* GetAt(Long index);

	virtual Array<double> Recognize(Array<double>& signals, bool isTraining);
	virtual Array<Array<double>> BatchRecognize(Array<Array<double>>& signals, bool isTraining);
	virtual void Learn(Array<double>& targets, double learningRate);
	virtual void Learn(Array<double>& targets, double learningRate, double beta1, double beta2);
	virtual void BatchLearn(Array<Array<double>>& targets, double learningRate);
	virtual void BatchLearn(Array<Array<double>>& targets, double learningRate, double beta1, double beta2);
	virtual double GetCrossEntropy(Array<double>& results, Array<double>& targets);
	virtual double GetBatchCrossEntropy(Array<Array<double>>& results, Array<Array<double>>& targets);
	virtual void Update(double learningRate); //SGD
	virtual void Update(double updatedLearningRate, double beta1, double beta2); //Adam
	virtual Long GetOutputCount();
	virtual Long GetChannelCount();
	virtual Long Save(fstream *fs);
	virtual Long Load(fstream *fs);

	virtual Neuron* Clone() = 0;
	virtual Long GetCapacity() const;
	virtual Long GetLength() const;
	virtual Long GetCurrent() const;
	Neuron& operator =(const Neuron& source);
};




#endif _NEURON_H