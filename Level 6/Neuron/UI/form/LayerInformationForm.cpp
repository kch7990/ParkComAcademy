#include "LayerInformationForm.h"
#include "GraphMaker.h"
#include "Layout.h"
#include "Graph.h"
#include "DrawingVisitor.h"
#include "Visitor.h"
#include "Layer.h"
#include "Neuron.h"
#include "Convolution.h"
#include "Pooling.h"
#include "ScrollControllers.h"
#include "Scroll.h"
#include "VScrollActionFactory.h"
#include "VScrollActions.h"
#include "SpatialTransformer.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
BEGIN_MESSAGE_MAP(LayerInformationForm, CFrameWnd)//
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_VSCROLL()
	ON_WM_SIZE()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

LayerInformationForm::LayerInformationForm(Neuron *layer) {
	this->layer = layer;
	this->layout = NULL;
	this->scrollController = NULL;
}

int LayerInformationForm::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CFrameWnd::OnCreate(lpCreateStruct);
	GraphMaker graphMaker;
	
	if (dynamic_cast<Convolution*>(this->layer)) {
		this->layout = graphMaker.Make(dynamic_cast<Convolution*>(this->layer), 10, 10);
	}
	else if (dynamic_cast<Pooling*>(this->layer)) {
		this->layout = graphMaker.Make(dynamic_cast<Pooling*>(this->layer), 10, 10);
	}
	else if (dynamic_cast<SpatialTransformer*>(this->layer)) {
		this->layout = graphMaker.Make(dynamic_cast<SpatialTransformer*>(this->layer), 10, 40);
	}

	this->scrollController = new LayerInformationFormScrollController(this);
	this->scrollController->Update();

	return 0;
}

void LayerInformationForm::OnPaint() {
	CPaintDC dc(this);

	CRect rect;
	this->GetClientRect(&rect);

	CDC memDC;
	CBitmap bitmap;

	memDC.CreateCompatibleDC(&dc);

	CPen pen;
	pen.CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
	CPen *oldPen = memDC.SelectObject(&pen);

	GetClientRect(&rect);
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	CBitmap *oldBitmap = memDC.SelectObject(&bitmap);
	memDC.FillSolidRect(&rect, RGB(248, 248, 248));

	Visitor *drawingVisitor = new DrawingVisitor(&memDC, this->scrollController);

	this->layout->Accept(drawingVisitor);


	if (drawingVisitor != NULL) {
		delete drawingVisitor;
	}

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(oldBitmap);
	memDC.SelectObject(oldPen);
	memDC.DeleteDC();
	bitmap.DeleteObject();
	pen.DeleteObject();
}

void LayerInformationForm::OnSize(UINT nType, int cx, int cy) {
	if (this->scrollController == NULL) {
		this->scrollController = new LayerInformationFormScrollController(this);
	}
	this->scrollController->Update();
}

void LayerInformationForm::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	VScrollActionFactory vScrollActionFactory(NULL, this);

	VScrollAction *vScrollAction = vScrollActionFactory.Make(nSBCode);
	if (vScrollAction != NULL) {
		vScrollAction->OnVScroll(nSBCode, nPos, pScrollBar);
		delete vScrollAction;
	}
	this->Invalidate();
}


BOOL LayerInformationForm::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
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

void LayerInformationForm::OnClose() {
	if (this->layout != NULL) {
		delete this->layout;
	}

	CFrameWnd::OnClose(); //CFrameWnd::OnClose();
}