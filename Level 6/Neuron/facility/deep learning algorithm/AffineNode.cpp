#include "AffineNode.h"
#if !defined(_AFXDLL)

#include <crtdbg.h>
#if defined(DEBUG) |defined(_DEBUG)
#if !defined(DEBUG_NEW)
#define DEBUG_NEW new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif
#endif
#endif
AffineNode::AffineNode(Long capacity)
	:weights(capacity), weightGradients(capacity), weightMomentums(capacity), weightVelocities(capacity) {
	this->bias = 0.0;
	this->biasGradient = 0.0;
	this->biasMomentum = 0.0;
	this->biasVelocity = 0.0;
	this->capacity = capacity;
	this->length = 0;

}

AffineNode::AffineNode(const Array<double>& weights, double bias,
	const Array<double>& weightMomentums, const Array<double>& weightVelocities, double biasMomentum, double biasVelocity)
	: weights(weights), weightGradients(weights.GetLength()), weightMomentums(weightMomentums), weightVelocities(weightVelocities) {
	this->bias = bias;
	this->biasGradient = 0.0;
	this->biasMomentum = biasMomentum;
	this->biasVelocity = biasVelocity;
	this->capacity = this->weights.GetCapacity();
	this->length = this->weights.GetLength();
}

AffineNode::AffineNode(const AffineNode& source)
	: weights(source.weights), weightGradients(source.weightGradients), weightMomentums(source.weightMomentums), weightVelocities(source.weightVelocities) {
	this->bias = source.bias;
	this->biasGradient = source.biasGradient;
	this->biasMomentum = source.biasMomentum;
	this->biasVelocity = source.biasVelocity;
	this->capacity = this->weights.GetCapacity();
	this->length = this->weights.GetLength();
}

AffineNode::~AffineNode() {

}

double AffineNode::Flow(Array<double>& signals) {
	this->result = 0.0;
	Long i = 0;
	while (i < this->length) {
		this->result += this->weights[i] * signals[i]; //Flow 결과(Node하나) = 가중치1*입력1 + 가중치2*입력2 ...
		i++;
	}
	this->result += this->bias; //노드 하나당 편향 하나

	return this->result;
}

void AffineNode::BackFlow(double signal, Array<double>& inputs) {
	double gradient = 0.0;
	double weightGradient;
	this->weightGradients = Array<double>(this->length);

	this->biasGradient = signal;
	Long i = 0;
	while (i < this->length) {
		weightGradient = inputs[i] * signal;
		this->weightGradients.Store(i, weightGradient);
		i++;
	}
}

void AffineNode::BatchBackFlow(Array<double>& signals, Array<Array<double>>& inputs) {
	Long i = 0;
	while (i < signals.GetLength()) {
		this->biasGradient += signals[i];
		i++;
	}
	this->weightGradients = Array<double>(this->length);

	Long batch = inputs.GetLength();
	i = 0;
	while (i < inputs.GetAt(0).GetLength()) { //입력 개수=가중치 개수만큼 반복한다.
		double weightGradient = 0.0;
		Long j = 0;
		while (j < inputs.GetLength()) { //배치 개수만큼 반복한다.
			weightGradient += inputs[j][i] * signals[j];
			j++;
		}
		this->weightGradients.Store(i, weightGradient);
		i++;
	}
}

void AffineNode::Update(double learningRate) {
	Long i = 0;
	while (i < this->length) {
		double weight = this->weights[i] - this->weightGradients[i] * learningRate;
		this->weights.Modify(i, weight);
		i++;
	}

	this->bias -= learningRate * this->biasGradient;
}

void AffineNode::Update(double updatedLearningRate, double beta1, double beta2) {
	double weightMomentum;
	double weightVelocity;
	double weight;
	Long i = 0;
	while (i < this->length) {
		weightMomentum = this->weightMomentums[i] + (1 - beta1) * (this->weightGradients[i] - this->weightMomentums[i]);
		this->weightMomentums.Modify(i, weightMomentum);
		weightVelocity = this->weightVelocities[i] + (1 - beta2) * (pow(this->weightGradients[i], 2) - this->weightVelocities[i]);
		this->weightVelocities.Modify(i, weightVelocity);
		weight = this->weights[i] - (updatedLearningRate * this->weightMomentums[i] / (sqrt(this->weightVelocities[i]) + 1e-7));
		this->weights.Modify(i, weight);
		i++;
	}
	this->biasMomentum += (1 - beta1) * (this->biasGradient - this->biasMomentum);
	this->biasVelocity += (1 - beta2) * (pow(this->biasGradient, 2) - this->biasVelocity);
	this->bias -= (updatedLearningRate * this->biasMomentum / (sqrt(this->biasVelocity) + 1e-7));
}

Neuron* AffineNode::Clone() {
	return new AffineNode(*this);
}

AffineNode& AffineNode::operator=(const AffineNode& source) {
	this->weights = source.weights;
	this->bias = source.bias;
	this->weightGradients = source.weightGradients;
	this->biasGradient = source.biasGradient;
	this->weightMomentums = source.weightMomentums;
	this->weightVelocities = source.weightVelocities;
	this->biasMomentum = source.biasMomentum;
	this->biasVelocity = source.biasVelocity;
	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}
