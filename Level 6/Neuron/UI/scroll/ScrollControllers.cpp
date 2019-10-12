#include "ScrollControllers.h"
#include "Scroll.h"
#include "NeuralNetworkForm.h"
#include "Graph.h"
#include <afxwin.h>
#include "LayerInformationForm.h"
#include "Neuron.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//ScrollController
ScrollController::ScrollController()
	: scroll() {
	this->width = 0;
	this->height = 0;
}

ScrollController::ScrollController(const ScrollController& source) 
	: scroll(source.scroll) {
	this->width = source.width;
	this->height = source.height;
}

ScrollController::~ScrollController() {
	if (this->scroll != 0) {
		delete this->scroll;
	}
}

Long ScrollController::Up() {
	return this->scroll->Down();
}

Long ScrollController::Down() {
	return this->scroll->Up();
}

Long ScrollController::PageUp() {
	return this->scroll->PageDown();
}

Long ScrollController::PageDown() {
	return this->scroll->PageUp();
}

Long ScrollController::Move(Long position) {
	return this->scroll->Move(position);
}

Long ScrollController::Rotate(short delta) {
	return this->scroll->Rotate(delta);
}

ScrollController& ScrollController::operator=(const ScrollController& source) {
	this->scroll = source.scroll;
	this->width = source.width;
	this->height = source.height;
	
	return *this;
}

//NeuralNetworkFormScrollController
NeuralNetworkFormScrollController::NeuralNetworkFormScrollController(NeuralNetworkForm *neuralNetworkForm) {
	this->neuralNetworkForm = neuralNetworkForm;
	this->width = 200;
	Graph *layerBoxControl = this->neuralNetworkForm->layerBoxControl;
	this->height = 30 + (layerBoxControl->GetBoxHeight() + layerBoxControl->GetInterval())*layerBoxControl->GetLength();

	RECT clientRect = { 0, };
	this->neuralNetworkForm->GetClientRect(&clientRect);
	Long clientHeight = clientRect.bottom - clientRect.top;
	Long maximum = this->height - clientHeight;
	this->scroll = new Scroll(0, 0, maximum, 50, clientHeight);
}

NeuralNetworkFormScrollController::NeuralNetworkFormScrollController(const NeuralNetworkFormScrollController& source)
	: ScrollController(source) {
	this->neuralNetworkForm = source.neuralNetworkForm;
}

NeuralNetworkFormScrollController::~NeuralNetworkFormScrollController() {

}

void NeuralNetworkFormScrollController::Update() {
	RECT clientRect;
	this->neuralNetworkForm->GetClientRect(&clientRect);
	Long clientHeight = clientRect.bottom - clientRect.top;
	LONG style;
	Long position;
	Long minimum;
	Long maximum;
	Long lineSize;
	Long pageSize;
	SCROLLINFO scrollInfo;

	style = ::GetWindowLong(this->neuralNetworkForm->m_hWnd, GWL_STYLE);
	Graph *layerBoxControl = this->neuralNetworkForm->layerBoxControl;
	this->height = 30 + (layerBoxControl->GetBoxHeight() + layerBoxControl->GetInterval())*layerBoxControl->GetLength();

	if (clientHeight < this->height) {
		style = style | WS_VSCROLL;
		position = this->scroll->GetPosition();
		minimum = this->scroll->GetMinimum();
		maximum = this->height;
		lineSize = 50;
		pageSize = clientHeight;
		if (this->scroll != 0) {
			delete this->scroll;
		}
		this->scroll = new Scroll(position, minimum, maximum, lineSize, pageSize);
		scrollInfo = this->scroll->GetScrollInfo();
		this->neuralNetworkForm->SetScrollInfo(SB_VERT, &scrollInfo, TRUE);

	}
	else {
		style = style & ~WS_VSCROLL;
		if (this->scroll != 0) {
			delete this->scroll;
			this->scroll = new Scroll;
			scrollInfo = this->scroll->GetScrollInfo();
		}
	}
	this->neuralNetworkForm->SetScrollInfo(SB_VERT, &scrollInfo, TRUE);
	::SetWindowLong(this->neuralNetworkForm->m_hWnd, GWL_STYLE, style);
	this->neuralNetworkForm->RedrawWindow();
}

