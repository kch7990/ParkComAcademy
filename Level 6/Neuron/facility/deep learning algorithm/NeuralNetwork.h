#ifndef _NEURALNETWORK_H
#define _NEURALNETWORK_H

#include "CompositeNeuron.h"
#include "Array.h"
#include <fstream>

typedef signed long int Long;

using namespace std;

class NeuralNetwork :public CompositeNeuron {
public:
	NeuralNetwork(Long capacity = 32, Long learningCount = 0);
	NeuralNetwork(const NeuralNetwork& source);
	virtual	~NeuralNetwork();
	virtual Array<double> Recognize(Array<double>& signals, bool isTraining);
	virtual Array<Array<double>> BatchRecognize(Array<Array<double>>& signals, bool isTraining);
	virtual void Learn(Array<double>& targets, double learningRate);
	virtual void Learn(Array<double>& targets, double learningRate, double beta1, double beta2);
	virtual void BatchLearn(Array<Array<double>>& targets, double learningRate);
	virtual void BatchLearn(Array<Array<double>>& targets, double learningRate, double beta1, double beta2);
	virtual double GetCrossEntropy(Array<double>& results, Array<double>& targets);
	virtual double GetBatchCrossEntropy(Array<Array<double>>& results, Array<Array<double>>& targets);
	virtual void ReSynchronization();
	virtual Long GetOutputCount();
	virtual Long GetChannelCount();
	virtual Long Save(fstream *fs);
	virtual Long Load(fstream *fs);

	virtual Neuron* Clone();
	
	Long GetLearningCount() const;
	NeuralNetwork& operator=(const NeuralNetwork& source);
private:
	Long learningCount;

};

inline Long NeuralNetwork::GetLearningCount() const {
	return this->learningCount;
}


#endif // !_NEURALNETWORK_H
