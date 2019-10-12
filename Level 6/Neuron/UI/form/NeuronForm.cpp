#include "NeuronForm.h"
#include "NeuralNetwork.h"
#include "Affine.h"
#include <afxwin.h>
#include "Visitor.h"
#include "DrawingVisitor.h"
#include "CoordinateSystem.h"
#include "Graph.h"
#include "GraphMaker.h"
#include "Axis.h"
#include "NeuronFactory.h"
#include "Neuron.h"
#include "Node.h"
#include <random>
#include <chrono>
#include "ImageFile.h"
#include "LabelFile.h"
#include "GraphFactory.h"
#include "Texts.h"
#include "CommandFactory.h"
#include "Command.h"
#include "resource.h"
#include "NeuralNetworkForm.h"
#include "RecognizingForm.h" 
#include "LearningForm.h"
#include "NeuralNetworkToolBoxForm.h"
#include "Trainer.h"
#include "Recognizer.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;

#define MAX 784 //구현 위한 값 : 추후 삭제
#define MAGNIFICATION 8 // 이미지 출력 배율

BEGIN_MESSAGE_MAP(NeuronForm, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_COMMAND_RANGE(IDM_EDIT_ADD, IDM_EDIT_CLEAR, OnCommandRange)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

NeuronForm::NeuronForm() {
	this->neuralNetwork = NULL;
	this->neuralNetworkForm = NULL;
	this->learningForm = NULL;
	this->isWorking = FALSE;
}

int NeuronForm::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CFrameWnd::OnCreate(lpCreateStruct);

	this->neuralNetwork = new NeuralNetwork; //신경망을 생성하다.

	RECT rect = { 10, 10, 600, 850 }; //
	this->recognizingForm = new RecognizingForm(this); //
	this->recognizingForm->Create(NULL, "추론하기", WS_CHILD | WS_BORDER, rect, this, NULL, NULL); //
	this->recognizingForm->ShowWindow(SW_NORMAL); //
	this->recognizingForm->UpdateWindow(); //

	rect = { 610, 10, 1370, 850 };
	this->learningForm = new LearningForm(this);
	this->learningForm->Create(NULL, "학습하기", WS_CHILD | WS_BORDER, rect, this, NULL, NULL);
	this->learningForm->ShowWindow(SW_NORMAL);
	this->learningForm->UpdateWindow();

	rect = { 1380, 50, 1560, 850 };
	this->neuralNetworkForm = new NeuralNetworkForm(this);
	this->neuralNetworkForm->Create(NULL, "신경망", WS_CHILD | WS_BORDER | WS_EX_LAYERED, rect, this, NULL, NULL);
	this->neuralNetworkForm->ShowWindow(SW_NORMAL);
	this->neuralNetworkForm->UpdateWindow();

	rect = { 1380, 10, 1560, 50 };
	this->neuralNetworkToolBoxForm = new NeuralNetworkToolBoxForm(this);
	this->neuralNetworkToolBoxForm->Create(NULL, "신경망도구상자", WS_CHILD | WS_BORDER, rect, this, NULL, NULL);
	this->neuralNetworkToolBoxForm->ShowWindow(SW_NORMAL);
	this->neuralNetworkToolBoxForm->UpdateWindow();


	this->menu.LoadMenuA(IDR_MENU1);
	this->SetMenu(&menu);

	return 0;
}


void NeuronForm::OnClose() {

	if (this->learningForm != NULL) {
		delete this->learningForm;
	}
	if (this->recognizingForm != NULL) {
		delete this->recognizingForm;
	}
	
#if 0
	if (this->learningDialog != NULL) {
		delete this->learningDialog;
	}
#endif
	if (this->neuralNetworkForm != NULL) {
		delete this->neuralNetworkForm;
	}
	if (this->neuralNetworkToolBoxForm != NULL) {
		delete this->neuralNetworkToolBoxForm;
	}
	if (this->neuralNetwork != NULL) { //신경망을 없애다.
		delete this->neuralNetwork;
	}

	CFrameWnd::OnClose(); //윈도우를 닫다.
}

void NeuronForm::OnCommandRange(UINT uID) {
	CommandFactory commandFactory(this);
	
	Command *command = commandFactory.Make(uID);
	if (command != NULL) {
		if (this->isWorking == FALSE) {
			command->Execute();
		}
		delete command;
	}
}

void NeuronForm::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (nChar == VK_F5)
	{
		this->recognizingForm->index = -1;
		this->recognizingForm->recognizingNumber = -1;
		this->recognizingForm->label = -1;
		this->recognizingForm->recognizationResult = { 0, 0, 0, 0.0 };
		this->recognizingForm->results.Clear();
		this->recognizingForm->results.Resize(10);
		Long i = 0;
		while (i < this->recognizingForm->results.GetCapacity()) {
			this->recognizingForm->results.Store(i, 0.0);
			i++;
		}
		this->recognizingForm->imageDC.FillSolidRect(&this->recognizingForm->imageRect, RGB(0, 0, 0));
		this->recognizingForm->Invalidate();
	}
	else if (nChar == VK_SPACE)
	{
		this->recognizingForm->recognizer->Recognize();

		CPaintDC dc(this);
		CDC memoryDC;
		CBitmap bitmap;
		memoryDC.CreateCompatibleDC(&dc);
		bitmap.CreateCompatibleBitmap(&dc, this->recognizingForm->imageFile.GetRowCount(), this->recognizingForm->imageFile.GetColumnCount());
		memoryDC.SelectObject(&bitmap);

		if (this->recognizingForm->recognizingNumber != -1) {
			Long j = 0;
			for (Long row = 0; row < this->recognizingForm->imageFile.GetRowCount(); row++) {
				for (Long column = 0; column < this->recognizingForm->imageFile.GetColumnCount(); column++) {
					double pixel = this->recognizingForm->image[j++];
					memoryDC.SetPixel(column, row, RGB(pixel, pixel, pixel));
				}
			}
		}

		this->recognizingForm->imageDC.StretchBlt(0, 0, this->recognizingForm->imageRect.Width(), this->recognizingForm->imageRect.Height(), &memoryDC, 0, 0, 28, 28, SRCCOPY);
		this->recognizingForm->Invalidate();
		this->recognizingForm->isPaint = false;
	}
}