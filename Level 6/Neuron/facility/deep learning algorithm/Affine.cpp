#include "Affine.h"
#include "AffineNode.h"
#include "Node.h"
#include <random> //난수 생성
#include <chrono> //난수 생성
#include <iostream>



using namespace std; //난수 생성

Affine::Affine(Long capacity, Long inputCount, double deviation)
	: Layer(capacity) {
	this->inputCount = inputCount;
	this->deviation = deviation;
}

Affine::Affine(const Affine& source)
	: Layer(source) {
	this->deviation = source.deviation;
}

Affine::~Affine() {

}

Array<double> Affine::Forward(Array<double>& signals) {
	this->inputs = signals;
	this->inputCount = signals.GetLength();
	Array<double> outputs(this->length); //순전파의 결과 배열
	double output;

	Long i = 0;
	while (i < this->length) {
		output = dynamic_cast<Node*>(this->neurons[i])->Flow(signals);
		//입력값 모두와 노드 하나의 가중치 배열을 각각 행렬곱
		outputs.Store(i, output);
		i++;
	}

	return outputs;
}

Array<Array<double>> Affine::BatchForward(Array<Array<double>>& signals) {
	this->batchInputs = signals;
	this->inputCount = signals.GetAt(0).GetLength();
	Array<Array<double>> outputs(signals.GetLength()); //순전파의 결과 배열
	double output;

	Long i = 0;
	//배치 크기만큼 반복한다.
	while(i < signals.GetLength()) {
		Array<double> outputsPerBatch(this->length);
		Array<double> signalsPerBatch = signals.GetAt(i);
		Long j = 0;
		while (j < this->length) { //노드 개수만큼 반복한다.
			output = dynamic_cast<Node*>(this->neurons[j])->Flow(signalsPerBatch);
			outputsPerBatch.Store(j, output);
			j++;
		}
		outputs.Store(i, outputsPerBatch);
		i++;
	}


	return outputs;
}

Array<double> Affine::Backward(Array<double>& signals) {
	//Array<double> weights(this->length); //노드들의 n번째 가중치 배열
	this->inputGradients = Array<double>(this->inputCount);
	double weight;
	Neuron *node = 0;
	Long i = 0;
	while (i < this->inputCount) { //입력값에 대한 기울기의 개수 = 입력값 개수
		//n번째 가중치만 모든 노드에서 가져오기
		Array<double> weights(this->length);
		Long j = 0;
		while (j < this->length) {
			node = this->neurons[j];
			weight = dynamic_cast<AffineNode*>(node)->GetWeight(i); //현재 노드의 k번째 가중치
			weights.Store(j, weight);
			j++;
		}
		//기울기를 가져온 가중치와 signal을 이용해 행렬곱하기
		double gradient = 0.0;
		j = 0;
		while (j < this->length) {
			gradient += signals[j] * weights[j];
			j++;
		}
		//입력값에 대한 기울기 구하기
		this->inputGradients.Store(i, gradient);
		i++;
	}
	//가중치에 대한 기울기, 편향에 대한 기울기 수정하기
	i = 0;
	while (i < this->length) {
		node = this->neurons[i];
		//역전파값들, k번째가중치들, 입력값들과 현재 인덱스
		dynamic_cast<Node*>(node)->BackFlow(signals[i], this->inputs);
		i++;
	}

	return this->inputGradients;
}

