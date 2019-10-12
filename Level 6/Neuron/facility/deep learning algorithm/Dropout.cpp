#include "Dropout.h"
#include "DropoutNode.h"
#include "Node.h"
#include <random>
#include <chrono>
#if !defined(_AFXDLL)

#include <crtdbg.h>
#if defined(DEBUG) |defined(_DEBUG)
#if !defined(DEBUG_NEW)
#define DEBUG_NEW new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif
#endif
#endif
Dropout::Dropout(Long capacity, double ratio)
	: Layer(capacity) {
	this->ratio = ratio;

}

Dropout::Dropout(const Dropout& source)
	: Layer(source) {
	this->ratio = source.ratio;
}

Dropout::~Dropout() {

}

Array<double> Dropout::Forward(Array<double>& signals, bool isTraining) {
	unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	uniform_real_distribution<double> distribution(0.0, 1.0);

	this->inputs = signals;
	this->inputCount = signals.GetLength();

	Array<double> results(this->length);
	Neuron *node;
	Long i = 0;
	while (i < this->length) {
		node = this->neurons.GetAt(i);
		double randomNumber = distribution(generator);
		double result;
		if (randomNumber > this->ratio || isTraining == false) {
			result = dynamic_cast<Node*>(node)->Flow(signals[i], true);
		}
		else {
			result = dynamic_cast<Node*>(node)->Flow(0.0, false);
		}
		results.Store(i, result);
		i++;
	}

	return results;
}

Array<Array<double>> Dropout::BatchForward(Array<Array<double>>& signals, bool isTraining) {
	unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	uniform_real_distribution<double> distribution(0.0, 1.0);

	Long batch = signals.GetLength();
	this->batchInputs = signals;
	this->inputCount = signals.GetAt(0).GetLength();
	Array<Array<double>> results(signals);

	Long i = 0;
	while (i < this->length) { // 노드 개수만큼 반복
		Array<double> signalsPerBatch(signals.GetLength());
		Long j = 0;
		while (j < signals.GetLength()) { // 배치 개수만큼 반복, 시그널스들의 i번째를 가져옴
			signalsPerBatch.Store(j, signals[j][i]);
			j++;
		}

		Array<bool> batchIsActive(signals.GetLength());
		j = 0;
		while (j < signals.GetLength()) { // 삭제할 노드들을 결정
			double randomNumber = distribution(generator);
			if (randomNumber > this->ratio || isTraining == false) {
				batchIsActive.Store(j, true);
			}
			else {
				batchIsActive.Store(j, false);
				signalsPerBatch[j] = 0.0;
			}
			j++;
		}

		Neuron *node = this->neurons.GetAt(i);
		signalsPerBatch = dynamic_cast<Node*>(node)->BatchFlow(signalsPerBatch, batchIsActive);

		// results에 결과를 적는다. 
		j = 0;
		while (j < signalsPerBatch.GetLength()) {
			results[j][i] = signalsPerBatch[j];
			j++;
		}
		i++;
	}

	return results;
}

Array<double> Dropout::Backward(Array<double>& signals) {
	this->inputGradients = Array<double>(this->inputCount);
	Neuron *node;
	double gradient;

	Long i = 0;
	while (i < this->length) {
		node = this->neurons.GetAt(i);
		gradient = dynamic_cast<Node*>(node)->BackFlow(signals[i]);
		this->inputGradients.Store(i, gradient);
		i++;
	}

	return this->inputGradients;
}

Array<Array<double>> Dropout::BatchBackward(Array<Array<double>>& signals) {
	Long batch = signals.GetLength();
	Array<Array<double>> batchInputGradients(signals);

	Long i = 0;
	while (i < this->length) { // 노드 개수만큼 반복
		Array<double> signalsPerBatch(signals.GetLength());
		Long j = 0;
		while (j < signals.GetLength()) { // 배치 개수만큼 반복, 시그널스들의 i번째를 가져옴
			signalsPerBatch.Store(j, signals[j][i]);
			j++;
		}

		Neuron *node = this->neurons.GetAt(i);
		signalsPerBatch = dynamic_cast<Node*>(node)->BatchBackFlow(signalsPerBatch);

		// results에 결과를 적는다. 
		j = 0;
		while (j < signalsPerBatch.GetLength()) {
			batchInputGradients[j][i] = signalsPerBatch[j];
			j++;
		}
		i++;
	}

	return batchInputGradients;
}

void Dropout::MakeNodes(Long inputCount, Long outputCount) {
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
		node = new DropoutNode;
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
}

Long Dropout::Save(fstream *fs) {
	*fs << this->length << endl;
	*fs << this->ratio << endl;

	return this->length;
}

Long Dropout::Load(fstream *fs) {
	// 노드 수를 읽다.
	Long nodeCount;
	*fs >> nodeCount;
	this->neurons.Resize(nodeCount);
	this->capacity = nodeCount;
	// 비율을 읽다.
	*fs >> this->ratio;

	// 노드 수만큼 반복하다.
	Long i = 0;
	while (i < nodeCount) {
		Node *node = new DropoutNode;//  노드를 만들다.
		this->Add(node);//  저장한다.
		i++;
	}
	return this->length;
}

string Dropout::GetType() {
	return "Dropout";
}

Neuron* Dropout::Clone() {
	return new Dropout(*this);
}

Dropout& Dropout::operator =(const Dropout& source) {
	Layer::operator=(source);
	this->ratio = source.ratio;


	return *this;
}
