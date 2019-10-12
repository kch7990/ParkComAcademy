#include "NeuralNetworkForm.h"
#include "NeuronForm.h"
#include "GraphMaker.h"
#include "Graph.h"
#include "Visitor.h"
#include "DrawingVisitor.h"
#include <iostream>
#include "LayerInformationForm.h"
#include "NeuralNetwork.h"
#include "AddLayerDialog.h"
#include "LayerBoxControl.h"
#include "AddBox.h"
#include "CommandFactory.h"
#include "Command.h"
#include "ScrollControllers.h"
#include "Scroll.h"
#include "VScrollActionFactory.h"
#include "VScrollActions.h"
#include "Affine.h"
#include "ReLU.h"
#include "Softmax.h"
#include "Convolution.h"
#include "Pooling.h"
#include "Dropout.h"
#include "Sigmoid.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;

BEGIN_MESSAGE_MAP(NeuralNetworkForm, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONUP()
	ON_COMMAND_RANGE(IDM_CONTEXT_REMOVELAYER, IDM_CONTENT_INSERTLAYER, OnCommandRange)
	ON_WM_VSCROLL()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

NeuralNetworkForm::NeuralNetworkForm(NeuronForm *neuronForm) {
	this->neuronForm = neuronForm;
	this->layerInformationForm = NULL;
	this->layerBoxControl = NULL;
	this->current = NULL;
	this->scrollController = NULL;
	this->layerToolTip = NULL;
}

int NeuralNetworkForm::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CWnd::OnCreate(lpCreateStruct);

	//윈도우가 생성될 때
	//1. 레이어박스 컨트롤을 만든다.
	GraphMaker graphMaker;
	this->layerBoxControl = graphMaker.Make(dynamic_cast<NeuralNetwork*>(this->neuronForm->neuralNetwork), 20, 30, false);
	this->scrollController = new NeuralNetworkFormScrollController(this);
	this->scrollController->Update();

	
	return 0;
}

void NeuralNetworkForm::OnPaint() {
	CPaintDC dc(this);
	CRect rect;
	this->GetClientRect(&rect);

	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	CBitmap bitmap;
	
	this->GetClientRect(&rect);
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	CBitmap *oldBitmap = memDC.SelectObject(&bitmap);
	memDC.FillSolidRect(&rect, RGB(248, 248, 248));

	Visitor *drawingVisitor = new DrawingVisitor(&memDC, this->scrollController);
	this->layerBoxControl->Accept(drawingVisitor);

	if (this->layerToolTip != NULL) {
		this->layerToolTip->Accept(drawingVisitor);
	}


	if (drawingVisitor != NULL) {
		delete drawingVisitor;
	}

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(oldBitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();

}

void NeuralNetworkForm::OnLButtonDown(UINT nFlags, CPoint point) {
	GraphMaker graphMaker;
	Graph *addBox = this->layerBoxControl->GetAt(this->layerBoxControl->GetLength() - 1);
	RECT rect = addBox->GetRect();

	Scroll *scroll = this->scrollController->GetScroll();
	rect.top -= scroll->GetPosition();
	rect.bottom -= scroll->GetPosition();

	if ((rect.left <= point.x && rect.right >= point.x) && (rect.top <= point.y && rect.bottom >= point.y)) {
		if (this->layerBoxControl != NULL) {
			delete this->layerBoxControl;
		}
		this->layerBoxControl = graphMaker.Make(dynamic_cast<NeuralNetwork*>(this->neuronForm->neuralNetwork), 20, 30, true);
	}
	this->Invalidate();
}

void NeuralNetworkForm::OnLButtonUp(UINT nFlags, CPoint point) {
	GraphMaker graphMaker;
	Graph *addBox = this->layerBoxControl->GetAt(layerBoxControl->GetLength() - 1);
	RECT rect = addBox->GetRect();

	Scroll *scroll = this->scrollController->GetScroll();
	rect.top -= scroll->GetPosition();
	rect.bottom -= scroll->GetPosition();

	if (this->layerBoxControl != NULL) {
		delete this->layerBoxControl;
	}
	this->layerBoxControl = graphMaker.Make(dynamic_cast<NeuralNetwork*>(this->neuronForm->neuralNetwork), 20, 30, false);
	this->Invalidate();
	if (rect.right >= point.x && rect.left <= point.x && rect.top <= point.y && rect.bottom >= point.y && this->neuronForm->isWorking == FALSE) {
		//AddLayerDialog 객체 생성 후 출력까지
		this->neuronForm->neuralNetwork->Move(-1);
		AddLayerDialog addLayerDialog((CWnd*)this);
		addLayerDialog.DoModal();
	}

	this->Invalidate();
	this->neuronForm->UpdateWindow();
}

void NeuralNetworkForm::OnSize(UINT nType, int cx, int cy) {
	if (this->scrollController == NULL) {
		this->scrollController = new NeuralNetworkFormScrollController(this);
	}
	this->scrollController->Update();
}

void NeuralNetworkForm::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	VScrollActionFactory vScrollActionFactory(this);

	VScrollAction *vScrollAction = vScrollActionFactory.Make(nSBCode);
	if (vScrollAction != NULL) {
		vScrollAction->OnVScroll(nSBCode, nPos, pScrollBar);
		delete vScrollAction;
	}
	this->Invalidate();
}


