#include "SigmoidNode.h"

SigmoidNode::SigmoidNode() {

}

SigmoidNode::SigmoidNode(const SigmoidNode& source) 
	: Node(source){

}

SigmoidNode::~SigmoidNode() {
	
}

double SigmoidNode::Flow(double signal) {
	this->result = 1 / (1 + exp(-signal));

	return this->result;
}

Array<double> SigmoidNode::BatchFlow(Array<double>& signals) {
	this->batchResult = Array<double> (signals.GetLength());
	
	Long i = 0;
	while (i < signals.GetLength()) {
		this->batchResult.Store(i, 1.0 / (1 + exp(-signals[i])));
		i++;
	}
	return this->batchResult;
}

double SigmoidNode::BackFlow(double signal) {
	double gradient = signal * this->result * (1 - this->result);

	return gradient;
}

Array<double> SigmoidNode::BatchBackFlow(Array<double>& signals) {
	Array<double>inputGradients(signals.GetLength());

	Long i = 0;
	while (i < signals.GetLength()) {
		inputGradients.Store(i, signals[i] * this->batchResult[i] * (1 - this->batchResult[i]));
		i++;
	}
	return inputGradients;
}

Neuron* SigmoidNode::Clone() {
	return new SigmoidNode(*this);
}

SigmoidNode& SigmoidNode::operator =(const SigmoidNode& source) {
	Node::operator =(source);

	return *this;
}