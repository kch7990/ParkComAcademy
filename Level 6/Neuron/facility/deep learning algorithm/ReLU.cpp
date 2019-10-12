#include "ReLU.h"
#include "ReluNode.h"
#include "CompositeNeuron.h"
#include "Layer.h"

#if !defined(_AFXDLL)

#include <crtdbg.h>
#if defined(DEBUG) |defined(_DEBUG)
#if !defined(DEBUG_NEW)
#define DEBUG_NEW new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif
#endif
#endif

ReLU::ReLU(Long capacity)
	: Layer(capacity) {

}

ReLU::ReLU(const ReLU& source)
	: Layer(source) {

}

ReLU::~ReLU() {

}

Array<double> ReLU::Forward(Array<double>& signals) {
	this->inputs = signals;
	this->inputCount = signals.GetLength();
	double result;
	Array<double> results(this->length); //출력값의 개수 = 노드 개수
	Neuron *node;
	Long i = 0;
	while (i < this->length) {
		node = this->neurons.GetAt(i);
		result = dynamic_cast<Node*>(node)->Flow(const_cast<Array<double>&>(signals)[i]); //입력값 하나씩만 순전파
		results.Store(i, result);
		i++;
	}


	return results;
}

Array<Array<double>> ReLU::BatchForward(Array<Array<double>>& signals) {
	this->batchInputs = signals;
	this->inputCount = signals.GetAt(0).GetLength();
	double result;
	Array<Array<double>> results(signals);

	Long i = 0;
	//배치 크기만큼 반복한다.
	while (i < signals.GetLength()) {
		Array<double> signalsPerBatch = signals.GetAt(i);
		Long j = 0;
		while (j < this->length) { //노드 개수만큼 반복한다.
			result = dynamic_cast<Node*>(this->neurons[j])->Flow(signalsPerBatch[j]);
			results[i].Modify(j, result);
			j++;
		}
		i++;
	}

	return results;
}

Array<double> ReLU::Backward(Array<double>& signals) {
	this->inputGradients = Array<double>(this->inputCount);
	Neuron *node;
	double gradient;

	Long i = 0;
	while (i < this->length) {
		node = this->neurons.GetAt(i);
		gradient = dynamic_cast<Node*>(node)->BackFlow(const_cast<Array<double>&>(signals)[i], this->inputs[i]);
		this->inputGradients.Store(i, gradient);
		i++;
	}

	return this->inputGradients;
}

Array<Array<double>> ReLU::BatchBackward(Array<Array<double>>& signals) {
	Array<Array<double>> batchInputGradients(signals.GetLength());
	double gradient;

	Long i = 0;
	while (i < signals.GetLength()) {
		Array<double> batchInputGradientsPerBatch(this->length);
		Array<double> signalsPerBatch = signals.GetAt(i);
		Array<double> inputsPerBatch = this->batchInputs.GetAt(i);
		Long j = 0;
		while (j < this->length) {
			gradient = dynamic_cast<Node*>(this->neurons[j])->BackFlow(signalsPerBatch[j], inputsPerBatch[j]);
			batchInputGradientsPerBatch.Store(j, gradient);
			j++;
		}
		batchInputGradients.Store(i, batchInputGradientsPerBatch);
		i++;
	}

	return batchInputGradients;
}

void ReLU::MakeNodes(Long inputCount, Long outputCount) {
	Neuron *neuron;
	Long i = 0;
	while (i < this->length) { //neurons의 요소들이 포인터 : 할당 해제
		neuron = this->neurons[i];
		if (neuron != 0) {
			delete neuron;
		}
		i++;
	}
	this->neurons.Clear();
	this->neurons.Resize(outputCount);
	this->capacity = outputCount;
	this->length = 0;

	Neuron *node = 0;
	i = 0;
	while (i < outputCount) { //노드 개수만큼 반복 ReLU에서는 입력개수 = 출력(노드)개수
		node = new ReLUNode;
		if (this->length < this->capacity) {
			this->neurons.Store(i, node);
		}
		else {
			this->neurons.AppendFromRear(node);
			this->capacity++;
		}
		this->length++;
		i++;
	}

	this->inputCount = inputCount;
}

Long ReLU::Save(fstream *fs) {
	*fs << this->length << endl;

	return this->length;
}

Long ReLU::Load(fstream *fs) {
	// 1. 노드 수를 읽는다.
	Long nodeCount;
	*fs >> nodeCount;
	this->neurons.Resize(nodeCount);
	this->capacity = nodeCount;

	Long i = 0;
	while (i < nodeCount) {	// 2. 노드 수만큼 반복한다.
		Node *node = new ReLUNode; 	//  2.1. 노드를 만들다.
		this->Add(node); //  2.2. 저장한다.
		i++;
	}

	return this->length; // 3. 노드 수를 출력한다.
}

string ReLU::GetType() {
	return "ReLU";
}

Neuron* ReLU::Clone() {
	return new ReLU(*this);
}

ReLU& ReLU::operator =(const ReLU& source) {
	Layer::operator =(source);

	return *this;
}