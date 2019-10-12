#include "NeuralNetworkToolBoxForm.h"
#include "Icon.h"
#include "DrawingVisitor.h"
#include "resource.h"
#include "CommandFactory.h"
#include "Command.h"
#include "resource.h"
#include "NeuronForm.h"

BEGIN_MESSAGE_MAP(NeuralNetworkToolBoxForm, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

NeuralNetworkToolBoxForm::NeuralNetworkToolBoxForm(NeuronForm *neuronForm) {
	this->neuronForm = neuronForm;
	this->newIcon = NULL;
	this->openIcon = NULL;
	this->saveIcon = NULL;
}

NeuralNetworkToolBoxForm::~NeuralNetworkToolBoxForm() {
	if (this->newIcon != NULL) {
		delete this->newIcon;
	}
	if (this->openIcon != NULL) {
		delete this->openIcon;
	}
	if (this->saveIcon != NULL) {
		delete this->saveIcon;
	}
}

int NeuralNetworkToolBoxForm::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CWnd::OnCreate(lpCreateStruct);
	RECT clientRect;
	this->GetClientRect(&clientRect);

	RECT rect = { 5, 2, 40, 38 };
	this->newIcon = new Icon(rect, RGB(0, 0, 0), IDB_NEW, false);

	rect = { 48, 6, 80, 38 };
	this->openIcon = new Icon(rect, RGB(0, 0, 0), IDB_OPEN, false);

	rect = { 90, 4, 120, 38 };
	this->saveIcon = new Icon(rect, RGB(0, 0, 0), IDB_SAVE, false);

	return 0;
}

void NeuralNetworkToolBoxForm::OnPaint() {
	CPaintDC dc(this);
	CRect rect;

	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	CBitmap bitmap;

	this->GetClientRect(&rect);
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	CBitmap *oldBitmap = memDC.SelectObject(&bitmap);
	memDC.FillSolidRect(&rect, RGB(248, 248, 248));

	Visitor *drawingVisitor = new DrawingVisitor(&memDC);

	this->newIcon->Accept(drawingVisitor);
	this->openIcon->Accept(drawingVisitor);
	this->saveIcon->Accept(drawingVisitor);

	if (drawingVisitor != NULL) {
		delete drawingVisitor;
	}

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(oldBitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();
}

void NeuralNetworkToolBoxForm::OnMouseMove(UINT nFlags, CPoint point) {
	RECT newRect = this->newIcon->GetRect();
	RECT openRect = this->openIcon->GetRect();
	RECT saveRect = this->saveIcon->GetRect();

	if (((newRect.left <= point.x && newRect.right >= point.x) && (newRect.top <= point.y && newRect.bottom >= point.y)) ||
		((openRect.left <= point.x && openRect.right >= point.x) && (openRect.top <= point.y && openRect.bottom >= point.y)) ||
		((saveRect.left <= point.x && saveRect.right >= point.x) && (saveRect.top <= point.y && saveRect.bottom >= point.y))) {
		SetCursor(LoadCursor(NULL, IDC_HAND));
	}


}

void NeuralNetworkToolBoxForm::OnLButtonUp(UINT nFlags, CPoint point) {
	RECT newRect = this->newIcon->GetRect();
	RECT openRect = this->openIcon->GetRect();
	RECT saveRect = this->saveIcon->GetRect();

	UINT uID=0;
	if ((newRect.left <= point.x && newRect.right >= point.x) && (newRect.top <= point.y && newRect.bottom >= point.y)) {
		uID = IDM_EDIT_CLEAR;
	}
	else if ((openRect.left <= point.x && openRect.right >= point.x) && (openRect.top <= point.y && openRect.bottom >= point.y)) {
		uID = IDM_FILE_OPEN;
	}
	else if ((saveRect.left <= point.x && saveRect.right >= point.x) && (saveRect.top <= point.y && saveRect.bottom >= point.y)) {
		uID = IDM_FILE_SAVE;
	}
	CommandFactory commandFactory(this->neuronForm);
	Command *command = commandFactory.Make(uID);
	if (command != NULL) {
		if (this->neuronForm->isWorking == FALSE) {
			command->Execute();
		}
		delete command;
	}
}