Array<Array<double>> Affine::BatchBackward(Array<Array<double>>& signals) {
	double weight;
	Neuron *node = 0;
	Long batch = signals.GetLength();
	Array<Array<double>> batchInputGradients(batch);

	Array<Array<double>> allWeights(this->inputCount);
	Long i = 0;
	while (i < this->inputCount) {
		Array<double> weights(this->length);
		Long j = 0;
		while (j < this->length) {
			node = this->neurons[j];
			weight = dynamic_cast<AffineNode*>(node)->GetWeight(i); //현재 노드의 k번째 가중치
			weights.Store(j, weight);
			j++;
		}
		allWeights.Store(i, weights);
		i++;
	}

	i = 0;
	//배치 크기만큼 반복한다.
	while (i < batch) {
		Array<double> batchInputGradientsPerBatch(this->inputCount);
		//Array<double> signalsPerBatch = signals.GetAt(i);
		Long j = 0;
		//입력 개수만큼 반복한다.
		while (j < this->inputCount) { //입력값에 대한 기울기의 개수 = 입력값 개수
			double gradient = 0.0;
			Long k = 0;
			while (k < this->length) {
				gradient += signals[i][k] * allWeights[j][k];
				k++;
			}
			batchInputGradientsPerBatch.Store(j, gradient);
			j++;
		}
		batchInputGradients.Store(i, batchInputGradientsPerBatch);
		i++;
	}

	i = 0;
	//노드 개수만큼 반복하면서 batchbackflow를 통해 가중치와 편향 기울기를 구한다.
	while (i < this->length) {
		Array<double> backFlowSignals(batch); //BatchBackFlow 할 신호들 : n번째 기울기들
		Long j = 0;
		while (j < batch) { //배치 크기만큼 반복하면서 j번째 기울기들만 기억한다.
			Array<double> signalsPerBatch = signals.GetAt(j);
			backFlowSignals.Store(j, signalsPerBatch[i]);
			j++;
		}
		dynamic_cast<Node*>(this->neurons[i])->BatchBackFlow(backFlowSignals, this->batchInputs);
		i++;
	}

	return batchInputGradients;
}

void Affine::Update(double learningRate) {
	Long i = 0;
	while (i < this->GetLength()) {
		Neuron *affineNode = this->neurons[i];
		dynamic_cast<Node*>(affineNode)->Update(learningRate);
		i++;
	}
}

void Affine::Update(double updatedLearningRate, double beta1, double beta2) {
	Long i = 0;
	while (i < this->length) {
		Neuron *affineNode = this->neurons[i];
		dynamic_cast<Node*>(affineNode)->Update(updatedLearningRate, beta1, beta2);
		i++;
	}
}

