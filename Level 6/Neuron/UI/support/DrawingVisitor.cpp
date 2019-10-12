#include "DrawingVisitor.h"
#include "CoordinateSystem.h"
#include "Point.h"
#include "Line.h"
#include "Texts.h"
#include "Arrow.h"
#include "LayerBoxControl.h"
#include "LayerBox.h"
#include "RectangleGraph.h"
#include "AddBox.h"
#include "Cell.h"
#include "Layout.h"
#include "Table.h"
#include "ScrollControllers.h"
#include "Scroll.h"
#include "RoundRectangle.h"
#include "LayerToolTip.h"
#include "resource.h"
#include "Icon.h"
#include "Circle.h"
#include "Cross.h"

DrawingVisitor::DrawingVisitor(CDC *dc, ScrollController *scrollController) {
	this->dc = dc;
	this->scrollController = scrollController;
}

DrawingVisitor::DrawingVisitor(const DrawingVisitor& source) {
	this->dc = source.dc;
	this->scrollController = source.scrollController;
}

DrawingVisitor::~DrawingVisitor() {

}

void DrawingVisitor::Visit(Point *point) {
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0)); //선 스타일 지정
	CBrush brush;
	brush.CreateSolidBrush(point->GetColor());

	//COLORREF oldColor = this->dc->SetBkColor(point->GetColor()); //배경색 지정
	CPen *oldPen = this->dc->SelectObject(&pen);
	CBrush *oldBrush = this->dc->SelectObject(&brush);

	this->dc->Ellipse(point->GetX() - 2, point->GetY() - 2, point->GetX() + 2, point->GetY() + 2);

	this->dc->SelectObject(oldPen);
	this->dc->SelectObject(oldBrush);
	//this->dc->SetBkColor(oldColor);

	pen.DeleteObject();
	brush.DeleteObject();
}

void DrawingVisitor::Visit(CoordinateSystem *coordinateSystem) {
	//좌표계 그리는건 Line에서 함 : Add되어있는 모든 Graph의 Accept 호출하기
	//폰트 지정
	CFont *oldFont;
	CFont *currentFont = this->dc->GetCurrentFont();
	LOGFONT logFont;
	currentFont->GetLogFont(&logFont);

	CFont font;
	font.CreateFont(18, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS, "궁서");
	oldFont = this->dc->SelectObject(&font);

	Array<CPoint>points(coordinateSystem->GetLength());
	Graph *graph;
	Long i = 0;
	while (i < coordinateSystem->GetLength()) {
		graph = coordinateSystem->GetAt(i);
		if (graph == dynamic_cast<Point*>(graph)) {
			CPoint point= CPoint(dynamic_cast<Point*>(graph)->GetX(), dynamic_cast<Point*>(graph)->GetY());
			points.Store(points.GetLength(), point);
		}
		else {
			graph->Accept(this);
		}

		i++;
	}

	CPen pen;
	pen.CreatePen(PS_SOLID, 3, RGB(0, 0, 0)); //선 스타일 지정
	CPen *oldPen = this->dc->SelectObject(&pen);
	this->dc->Polyline(&points.GetAt(0), points.GetLength());

	this->dc->SelectObject(oldFont);
	this->dc->SelectObject(oldPen);

}

void DrawingVisitor::Visit(Line *line) {
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, line->GetColor()); //선 스타일 지정
	CBrush brush;
	brush.CreateSolidBrush(line->GetColor());
	CPen *oldPen = this->dc->SelectObject(&pen);
	CBrush *oldBrush = this->dc->SelectObject(&brush);

	this->dc->MoveTo(line->GetStartX(), line->GetStartY());
	this->dc->LineTo(line->GetEndX(), line->GetEndY());

	this->dc->SelectObject(oldPen);
	this->dc->SelectObject(oldBrush);

	pen.DeleteObject();
	brush.DeleteObject();
}

void DrawingVisitor::Visit(HorizontalText *text) {
	COLORREF oldColor = this->dc->SetTextColor(text->GetColor()); //배경색 지정

	this->dc->TextOutA(text->GetX(), text->GetY(), text->GetContent().c_str());

	this->dc->SetTextColor(oldColor);
}

