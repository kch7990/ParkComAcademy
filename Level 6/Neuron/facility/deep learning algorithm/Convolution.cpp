#include "Convolution.h"
#include "FilterCube.h"
#include "ConvolutionFilter.h"
#include <random>
#include <chrono>
#include <iostream>
#include "Matrix.h"

using namespace std;

Convolution::Convolution(Long capacity, Long pad, Long stride, Long filterSize)
	:Layer(capacity) {
	this->pad = pad;
	this->stride = stride;
	this->filterSize = filterSize;
	this->channelCount = 1;
	this->deviation = 0.0;
}

Convolution::Convolution(const Convolution& source)
	:Layer(source) {
	this->pad = source.pad;
	this->stride = source.stride;
	this->filterSize = source.filterSize;
	this->channelCount = source.channelCount;
	this->deviation = source.deviation;
}

Convolution::~Convolution() {

}

Array<double> Convolution::Forward(Array<double>& signals) {
	this->inputs = signals;
	this->inputCount = signals.GetLength();
	Long signalsSize = sqrt(static_cast<double>(signals.GetLength() / this->GetAt(0)->GetLength()));
	Long resultSize = ((signalsSize + this->pad * 2) - this->filterSize) / this->stride + 1;
	Array<double> results(resultSize * resultSize * this->length);

	Long k = 0;
	Long i = 0;
	while (i < this->length)
	{
		Array<double> outputs(dynamic_cast<FilterCube*>(this->neurons[i])->Flow(signals, signalsSize, this->stride, this->pad));

		Long j = 0;
		while (j < outputs.GetLength())
		{
			results.Store(k++, outputs[j]);
			j++;
		}

		i++;
	}

	return results;
}

Array<Array<double>> Convolution::BatchForward(Array<Array<double>>& signals) {
	this->batchInputs = signals;
	this->inputCount = signals.GetAt(0).GetLength();
	Long signalsSize = sqrt(static_cast<double>(inputCount / this->GetAt(0)->GetLength()));
	Long resultSize = ((signalsSize + this->pad * 2) - this->filterSize) / this->stride + 1;

	Long batch = signals.GetLength();
	Array<Array<double>> results(batch);
	Long i = 0;
	while (i < batch) {
		Array<double> resultsPerBatch(resultSize * resultSize * this->length);
		Long l = 0;
		Long j = 0;
		while (j < this->length)
		{
			Array<double> outputs(dynamic_cast<FilterCube*>(this->neurons[j])->Flow(signals.GetAt(i), signalsSize, this->stride, this->pad));

			Long k = 0;
			while (k < outputs.GetLength())
			{
				resultsPerBatch.Store(l++, outputs[k]);
				k++;
			}

			j++;
		}
		results.Store(i, resultsPerBatch);
		i++;
	}


	return results;
}

Array<double> Convolution::Backward(Array<double>& signals) {
	this->inputGradients = Array<double>(this->inputCount);
	Long i = 0;
	while (i < this->inputGradients.GetCapacity()) {
		this->inputGradients.Store(i, 0.0);
		i++;
	}

	Long k = 0;
	Long l = 0;
	i = 0;
	while (i < this->length) // 필터 큐브 수만큼 반복
	{
		Array<double> gradients(signals.GetLength() / this->length);

		Long j = 0;
		while (j < gradients.GetCapacity()) // i번째 채널의 역전파 값들을 가져온다.
		{
			gradients.Store(j, signals[k++]);
			j++;
		}

		Array<double> outputs(dynamic_cast<FilterCube*>(this->neurons[i])->BackFlow(this->inputs, gradients, this->stride, this->pad));
		j = 0;
		while (j < outputs.GetLength())
		{
			this->inputGradients.Modify(j, this->inputGradients[j] + outputs[j]);
			j++;
		}

		i++;
	}


	return this->inputGradients;
}

