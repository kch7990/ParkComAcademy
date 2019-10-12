#include "Sigmoid.h"
#include "SigmoidNode.h"

Sigmoid::Sigmoid(Long capacity)
	: Layer(capacity) {

}

Sigmoid::Sigmoid(const Sigmoid& source)
	: Layer(source) {

}

Sigmoid::~Sigmoid() {

}

Array<double> Sigmoid::Forward(Array<double>& signals) {
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

Array<Array<double>> Sigmoid::BatchForward(Array<Array<double>>& signals) {
	this->batchInputs = signals;
	this->inputCount = signals.GetAt(0).GetLength();
	Array<Array<double>> results(signals);

	Long i = 0; 
	while (i < this->length) {
		// signals[j][i] 번째 가져오기
		Array<double> resultsPerBatch(signals.GetLength());
		Array<double> signalsPerBatch(signals.GetLength());
		Long j = 0;
		while (j < signals.GetLength()) {
			signalsPerBatch.Store(j, signals[j][i]);
			j++;
		}
		// 시그모이드 노드의 배치연산 부르기
		resultsPerBatch = dynamic_cast<Node*>(this->neurons[i])->BatchFlow(signalsPerBatch);

		j = 0; // 결과를 results[j][i] 에 적기 
		while (j < signals.GetLength()) {
			results[j][i] = resultsPerBatch[j];
			j++;
		}
		i++;
	}

	return results;
}

Array<double> Sigmoid::Backward(Array<double>& signals) {
	this->inputGradients = Array<double>(this->inputCount);
	Neuron *node;
	double gradient;

	Long i = 0;
	while (i < this->length) {
		node = this->neurons.GetAt(i);
		gradient = dynamic_cast<Node*>(node)->BackFlow(const_cast<Array<double>&>(signals)[i]);
		this->inputGradients.Store(i, gradient);
		i++;
	}

	return this->inputGradients;
}

Array<Array<double>> Sigmoid::BatchBackward(Array<Array<double>>& signals) {
	Array<Array<double>> batchInputGradients(signals);

	Long i = 0;
	while (i < this->length) {
		// signals[j][i] 번째 가져오기
		Array<double> resultsPerBatch(signals.GetLength());
		Array<double> signalsPerBatch(signals.GetLength());
		Long j = 0;
		while (j < signals.GetLength()) {
			signalsPerBatch.Store(j, signals[j][i]);
			j++;
		}
		// 시그모이드 노드의 배치연산 부르기
		resultsPerBatch = dynamic_cast<Node*>(this->neurons[i])->BatchBackFlow(signalsPerBatch);

		j = 0; // 결과를 results[j][i] 에 적기 
		while (j < signals.GetLength()) {
			batchInputGradients[j][i] = resultsPerBatch[j];
			j++;
		}
		i++;
	}


	return batchInputGradients;
}

void Sigmoid::MakeNodes(Long inputCount, Long outputCount) {
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
		node = new SigmoidNode;
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

Long Sigmoid::Save(fstream *fs) {
	*fs << this->length << endl;

	return this->length;
}

Long Sigmoid::Load(fstream *fs) {
	// 1. 노드 수를 읽는다.
	Long nodeCount;
	*fs >> nodeCount;
	this->neurons.Resize(nodeCount);
	this->capacity = nodeCount;

	Long i = 0;
	while (i < nodeCount) {	// 2. 노드 수만큼 반복한다.
		Node *node = new SigmoidNode; 	//  2.1. 노드를 만들다.
		this->Add(node); //  2.2. 저장한다.
		i++;
	}

	return this->length; // 3. 노드 수를 출력한다.
}

string Sigmoid::GetType() {
	return "Sigmoid";
}

Neuron* Sigmoid::Clone() {
	return new Sigmoid(*this);
}

Sigmoid& Sigmoid::operator =(const Sigmoid& source) {
	Layer::operator =(source);

	return *this;
}