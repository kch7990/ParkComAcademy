#include "NeuralNetwork.h"
#include "Convolution.h"
#include "Affine.h"
#include "ReLU.h"
#include "Softmax.h"
#include "Dropout.h"
#include "Layer.h"
#include "Pooling.h"
#include "NeuronFactory.h"
#include "SpatialTransformer.h"

#include <string>
#include <cmath>
#include <ctime>
#include <iostream>

using namespace std;

#if !defined(_AFXDLL)

#include <crtdbg.h>
#if defined(DEBUG) |defined(_DEBUG)
#if !defined(DEBUG_NEW)
#define DEBUG_NEW new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif
#endif
#endif

NeuralNetwork::NeuralNetwork(Long capacity, Long learningCount)
	: CompositeNeuron(capacity) {
	this->learningCount = learningCount;
}

NeuralNetwork::NeuralNetwork(const NeuralNetwork& source)
	: CompositeNeuron(source) {

}

NeuralNetwork::~NeuralNetwork() {

}

Array<double> NeuralNetwork::Recognize(Array<double>& signals, bool isTraining) {
	Array<double> outputs(signals);

	// 1. 입력받는다.

	Long i = 0;
	while (i < this->length) {// 2. 계층 개수만큼 반복한다.
		if (dynamic_cast<SpatialTransformer*>(this->neurons[i])) {
			outputs = dynamic_cast<SpatialTransformer*>(this->neurons[i])->Forward(outputs, isTraining);
		}
		else if (dynamic_cast<Dropout*>(this->neurons[i])) {
			outputs = dynamic_cast<Layer*>(this->neurons[i])->Forward(outputs, isTraining); //계층마다 순전파 시행
		}
		else {
			outputs = dynamic_cast<Layer*>(this->neurons[i])->Forward(outputs);
		}
		i++;
	}

	return outputs;// 3. 출력하다.
}

Array<Array<double>> NeuralNetwork::BatchRecognize(Array<Array<double>>& signals, bool isTraining) {
	Array<Array<double>> outputs(signals);
	// 1. 입력받는다.

	Long i = 0;
	while (i < this->length) {// 2. 계층 개수만큼 반복한다.
		if (dynamic_cast<SpatialTransformer*>(this->neurons[i])) {
			outputs = dynamic_cast<SpatialTransformer*>(this->neurons[i])->BatchForward(outputs, isTraining);
		}
		else if (dynamic_cast<Dropout*>(this->neurons[i])) {
			outputs = dynamic_cast<Layer*>(this->neurons[i])->BatchForward(outputs, isTraining); //계층마다 순전파 시행
		}
		else {
			outputs = dynamic_cast<Layer*>(this->neurons[i])->BatchForward(outputs);
		}
		i++;
	}

	return outputs;// 3. 출력하다.
}

void NeuralNetwork::Learn(Array<double>& targets, double learningRate) {
	Array<double> signals(targets);

	Long i = this->length - 1;
	while (i >= 0) {
		if (dynamic_cast<SpatialTransformer*>(this->neurons[i]))
		{
			signals = dynamic_cast<SpatialTransformer*>(this->neurons[i])->Backward(signals);
		}
		else {
			signals = dynamic_cast<Layer*>(this->neurons[i])->Backward(signals);
		}
		i--;
	}
	i = 0;
	while (i < this->length) {
		dynamic_cast<Layer*>(this->neurons[i])->Update(learningRate);
		i++;
	}
}

void NeuralNetwork::BatchLearn(Array<Array<double>>& targets, double learningRate) {
	Array<Array<double>> signals(targets);
	Long i = this->length - 1;
	while (i >= 0) {
		if (dynamic_cast<SpatialTransformer*>(this->neurons[i]))
		{
			signals = dynamic_cast<SpatialTransformer*>(this->neurons[i])->BatchBackward(signals);
		}
		else {
		signals = dynamic_cast<Layer*>(this->neurons[i])->BatchBackward(signals);
		}
		i--;
	}
	i = 0;
	while (i < this->length) {
		if (dynamic_cast<SpatialTransformer*>(this->neurons[i]))
		{
			dynamic_cast<SpatialTransformer*>(this->neurons[i])->Update(learningRate);
		}
		else {
			dynamic_cast<Layer*>(this->neurons[i])->Update(learningRate);
		}
		i++;
	}
}