void Affine::MakeNodes(Long inputCount, Long outputCount, double deviation) {
	unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
	default_random_engine e(seed);
	this->deviation = deviation;
	normal_distribution<double> distrN(0.0, deviation);
	Neuron *node;

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

	i = 0;
	while (i < outputCount) { //노드 개수만큼 반복한다.
		Array<double> temp(inputCount); //노드 한 개의 속성인 가중치 배열
		Array<double> weightMomentums(inputCount);
		Array<double> weightVelocities(inputCount);

		Long j = 0;
		while (j < inputCount) {
			temp.Store(j, distrN(e));//난수를 배열에 넣기
			weightMomentums.Store(j, 0.0);
			weightVelocities.Store(j, 0.0);
			j++;
		}

		node = new AffineNode(temp, 0.0, weightMomentums, weightVelocities, 0.0, 0.0); //AffineNode의 매개변수를 갖는 생성자 : 가중치배열, 편향

		if (this->length < this->capacity) {
			this->neurons.Store(this->length, node); //neurons 배열에 추가
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

Long Affine::Save(fstream *fs) {
	string content;

	(*fs) << to_string(this->length) << "\n"; // 노드 개수
	(*fs) << to_string(this->inputCount) << "\n"; // 가중치 개수
	(*fs) << to_string(this->deviation) << "\n"; //편차
	double value;
	double bias;
	double biasMomentum;
	double biasVelocity;
	Long j;
	Long i = 0;
	while (i < this->length) {
		Neuron *node = this->neurons[i];
		j = 0;
		while (j < node->GetLength()) {
			value = dynamic_cast<Node*>(node)->GetWeight(j);
			(*fs) << value << " ";
			j++;
		}
		(*fs) << "\n";

		bias = dynamic_cast<Node*>(node)->GetBias();
		(*fs) << bias << "\n";
		biasMomentum = dynamic_cast<Node*>(node)->GetBiasMomentum();
		(*fs) << biasMomentum << "\n";
		biasVelocity = dynamic_cast<Node*>(node)->GetBiasVelocity();
		(*fs) << biasVelocity << "\n";

		j = 0;
		while (j < node->GetLength()) { // 모멘텀 저장
			value = dynamic_cast<Node*>(node)->GetWeightMomentum(j);
			(*fs) << value << " ";
			j++;
		}
		(*fs) << "\n";
		j = 0;
		while (j < node->GetLength()) { // 속도 저장
			value = dynamic_cast<Node*>(node)->GetWeightVelocity(j);
			(*fs) << value << " ";
			j++;
		}
		(*fs) << "\n";

		i++;
	}

	return this->length;
}

Long Affine::Load(fstream *fs) {
	Long nodeCount;
	Long weightCount;
	double value;
	double bias;
	Neuron *node;
	// 1. 노드 개수를 읽는다.
	// 2. 가중치 개수를 읽는다.
	*fs >> nodeCount;
	this->neurons.Resize(nodeCount);
	this->capacity = nodeCount;

	*fs >> weightCount;

	*fs >> this->deviation;
	double biasMomentum;
	double biasVelocity;
	Long i = 0;
	Long j;

	// 3. 노드 개수만큼 반복한다.
	while (i < nodeCount) {
		//  3.1. 가중치 개수만큼 반복한다.
		Array<double> weights(weightCount);
		Array<double> weightMomentums(weightCount);
		Array<double> weightVelocities(weightCount);
		j = 0;
		while (j < weightCount) {
			//   3.1.1. 가중치를 읽다.
			*fs >> value;
			weights.Store(j, value);
			j++;
		}
		//  3.2. 편향을 읽다.
		*fs >> bias;
		*fs >> biasMomentum;
		*fs >> biasVelocity;
		//  3.3. 노드를 만든다.
		// 모멘텀을 읽다.
		j = 0;
		while (j < weightCount) {
			*fs >> value;
			weightMomentums.Store(j, value);
			j++;
		}
		// 속도를 읽다.
		j = 0;
		while (j < weightCount) {
			//   3.1.1. 가중치를 읽다.
			*fs >> value;
			weightVelocities.Store(j, value);
			j++;
		}

		node = new AffineNode(weights, bias, weightMomentums, weightVelocities, biasMomentum, biasVelocity);
		//  3.4. Affine에 넣는다.
		this->Add(node);
		i++;
	}

	// 4. 노드 개수를 출력하다.
	return this->length;
}

Array<double> Affine::GetWeights() {
	Array<double> weights(this->length * this->inputCount); //길이 = 노드 개수 * 노드 하나의 가중치 배열 길이
	Long k = 0;
	Neuron* node;
	double weight;
	Long j;
	Long i = 0;

	while (i < this->length) { //노드 개수만큼 반복
		node = this->neurons[i]; //현재 노드 가져오기
		j = 0;
		while (j < this->inputCount) { //노드의 가중치 개수만큼 반복
			weight = dynamic_cast<AffineNode*>(node)->GetWeight(j);
			weights.Store(k, weight);
			k++; //weigths 배열의 첨자
			j++;
		}
		i++;
	}

	return weights;
}

Array<double> Affine::GetWeightGradients() {
	Array<double> weights(this->length * this->inputCount);
	Long k = 0;
	Neuron* node;
	double weight;
	Long j;
	Long i = 0;

	while (i < this->length) {
		node = this->neurons[i];
		j = 0;
		while (j < this->inputCount) {
			weight = dynamic_cast<AffineNode*>(node)->GetWeightGradient(j);
			weights.Store(k, weight);
			k++;
			j++;
		}
		i++;
	}

	return weights;
}

string Affine::GetType() {
	return "Affine";
}

Neuron* Affine::Clone() {
	return new Affine(*this);
}

Affine& Affine::operator=(const Affine& source) {
	Layer::operator =(source);
	this->deviation = source.deviation;
	return *this;
}