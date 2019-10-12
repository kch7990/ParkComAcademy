#include "Recognizer.h"
#include "RecognizingForm.h"
#include "LabelFile.h"
#include "ImageFile.h"
#include "NeuronForm.h"
#include "NeuralNetwork.h"
#include "Softmax.h"
#include "GraphFactory.h"
#include "CoordinateSystem.h"
#include "LearningForm.h"
#include "RoundRectangle.h"

#include "Point.h"
#include <ctime>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include <chrono>
#include <random>

Recognizer::Recognizer(RecognizingForm *recognizingForm) {
	this->recognizingForm = recognizingForm;
	this->thread = NULL;
	this->isRecognizing = FALSE;
}

Recognizer::Recognizer(const Recognizer& source) {
	this->recognizingForm = source.recognizingForm;
	this->thread = source.thread;
}

Recognizer::~Recognizer() {
	this->isRecognizing = FALSE;
	if (this->thread != NULL) {
		::WaitForSingleObject(this->thread->m_hThread, INFINITE);
	}
}

void Recognizer::Recognize() {
	unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	uniform_int_distribution<int> distribution(0, 9999);
	Long randomNumber;

	//1. 이미지를 임의로 mnist에서 가져온다.
	randomNumber = distribution(generator);
	this->recognizingForm->index = randomNumber;
	this->recognizingForm->image = this->recognizingForm->imageFile.GetAt(randomNumber, false);
	Array<double> signals(this->recognizingForm->image);
	Long i = 0;
	while (i < signals.GetCapacity()) {
		signals.Modify(i, this->recognizingForm->image[i] / 255.0);
		i++;
	}
	this->recognizingForm->label = this->recognizingForm->labelFile.GetAt(randomNumber);
	//2. 추론하다 폼의 뉴런폼의 신경망에서 추론하다.
	//3. 추론하다 폼의 결과들에 적는다.(정답 개수, 틀린 개수, 개수, 정확도), (추론한 숫자, 결과, 정답 숫자, 소프트맥스 값)
	this->recognizingForm->results = this->recognizingForm->neuronForm->neuralNetwork->Recognize(signals, false);
	this->recognizingForm->recognizingNumber = this->recognizingForm->results.Max(Compare);

	this->recognizingForm->recognizationResult.count++;
	if (this->recognizingForm->label == this->recognizingForm->recognizingNumber) {
		this->recognizingForm->recognizationResult.answerCount++;
	}
	else {
		this->recognizingForm->recognizationResult.wrongAnswerCount++;
	}
	this->recognizingForm->recognizationResult.accuracy = this->recognizingForm->recognizationResult.answerCount /
		(this->recognizingForm->recognizationResult.count * 1.0);

	//5. 추론하다 폼을 갱신하다.
	this->recognizingForm->Invalidate();
}

void Recognizer::AutoRecognize() {
	//1. 스레드를 만든다.
	//2. 스레드를 실행한다.
	this->isRecognizing = TRUE;
	this->recognizingForm->neuronForm->isWorking = TRUE;
	this->thread = AfxBeginThread(AutoRecognizeThread, (LPVOID)this);
}

void Recognizer::Recognize(Array<double>& signals) {
	this->recognizingForm->results = this->recognizingForm->neuronForm->neuralNetwork->Recognize(signals, false);
	this->recognizingForm->recognizingNumber = this->recognizingForm->results.Max(Compare);
	this->recognizingForm->Invalidate();
}

void Recognizer::Stop() {
	this->isRecognizing = FALSE;
	this->recognizingForm->neuronForm->isWorking = FALSE;
	if (this->thread != NULL) {
		::WaitForSingleObject(this->thread->m_hThread, 1000);
	}
}