void NeuralNetwork::Learn(Array<double>& targets, double learningRate, double beta1, double beta2) {
	Array<double> signals(targets);

	Long i = this->length - 1;
	while (i >= 0) {
		if (dynamic_cast<SpatialTransformer*>(this->neurons[i]))
		{
			signals = dynamic_cast<SpatialTransformer*>(this->neurons[i])->Backward(signals);
		}
		else {
			signals = dynamic_cast<Layer*>(this->neurons[i])->Backward(signals);
		}
		i--;
	}

	this->learningCount++;
	double updatedLearningRate = learningRate * sqrt(1.0 - pow(beta2, this->learningCount)) / (1.0 - pow(beta1, this->learningCount));
	i = 0;
	while (i < this->length) {
		if (dynamic_cast<SpatialTransformer*>(this->neurons[i])) {
			dynamic_cast<SpatialTransformer*>(this->neurons[i])->Update(updatedLearningRate, beta1, beta2);
		}
		else {
			dynamic_cast<Layer*>(this->neurons[i])->Update(updatedLearningRate, beta1, beta2);
		}
		i++;
	}
}

void NeuralNetwork::BatchLearn(Array<Array<double>>& targets, double learningRate, double beta1, double beta2) {
	Array<Array<double>> signals(targets);
	Long i = this->length - 1;
	while (i >= 0) {
		if (dynamic_cast<SpatialTransformer*>(this->neurons[i]))
		{
			signals = dynamic_cast<SpatialTransformer*>(this->neurons[i])->BatchBackward(signals);
		}
		else {
			signals = dynamic_cast<Layer*>(this->neurons[i])->BatchBackward(signals);
		}
		i--;
	}
	this->learningCount++;
	double updatedLearningRate = learningRate * sqrt(1.0 - pow(beta2, this->learningCount)) / (1.0 - pow(beta1, this->learningCount));
	i = 0;
	while (i < this->length) {
		if (dynamic_cast<SpatialTransformer*>(this->neurons[i]))
		{
			dynamic_cast<SpatialTransformer*>(this->neurons[i])->Update(updatedLearningRate, beta1, beta2);
		}
		else {
			dynamic_cast<Layer*>(this->neurons[i])->Update(updatedLearningRate, beta1, beta2);
		}
		i++;
	}
}

double NeuralNetwork::GetCrossEntropy(Array<double>& results, Array<double>& targets) {
	double sum = 0.0;
	const double DELTA = static_cast<double>(1e-7);

	Long i = 0;
	while (i < results.GetLength()) {
		sum += targets[i] * log(results[i] + DELTA);
		i++;
	}

	return -sum;
}

double NeuralNetwork::GetBatchCrossEntropy(Array<Array<double>>& results, Array<Array<double>>& targets) {
	Long batch = results.GetLength();
	Long i = 0;
	double loss = 0.0;
	double sum;
	while (i < batch) {
		Array<double> resultsPerBatch = results.GetAt(i);
		Array<double> targetsPerBatch = targets.GetAt(i);
		const double DELTA = static_cast<double>(1e-7);
		sum = 0.0;
		Long j = 0;
		while (j < resultsPerBatch.GetLength()) {
			sum += targetsPerBatch[j] * log(resultsPerBatch[j] + DELTA);
			j++;
		}
		loss += -sum;
		i++;
	}
	double average = loss / batch;

	return average;
}

void NeuralNetwork::ReSynchronization() {
	Long inputSize;
	Long outputCount = 28 * 28;
	Long channelCount = 1;
	Long count;
	double deviation;
	Neuron *layer;
	Long i = 0;

	while (i < this->length) {
		layer = this->neurons[i];
		if (dynamic_cast<Affine*>(layer)) {
			deviation = dynamic_cast<Affine*>(layer)->GetDeviation();
			count = layer->GetLength();
			dynamic_cast<Layer*>(layer)->MakeNodes(outputCount, count, deviation);
			Long channelCount = 1;
			outputCount = count;
		}
		else if (dynamic_cast<ReLU*>(layer) ||
			dynamic_cast<Softmax*>(layer) || dynamic_cast<Dropout*>(layer)) {
			dynamic_cast<Layer*>(layer)->MakeNodes(outputCount, outputCount);
		}
		else if (dynamic_cast<Convolution*>(layer)) {
			deviation = dynamic_cast<Convolution*>(layer)->GetDeviation();
			dynamic_cast<Layer*>(layer)->MakeFilters(channelCount, layer->GetLength(), deviation);
			inputSize = sqrt(outputCount / dynamic_cast<Convolution*>(layer)->GetChannelCount());
			outputCount = pow((inputSize - dynamic_cast<Convolution*>(layer)->GetFilterSize() +
				2 * dynamic_cast<Convolution*>(layer)->GetPad()) / dynamic_cast<Convolution*>(layer)->GetStride() + 1, 2)*
				layer->GetLength();
			channelCount = layer->GetLength();
		}
		else if (dynamic_cast<Pooling*>(layer)) {
			dynamic_cast<Layer*>(layer)->MakeFilters(channelCount, channelCount);
			inputSize = sqrt(outputCount / layer->GetLength());
			outputCount = pow((inputSize - dynamic_cast<Pooling*>(layer)->GetSize()) / dynamic_cast<Pooling*>(layer)->GetStride() + 1, 2) *
				layer->GetLength();
		}
		i++;
	}

}