Array<Array<double>> Convolution::BatchBackward(Array<Array<double>>& signals) {
	Long batch = signals.GetLength();
	Array<Array<double>> batchInputGradients(batch);

	//*************입력 기울기 구하기

	Long indexOfBatch = 0;
	while (indexOfBatch < batch) { //배치만큼 반복한다.
		Array<double> signalsPerBatch = signals.GetAt(indexOfBatch); //한꺼번에 들어온 기울기들을 배치별로 나눔
		Array<double> inputsPerBatch = this->batchInputs.GetAt(indexOfBatch); //한꺼번에 존재하는 입력값들을 배치별로 나눔
		Array<double> batchInputGradientsPerBatch(this->inputCount); //입력값에 대한 기울기를 배치별로 나눠 저장할 배열
		Long i = 0;
		while (i < batchInputGradientsPerBatch.GetCapacity()) {
			batchInputGradientsPerBatch.Store(i, 0.0); //입력값에 대한 기울기는 Convolution 연산으로 누적될 것이므로 초기화
			i++;
		}

		Long k = 0;
		Long l = 0;
		i = 0;
		while (i < this->length) // 필터 큐브 수만큼 반복
		{
			Array<double> gradients(signalsPerBatch.GetLength() / this->length); //배치별로 나눠진 기울기를 필터큐브별로 나누어 저장할 배열

			Long j = 0;
			while (j < gradients.GetCapacity())
			{
				gradients.Store(j, signalsPerBatch[k++]); //현재 필터큐브에 들어갈 기울기들
				j++;
			}
			//이 backflow는 가중치 기울기와 편향 기울기에는 영향을 끼치지 않는다.
			Array<double> outputs(dynamic_cast<FilterCube*>(this->neurons[i])->BatchBackFlow(inputsPerBatch, gradients, this->stride, this->pad));
			j = 0;
			while (j < outputs.GetLength())
			{
				batchInputGradientsPerBatch.Modify(j, batchInputGradientsPerBatch[j] + outputs[j]); //필터큐브 수만큼 나오는 입력기울기를 모두 더함
				j++;
			}

			i++;
		}
		batchInputGradients.Store(indexOfBatch, batchInputGradientsPerBatch); //입력 기울기 배열을 하나에 배열에 모은다.
		indexOfBatch++;
	}

	//************가중치 기울기, 편향 기울기 구하기
	Long signalsSize = sqrt(static_cast<double>(signals.GetAt(0).GetLength() / batch / this->GetAt(0)->GetLength()));
	Long resultSize = ((signalsSize + this->pad * 2) - this->filterSize) / this->stride + 1;
	Long i = 0;
	while (i < this->length) {
		Array<Array<double>> signalsPerBatchAndLength(batch);
		Long j = 0;
		while (j < batch) {
			Array<double> signalsArrayPerBatch = signals.GetAt(j); //배치별로 나눴으나 채널별로는 통합돼있음
			Long arrayLength = signalsArrayPerBatch.GetLength() / this->length;
			Array<double> signalsArray(arrayLength);
			Long l = i * arrayLength;
			Long k = 0;
			while (k < arrayLength) {
				signalsArray.Store(k, signalsArrayPerBatch[l++]);
				k++;
			}
			signalsPerBatchAndLength.Store(j, signalsArray);
			j++;
		}
		dynamic_cast<FilterCube*>(this->neurons[i])->BatchBackFlow(this->batchInputs, signalsPerBatchAndLength, stride, pad);
		i++;
	}

	return batchInputGradients;
}

void Convolution::Update(double learningRate) {
	Long i = 0;
	while (i < this->length) {
		this->neurons[i]->Update(learningRate);
		i++;
	}
}

void Convolution::Update(double updatedLearningRate, double beta1, double beta2) {
	Long i = 0;
	while (i < this->length) {
		this->neurons[i]->Update(updatedLearningRate, beta1, beta2);
		i++;
	}
}

Long Convolution::Save(fstream *fs) {
	*fs << this->pad << endl;
	*fs << this->stride << endl;
	*fs << this->filterSize << endl;
	*fs << this->length << endl;
	*fs << this->deviation << endl;
	Long i = 0;
	while (i < this->length) {
		Neuron *filterCube = this->neurons[i];
		*fs << dynamic_cast<FilterCube*>(filterCube)->GetBias() << endl;
		*fs << dynamic_cast<FilterCube*>(filterCube)->GetBiasMomentum() << endl;
		*fs << dynamic_cast<FilterCube*>(filterCube)->GetBiasVelocity() << endl;
		*fs << filterCube->GetLength() << endl;
		Long j = 0;
		while (j < filterCube->GetLength()) {
			Neuron *filter = filterCube->GetAt(j);
			Long k = 0;
			while (k < dynamic_cast<ConvolutionFilter*>(filter)->GetSize()) {
				Long l = 0;
				while (l < dynamic_cast<ConvolutionFilter*>(filter)->GetSize()) {
					*fs << dynamic_cast<ConvolutionFilter*>(filter)->GetWeight(k, l) << " ";
					l++;
				}
				k++;
			}
			*fs << endl;

			k = 0;
			while (k < dynamic_cast<ConvolutionFilter*>(filter)->GetSize()) {
				Long l = 0;
				while (l < dynamic_cast<ConvolutionFilter*>(filter)->GetSize()) {
					*fs << dynamic_cast<ConvolutionFilter*>(filter)->GetWeightMomentum(k, l) << " ";
					l++;
				}
				k++;
			}
			*fs << endl;

			k = 0;
			while (k < dynamic_cast<ConvolutionFilter*>(filter)->GetSize()) {
				Long l = 0;
				while (l < dynamic_cast<ConvolutionFilter*>(filter)->GetSize()) {
					*fs << dynamic_cast<ConvolutionFilter*>(filter)->GetWeightVelocity(k, l) << " ";
					l++;
				}
				k++;
			}
			*fs << endl;

			j++;
		}
		*fs << endl;
		i++;
	}
	return this->length;
}