UINT Recognizer::AutoRecognizeThread(LPVOID pParam) {
	Recognizer *recognizer = (Recognizer*)pParam;
	RecognizingForm *recognizingForm = recognizer->recognizingForm;
	GraphFactory graphFactory;
	Graph *accuracyCoordinateSystem = recognizingForm->neuronForm->learningForm->accuracyCoordinateSystem;
	Graph *lossCoordinateSystem = recognizingForm->neuronForm->learningForm->lossCoordinateSystem;
	Array<double> signals(recognizingForm->imageFile.GetImageSize());
	Long k = 0;
	while (k < signals.GetCapacity()) {
		signals.Store(k, 0.0);
		k++;
	}
	Array<double> zeros(10);
	k = 0;
	while (k < zeros.GetCapacity()) {
		zeros.Store(k, 0.0);
		k++;
	}

	//1. 이미지를 mnist에서 가져온다.
	Long i = 0;
	while (i < 10000) {
		recognizingForm->index = i;
		recognizingForm->image = recognizingForm->imageFile.GetAt(i, false);
		Long j = 0;
		while (j < signals.GetLength()) {
			signals.Modify(j, recognizingForm->image[j] / 255.0);
			j++;
		}
		recognizingForm->label = recognizingForm->labelFile.GetAt(i);

		//2. 추론하다 폼의 뉴런폼의 신경망에서 추론하다.
		//3. 추론하다 폼의 결과들에 적는다.(정답 개수, 틀린 개수, 개수, 정확도), (추론한 숫자, 결과, 정답 숫자, 소프트맥스 값)
		recognizingForm->results = recognizingForm->neuronForm->neuralNetwork->Recognize(signals, false);
		recognizingForm->recognizingNumber = recognizingForm->results.Max(Compare);

		recognizingForm->recognizationResult.count++;
		if (recognizingForm->label == recognizingForm->recognizingNumber) {
			recognizingForm->recognizationResult.answerCount++;
		}
		else {
			recognizingForm->recognizationResult.wrongAnswerCount++;
		}
		recognizingForm->recognizationResult.accuracy = recognizingForm->recognizationResult.answerCount /
			(recognizingForm->recognizationResult.count * 1.0);

		if (recognizer->isRecognizing == FALSE) {
			return 0;
		}

		//5. 추론하다 폼을 갱신하다.
		recognizingForm->Invalidate();

		if ((i + 1) % 10 == 0) {
			Array<double> targets(zeros);
			targets.Modify(recognizingForm->label, 1.0);
			double loss = recognizingForm->neuronForm->neuralNetwork->GetCrossEntropy(recognizingForm->results, targets);
			//  7.1. 학습폼의 그래프의 점을 만들다.(정확도 및, 손실함수 값)
			//  7.2. 학습폼의 그래프의 넣다.
			// 정확도 점 생성
			Graph *point = graphFactory.Make(GRAPH_POINT);
			double x = dynamic_cast<CoordinateSystem*>(accuracyCoordinateSystem)->GetOriginX() + (i + 1) *
				dynamic_cast<CoordinateSystem*>(accuracyCoordinateSystem)->GetMagnificationX();
			double y = dynamic_cast<CoordinateSystem*>(accuracyCoordinateSystem)->GetOriginY() - recognizingForm->recognizationResult.accuracy *
				dynamic_cast<CoordinateSystem*>(accuracyCoordinateSystem)->GetMagnificationY();
			*dynamic_cast<Point*>(point) = Point(x, y, RGB(0, 0, 0));
			accuracyCoordinateSystem->Add(point);
			// 손실함수 점 생성
			point = graphFactory.Make(GRAPH_POINT);
			x = dynamic_cast<CoordinateSystem*>(lossCoordinateSystem)->GetOriginX() + (i + 1) *
				dynamic_cast<CoordinateSystem*>(lossCoordinateSystem)->GetMagnificationX();
			y = dynamic_cast<CoordinateSystem*>(lossCoordinateSystem)->GetOriginY() - loss *
				dynamic_cast<CoordinateSystem*>(lossCoordinateSystem)->GetMagnificationY();
			*dynamic_cast<Point*>(point) = Point(x, y, RGB(0, 0, 0));
			lossCoordinateSystem->Add(point);

			// 7.3. 학습 폼을 갱신하다.
			recognizingForm->neuronForm->learningForm->Invalidate();
		}

		Sleep(100);
		i++;
	}

	//추론 스레드 끝날때 시작 버튼 만들기
	recognizer->recognizingForm->neuronForm->learningForm->startButton = new RoundRectangle(CRect(600, 740, 700, 780), "학습 시작", RGB(0, 0, 255), false);
	recognizer->recognizingForm->neuronForm->isWorking = FALSE;

	return 0;
}

Recognizer& Recognizer::operator=(const Recognizer& source) {
	this->recognizingForm = source.recognizingForm;
	this->thread = source.thread;
	return *this;
}