#include "ReLUNode.h"
#if !defined(_AFXDLL)

#include <crtdbg.h>
#if defined(DEBUG) |defined(_DEBUG)
#if !defined(DEBUG_NEW)
#define DEBUG_NEW new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif
#endif
#endif
ReLUNode::ReLUNode() {

}

ReLUNode::ReLUNode(const ReLUNode& source)
	:Node(source) {

}

ReLUNode::~ReLUNode() {

}

double ReLUNode::Flow(double signal) {
	if (signal > 0.0f) { //입력이 0보다 크면 입력값 그대로 출력
		this->result = signal;
	}
	else { //입력이 0보다 작으면 0 출력
		this->result = 0;
	}

	return this->result;
}

double ReLUNode::BackFlow(double signal, double input) {
	double gradient = 0.0;
	if (input > 0) {
		gradient = signal;
	}

	return gradient;
}

Neuron* ReLUNode::Clone() {
	return new ReLUNode(*this);
}

ReLUNode& ReLUNode::operator =(const ReLUNode& source) {
	Node::operator =(source);

	return *this;
}