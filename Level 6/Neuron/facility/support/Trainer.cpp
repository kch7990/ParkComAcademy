#include "Trainer.h"
#include "LabelFile.h"
#include "ImageFile.h"
#include "Array.h"
#include "LearningForm.h"
#include "NeuronForm.h"
#include "Neuron.h"
#include "Softmax.h"
#include "GraphFactory.h"
#include "Graph.h"
#include "RoundRectangle.h"
#include "CoordinateSystem.h"
#include "Point.h"
#include "GraphMaker.h"
#include "NeuralNetwork.h"
#include "RecognizingForm.h"
#include "Texts.h"
#include "resource.h"
#include "Icon.h"
#include "Circle.h"
#include "Cross.h"
#include <afxcmn.h>
#include <chrono>
#include <random>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
Trainer::Trainer(LearningForm *learningForm) {
	this->learningForm = learningForm;
	this->thread = NULL;
	this->repeatCount = 0;
	this->learningRate = 0.0;
	this->beta1 = 0.0;
	this->beta2 = 0.0;
	this->isTraining = FALSE;
	this->isPausing = FALSE;
}

Trainer::Trainer(const Trainer& source) {
	this->learningForm = source.learningForm;
	this->thread = source.thread;
	this->repeatCount = source.repeatCount;
	this->learningRate = source.learningRate;
	this->beta1 = source.beta1;
	this->beta2 = source.beta2;
	this->isTraining = source.isTraining;
	this->isPausing = source.isPausing;
}

Trainer::~Trainer() {
	this->isTraining = FALSE;
	if (this->thread != NULL) {
		//DWORD ret;
		//::GetExitCodeThread(this->thread->m_hThread, &ret);
		if (this->isPausing == TRUE) {
			this->thread->ResumeThread();
		}
		::WaitForSingleObject(this->thread->m_hThread, INFINITE);
	}
}

void Trainer::Train(Long batchSize, Long repeatCount, double learningRate) {
	this->isTraining = TRUE;
	this->learningForm->neuronForm->isWorking = TRUE;
	this->batchSize = batchSize;
	this->repeatCount = repeatCount;
	this->learningRate = learningRate;
	
	this->learningForm->progressBar.SetPos(0);
	this->thread = AfxBeginThread(TrainForSGDThread, (LPVOID)this);

}

void Trainer::Train(Long batchSize, Long repeatCount, double learningRate, double beta1, double beta2) {
	this->isTraining = TRUE;
	this->learningForm->neuronForm->isWorking = TRUE;
	this->batchSize = batchSize;
	this->repeatCount = repeatCount;
	this->learningRate = learningRate;
	this->beta1 = beta1;
	this->beta2 = beta2;
	
	this->learningForm->progressBar.SetPos(0);
	this->thread = AfxBeginThread(TrainForAdamThread, (LPVOID)this);

}

void Trainer::Pause() {
	this->isTraining = FALSE;
	this->learningForm->neuronForm->isWorking = FALSE;
	this->isPausing = TRUE;
	this->thread->SuspendThread();
}

void Trainer::Resume() {
	this->isTraining = TRUE;
	this->learningForm->neuronForm->isWorking = TRUE;
	this->isPausing = FALSE;
	this->thread->ResumeThread();
}

void Trainer::End() {
	this->isTraining = FALSE;
	this->learningForm->neuronForm->isWorking = FALSE;
	if (this->thread != NULL) {
		DWORD ret;
		if (this->isPausing == TRUE) {
			this->thread->ResumeThread();
		}
		::WaitForSingleObject(this->thread->m_hThread, 1000);
	}
	this->isPausing = FALSE;
}

