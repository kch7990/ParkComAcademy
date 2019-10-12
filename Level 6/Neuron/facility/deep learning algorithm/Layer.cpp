#include "Layer.h"
#include "Node.h"

Layer::Layer(Long capacity)
	: CompositeNeuron(capacity) {
	this->inputCount = 0;
}

Layer::Layer(const Layer& source)
	: CompositeNeuron(source), inputGradients(source.inputGradients), inputs(source.inputs) {
	this->inputCount = source.inputCount;
}

Layer::~Layer() {

}

void Layer::MakeNodes(Long inputCount, Long outputCount) {

}

void Layer::MakeNodes(Long inputCount, Long outputCount, double deviation) {

}

void Layer::MakeFilters(Long channel, Long filterCount) {

}

void Layer::MakeFilters(Long channel, Long filterCount, double deviation) {

}


Array<double> Layer::Forward(Array<double>& signals) {
	return 0;
}

Array<double> Layer::Forward(Array<double>& signals, bool isTraining) {
	return 0;
}

Array<Array<double>> Layer::BatchForward(Array<Array<double>>& signals) {
	return 0;
}

Array<Array<double>> Layer::BatchForward(Array<Array<double>>& signals, bool isTraining) {
	return 0;
}

Array<Array<double>> Layer::BatchBackward(Array<Array<double>>& signals) {
	return 0;
}

/*
Array<double> Layer::Forward(Array<double>& signals) {
	return 0;
}

Array<double> Layer::Backward(Array<double>& signals) {
	return 0;
}

void Layer::MakeNodes(Long nodeCount) {

}

string Layer::GetType() {
	return "";
}
*/


Array<double> Layer::GetWeights() {
	return 0;
}

Array<double> Layer::GetWeightGradients() {
	return 0;
}

Array<double> Layer::GetResults() {
	Array<double> results(this->length);

	Long i = 0;
	while (i < this->length)
	{
		results.Store(i, dynamic_cast<Node*>(this->neurons[i])->GetResult());
		i++;
	}

	return results;
}

Layer& Layer::operator =(const Layer& source) {
	CompositeNeuron::operator =(source);
	this->inputGradients = source.inputGradients;
	this->inputs = source.inputs;
	this->inputCount = source.inputCount;

	return *this;
}