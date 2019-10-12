#include "ConvolutionFilter.h"
#if !defined(_AFXDLL)
#include <crtdbg.h>
#if defined(DEBUG) |defined(_DEBUG)
#if !defined(DEBUG_NEW)
#define DEBUG_NEW new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif
#endif
#endif
ConvolutionFilter::ConvolutionFilter() {
	this->size = 3;
	this->resultsSize = 0;
}

ConvolutionFilter::ConvolutionFilter(Long size, Matrix<double>& weights, Matrix<double>& weightMomentums, Matrix<double>& weightVelocities)
	: weights(weights), weightGradients(weights), weightMomentums(weightMomentums), weightVelocities(weightVelocities) {
	this->size = size;
	this->resultsSize = 0;
}

ConvolutionFilter::ConvolutionFilter(const ConvolutionFilter& source)
	: weights(source.weights), results(source.results), weightGradients(source.weightGradients),
	weightMomentums(source.weightMomentums), weightVelocities(source.weightVelocities) {
	this->size = source.size;
	this->resultsSize = source.resultsSize;
}

ConvolutionFilter::~ConvolutionFilter() {

}

Matrix<double> ConvolutionFilter::Flow(Matrix<double>& inputs, Long stride) {
	Long i;
	Long j;
	Long k;
	Long l;

	Long resultRow = (inputs.GetRow() - this->size) / stride + 1;
	Long resultColumn = (inputs.GetColumn() - this->size) / stride + 1;
	this->results = Matrix<double>(resultRow, resultColumn);
	this->resultsSize = this->results.GetRow();
	double output;

	// 1. 필터링 할 위치가 입력행렬 행 범위에 맞는동안 반복한다.
	i = 0;
	while (i < results.GetRow()) {
		j = 0;
		//  1.1. 필터링 할 위치가 입력행렬 열 범위에 맞는 동안 반복한다.
		while (j < results.GetColumn()) {
			//   1.1.1. 필터 행 수만큼 반복한다. 
			output = 0.0;
			k = 0;
			while (k < this->size) {
				//    1.1.1.1 필터 열 수만큼 반복한다.
				l = 0;
				while (l < this->size) {
					// 1.1.1.1.1. 두 개의 수를 곱한다.
					// 1.1.1.1.2. 합을 구한다.
					output += this->weights.GetAt(k, l) * inputs.GetAt(k + i, l + j);
					l++;
				}
				//   1.1.2. 결과 행렬에 적는다.
				k++;
			}
			//   1.1.3. 스트라이드만큼 우측으로 이동한다.
			results.Store(i, j, output);
			j += stride;
		}
		//  1.2. 스트라이드만큼 아래로 이동한다.
		i += stride;
	}

	return this->results;
}

