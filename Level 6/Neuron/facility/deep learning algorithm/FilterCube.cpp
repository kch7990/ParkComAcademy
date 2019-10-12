#include "FilterCube.h"
#include "ConvolutionFilter.h"
#include "Matrix.h"
#include <cmath>
#if !defined(_AFXDLL)

#include <crtdbg.h>
#if defined(DEBUG) |defined(_DEBUG)
#if !defined(DEBUG_NEW)
#define DEBUG_NEW new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif
#endif
#endif
FilterCube::FilterCube(Long capacity, double bias, double biasMomentum, double biasVelocity)
	: CompositeNeuron(capacity) {
	this->bias = bias;
	this->biasGradient = 0;
	this->biasMomentum = biasMomentum;
	this->biasVelocity = biasVelocity;
}

FilterCube::FilterCube(const FilterCube& source)
	: CompositeNeuron(source) {
	this->bias = source.bias;
	this->biasGradient = source.biasGradient;
	this->biasMomentum = source.biasMomentum;
	this->biasVelocity = source.biasVelocity;
}

FilterCube::~FilterCube() {

}

Array<double> FilterCube::Flow(Array<double>& inputs, Long inputsSize, Long stride, Long pad) {
	Long inputChannel = this->length;
	Long inputWidth = sqrt((double)inputs.GetLength() / inputChannel);
	Long length = pow((double)((inputsSize + pad * 2) - dynamic_cast<ConvolutionFilter*>(this->GetAt(0))->GetSize()) / stride + 1, 2);

	Array<double> results(length);
	Long i = 0;
	while (i < length) {
		results.Store(i, 0.0);
		i++;
	}

	Long k = 0;
	i = 0;
	while (i < inputChannel) {
		Matrix<double> inputsMatrix(inputWidth + pad * 2, inputWidth + pad * 2);
		Long j = 0;
		while (j < inputsMatrix.GetRow())
		{
			Long l = 0;
			while (l < inputsMatrix.GetColumn()) {
				if ((j >= pad && j < pad + inputWidth) && (l >= pad && l < pad + inputWidth)) {
					inputsMatrix.Store(j, l, inputs[k++]);
				}
				else {
					inputsMatrix.Store(j, l, 0);
				}
				l++;
			}
			j++;
		}

		Matrix<double> outputs((dynamic_cast<ConvolutionFilter*>(this->neurons[i]))->Flow(inputsMatrix, stride));
		j = 0;
		while (j < outputs.GetLength()) {
			results[j] = results[j] + outputs[j];
			j++;
		}
		i++;
	}
	i = 0;
	while (i < results.GetLength()) {
		results[i] += this->bias;
		i++;
	}

	return results;
}

Array<double> FilterCube::BackFlow(Array<double>& inputs, Array<double>& signals, Long stride, Long pad) {
	Array<double> results(inputs.GetLength());
	Matrix<double> resultMatrix;
	Long inputWidth = static_cast<Long>(sqrt(inputs.GetLength() / this->length));
	// 인풋에 너비 = 루트(inputs길이/채널 수) 
	Long indexOfInputs = 0;
	Long indexOfReulsts = 0;

	Long signalWidth = static_cast<Long>(sqrt(signals.GetLength()));
	Matrix<double>signalMatrix(signalWidth, signalWidth);


	//1. inputs, 기울기 일부 입력받는다.
	Long i = 0;
	//2. 역전파 신호를 행렬로 변환하다.
	while (i < signals.GetLength()) {
		signalMatrix.Store(i, signals[i]);
		i++;
	}

	i = 0;
	Long j;
	while (i < this->length) {//3. 필터 개수만큼 반복한다.
		 //3.1. inputs를 나눈다( 필터 개수만큼)
		 //3.2. 나눈 input를 행렬로 만든다.
		Matrix<double> inputMatrix(inputWidth, inputWidth);
		j = 0;
		while (j < inputWidth* inputWidth) {
			inputMatrix.Store(j, inputs[indexOfInputs++]);
			j++;
		}

		//3.3. Filter 별로 BackFlow하다.
		resultMatrix = dynamic_cast<ConvolutionFilter*>(this->neurons[i])->BackFlow(inputMatrix, signalMatrix, stride, pad);
		j = 0;
		while (j < resultMatrix.GetLength()) {
			results.Store(indexOfReulsts++, resultMatrix.GetAt(j));
			j++;
		}
		//3.4. 결과배열에 기록하다.
		i++;
	}

	//4. 편향 기울기를 구하다.
	this->biasGradient = 0;
	i = 0;
	while (i < signals.GetLength()) {
		this->biasGradient += signals[i];
		i++;
	}
	//4. 결과배열을 출력하다.
	return results;
	//5. 끝내다.
}