UINT Trainer::TrainForSGDThread(LPVOID pParam) {
	Trainer *trainer = (Trainer*)pParam;
	unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	uniform_int_distribution<int> distribution(0, 59999);
	Long randomNumber;
	ImageFile imageFile("train-images.idx3-ubyte");
	LabelFile labelFile("train-labels.idx1-ubyte");

	ImageFile imageFile2("t10k-images.idx3-ubyte");
	LabelFile labelFile2("t10k-labels.idx1-ubyte");

	imageFile.ReadHeader();
	labelFile.ReadHeader();
	imageFile2.ReadHeader();
	labelFile.ReadHeader();

	RecognizingForm *recognizingForm = trainer->learningForm->neuronForm->recognizingForm;
	Neuron *neuralNetwork = trainer->learningForm->neuronForm->neuralNetwork;

	Graph *accuracyCoordinateSystem = trainer->learningForm->accuracyCoordinateSystem;
	Graph *lossCoordinateSystem = trainer->learningForm->lossCoordinateSystem;

	Long batchSize = trainer->GetBatchSize();
	Long repeatCount = trainer->GetRepeatCount();
	double learningRate = trainer->GetLearningRate();

	Array<double> array(10);
	for (Long i = 0; i < array.GetCapacity(); i++)
	{
		array.Store(i, 0.0);
	}

	//학습폼의 그래프 초기화

	//학습 정보 읽고

	GraphFactory graphFactory;
	Long answerCount = 0;
	double loss = 0.0;

	//뉴런폼의 뉴럴네트워크에서 학습
	Long i = 0;
	while (i < repeatCount) {
		clock_t start;
		clock_t end;
		start = clock();

		Array<Array<double>> signals(batchSize);
		Array<Array<double>> targets(batchSize);
		Long indexOfBatch = 0;
		while (indexOfBatch < batchSize) {
			randomNumber = distribution(generator);
			// 1. 이미지를 읽는다.(정규화)
			// 2. 정답을 읽는다.
			recognizingForm->index = randomNumber;
			recognizingForm->image = imageFile.GetAt(randomNumber, false);

			Array<double> signalsPerBatch(recognizingForm->image);
			for (Long i = 0; i < signalsPerBatch.GetLength(); i++)
			{
				signalsPerBatch.Modify(i, signalsPerBatch[i] / 255.0);
			}
			signals.Store(indexOfBatch, signalsPerBatch);

			Long label = labelFile.GetAt(randomNumber);
			Array<double> targetsPerBatch(array);
			targetsPerBatch.Modify(label, 1.0);
			targets.Store(indexOfBatch, targetsPerBatch);

			indexOfBatch++;
		}
		// 3. 뉴런폼의 신경망에서 추론한다.
		Array<Array<double>> results(neuralNetwork->BatchRecognize(signals, true));
		// 5. 채점하다.
		Long label;
		Long recognizeNumber;
		indexOfBatch = 0;
		while (indexOfBatch < batchSize) {
			recognizeNumber = results[indexOfBatch].Max(Compare);
			label = targets[indexOfBatch][recognizeNumber];
			if (label == 1.0) {
				answerCount++;
			}
			indexOfBatch++;
		}


		// 4. 뉴런폼의 신경망에서 학습한다.
		neuralNetwork->BatchLearn(targets, learningRate);
		// 6. 손실함수 값을 구하다.
		loss = neuralNetwork->GetBatchCrossEntropy(results, targets);

		if (trainer == NULL || trainer->isTraining == FALSE) {
			return 0;
		}

		recognizingForm->label = label;
		recognizingForm->results = results[batchSize - 1];
		recognizingForm->recognizingNumber = recognizeNumber;
		recognizingForm->recognizationResult.count += batchSize;

		/*
		if (recognizingForm->label == recognizingForm->recognizingNumber) {
		   recognizingForm->recognizationResult.answerCount++;
		}
		else {
		   recognizingForm->recognizationResult.wrongAnswerCount++;
		}
		*/
		recognizingForm->recognizationResult.answerCount = answerCount;
		recognizingForm->recognizationResult.wrongAnswerCount = recognizingForm->recognizationResult.count - answerCount;

		recognizingForm->recognizationResult.accuracy = recognizingForm->recognizationResult.answerCount /
			(recognizingForm->recognizationResult.count * 1.0);



		double accuracy = answerCount / ((i + 1)*batchSize*1.0);
		
		//  7.1. 학습폼의 그래프의 점을 만들다.(정확도 및, 손실함수 값)
		//  7.2. 학습폼의 그래프의 넣다.
		// 정확도 점 생성
		Graph *point = graphFactory.Make(GRAPH_POINT);
		double x = dynamic_cast<CoordinateSystem*>(accuracyCoordinateSystem)->GetOriginX() + (i + 1) *
			dynamic_cast<CoordinateSystem*>(accuracyCoordinateSystem)->GetMagnificationX();
		double y = dynamic_cast<CoordinateSystem*>(accuracyCoordinateSystem)->GetOriginY() - accuracy *
			dynamic_cast<CoordinateSystem*>(accuracyCoordinateSystem)->GetMagnificationY();
		*dynamic_cast<Point*>(point) = Point(x + 1, y - 1, RGB(0, 0, 0));
		accuracyCoordinateSystem->Add(point);

		// 손실함수 점 생성
		point = graphFactory.Make(GRAPH_POINT);
		x = dynamic_cast<CoordinateSystem*>(lossCoordinateSystem)->GetOriginX() + (i + 1) *
			dynamic_cast<CoordinateSystem*>(lossCoordinateSystem)->GetMagnificationX();
		y = dynamic_cast<CoordinateSystem*>(lossCoordinateSystem)->GetOriginY() - loss *
			dynamic_cast<CoordinateSystem*>(lossCoordinateSystem)->GetMagnificationY();
		*dynamic_cast<Point*>(point) = Point(x + 1, y - 1, RGB(0, 0, 0));
		lossCoordinateSystem->Add(point);

		// 7.3. 학습 폼을 갱신하다.
		trainer->learningForm->Invalidate();


		trainer->learningForm->progressBar.SetPos(i + 1);
		recognizingForm->Invalidate();
		Sleep(50);


		end = clock();
		double time = (double)(end - start) / CLOCKS_PER_SEC;

		if (time != 0)
		{
			Long remainingTime = time * (repeatCount - (i + 1));
			Long hour = remainingTime / 3600;
			Long remainder = remainingTime % 3600;
			Long min = remainder / 60;
			remainder = remainder % 60;
			Long sec = remainder;

			string timeString = to_string(hour) + "시간 " + to_string(min) + "분 " + to_string(sec) + "초";
			trainer->learningForm->timeText = new HorizontalText(350, 620, timeString, RGB(0, 0, 0));
		}

		i++;
	}

	if (trainer->learningForm->stopButton != NULL) {
		delete trainer->learningForm->stopButton;
		trainer->learningForm->stopButton = NULL;
	}
	trainer->learningForm->startButton = new RoundRectangle(CRect(500, 900, 620, 940), "학습 시작", RGB(0, 0, 255), false);

	recognizingForm->recognizeButton = new Icon(CRect(30, 340, 100, 410), RGB(255, 255, 255), IDB_RECOGNIZE_OFF, false);
	recognizingForm->correctButton = new Circle(CRect(120, 355, 160, 395), RGB(0, 102, 255), false);
	recognizingForm->wrongButton = new Cross(CRect(190, 355, 230, 395), RGB(255, 0, 102), false);

	trainer->isTraining = FALSE;
	trainer->learningForm->neuronForm->isWorking = FALSE;
	trainer->learningForm->progressBar.ShowWindow(SW_HIDE);
	trainer->learningForm->Invalidate();
	recognizingForm->Invalidate();

	return 0;
}