Matrix<double> ConvolutionFilter::BackFlow(Matrix<double>& inputs, Matrix<double>& gradients, Long stride, Long pad) {
	Long i;
	Long j;
	Long k;
	Long l;
	Matrix<double> processingInputs(inputs.AddPadding(pad));

	//필터 가중치 기울기 구하기
	double weightGradient;
	// 1. 필터 사이즈만큼 반복한다.
	i = 0;
	while (i < this->size) {
		j = 0;
		//  1.1. 필터 사이즈만큼 반복한다.
		while (j < this->size) {
			//   1.1.1. 기울기 사이즈만큼 반복한다. 
			weightGradient = 0.0;
			k = 0;
			while (k < gradients.GetRow()) {
				//    1.1.1.1 기울기 사이즈만큼 반복한다.
				l = 0;
				while (l < gradients.GetColumn()) {
					// 1.1.1.1.1. 두 개의 수를 곱한다.
					// 1.1.1.1.2. 합을 구한다.
					weightGradient += processingInputs.GetAt(k + i, l + j) * gradients.GetAt(k, l);
					l++;
				}
				k++;
			}
			//   1.1.2. 필터 기울기 행렬에 적는다.
			this->weightGradients.Modify(i / stride, j / stride, weightGradient);
			//   1.1.3. 스트라이드만큼 우측으로 이동한다.
			j += stride;
		}
		//  1.2. 스트라이드만큼 아래로 이동한다.
		i += stride;
	}

	//입력값에 대한 기울기 구하기

	//2. 원래 필터 가중치를 뒤집다.
	Matrix<double> reversedWeights(this->weights.Reverse());
	Matrix<double> processingMatrix(gradients);

	//3. 역전파 신호행렬을 가공하다.
	Long subSize = this->size - 1 - pad;
	if (subSize > 0) {
		processingMatrix = gradients.AddPadding(subSize);
	}
	else if (subSize < 0) {
		processingMatrix = gradients.CutEdge(-subSize);
	}

	Matrix<double> inputGradients(inputs.GetRow(), inputs.GetColumn());
	double inputGradient;
	//3. 기울기 사이즈만큼 반복한다.
	i = 0;
	while (i < inputGradients.GetRow()) {
		//3.1. 기울기 사이즈만큼 반복한다.
		j = 0;
		while (j < inputGradients.GetColumn()) {
			//3.1.1. 필터 사이즈만큼 반복한다.
			inputGradient = 0.0;
			k = 0;
			while (k < this->size) {
				//3.1.1.1. 필터사이즈만큼 반복한다.
				l = 0;
				while (l < this->size) {
					//3.1.1.1.1. 입력기울기를 구한다.
					inputGradient += processingMatrix.GetAt(k + i, l + j) * reversedWeights.GetAt(k, l);
					l++;
				}
				k++;
			}
			//3.1.2. 입력기울기 행렬에 적는다.
			inputGradients.Store(i, j, inputGradient);
			//3.1.3. 스트라이드만큼 이동한다.
			j += stride;
		}
		//3.2. 스트라이드만큼 이동한다.
		i += stride;
	}
	return inputGradients;
}

Matrix<double> ConvolutionFilter::BatchBackFlow(Matrix<double>& inputs, Matrix<double>& gradients, Long stride, Long pad) {
	Long i;
	Long j;
	Long k;
	Long l;
	Matrix<double> processingInputs(inputs.AddPadding(pad));

	//입력값에 대한 기울기 구하기

	//2. 원래 필터 가중치를 뒤집다.
	Matrix<double> reversedWeights(this->weights.Reverse());
	Matrix<double> processingMatrix(gradients);

	//3. 역전파 신호행렬을 가공하다.
	Long subSize = this->size - 1 - pad;
	if (subSize > 0) {
		processingMatrix = gradients.AddPadding(subSize);
	}
	else if (subSize < 0) {
		processingMatrix = gradients.CutEdge(-subSize);
	}

	Matrix<double> inputGradients(inputs.GetRow(), inputs.GetColumn());
	double inputGradient;
	//3. 기울기 사이즈만큼 반복한다.
	i = 0;
	while (i < inputGradients.GetRow()) {
		//3.1. 기울기 사이즈만큼 반복한다.
		j = 0;
		while (j < inputGradients.GetColumn()) {
			//3.1.1. 필터 사이즈만큼 반복한다.
			inputGradient = 0.0;
			k = 0;
			while (k < this->size) {
				//3.1.1.1. 필터사이즈만큼 반복한다.
				l = 0;
				while (l < this->size) {
					//3.1.1.1.1. 입력기울기를 구한다.
					inputGradient += processingMatrix.GetAt(k + i, l + j) * reversedWeights.GetAt(k, l);
					l++;
				}
				k++;
			}
			//3.1.2. 입력기울기 행렬에 적는다.
			inputGradients.Store(i, j, inputGradient);
			//3.1.3. 스트라이드만큼 이동한다.
			j += stride;
		}
		//3.2. 스트라이드만큼 이동한다.
		i += stride;
	}

	return inputGradients;
}