Array<double> FilterCube::BatchBackFlow(Array<double>& inputs, Array<double>& signals, Long stride, Long pad) {
	Array<double> results(inputs.GetLength());
	Matrix<double> resultMatrix;
	Long inputWidth = static_cast<Long>(sqrt(inputs.GetLength() / this->length));
	// 인풋에 너비 = 루트(inputs길이/채널 수) 
	Long indexOfInputs = 0;
	Long indexOfReulsts = 0;

	Long signalWidth = static_cast<Long>(sqrt(signals.GetLength()));
	Matrix<double>signalMatrix(signalWidth, signalWidth);


	//1. inputs, 기울기 일부 입력받는다.
	Long i = 0;
	//2. 역전파 신호를 행렬로 변환하다.
	while (i < signals.GetLength()) {
		signalMatrix.Store(i, signals[i]);
		i++;
	}

	i = 0;
	Long j;
	while (i < this->length) {//3. 필터 개수만큼 반복한다.
		 //3.1. inputs를 나눈다( 필터 개수만큼)
		 //3.2. 나눈 input를 행렬로 만든다.
		Matrix<double> inputMatrix(inputWidth, inputWidth);
		j = 0;
		while (j < inputWidth* inputWidth) {
			inputMatrix.Store(j, inputs[indexOfInputs++]);
			j++;
		}

		//3.3. Filter 별로 BackFlow하다.
		resultMatrix = dynamic_cast<ConvolutionFilter*>(this->neurons[i])->BatchBackFlow(inputMatrix, signalMatrix, stride, pad);
		j = 0;
		while (j < resultMatrix.GetLength()) {
			results.Store(indexOfReulsts++, resultMatrix.GetAt(j));
			j++;
		}
		//3.4. 결과배열에 기록하다.
		i++;
	}

	//4. 결과배열을 출력하다.
	return results;
	//5. 끝내다.
}

void FilterCube::BatchBackFlow(Array<Array<double>>& inputs, Array<Array<double>>& signals, Long stride, Long pad) {
	Long batch = inputs.GetLength(); //배치 크기

	//배열의 배열 signals를 행렬의 배열로 만들기
	Array<Matrix<double>> signalsOfFilter(batch); //필터의 BatchBackFlow의 매개변수 만들기 : 배열의 배열 -> 행렬의 배열
	Long i = 0;
	while (i < signals.GetLength()) { //배치 크기만큼 반복한다.
		Array<double> signalsPerBatch = signals.GetAt(i); //해당 필터큐브와 관련 있는(동일한 번째의) 기울기 배열
		Matrix<double> signalsMatrixPerBatch(sqrt(signalsPerBatch.GetLength()), sqrt(signalsPerBatch.GetLength())); //위의 기울기 배열을 변환할 행렬
		Long j = 0;
		while (j < signalsPerBatch.GetLength()) { //배열의 크기만큼 반복한다.
			signalsMatrixPerBatch.Store(j, signalsPerBatch[j]); //행렬에 배열의 요소들을 모두 넣는다.
			j++;
		}
		signalsOfFilter.Store(i, signalsMatrixPerBatch); //행렬을 배열에 모은다.
		i++;
	}

	//필터 개수만큼 반복한다.
	i = 0;
	while (i < this->length) {
		//현재 번째 inputs를 추려 각각 행렬로 만든 후 배열로 묶기
		Array<Matrix<double>> inputsOfFilter(batch);
		Long j = 0;
		while (j < batch) { //배치만큼 반복한다.
			Array<double> inputsArrayPerBatch = inputs.GetAt(j); //배치별로 나눴으나 채널별로는 통합돼있음
			Long matrixLength = inputsArrayPerBatch.GetLength() / this->length; //행렬 길이 = 배치별로 나눈 입력값 배열의 크기 / 필터개수(채널 수)
			Matrix<double> inputsMatrixPerBatch(sqrt(matrixLength), sqrt(matrixLength)); //변환할 행렬
			//현재 번째 inputs만 추리기 위한 첨자 : 배치별로 나뉘어져 있지만 채널별로는 통합되어있는 배열에서 채널별로 값을 가져올 수 있게 시작지점을 정함
			Long l = i * matrixLength;
			Long k = 0;
			while (k < matrixLength) {
				inputsMatrixPerBatch.Store(k, inputsArrayPerBatch[l++]); //채널별 통합된 배열에서 채널별로 나눔과 동시에 행렬로 변환한다.
				k++;
			}
			inputsOfFilter.Store(j, inputsMatrixPerBatch); //행렬을 배열로 모은다.
			j++;
		}
		//필터에서 역전파 : 가중치 기울기만 구함
		dynamic_cast<ConvolutionFilter*>(this->neurons[i])->BatchBackFlow(inputsOfFilter, signalsOfFilter, stride, pad);

		i++;
	}

	// 편향 기울기를 구하다. : 매개변수 signals는 배치별로 해당 필터큐브와 번째가 같으므로 그것을 모두 더한 것이 해당 필터큐브의 편향 기울기가 된다.
	this->biasGradient = 0;
	i = 0;
	while (i < signals.GetLength()) {
		Array<double> signalsPerBatch = signals.GetAt(i);
		Long j = 0;
		while (j < signalsPerBatch.GetLength()) {
			this->biasGradient += signalsPerBatch[j];
			j++;
		}
		i++;
	}
}

void FilterCube::Update(double learningRate) {
	Long i = 0;
	while (i < this->length) {
		this->neurons[i]->Update(learningRate);
		i++;
	}
	this->bias -= learningRate * this->biasGradient;
}

void FilterCube::Update(double updatedLearningRate, double beta1, double beta2) {
	Long i = 0;
	while (i < this->length) {
		this->neurons[i]->Update(updatedLearningRate, beta1, beta2);
		i++;
	}
	this->biasMomentum += (1 - beta1) * (this->biasGradient - this->biasMomentum);
	this->biasVelocity += (1 - beta2) * (pow(this->biasGradient, 2) - this->biasVelocity);
	this->bias -= (updatedLearningRate * this->biasMomentum / (sqrt(this->biasVelocity) + 1e-7));
}

FilterCube& FilterCube::operator =(const FilterCube& source) {
	CompositeNeuron::operator =(source);
	this->bias = source.bias;
	this->biasGradient = source.biasGradient;
	this->biasMomentum = source.biasMomentum;
	this->biasVelocity = source.biasVelocity;

	return *this;
}

Neuron* FilterCube::Clone() {
	return new FilterCube(*this);
}