Long NeuralNetwork::GetOutputCount() {
	Long inputSize = 28; //
	Long outputCount = inputSize * inputSize; //
	Neuron *layer;
	Long i = 0;
	while (i < this->length) {
		layer = this->neurons[i];
		if (dynamic_cast<Affine*>(layer) || dynamic_cast<ReLU*>(layer)
			|| dynamic_cast<Softmax*>(layer) || dynamic_cast<Dropout*>(layer)) {
			outputCount = layer->GetLength();
		}
		else if (dynamic_cast<Convolution*>(layer)) {
			inputSize = sqrt(outputCount / dynamic_cast<Convolution*>(layer)->GetChannelCount());
			outputCount = pow((inputSize - dynamic_cast<Convolution*>(layer)->GetFilterSize() +
				2 * dynamic_cast<Convolution*>(layer)->GetPad()) / dynamic_cast<Convolution*>(layer)->GetStride() + 1, 2)*
				layer->GetLength();
		}
		else if (dynamic_cast<Pooling*>(layer)) {
			inputSize = sqrt(outputCount / layer->GetLength());
			outputCount = pow((inputSize - dynamic_cast<Pooling*>(layer)->GetSize()) / dynamic_cast<Pooling*>(layer)->GetStride() + 1, 2) *
				layer->GetLength();
		}
		i++;
	}


	return outputCount;
}

Long NeuralNetwork::GetChannelCount() {
	Long channelCount = 1;
	Long i = this->length - 1; //마지막에서 두번째를 i의 초깃값으로 한다.
	while (i >= 0 && !(dynamic_cast<Convolution*>(this->neurons[i])) && !(dynamic_cast<Affine*>(this->neurons[i]))) { //마지막 계층부터 Convolution이 아닌지 확인한다.
		i--;
	}
	if (i >= 0 && !(dynamic_cast<Affine*>(this->neurons[i]))) {
		channelCount = dynamic_cast<Convolution*>(this->neurons[i])->GetLength();
	}

	return channelCount;
}

Long NeuralNetwork::Save(fstream *file) {
	*file << this->learningCount << endl;
	*file << this->length << endl;
	Long i = 0;
	while (i < this->length) {
		string type = dynamic_cast<CompositeNeuron*>(this->neurons[i])->GetType();
		*file << type << endl;
		this->neurons[i]->Save(file);
		i++;
	}
	return this->length;
}

Long NeuralNetwork::Load(fstream *fs) {
	NeuronFactory neuronFactory;
	string receive;
	Long layerCount;
	*fs >> this->learningCount;
	*fs >> layerCount;

	Long i = 0;
	while (i < layerCount && !(fs->eof())) {
		string type;
		*fs >> type;
		NeuronType neuronType;
		if (type == "Conv") {
			neuronType = NEURON_CONVOLUTION;
		}
		else if (type == "Affine") {
			neuronType = NEURON_AFFINE;
		}
		else if (type == "Pooling") {
			neuronType = NEURON_POOLING;
		}
		else if (type == "ReLU") {
			neuronType = NEURON_RELU;
		}
		else if (type == "Sigmoid") {
			neuronType = NEURON_SIGMOID;
		}
		else if (type == "SoftMax") {
			neuronType = NEURON_SOFTMAX;
		}
		else if (type == "Dropout") { //dropout
			neuronType = NEURON_DROPOUT;
		}
		else if (type == "STN") {
			neuronType = NEURON_SPATIALTRANSFORMER;
		}
		Neuron *layer = neuronFactory.Make(neuronType);
		layer->Load(fs);
		CompositeNeuron::Add(layer);
		i++;
	}

	return this->length;
}

Neuron* NeuralNetwork::Clone() {
	return new NeuralNetwork(*this);
}

NeuralNetwork& NeuralNetwork::operator=(const NeuralNetwork& source) {
	CompositeNeuron::operator=(source);
	return *this;
}