void ConvolutionFilter::BatchBackFlow(Array<Matrix<double>>& inputs, Array<Matrix<double>>& gradients, Long stride, Long pad) {
	//매개변수 설명
	//inputs : 해당 필터와 관련 있는(동일한 채널인) 입력값 행렬이 배치크기만큼 모인 배열
	//gradients : 해당 필터와 관련 있는(동일 번째의) 기울기 행렬이 배치크기만큼 모인 배열

	Long batch = inputs.GetLength(); //배치 크기

	Long i = 0;
	while (i<this->weightGradients.GetLength()) {
		this->weightGradients.Modify(i, 0.0);
		i++;
	}

	Long indexOfBatch = 0;
	while (indexOfBatch < batch) {
		Matrix<double> gradientsPerBatch(gradients.GetAt(indexOfBatch)); //해당 필터와 관련 있는 n번째 기울기 행렬
		Matrix<double> processingInputs(inputs.GetAt(indexOfBatch).AddPadding(pad)); //입력값 행렬에 패딩적용
		Matrix<double> weightGradientsPerBatch(this->weightGradients); //가중치기울기를 누적시켜야 하기 때문에 넣은 가중치기울기행렬과 크기가 동일한 행렬

		//필터 가중치 기울기 구하기
		double weightGradient;
		// 1. 필터 사이즈만큼 반복한다.
		Long i = 0;
		while (i < this->size) {
			Long j = 0;
			//  1.1. 필터 사이즈만큼 반복한다.
			while (j < this->size) {
				//   1.1.1. 기울기 사이즈만큼 반복한다. 
				weightGradient = 0.0;
				Long k = 0;
				while (k < gradientsPerBatch.GetRow()) {
					//    1.1.1.1 기울기 사이즈만큼 반복한다.
					Long l = 0;
					while (l < gradientsPerBatch.GetColumn()) {
						// 1.1.1.1.1. 두 개의 수를 곱한다.
						// 1.1.1.1.2. 합을 구한다.
						weightGradient += processingInputs.GetAt(k + i, l + j) * gradientsPerBatch.GetAt(k, l);
						l++;
					}
					k++;
				}
				//   1.1.2. 필터 기울기 행렬에 적는다.
				weightGradientsPerBatch.Modify(i / stride, j / stride, weightGradient);
				//   1.1.3. 스트라이드만큼 우측으로 이동한다.
				j += stride;
			}
			//  1.2. 스트라이드만큼 아래로 이동한다.
			i += stride;
		}
		this->weightGradients.Plus(weightGradientsPerBatch); //속성 가중치기울기행렬을 배치별로 구한 가중치 기울기 행렬을 누적시킨다.
		indexOfBatch++;
	}
}

void ConvolutionFilter::Update(double learningRate) {
	this->weights = this->weights - (this->weightGradients * learningRate);
}

void ConvolutionFilter::Update(double updatedLearningRate, double beta1, double beta2) {
	double weightMomentum;
	double weightVelocity;
	double weight;
	Long length = this->size * this->size;
	Long i = 0;
	while (i < length) {
		weightMomentum = this->weightMomentums[i] + (1 - beta1) * (this->weightGradients[i] - this->weightMomentums[i]);
		this->weightMomentums.Modify(i, weightMomentum);
		weightVelocity = this->weightVelocities[i] + (1 - beta2) * (pow(this->weightGradients[i], 2) - this->weightVelocities[i]);
		this->weightVelocities.Modify(i, weightVelocity);
		weight = this->weights[i] - (updatedLearningRate * this->weightMomentums[i] / (sqrt(this->weightVelocities[i]) + 1e-7));
		this->weights.Modify(i, weight);
		i++;
	}
}

Neuron* ConvolutionFilter::Clone() {
	return new ConvolutionFilter(*this);
}

ConvolutionFilter& ConvolutionFilter::operator =(const ConvolutionFilter& source) {
	Neuron::operator =(source);
	this->weights = source.weights;
	this->size = source.size;
	this->results = source.results;
	this->resultsSize = source.resultsSize;
	this->weightGradients = source.weightGradients;
	this->weightMomentums = source.weightMomentums;
	this->weightVelocities = source.weightVelocities;

	return *this;
}