BOOL NeuralNetworkForm::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
	LONG style = this->GetStyle();

	if ((style & WS_VSCROLL) != 0) {
		Long position = this->scrollController->Rotate(zDelta);
		Long previousPosition = this->SetScrollPos(SB_VERT, position, TRUE);
		position = this->GetScrollPos(SB_VERT);
		this->scrollController->Move(position);
		this->ScrollWindow(0, previousPosition - position);
		this->scrollController->Update();
	}
	return TRUE;
}

void NeuralNetworkForm::OnLButtonDblClk(UINT nFlags, CPoint point) {
	Scroll *scroll = this->scrollController->GetScroll();
	if (this->layerBoxControl->GetLength() > 1) { // 계층을 가지고 있으면
		Graph *layerBox = this->layerBoxControl->GetAt(0);
		RECT rect = layerBox->GetRect();
		rect.top -= scroll->GetPosition();
		rect.bottom -= scroll->GetPosition();
		Long i = 0;
		while (i < this->layerBoxControl->GetLength() &&
			((rect.right < point.x || rect.left > point.x) || (rect.top > point.y || rect.bottom < point.y))) {
			i++;
			if (i < this->layerBoxControl->GetLength()) {
				layerBox = layerBoxControl->GetAt(i);
				rect = layerBox->GetRect();
				rect.top -= scroll->GetPosition();
				rect.bottom -= scroll->GetPosition();
			}
		}
		string type = layerBox->GetType();

		if (i < layerBoxControl->GetLength() && !(dynamic_cast<AddBox*>(layerBox)) && (type=="Conv" || type=="Pooling" || type=="STN")) {
			Neuron *layer = this->neuronForm->neuralNetwork->GetAt(i);
			//클릭한 계층의 정보 창을 출력한다.
			this->layerInformationForm = new LayerInformationForm(layer);
			this->layerInformationForm->Create(NULL, type.c_str());
			this->layerInformationForm->ShowWindow(SW_NORMAL);
			this->layerInformationForm->UpdateWindow();
		}
	}
}

void NeuralNetworkForm::OnRButtonUp(UINT nFlags, CPoint point) {

	Scroll *scroll = this->scrollController->GetScroll();
	if (this->layerBoxControl->GetLength() > 1) { // 계층을 가지고 있으면
		this->current = this->layerBoxControl->GetAt(0);
		RECT rect = this->current->GetRect();
		rect.top -= scroll->GetPosition();
		rect.bottom -= scroll->GetPosition();
		Long i = 0;
		while (i < this->layerBoxControl->GetLength() && ((rect.right < point.x || rect.left > point.x) || (rect.top > point.y || rect.bottom < point.y))) {
			i++;
			if (i < this->layerBoxControl->GetLength()) {
				this->current = layerBoxControl->GetAt(i);
				rect = this->current->GetRect();
				rect.top -= scroll->GetPosition();
				rect.bottom -= scroll->GetPosition();
			}
		}
		string type = this->current->GetType();

		if (i < layerBoxControl->GetLength() && !(dynamic_cast<AddBox*>(this->current))) {
			this->neuronForm->neuralNetwork->Move(i);
			CMenu menu;
			menu.CreatePopupMenu();
			menu.AppendMenuA(MF_STRING, IDM_CONTEXT_REMOVELAYER, "계층 빼기");
			menu.AppendMenuA(MF_STRING, IDM_CONTENT_INSERTLAYER, "계층 삽입");

			GetCursorPos(&point);

			menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
			menu.DestroyMenu();
		}
	}
}