UINT Trainer::TrainForAdamThread(LPVOID pParam) {
	Trainer *trainer = (Trainer*)pParam;
	unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	uniform_int_distribution<int> distribution(0, 59999);
	Long randomNumber;
	ImageFile imageFile("train-images.idx3-ubyte");
	LabelFile labelFile("train-labels.idx1-ubyte");

	ImageFile imageFile2("t10k-images.idx3-ubyte");
	LabelFile labelFile2("t10k-labels.idx1-ubyte");

	imageFile.ReadHeader();
	labelFile.ReadHeader();
	imageFile2.ReadHeader();
	labelFile.ReadHeader();
	Neuron *neuralNetwork = trainer->learningForm->neuronForm->neuralNetwork;
	RecognizingForm *recognizingForm = trainer->learningForm->neuronForm->recognizingForm;

	Graph *accuracyCoordinateSystem = trainer->learningForm->accuracyCoordinateSystem;
	Graph *lossCoordinateSystem = trainer->learningForm->lossCoordinateSystem;

	Long batchSize = trainer->GetBatchSize();
	Long repeatCount = trainer->GetRepeatCount();
	double learningRate = trainer->GetLearningRate();
	double beta1 = trainer->GetBeta1();
	double beta2 = trainer->GetBeta2();

	Array<double> array(10);
	for (Long i = 0; i < array.GetCapacity(); i++)
	{
		array.Store(i, 0.0);
	}

	//학습폼의 그래프 초기화

	//학습 정보 읽고

	GraphFactory graphFactory;
	Long answerCount = 0;
	double loss;

	//뉴런폼의 뉴럴네트워크에서 학습
	//뉴런폼의 뉴럴네트워크에서 학습
	Long i = 0;
	while (i < repeatCount) {
		clock_t start;
		clock_t end;
		start = clock();

		Array<Array<double>> signals(batchSize);
		Array<Array<double>> targets(batchSize);
		Long indexOfBatch = 0;
		while (indexOfBatch < batchSize) {
			randomNumber = distribution(generator);
			// 1. 이미지를 읽는다.(정규화)
			// 2. 정답을 읽는다.
			recognizingForm->index = randomNumber;
			recognizingForm->image = imageFile.GetAt(randomNumber, false);

			Array<double> signalsPerBatch(recognizingForm->image);
			for (Long i = 0; i < signalsPerBatch.GetLength(); i++)
			{
				signalsPerBatch.Modify(i, signalsPerBatch[i] / 255.0);
			}
			signals.Store(indexOfBatch, signalsPerBatch);

			Long label = labelFile.GetAt(randomNumber);
			Array<double> targetsPerBatch(array);
			targetsPerBatch.Modify(label, 1.0);
			targets.Store(indexOfBatch, targetsPerBatch);

			indexOfBatch++;
		}
		// 3. 뉴런폼의 신경망에서 추론한다.
		Array<Array<double>> results(neuralNetwork->BatchRecognize(signals, true));
		// 5. 채점하다.
		Long label;
		Long recognizeNumber;
		indexOfBatch = 0;
		while (indexOfBatch < batchSize) {
			recognizeNumber = results[indexOfBatch].Max(Compare);
			label = targets[indexOfBatch][recognizeNumber];
			if (label == 1.0) {
				answerCount++;
			}
			indexOfBatch++;
		}


		// 4. 뉴런폼의 신경망에서 학습한다.
		neuralNetwork->BatchLearn(targets, learningRate, beta1, beta2);
		// 6. 손실함수 값을 구하다.
		loss = neuralNetwork->GetBatchCrossEntropy(results, targets);

		if (trainer == NULL || trainer->isTraining == FALSE) {
			return 0;
		}

		recognizingForm->label = label;
		recognizingForm->results = results[batchSize - 1];
		recognizingForm->recognizingNumber = recognizeNumber;
		recognizingForm->recognizationResult.count += batchSize;

		/*
		if (recognizingForm->label == recognizingForm->recognizingNumber) {
		   recognizingForm->recognizationResult.answerCount++;
		}
		else {
		   recognizingForm->recognizationResult.wrongAnswerCount++;
		}
		*/
		recognizingForm->recognizationResult.answerCount = answerCount;
		recognizingForm->recognizationResult.wrongAnswerCount = recognizingForm->recognizationResult.count - answerCount;

		recognizingForm->recognizationResult.accuracy = recognizingForm->recognizationResult.answerCount /
			(recognizingForm->recognizationResult.count * 1.0);



		double accuracy = answerCount / ((i + 1)*batchSize*1.0);
		//  7.1. 학습폼의 그래프의 점을 만들다.(정확도 및, 손실함수 값)
		//  7.2. 학습폼의 그래프의 넣다.
		// 정확도 점 생성
		Graph *point = graphFactory.Make(GRAPH_POINT);
		double x = dynamic_cast<CoordinateSystem*>(accuracyCoordinateSystem)->GetOriginX() + (i + 1) *
			dynamic_cast<CoordinateSystem*>(accuracyCoordinateSystem)->GetMagnificationX();
		double y = dynamic_cast<CoordinateSystem*>(accuracyCoordinateSystem)->GetOriginY() - accuracy *
			dynamic_cast<CoordinateSystem*>(accuracyCoordinateSystem)->GetMagnificationY();
		*dynamic_cast<Point*>(point) = Point(x + 1, y - 1, RGB(0, 0, 0));
		accuracyCoordinateSystem->Add(point);

		// 손실함수 점 생성
		point = graphFactory.Make(GRAPH_POINT);
		x = dynamic_cast<CoordinateSystem*>(lossCoordinateSystem)->GetOriginX() + (i + 1) *
			dynamic_cast<CoordinateSystem*>(lossCoordinateSystem)->GetMagnificationX();
		y = dynamic_cast<CoordinateSystem*>(lossCoordinateSystem)->GetOriginY() - loss *
			dynamic_cast<CoordinateSystem*>(lossCoordinateSystem)->GetMagnificationY();
		*dynamic_cast<Point*>(point) = Point(x + 1, y - 1, RGB(0, 0, 0));
		lossCoordinateSystem->Add(point);

		// 7.3. 학습 폼을 갱신하다.
		trainer->learningForm->Invalidate();


		trainer->learningForm->progressBar.SetPos(i + 1);
		recognizingForm->Invalidate();
		Sleep(50);

		end = clock();
		double time = (double)(end - start) / CLOCKS_PER_SEC;

		if (time != 0)
		{
			Long remainingTime = time * (repeatCount - (i + 1));
			Long hour = remainingTime / 3600;
			Long remainder = remainingTime % 3600;
			Long min = remainder / 60;
			remainder = remainder % 60;
			Long sec = remainder;

			string timeString = to_string(hour) + "시간 " + to_string(min) + "분 " + to_string(sec) + "초";
			trainer->learningForm->timeText = new HorizontalText(350, 620, timeString, RGB(0, 0, 0));
		}

		i++;
	}

	if (trainer->learningForm->stopButton != NULL) {
		delete trainer->learningForm->stopButton;
		trainer->learningForm->stopButton = NULL;
	}
	trainer->learningForm->startButton = new RoundRectangle(CRect(500, 900, 620, 940), "학습 시작", RGB(0, 0, 255), false);

	recognizingForm->recognizeButton = new Icon(CRect(30, 340, 100, 410), RGB(255, 255, 255), IDB_RECOGNIZE_OFF, false);
	recognizingForm->correctButton = new Circle(CRect(120, 355, 160, 395), RGB(0, 102, 255), false);
	recognizingForm->wrongButton = new Cross(CRect(190, 355, 230, 395), RGB(255, 0, 102), false);

	trainer->isTraining = FALSE;
	trainer->learningForm->neuronForm->isWorking = FALSE;
	trainer->learningForm->progressBar.ShowWindow(SW_HIDE);
	trainer->learningForm->Invalidate();
	recognizingForm->Invalidate();

	return 0;
}

Trainer& Trainer::operator=(const Trainer& source) {
	this->learningForm = source.learningForm;
	this->thread = source.thread;
	this->repeatCount = source.repeatCount;
	this->learningRate = source.learningRate;
	this->beta1 = source.beta1;
	this->beta2 = source.beta2;
	this->isTraining = source.isTraining;
	this->isPausing = source.isPausing;
	return *this;
}