#include "RecognizeCommand.h"
#include "RecognizingForm.h"
#include "NeuronForm.h"
#include "Graph.h"
#include "resource.h"
#include "LearningForm.h"
#include "GraphMaker.h"
#include "Recognizer.h"
#include "Icon.h"
#include "RoundRectangle.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
RecognizeCommand::RecognizeCommand(NeuronForm *neuronForm) {
	this->neuronForm = neuronForm;
}

RecognizeCommand::RecognizeCommand(const RecognizeCommand& source) {
	this->neuronForm = source.neuronForm;
}

RecognizeCommand::~RecognizeCommand() {

}

void RecognizeCommand::Execute() {
	if (this->neuronForm->recognizingForm->recognizeButton->GetID() == IDB_RECOGNIZE_OFF) { // 추론상태 아이콘이면
		*dynamic_cast<Icon*>(this->neuronForm->recognizingForm->recognizeButton)
			= Icon(this->neuronForm->recognizingForm->recognizeButton->GetRect(), this->neuronForm->recognizingForm->recognizeButton->GetColor(),
				IDB_RECOGNIZE_ON, false);

		// Clear버튼을 지우다.
		if (this->neuronForm->recognizingForm->clearButton != NULL) {
			delete this->neuronForm->recognizingForm->clearButton;
			this->neuronForm->recognizingForm->clearButton = NULL;
		}
		// 학습하다 폼의 그래프를 만든다.

		if (this->neuronForm->learningForm->accuracyCoordinateSystem != NULL) {
			delete this->neuronForm->learningForm->accuracyCoordinateSystem;
			this->neuronForm->learningForm->accuracyCoordinateSystem = NULL;
		}
		if (this->neuronForm->learningForm->lossCoordinateSystem != NULL) {
			delete this->neuronForm->learningForm->lossCoordinateSystem;
			this->neuronForm->learningForm->lossCoordinateSystem = NULL;
		}
		// 학습하다 폼의 시작 버튼을 지우다.
		if (this->neuronForm->learningForm->startButton != NULL) {
			delete this->neuronForm->learningForm->startButton;
			this->neuronForm->learningForm->startButton = NULL;
			// 학습하다 폼을 갱신하다.
			this->neuronForm->learningForm->Invalidate();
		}

		GraphMaker graphMaker;
		this->neuronForm->learningForm->accuracyCoordinateSystem = graphMaker.Make("반복횟수", "정확도", CRect(100, 350, 700, 530), 10000, 1);
		this->neuronForm->learningForm->lossCoordinateSystem = graphMaker.Make("반복횟수", "오차", CRect(100, 50, 700, 230), 10000, 5);

		// 인식기에서 추론하다.
		this->neuronForm->recognizingForm->recognizer->AutoRecognize();

	}
	else if (this->neuronForm->recognizingForm->recognizeButton->GetID() == IDB_RECOGNIZE_ON) { // 추론아님상태 아이콘이면
	   // 인식기에서 멈춘다.
		this->neuronForm->recognizingForm->recognizer->Stop();

		*dynamic_cast<Icon*>(this->neuronForm->recognizingForm->recognizeButton)
			= Icon(this->neuronForm->recognizingForm->recognizeButton->GetRect(), this->neuronForm->recognizingForm->recognizeButton->GetColor(),
				IDB_RECOGNIZE_OFF, true);

		// Clear 버튼을 만들다.
		this->neuronForm->recognizingForm->clearButton = new Icon(CRect(neuronForm->recognizingForm->imageRect.left,
			neuronForm->recognizingForm->imageRect.top - 30, neuronForm->recognizingForm->imageRect.left + 30, neuronForm->recognizingForm->imageRect.top - 10),
			RGB(0, 245, 0), IDB_RESET, false);
		// 학습하다 폼의 시작 버튼을 만들다.
		this->neuronForm->learningForm->startButton = new RoundRectangle(CRect(600, 740, 700, 780), "학습 시작", RGB(0, 0, 255), false);
		// 학습하다 폼을 갱신하다.
		this->neuronForm->learningForm->Invalidate();
	}
	this->neuronForm->recognizingForm->isPaint = false;
}

RecognizeCommand& RecognizeCommand::operator =(const RecognizeCommand& source) {
	this->neuronForm = source.neuronForm;
	return *this;
}