#include "SpatialTransformer.h"
#include "GridGenerator.h"
#include "Neuron.h"
#include "CompositeNeuron.h"
#include "Layer.h"
#include "Convolution.h"
#include "Affine.h"
#include "ReLU.h"
#include "Softmax.h"
#include "Dropout.h"
#include "Pooling.h"
#include "Sampler.h"
#include "NeuronFactory.h"
#include "Sigmoid.h"

SpatialTransformer::SpatialTransformer(Long capacity)
	:CompositeNeuron(capacity) {
}

SpatialTransformer::SpatialTransformer(Long capacity, GridGenerator gridGenerator, Sampler sampler)
:CompositeNeuron(capacity), gridGenerator(gridGenerator), sampler(sampler){

}

SpatialTransformer::SpatialTransformer(const SpatialTransformer& source)
	: CompositeNeuron(source), inputs(source.inputs), results(source.results), gridGenerator(source.gridGenerator), sampler(source.sampler)
, batchInputs(source.batchInputs){
}

SpatialTransformer::~SpatialTransformer() {
}

SpatialTransformer& SpatialTransformer::operator=(const SpatialTransformer& source) {
	CompositeNeuron::operator=(source);
	this->inputs = source.inputs;
	this->batchInputs = source.batchInputs;
	this->results = source.results;
	this->gridGenerator = source.gridGenerator;
	this->sampler = source.sampler;

	return *this;
}

Neuron* SpatialTransformer::Clone() {
	return new SpatialTransformer(*this);
}

Array<double> SpatialTransformer::Forward(Array<double>& signals, bool isTraining) {
	this->inputs = signals;
	Array<double> outputs(signals);

	Neuron *neuron;
	// Affine, ReLU, Convolution, Dropout
	// Localisation
	Long i = 0;
	while (i < this->length) {
		neuron = this->neurons[i];
		 if (dynamic_cast<Dropout*>(neuron)) {
			outputs = dynamic_cast<Dropout*>(neuron)->Forward(outputs, isTraining);
		}
		else {
			outputs = dynamic_cast<Layer*>(neuron)->Forward(outputs);
		}
		i++;
	}
	
	Array<double> sampleRows(signals.GetLength());
	Array<double> sampleColumns(signals.GetLength());
	
	// GridGenerator
	this->gridGenerator.Forward(outputs, &sampleRows, &sampleColumns); 
	// Sampler
	this->results = this->sampler.Forward(signals, sampleRows, sampleColumns);

	return this->results;
}

Array<Array<double>> SpatialTransformer::BatchForward(Array<Array<double>>& signals, bool isTraining) {
	this->batchInputs = signals;
	Array<Array<double>>outputs(signals);

	Long i = 0;
	while (i < this->length) {
		Neuron *layer = this->neurons[i];
		if (dynamic_cast<Dropout*>(layer)) {
			outputs = dynamic_cast<Dropout*>(layer)->BatchForward(outputs, isTraining);
		}
		else {
			outputs = dynamic_cast<Layer*>(layer)->BatchForward(outputs);
		}
		i++;
	}
	
	Array<Array<double>> batchresults(signals.GetLength());
	Array<Array<double>> batchSampleRows(signals.GetLength());
	Array<Array<double>> batchSampleColumns(signals.GetLength());

	i = 0;
	while (i < signals.GetLength()) {
		Array<double>sampleRows(signals[0].GetLength());
		Array<double>sampleColumns(signals[0].GetLength());
		this->gridGenerator.Forward(outputs[i], &sampleRows, &sampleColumns);
		batchSampleRows.Store(i, sampleRows);
		batchSampleColumns.Store(i, sampleColumns);
		i++;
	}

	batchresults = this->sampler.BatchForward(this->batchInputs, batchSampleRows, batchSampleColumns);
	this->results = batchresults[batchresults.GetLength()-1];
	this->inputs = batchInputs[batchInputs.GetLength() - 1];

	return batchresults;
}

Array<double> SpatialTransformer::Backward(Array<double>& signals){
	Array<double> imageGradients;
	Array<double> rowGradients;
	Array<double> columnGradients;

	this->sampler.Backward(this->inputs, signals, &rowGradients, &columnGradients, &imageGradients);
	Array<double> backSignal(this->gridGenerator.Backward(rowGradients, columnGradients));

	Long i = this->neurons.GetLength() - 1;
	while (i >= 0) {
		backSignal = dynamic_cast<Layer*>(this->neurons[i])->Backward(backSignal);
		i--;
	}
	
	return imageGradients;
}

Array <Array<double>> SpatialTransformer::BatchBackward(Array<Array<double>>& signals) {
	Array<Array<double>> batchImageGradients;
	Array<Array<double>> batchRowGradients;
	Array<Array<double>> batchColumnGradients;

	this->sampler.BatchBackward(this->batchInputs, signals, &batchRowGradients, &batchColumnGradients, &batchImageGradients);

	Array<Array<double>> batchBackSignals(signals.GetLength());
	Long i = 0;
	while (i < signals.GetLength()) {
		Array<double> backSignal(this->gridGenerator.Backward(batchRowGradients[i], batchColumnGradients[i]));
		batchBackSignals.Store(i, backSignal);
		i++;
	}

	i = this->length - 1;
	while (i >= 0) {
		batchBackSignals = dynamic_cast<Layer*>(this->neurons[i])->BatchBackward(batchBackSignals);
		i--;
	}
	return batchImageGradients;
}

void SpatialTransformer::Update(double learningRate) {
	Long i = 0;
	while (i < this->length) {
		dynamic_cast<Layer*>(this->neurons[i])->Update(learningRate);
		i++;
	}
}

void SpatialTransformer::Update(double updatedLearningRate, double beta1, double beta2) {
	Long i = 0;
	while (i < this->length) {
		dynamic_cast<Layer*>(this->neurons[i])->Update(updatedLearningRate, beta1, beta2);
		i++;
	}
}

string SpatialTransformer::GetType() {
	return "STN";
}

Long SpatialTransformer::Save(fstream *file) {
	*file << this->length << endl;
	Long i = 0;
	while (i < this->length) {
		string type = dynamic_cast<Layer*>(this->neurons[i])->GetType();
		*file << type << endl;
		this->neurons[i]->Save(file);
		i++;
	}
	return this->length;
}

Long SpatialTransformer::Load(fstream *fs) {
	NeuronFactory neuronFactory;
	string receive;
	Long layerCount;
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
		else { //dropout
			neuronType = NEURON_DROPOUT;
		}
		Neuron *layer = neuronFactory.Make(neuronType);
		layer->Load(fs);
		CompositeNeuron::Add(layer);

		i++;
	}

	return this->length;
}