#include "SoftmaxNode.h"
#if !defined(_AFXDLL)

#include <crtdbg.h>
#if defined(DEBUG) |defined(_DEBUG)
#if !defined(DEBUG_NEW)
#define DEBUG_NEW new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif
#endif
#endif
SoftmaxNode::SoftmaxNode() {

}

SoftmaxNode::SoftmaxNode(const SoftmaxNode& source)
	:Node(source) {
	this->batchResults = source.batchResults;
}

SoftmaxNode::~SoftmaxNode() {

}

double SoftmaxNode::Flow(double numerator, double sum) {
	this->result = numerator / sum;

	return this->result;
}

Array<double> SoftmaxNode::BatchFlow(Array<double> &numerators, Array<double> &sums) {
	Long i = 0;
	this->batchResults = Array<double>(numerators.GetLength());
	while (i < numerators.GetLength()) {
		this->batchResults.Store(i, numerators[i] / sums[i]);
		i++;
	}

	return this->batchResults;
}

double SoftmaxNode::BackFlow(double signal) {
	double gradient = this->result - signal;

	return gradient;
}

Array<double> SoftmaxNode::BatchBackFlow(Array<double> &signals) {
	// 1. y-t
	Array<double> batchBackSignal(signals.GetLength());
	Long i = 0;
	while (i < signals.GetLength()) {
		batchBackSignal.Store(i, this->batchResults[i] - signals[i]);
		i++;
	}
	return batchBackSignal;
}

Neuron* SoftmaxNode::Clone() {
	return new SoftmaxNode(*this);
}

SoftmaxNode& SoftmaxNode::operator =(const SoftmaxNode& source) {
	Node::operator =(source);
	this->batchResults = source.batchResults;
	return *this;
}