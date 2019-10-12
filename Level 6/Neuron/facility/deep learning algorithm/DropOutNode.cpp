#include "DropoutNode.h"
#include <random>
#include <chrono>

using namespace std;
#if !defined(_AFXDLL)

#include <crtdbg.h>
#if defined(DEBUG) |defined(_DEBUG)
#if !defined(DEBUG_NEW)
#define DEBUG_NEW new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif
#endif
#endif
DropoutNode::DropoutNode(bool isActive){

}

DropoutNode::DropoutNode(const DropoutNode& source)
:Node(source){
	
}

DropoutNode::~DropoutNode(){
}

double DropoutNode::Flow(double signal, bool isActive){
	this->result = signal;
	this->isActive = isActive;

	return this->result;
}

Array<double> DropoutNode::BatchFlow(Array<double>& signals, Array<bool>& isActives) {
	this->batchResults = signals;
	this->batchIsActive = isActives;

	return this->batchResults;
}

double DropoutNode::BackFlow(double signal){
	double out = signal;
	if (this->isActive == false) {
		out = 0;
	}

	return out;
}

Array<double> DropoutNode::BatchBackFlow(Array<double>& signals){
	Array<double> outputs(signals);
	Long i = 0;
	while (i < outputs.GetLength()) {
		if (this->batchIsActive[i] == false) {
			outputs[i] = 0;
		}
		i++;
	}
	return outputs;
}

Neuron* DropoutNode::Clone() {
	return new DropoutNode(*this);
}

DropoutNode& DropoutNode::operator=(const DropoutNode& source){
	Node::operator=(source);
	return *this;
}