void DrawingVisitor::Visit(VerticalText *text) {
	CFont *oldFont;
	CFont *currentFont = this->dc->GetCurrentFont();
	LOGFONT logFont;
	currentFont->GetLogFont(&logFont);
	logFont.lfEscapement = 900; //기울기
	logFont.lfWeight = 700;

	CFont font;
	font.CreateFontIndirectA(&logFont);
	oldFont = this->dc->SelectObject(&font);

	this->dc->TextOutA(text->GetX(), text->GetY(), text->GetContent().c_str());

	this->dc->SelectObject(oldFont);
}

void DrawingVisitor::Visit(RectangleGraph *rectangleGraph) {
	this->dc->Rectangle(&rectangleGraph->GetRect());
}

void DrawingVisitor::Visit(LayerBox *layerBox) {
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, layerBox->GetColor()); //선 스타일 지정
	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 255, 255));

	COLORREF oldColor = this->dc->SetBkColor(RGB(255, 255, 255)); //배경색 지정
	CPen *oldPen = this->dc->SelectObject(&pen);
	CBrush *oldBrush = this->dc->SelectObject(&brush);

	RECT rect = layerBox->GetRect();
	Scroll *scroll = this->scrollController->GetScroll();
	rect.top -= scroll->GetPosition();
	rect.bottom -= scroll->GetPosition();

	this->dc->Rectangle(&rect);//사각형 그리기

	this->dc->MoveTo(rect.left, rect.bottom + 1);
	this->dc->LineTo(rect.right + 1, rect.bottom + 1);
	this->dc->MoveTo(rect.right + 1, rect.top);
	this->dc->LineTo(rect.right + 1, rect.bottom + 1);

	//폰트 지정
	CFont *oldFont;
	CFont *currentFont = this->dc->GetCurrentFont();
	LOGFONT logFont;
	currentFont->GetLogFont(&logFont);
	CFont font;
	font.CreateFont(25, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS, "궁서");

	oldFont = this->dc->SelectObject(&font);

	//폰트 사이즈 계산
	CSize size;
	CString type(layerBox->GetType().c_str());
	size = this->dc->GetTextExtent(type); //type을 dc에 쓸 때 크기 가져오기
	Long typeWidth = size.cx;
	Long typeHeight = size.cy;

	//텍스트 쓸 x좌표=사각형 시작좌표x + (사각형 폭-글자폭)/2
	Long x = rect.left + ((rect.right - rect.left) - typeWidth) / 2;
	//텍스트 쓸 y좌표=사각형 시작좌표y + 사각형 높이/2 - 글자높이/2
	Long y = (rect.top + (rect.bottom - rect.top) / 2) - size.cy / 2;
	Text *text = new HorizontalText(x, y, layerBox->GetType(), layerBox->GetColor());

	text->Accept(this); //텍스트 그리기
	if (text != NULL) {
		delete text;
	}

	this->dc->SelectObject(oldFont);

	this->dc->SelectObject(oldPen);
	this->dc->SelectObject(oldBrush);
	this->dc->SetBkColor(oldColor);

	font.DeleteObject();
	pen.DeleteObject();
	brush.DeleteObject();

}


void DrawingVisitor::Visit(LayerBoxControl *layerBoxControl) {
	Long i = 0;

	while (i < layerBoxControl->GetLength()) {
		layerBoxControl->GetAt(i)->Accept(this);
		i++;
	}
}

void DrawingVisitor::Visit(Arrow * arrow) {
	RECT rect = arrow->GetRect();
	CPen pen;
	pen.CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
	CPen *oldPen = this->dc->SelectObject(&pen);

	//rect의 왼쪽끝 중앙으로 이동
	dc->MoveTo(rect.left, rect.top + (rect.bottom - rect.top) / 2);
	//오른쪽 끝까지 중앙 가로선 긋기
	dc->LineTo(rect.right, rect.top + (rect.bottom - rect.top) / 2);
	//오른쪽 끝에서 중앙 맨위로 대각선 긋기
	dc->LineTo(rect.left + (rect.right - rect.left) / 2, rect.top);
	//오른쪽끝 중앙으로 이동
	dc->MoveTo(rect.right, rect.top + (rect.bottom - rect.top) / 2);
	//오른쪽 끝 중앙에서 중앙맨아래로 대각선 긋기
	dc->LineTo(rect.left + (rect.right - rect.left) / 2, rect.bottom);

	this->dc->SelectObject(oldPen);
}

