#ifndef _SPATIALTRANSFORMER_H
#define _SPATIALTRANSFORMER_H

#include "CompositeNeuron.h"
#include "Array.h"
#include "GridGenerator.h"
#include "Sampler.h"

class Neuron;
class SpatialTransformer : public CompositeNeuron {
public:
	SpatialTransformer(Long capacity = 32);
	SpatialTransformer(Long capacity, GridGenerator gridGenerator, Sampler sampler);
	SpatialTransformer(const SpatialTransformer& source);
	virtual ~SpatialTransformer();
	SpatialTransformer& operator=(const SpatialTransformer& source);
	virtual Neuron* Clone();

	Array<double> Forward(Array<double>& signals, bool isTraining);
	Array <Array<double>> BatchForward(Array<Array<double>>& signals, bool isTraining);

	Array<double> Backward(Array<double>& signals);
	Array <Array<double>> BatchBackward(Array<Array<double>>& signals);
	void Update(double learningRate);
	void Update(double updatedLearningRate, double beta1, double beta2);

	virtual Long Save(fstream *fs);
	virtual Long Load(fstream *fs);
	virtual string GetType();

	double GetInput(Long index) const;
	double GetInputLength() const;
	double GetResult(Long index) const;
	double GetResultLength() const;

private:
	Array<double> inputs;
	Array<Array<double>> batchInputs;
	Array<double> results; 
	GridGenerator gridGenerator;
	Sampler sampler;
	
};

inline double SpatialTransformer::GetInput(Long index) const {
	return const_cast<Array<double>&>(this->inputs).GetAt(index);
}

inline double SpatialTransformer::GetInputLength() const {
	return const_cast<Array<double>&>(this->inputs).GetLength();
}

inline double SpatialTransformer::GetResult(Long index) const {
	return const_cast<Array<double>&>(this->results).GetAt(index);
}

inline double SpatialTransformer::GetResultLength() const {
	return const_cast<Array<double>&>(this->results).GetLength();
}

#endif // !_SPATIALTRANSFORMER_H