Long Convolution::Load(fstream *fs) {
	*fs >> this->pad;
	*fs >> this->stride;
	*fs >> this->filterSize;
	Long filterCubeCount;
	*fs >> filterCubeCount;
	*fs >> this->deviation;

	this->neurons.Resize(filterCubeCount);
	this->capacity = filterCubeCount;

	Long i = 0;
	while (i < filterCubeCount) {
		double bias;
		double biasMomentum;
		double biasVelocity;
		*fs >> bias;
		*fs >> biasMomentum;
		*fs >> biasVelocity;
		Long channel;
		*fs >> channel;
		Neuron *filterCube = new FilterCube(channel, bias, biasMomentum, biasVelocity);
		Long j = 0;
		while (j < channel) {
			Matrix<double> weights(this->filterSize, this->filterSize);
			Matrix<double> weightMomentums(this->filterSize, this->filterSize);
			Matrix<double> weightVelocities(this->filterSize, this->filterSize);
			Long k = 0;
			while (k < this->filterSize) {
				Long l = 0;
				while (l < this->filterSize) {
					double weight;
					*fs >> weight;
					weights.Store(k, l, weight);
					l++;
				}
				k++;
			}

			k = 0;
			while (k < this->filterSize) {
				Long l = 0;
				while (l < this->filterSize) {
					double momentum;
					*fs >> momentum;
					weightMomentums.Store(k, l, momentum);
					l++;
				}
				k++;
			}

			k = 0;
			while (k < this->filterSize) {
				Long l = 0;
				while (l < this->filterSize) {
					double velocity;
					*fs >> velocity;
					weightVelocities.Store(k, l, velocity);
					l++;
				}
				k++;
			}

			Neuron *convolutionFilter = new ConvolutionFilter(this->filterSize, weights, weightMomentums, weightVelocities);
			filterCube->Add(convolutionFilter);
			j++;
		}
		this->Add(filterCube);
		i++;
	}
	return this->length;
}

Neuron* Convolution::Clone() {
	return new Convolution(*this);
}

void Convolution::MakeFilters(Long channel, Long filterCount, double deviation) {
	unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
	default_random_engine e(seed);
	this->deviation = deviation;
	normal_distribution<double> distrN(0.0, deviation);
	this->channelCount = channel;

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
	this->neurons.Resize(filterCount);
	this->capacity = filterCount;
	this->length = 0;

	i = 0;
	while (i < filterCount) //필터큐브의 개수만큼 반복한다.
	{
		Neuron *filterCube = new FilterCube(channel); //채널 개수만큼 필터를 가지는 필터큐브를 생성한다.

		Long j = 0;
		while (j < channel) //필터개수만큼 반복한다.
		{
			Matrix<double> weights(this->filterSize, this->filterSize); //n*n 가중치 행렬을 만든다.
			Matrix<double> weightMomentums(this->filterSize, this->filterSize);
			Matrix<double> weightVelocities(this->filterSize, this->filterSize);
			Long k = 0;
			while (k < weights.GetCapacity()) //n*n만큼 반복한다.
			{
				weights.Store(k, distrN(e)); //난수를 행렬에 넣는다.
				weightMomentums.Store(k, 0.0);
				weightVelocities.Store(k, 0.0);
				k++;
			}

			double bias = 0.0;
			Neuron *filter = new ConvolutionFilter(filterSize, weights, weightMomentums, weightVelocities);
			filterCube->Add(filter);

			j++;
		}

		this->Add(filterCube);
		i++;
	}
}

string Convolution::GetType() {
	return "Conv";
}

Convolution& Convolution::operator=(const Convolution& source) {
	Layer::operator=(source);
	this->pad = source.pad;
	this->stride = source.stride;
	this->filterSize = source.filterSize;
	this->channelCount = source.channelCount;
	this->deviation = source.deviation;

	return *this;
}