void DrawingVisitor::Visit(AddBox* addBox) {
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, addBox->GetColor());
	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 255, 255));
	CPen *oldPen = this->dc->SelectObject(&pen);
	CBrush *oldBrush = this->dc->SelectObject(&brush);
	COLORREF oldColor = this->dc->SetBkColor(RGB(255, 255, 255)); //배경색 지정

	// 1. 사각형 좌표를 읽는다.
	RECT rect = addBox->GetRect();
	Scroll *scroll = this->scrollController->GetScroll();
	rect.top -= scroll->GetPosition();
	rect.bottom -= scroll->GetPosition();

	// 2. 사각형을 그린다.
//기존에 그리는 처리를 바꿉니다.
	if (addBox->GetIsClicked() == true) {
		this->dc->Rectangle(rect.left + 1, rect.top + 1, rect.right + 1, rect.bottom + 1);
		this->dc->Draw3dRect(&rect, ::GetSysColor(COLOR_3DHIGHLIGHT), ::GetSysColor(COLOR_3DHILIGHT));
	}
	else {
		this->dc->Rectangle(&rect);
		//입체 효과
		this->dc->MoveTo(rect.left, rect.bottom + 1);
		this->dc->LineTo(rect.right + 1, rect.bottom + 1);
		this->dc->MoveTo(rect.right + 1, rect.top);
		this->dc->LineTo(rect.right + 1, rect.bottom + 1);

		this->dc->Draw3dRect(&rect, ::GetSysColor(COLOR_3DHILIGHT), ::GetSysColor(COLOR_3DHIGHLIGHT));
	}



	// 3. +에 위치를 구한다.
	Long plusX = rect.left + (rect.right - rect.left) / 2; //딱정중앙x
	Long plusY = rect.top + (rect.bottom - rect.top) / 2; //딱정중앙y
	Long plusLength = static_cast<Long>((rect.bottom - rect.top)*0.6);
	//더하기 기호의 가로세로 길이: 싸는 사각형폭의 60%

	if (addBox->GetIsClicked() == true) {
		plusX += 2;
		plusY += 2;
	}

	// 4. +를 그린다.
	this->dc->MoveTo(plusX - plusLength / 2, plusY); //+그릴때 왼쪽중앙으로 이동
	this->dc->LineTo(plusX + plusLength / 2, plusY); //가로줄쫙긋기
	this->dc->MoveTo(plusX, plusY - plusLength / 2); //중앙맨위로 이동
	this->dc->LineTo(plusX, plusY + plusLength / 2); //세로줄쫙긋기

	this->dc->SelectObject(oldPen);
	this->dc->SelectObject(oldBrush);
	pen.DeleteObject();
	brush.DeleteObject();

}

DrawingVisitor& DrawingVisitor::operator=(const DrawingVisitor& source) {
	this->dc = source.dc;

	return *this;
}

void DrawingVisitor::Visit(Cell* cell) {
	CBrush brush;
	brush.CreateSolidBrush(cell->GetColor());
	CBrush *oldBrush = this->dc->SelectObject(&brush);

	RECT rect = cell->GetRect();
	Scroll *scroll = this->scrollController->GetScroll();
	rect.top -= scroll->GetPosition();
	rect.bottom -= scroll->GetPosition();

	RectangleGraph rectangleGraph(rect, cell->GetColor());
	rectangleGraph.Accept(this);

	this->dc->SelectObject(oldBrush);
	brush.DeleteObject();
}

void DrawingVisitor::Visit(Table* table) {
	Long i = 0;
	while (i < table->GetLength()) {
		table->GetAt(i)->Accept(this);
		i++;
	}
}