NeuralNetworkFormScrollController& NeuralNetworkFormScrollController::operator=(const NeuralNetworkFormScrollController& source) {
	ScrollController::operator=(source);
	this->neuralNetworkForm = source.neuralNetworkForm;

	return *this;
}

//LayerInformationFormScrollController
LayerInformationFormScrollController::LayerInformationFormScrollController(LayerInformationForm *layerInformationForm) {
	this->layerInformationForm = layerInformationForm;
	
	this->width = 1130; //최대열수(28) * 픽셀사각형한변크기(10) * 한 가로줄에 보여줄 결과행렬의 수(4) + Layout만들때 x값(10)으로 고정
	
	
	Long layoutLength = layerInformationForm->layout->GetLength(); //사각형 전체 개수 ex)28*28*16
	Long layerLength = layerInformationForm->layer->GetLength(); //필터(큐브) 개수 ex)16
	Long resultMatrixSize = sqrt(layoutLength / layerLength); //결과행렬의 한변 사이즈 ex)28
	//결과행렬의 한 변 사이즈 * 픽셀사각형한변크기(10) * 필터개수/4 + 여유공간150
	this->height = resultMatrixSize * 10 * (layerLength/4) + 150;

	RECT clientRect;
	layerInformationForm->GetClientRect(&clientRect);
	Long clientHeight = clientRect.bottom - clientRect.top;
	Long maximum = this->height - clientHeight;
	this->scroll = new Scroll(0, 0, maximum, 50, clientHeight);
}

LayerInformationFormScrollController::LayerInformationFormScrollController(const LayerInformationFormScrollController& source) 
	: ScrollController(source) {
	this->layerInformationForm = source.layerInformationForm;
}

LayerInformationFormScrollController::~LayerInformationFormScrollController() {

}

void LayerInformationFormScrollController::Update() {
	RECT clientRect;
	this->layerInformationForm->GetClientRect(&clientRect);
	Long clientHeight = clientRect.bottom - clientRect.top;
	LONG style;
	Long position;
	Long minimum;
	Long maximum;
	Long lineSize;
	Long pageSize;
	SCROLLINFO scrollInfo;

	style = ::GetWindowLong(this->layerInformationForm->m_hWnd, GWL_STYLE);

	Long layoutLength = layerInformationForm->layout->GetLength(); //사각형 전체 개수 ex)28*28*16
	Long layerLength = layerInformationForm->layer->GetLength(); //필터(큐브) 개수 ex)16
	Long resultMatrixSize = sqrt(layoutLength / layerLength); //결과행렬의 한변 사이즈 ex)28
	//결과행렬의 한 변 사이즈 * 픽셀사각형한변크기(10) * 필터개수/4 + 여유공간 150
	this->height = resultMatrixSize * 10 * (layerLength / 4) + 150;

	if (clientHeight < this->height) {
		style = style | WS_VSCROLL;
		position = this->scroll->GetPosition();
		minimum = this->scroll->GetMinimum();
		maximum = this->height;
		lineSize = 50;
		pageSize = clientHeight;
		if (this->scroll != 0) {
			delete this->scroll;
		}
		this->scroll = new Scroll(position, minimum, maximum, lineSize, pageSize);
		scrollInfo = this->scroll->GetScrollInfo();
		this->layerInformationForm->SetScrollInfo(SB_VERT, &scrollInfo, TRUE);

	}
	else {
		style = style & ~WS_VSCROLL;
		if (this->scroll != 0) {
			delete this->scroll;
			this->scroll = new Scroll;
			scrollInfo = this->scroll->GetScrollInfo();
		}
	}
	this->layerInformationForm->SetScrollInfo(SB_VERT, &scrollInfo, TRUE);
	::SetWindowLong(this->layerInformationForm->m_hWnd, GWL_STYLE, style);
	this->layerInformationForm->RedrawWindow();
}

LayerInformationFormScrollController& LayerInformationFormScrollController::operator=(const LayerInformationFormScrollController& source) {
	ScrollController::operator=(source);
	this->layerInformationForm = source.layerInformationForm;

	return *this;
}