void NeuralNetworkForm::OnMouseHover(UINT nFlags, CPoint point) {

	GraphMaker graphMaker;
	Scroll *scroll = this->scrollController->GetScroll();
	if (this->layerBoxControl->GetLength() > 1) { // 계층을 가지고 있으면
		this->current = this->layerBoxControl->GetAt(0);
		RECT rect = this->current->GetRect();
		rect.top -= scroll->GetPosition();
		rect.bottom -= scroll->GetPosition();
		Long i = 0;
		while (i < this->layerBoxControl->GetLength() && ((rect.right < point.x || rect.left > point.x) || (rect.top > point.y || rect.bottom < point.y))) {
			i++;
			if (i < this->layerBoxControl->GetLength()) {
				this->current = layerBoxControl->GetAt(i);
				rect = this->current->GetRect();
				rect.top -= scroll->GetPosition();
				rect.bottom -= scroll->GetPosition();
			}
		}
		if (i < this->layerBoxControl->GetLength() - 1) { // AddBox 아이콘은 제외

			rect.left = point.x;
			rect.top = point.y + 30;
			rect.right = rect.left + 130;
			rect.bottom = rect.top + 70;


			Neuron *layer = this->neuronForm->neuralNetwork->GetAt(i);

			if (dynamic_cast<Affine*>(layer)) {
				this->layerToolTip = graphMaker.Make(dynamic_cast<Affine*>(layer), rect);
			}
			else if (dynamic_cast<ReLU*>(layer)) {
				this->layerToolTip = graphMaker.Make(dynamic_cast<ReLU*>(layer), rect);
			}
			else if (dynamic_cast<Softmax*>(layer)) {
				this->layerToolTip = graphMaker.Make(dynamic_cast<Softmax*>(layer), rect);
			}
			else if (dynamic_cast<Dropout*>(layer)) {
				this->layerToolTip = graphMaker.Make(dynamic_cast<Dropout*>(layer), rect);
			}
			else if (dynamic_cast<Convolution*>(layer)) {
				this->layerToolTip = graphMaker.Make(dynamic_cast<Convolution*>(layer), rect);
			}
			else if (dynamic_cast<Pooling*>(layer)) {
				this->layerToolTip = graphMaker.Make(dynamic_cast<Pooling*>(layer), rect);
			}
			else if (dynamic_cast<Sigmoid*>(layer)) {
				this->layerToolTip = graphMaker.Make(dynamic_cast<Sigmoid*>(layer), rect);
			}
		}
	}
	CWnd::OnMouseHover(nFlags, point);
	this->Invalidate();
}

void NeuralNetworkForm::OnMouseLeave() {
	if (this->layerToolTip != NULL) {
		delete this->layerToolTip;
		this->layerToolTip = NULL;
	}
	CWnd::OnMouseLeave();
	this->Invalidate();
}

void NeuralNetworkForm::OnMouseMove(UINT nFlags, CPoint point) {
	TRACKMOUSEEVENT trackMouseEvent;
	trackMouseEvent.cbSize = sizeof(TRACKMOUSEEVENT);
	trackMouseEvent.dwFlags = TME_LEAVE | TME_HOVER;
	trackMouseEvent.dwHoverTime = 1000;
	trackMouseEvent.hwndTrack = this->m_hWnd;
	TrackMouseEvent(&trackMouseEvent);

	RECT rect = this->layerBoxControl->GetAt(this->layerBoxControl->GetLength() - 1)->GetRect();
	Scroll *scroll = this->scrollController->GetScroll();
	rect.top -= scroll->GetPosition();
	rect.bottom -= scroll->GetPosition();
	if ((rect.left <= point.x && rect.right >= point.x) && (rect.top <= point.y && rect.bottom >= point.y)) {
		SetCursor(LoadCursor(NULL, IDC_HAND));
	}

	if (this->layerToolTip != NULL) {
		delete this->layerToolTip;
		this->layerToolTip = NULL;
	}
	this->Invalidate();
	CWnd::OnMouseMove(nFlags, point);
}




void NeuralNetworkForm::OnCommandRange(UINT uID) {
	CommandFactory commandFactory(this->neuronForm);
	Command *command = commandFactory.Make(uID);
	if (command != NULL) {
		if (this->neuronForm->isWorking == FALSE) {
			command->Execute();
		}
		delete command;
	}
	this->Invalidate();
}

NeuralNetworkForm::~NeuralNetworkForm() {
	if (this->layerBoxControl != NULL) {
		delete this->layerBoxControl;
	}
	if (this->scrollController != NULL) {
		delete this->scrollController;
	}
	if (this->layerToolTip != NULL) {
		delete this->layerToolTip;
	}
	if (this->current != NULL) {
		delete this->current;
	}
}

void NeuralNetworkForm::OnClose() {
	if (this->layerBoxControl != NULL) {
		delete this->layerBoxControl;
	}
	if (this->scrollController != NULL) {
		delete this->scrollController;
	}
	if (this->layerToolTip != NULL) {
		delete this->layerToolTip;
	}
	if (this->current != NULL) {
		delete this->current;
	}

	CWnd::OnClose();
}