void DrawingVisitor::Visit(Layout *layout) {
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	CPen *oldPen = this->dc->SelectObject(&pen);

	//폰트 지정
	CFont *oldFont;
	CFont *currentFont = this->dc->GetCurrentFont();
	LOGFONT logFont;
	currentFont->GetLogFont(&logFont);
	CFont font;
	font.CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS, "궁서");

	oldFont = this->dc->SelectObject(&font);

	Long i = 0;
	while (i < layout->GetLength()) {
		layout->GetAt(i)->Accept(this);
		i++;
	}

	this->dc->SelectObject(oldFont);
	this->dc->SelectObject(oldPen);
	font.DeleteObject();
	pen.DeleteObject();
}

void DrawingVisitor::Visit(RoundRectangle *roundRectangle) {
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, roundRectangle->GetColor()); //선 스타일 지정
	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 255, 255));

	COLORREF oldColor = this->dc->SetBkColor(RGB(255, 255, 255)); //배경색 지정
	CPen *oldPen = this->dc->SelectObject(&pen);
	CBrush *oldBrush = this->dc->SelectObject(&brush);


	RECT rect = roundRectangle->GetRect();
	//그리는 코드를 수정합니다.
	if (roundRectangle->GetIsClicked() == true) {
		this->dc->RoundRect(rect.left + 1, rect.top + 1, rect.right + 1, rect.bottom + 1, 10, 10); //실제 둥근 사각형
		this->dc->Draw3dRect(&rect, ::GetSysColor(COLOR_3DHIGHLIGHT), ::GetSysColor(COLOR_3DHILIGHT));
	}
	else {
		this->dc->RoundRect(rect.left + 1, rect.top + 1, rect.right + 1, rect.bottom + 1, 10, 10); //입체 효과
		this->dc->RoundRect(rect.left, rect.top, rect.right, rect.bottom, 10, 10); //실제 둥근 사각형
		this->dc->Draw3dRect(&rect, ::GetSysColor(COLOR_3DHILIGHT), ::GetSysColor(COLOR_3DHIGHLIGHT));
	}

	//폰트 지정
	CFont *oldFont;
	CFont *currentFont = this->dc->GetCurrentFont();
	LOGFONT logFont;
	currentFont->GetLogFont(&logFont);

	CFont font;
	font.CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS, "궁서");
	oldFont = this->dc->SelectObject(&font);

	//폰트 사이즈 계산
	CSize size;
	CString content(roundRectangle->GetContent().c_str());
	size = this->dc->GetTextExtent(content); //type을 dc에 쓸 때 크기 가져오기
	Long contentWidth = size.cx;
	Long contentHeight = size.cy;

	if (roundRectangle->GetIsClicked() == true) {
		rect.right += 2;
		rect.bottom += 2;
	}
	//텍스트 쓸 x좌표=사각형 시작좌표x + (사각형 폭-글자폭)/2
	Long x = rect.left + ((rect.right - rect.left) - contentWidth) / 2;
	//텍스트 쓸 y좌표=사각형 시작좌표y + 사각형 높이/2 - 글자높이/2
	Long y = (rect.top + (rect.bottom - rect.top) / 2) - size.cy / 2;
	Text *text = new HorizontalText(x, y, roundRectangle->GetContent(), roundRectangle->GetColor());
	text->Accept(this); //텍스트 그리기
	if (text != NULL) {
		delete text;
	}

	this->dc->SelectObject(oldFont);

	this->dc->SelectObject(oldPen);
	this->dc->SelectObject(oldBrush);
	this->dc->SetBkColor(oldColor);

	font.DeleteObject();
	pen.DeleteObject();
	brush.DeleteObject();
}

void DrawingVisitor::Visit(LayerToolTip *layerToolTip) {
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0)); //선 스타일 지정
	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 255, 255));

	//COLORREF oldColor; //= this->dc->SetBkColor(RGB(255, 255, 255)); //배경색 지정
	CPen *oldPen = this->dc->SelectObject(&pen);
	CBrush *oldBrush = this->dc->SelectObject(&brush);

	//폰트 지정	
	CFont *oldFont;
	CFont *currentFont = this->dc->GetCurrentFont();
	LOGFONT logFont;
	currentFont->GetLogFont(&logFont);

	CFont font;
	font.CreateFont(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS, "궁서");
	oldFont = this->dc->SelectObject(&font);

	Long i = 0;
	while (i < layerToolTip->GetLength()) {
		layerToolTip->GetAt(i)->Accept(this);
		i++;
	}

	this->dc->SelectObject(oldFont);

	this->dc->SelectObject(oldPen);
	this->dc->SelectObject(oldBrush);
	//this->dc->SetBkColor(oldColor);

	font.DeleteObject();
	pen.DeleteObject();
	brush.DeleteObject();
}

void DrawingVisitor::Visit(Icon *icon) {
	CPen pen;
	//pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0)); //선 스타일 지정
	CBrush brush;
	//brush.CreateSolidBrush(RGB(235, 235, 235));

	CRect rect = icon->GetRect();

	CDC memDC;
	memDC.CreateCompatibleDC(this->dc);
	BITMAP bitmapInfo;
	CBitmap bitmap;
	CBitmap *oldBitmap;

	bitmap.LoadBitmapA(icon->GetID());

	bitmap.GetBitmap(&bitmapInfo);
	oldBitmap = memDC.SelectObject(&bitmap);
	this->dc->TransparentBlt(rect.left, rect.top, rect.Width(), rect.Height(),
		&memDC, 0, 0, bitmapInfo.bmWidth, bitmapInfo.bmHeight, RGB(255, 255, 255));

	memDC.SelectObject(oldBitmap);

	memDC.DeleteDC();
	pen.DeleteObject();
	brush.DeleteObject();
}

void DrawingVisitor::Visit(Circle *circle) {
	CPen pen;
	CPen *oldPen;
	CBrush brush;
	brush.CreateSolidBrush(RGB(248, 248, 248));

	//COLORREF oldColor = this->dc->SetBkColor(RGB(248, 248, 248)); //배경색 지정
	CBrush *oldBrush = this->dc->SelectObject(&brush);

	RECT rect = circle->GetRect();
	//그리는 코드를 수정합니다.
	if (circle->GetIsClicked() == true) {
		pen.CreatePen(PS_SOLID, 13, RGB(0, 0, 255)); //선 스타일 지정
		oldPen = this->dc->SelectObject(&pen);
		this->dc->Ellipse(rect.left + 1, rect.top + 1, rect.right + 1, rect.bottom + 1);
	}
	else {
		pen.CreatePen(PS_SOLID, 13, circle->GetColor()); //선 스타일 지정
		oldPen = this->dc->SelectObject(&pen);
		this->dc->Ellipse(&rect);
	}

	this->dc->SelectObject(oldPen);
	this->dc->SelectObject(oldBrush);
	//this->dc->SetBkColor(oldColor);

	pen.DeleteObject();
	brush.DeleteObject();
}

void DrawingVisitor::Visit(Cross *cross) {
	CPen pen;
	CPen *oldPen;
	CBrush brush;
	brush.CreateSolidBrush(cross->GetColor());

	CBrush *oldBrush = this->dc->SelectObject(&brush);

	RECT rect = cross->GetRect();
	//그리는 코드를 수정합니다.
	if (cross->GetIsClicked() == true) {
		pen.CreatePen(PS_SOLID, 13, RGB(255, 0, 0)); //선 스타일 지정
		oldPen = this->dc->SelectObject(&pen);
		this->dc->MoveTo(rect.left + 1, rect.top + 1);
		this->dc->LineTo(rect.right + 1, rect.bottom + 1);
		this->dc->MoveTo(rect.left + 1, rect.bottom + 1);
		this->dc->LineTo(rect.right + 1, rect.top + 1);
	}
	else {
		pen.CreatePen(PS_SOLID, 13, cross->GetColor()); //선 스타일 지정
		oldPen = this->dc->SelectObject(&pen);
		this->dc->MoveTo(rect.left, rect.top);
		this->dc->LineTo(rect.right, rect.bottom);
		this->dc->MoveTo(rect.left, rect.bottom);
		this->dc->LineTo(rect.right, rect.top);
	}


	this->dc->SelectObject(oldPen);
	this->dc->SelectObject(oldBrush);

	pen.DeleteObject();
	brush.DeleteObject();
}