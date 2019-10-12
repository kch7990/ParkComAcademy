#include "RecognizingForm.h"
#include "NeuronForm.h"
#include "NeuralNetwork.h"
#include "ImageFile.h"
#include "LabelFile.h"
#include "Array.h"
#include "Layer.h"
#include "Softmax.h"
#include "Recognizer.h"
#include "RoundRectangle.h"
#include "LearningForm.h"
#include "Trainer.h"
#include "Visitor.h"
#include "DrawingVisitor.h"
#include "Icon.h"
#include "Convolution.h"
#include "ConvolutionFilter.h"
#include "FilterCube.h"
#include "GraphMaker.h"
#include "resource.h"
#include "Circle.h"
#include "Cross.h"

BEGIN_MESSAGE_MAP(RecognizingForm, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

RecognizingForm::RecognizingForm(NeuronForm *neuronForm)
	: imageRect(30, 60, 30 + 28 * 6, 60 + 28 * 6)
	, recognizationResult({ 0, })
	, imageFile(TEST_IMAGE_FILE_NAME)
	, labelFile(TEST_LABEL_FILE_NAME)
{
	this->neuronForm = neuronForm;
	this->index = -1;
	this->recognizingNumber = -1;
	this->label = -1;
	this->recognizer = NULL;
	this->recognizeButton = NULL;
	this->clearButton = NULL;
	this->isPaint = FALSE;
	this->accuracyBarRect = { this->imageRect.left, this->imageRect.top + 210, this->imageRect.left + 388, this->imageRect.top + 210 + 50 };
	this->correctButton = NULL;
	this->wrongButton = NULL;
}

RecognizingForm::~RecognizingForm() {
	if (this->recognizer != NULL) {
		if (this->recognizer->GetIsRecognizing() == TRUE) {
			this->recognizer->Stop();
		}
		delete this->recognizer;
	}
	if (this->recognizeButton != NULL) {
		delete this->recognizeButton;
	}
	if (this->clearButton != NULL) {
		delete this->clearButton;
	}
	if (this->correctButton != NULL) {
		delete this->correctButton;
	}
	if (this->wrongButton != NULL) {
		delete this->wrongButton;
	}
}

int RecognizingForm::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CWnd::OnCreate(lpCreateStruct);

	for (Long i = 0; i < 10; i++)
	{
		this->results.Store(i, 0.0);
	}

	this->imageFile.ReadHeader();
	this->labelFile.ReadHeader();
	this->recognizer = new Recognizer(this);

	CPaintDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	this->imageDC.CreateCompatibleDC(&dc);
	this->imageBitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	this->imageDC.SelectObject(&this->imageBitmap);

	this->recognizeButton = new Icon(CRect(30, 340, 100, 410), RGB(255, 255, 255), IDB_RECOGNIZE_OFF, false);
	this->clearButton = new Icon(CRect(imageRect.left, imageRect.top - 30, imageRect.left + 30, imageRect.top - 10), RGB(0, 245, 0), IDB_RESET, false);

	this->correctButton = new Circle(CRect(120, 355, 160, 395), RGB(0, 102, 255), false);
	this->wrongButton = new Cross(CRect(190, 355, 230, 395), RGB(255, 0, 102), false);

	return 0;
}

void RecognizingForm::OnPaint() {
	CPaintDC dc(this);
	CRect rect;
	this->GetClientRect(&rect);

	CDC memoryDC;
	CBitmap bitmap;
	memoryDC.CreateCompatibleDC(&dc);
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	memoryDC.SelectObject(&bitmap);
	memoryDC.FillSolidRect(&rect, RGB(248, 248, 248));

	CFont font;
	font.CreateFont(13, 8, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS, "궁서");
	CFont *oldFont = memoryDC.SelectObject(&font);

	// 1. 이미지 출력

	CRect rectangleRect(this->imageRect.left - 1, this->imageRect.top - 1, this->imageRect.right + 2, this->imageRect.bottom + 2);
	memoryDC.Rectangle(&rectangleRect);
	memoryDC.TextOutA(this->imageRect.left + 60, this->imageRect.top - 30, "INPUT");
	//CString indexString;
	//indexString.Format("횟수 : %d", this->recognizationResult.count);
	//memoryDC.TextOutA(this->imageRect.left + 60, this->imageRect.top + imageRect.Height() + 10, indexString);

	CDC reductionDC;
	CBitmap reductionBitmap;
	reductionDC.CreateCompatibleDC(&imageDC);
	reductionBitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	reductionDC.SelectObject(&reductionBitmap);

	if (isPaint == false) {
		Long j = 0;
		for (Long row = 0; row < imageFile.GetRowCount(); row++) {
			for (Long column = 0; column < imageFile.GetColumnCount(); column++) {
				double pixel = this->image[j++];
				reductionDC.SetPixel(column, row, RGB(pixel, pixel, pixel));
			}
		}
		this->imageDC.StretchBlt(0, 0, this->imageRect.Width(), this->imageRect.Height(), &reductionDC, 0, 0, 28, 28, SRCCOPY);
	}
	reductionDC.DeleteDC();
	reductionBitmap.DeleteObject();

	// 2. 추론한 수 출력
	memoryDC.TextOutA(this->imageRect.left + this->imageRect.right + 70, this->imageRect.top - 30, "OUTPUT");
	CRect recognizationRect(this->imageRect.right + 50, this->imageRect.top, this->imageRect.right + 50 + this->imageRect.Width(), this->imageRect.bottom);
	memoryDC.Rectangle(&recognizationRect);

	if (this->recognizingNumber != -1) {
		CString recognizingNumber;
		recognizingNumber.Format("%d", this->recognizingNumber);

		CFont font;
		font.CreatePointFont(700, _T("Arial"), &memoryDC);
		CFont *oldFont = memoryDC.SelectObject(&font);
		CSize size = memoryDC.GetTextExtent(recognizingNumber);
		Long x = (recognizationRect.Width() - size.cx) / 2;
		Long y = (recognizationRect.Height() - size.cy) / 2;

		int oldBkMode = memoryDC.SetBkMode(TRANSPARENT);
		memoryDC.TextOutA(recognizationRect.left + x, recognizationRect.top + y, recognizingNumber);
		memoryDC.SetBkMode(oldBkMode);
		memoryDC.SelectObject(oldFont);
	}

	// 3. 정확도바
	CPen pen;
	pen.CreatePen(PS_NULL, 0, RGB(0, 0, 0));
	CPen *oldPen = memoryDC.SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(188, 229, 92));
	CBrush *oldBrush = memoryDC.SelectObject(&brush);
	memoryDC.Rectangle(&this->accuracyBarRect);
	brush.DeleteObject();
	memoryDC.SelectObject(oldBrush);

	brush.CreateSolidBrush(RGB(0x2F, 0x9D, 0x27));
	memoryDC.SelectObject(&brush);

	memoryDC.Rectangle(this->accuracyBarRect.left, this->accuracyBarRect.top, this->accuracyBarRect.left + this->recognizationResult.accuracy * 388, this->accuracyBarRect.bottom);

	brush.DeleteObject();
	pen.DeleteObject();
	memoryDC.SelectObject(oldPen);
	memoryDC.SelectObject(oldBrush);

	CString accuracyString;
	accuracyString.Format("%.2f%c (%d/%d)", this->recognizationResult.accuracy * 100, '%', this->recognizationResult.answerCount, this->recognizationResult.count);
	int oldBkMode = memoryDC.SetBkMode(TRANSPARENT);
	CSize size = memoryDC.GetTextExtent(accuracyString);
	CRect accuracyStringRect;
	accuracyStringRect.left = this->accuracyBarRect.left + (this->accuracyBarRect.Width() - size.cx) / 2;
	accuracyStringRect.top = this->accuracyBarRect.top + (this->accuracyBarRect.Height() - size.cy) / 2;
	accuracyStringRect.right = accuracyStringRect.left + size.cx;
	accuracyStringRect.bottom = accuracyStringRect.top + size.cy;

	memoryDC.DrawText(accuracyString, &accuracyStringRect, DT_CENTER);
	memoryDC.SetBkMode(oldBkMode);

	CRect barGraphRect(30, 450, 480, 770);
	memoryDC.Rectangle(barGraphRect);
	// 4. 확률 막대그래프

	CString number;
	for (Long i = 0; i < results.GetLength(); i++)
	{
		number.Format("%d - %.2f%c", i, this->results[i] * 100, '%');
		COLORREF oldColor = memoryDC.SetBkColor(RGB(255, 255, 255));
		memoryDC.TextOutA(barGraphRect.left + 10, i * 30 + barGraphRect.top + 10, number);
		memoryDC.TextOutA(barGraphRect.left + 95, i * 30 + barGraphRect.top + 10, "- ");
		{
			COLORREF rgb;
			if (this->results[i] > 0.8) {
				rgb = RGB(47, 157, 39);
			}
			else if (this->results[i] > 0.5) {
				rgb = RGB(100, 75, 0);
			}
			else if (this->results[i] > 0.1) {
				rgb = RGB(255, 94, 0);
			}
			else {
				rgb = RGB(255, 0, 0);
			}

			brush.CreateSolidBrush(rgb);
			oldBrush = memoryDC.SelectObject(&brush);
			pen.CreatePen(PS_NULL, 5, RGB(255, 255, 255));
			oldPen = memoryDC.SelectObject(&pen);
			memoryDC.Rectangle(barGraphRect.left + 105, barGraphRect.top + i * 30 + 10, barGraphRect.left + 108 + this->results[i] * 200, barGraphRect.top + i * 30 + 30);

			pen.DeleteObject();
			brush.DeleteObject();
			memoryDC.SelectObject(oldBrush);
			memoryDC.SelectObject(oldPen);
			memoryDC.SetBkColor(oldColor);
		}
	}

	//6. 버튼출력
	{
		Visitor *drawingVisitor = new DrawingVisitor(&memoryDC);
		if (this->recognizeButton != NULL) {
			drawingVisitor->Visit(dynamic_cast<Icon*>(this->recognizeButton));
		}
		if (this->clearButton != NULL) {
			drawingVisitor->Visit(dynamic_cast<Icon*>(this->clearButton));
		}
		if (this->correctButton != NULL) {
			this->correctButton->Accept(drawingVisitor);
		}
		if (this->wrongButton != NULL) {
			this->wrongButton->Accept(drawingVisitor);
		}

		if (drawingVisitor != NULL) {
			delete drawingVisitor;
		}
	}

	if (this->recognizingNumber != -1)
	{
		memoryDC.BitBlt(this->imageRect.left, this->imageRect.top, this->imageRect.Width(), this->imageRect.Height(), &this->imageDC, 0, 0, SRCCOPY);
	}

	memoryDC.SelectObject(oldFont);
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memoryDC, 0, 0, SRCCOPY);

}

void RecognizingForm::OnClose() {
	if (this->recognizer != NULL) {
		delete this->recognizer;
	}
	if (this->recognizeButton != NULL) {
		delete this->recognizeButton;
	}
	if (this->clearButton != NULL) {
		delete this->clearButton;
	}
	if (this->correctButton != NULL) {
		delete this->correctButton;
	}
	if (this->wrongButton != NULL) {
		delete this->wrongButton;
	}

	CWnd::OnClose();
}


void RecognizingForm::OnLButtonUp(UINT nFlags, CPoint point) {
	if (this->recognizeButton != NULL && this->recognizeButton->GetIsClicked() == TRUE) {
		if (this->recognizeButton->GetID() == IDB_RECOGNIZE_ON) { // 추론상태 아이콘이면
		   // Clear버튼을 지우다.
			if (this->clearButton != NULL) {
				delete this->clearButton;
				this->clearButton = NULL;
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
			this->recognizer->AutoRecognize();
		}
		else if (this->recognizeButton->GetID() == IDB_RECOGNIZE_OFF) { // 추론아님상태 아이콘이면
		   // 인식기에서 멈춘다.
			this->recognizer->Stop();
			// Clear 버튼을 만들다.
			this->clearButton = new Icon(CRect(imageRect.left, imageRect.top - 30, imageRect.left + 30, imageRect.top - 10), RGB(0, 245, 0), IDB_RESET, false);
			// 학습하다 폼의 시작 버튼을 만들다.
			this->neuronForm->learningForm->startButton = new RoundRectangle(CRect(600, 740, 700, 780), "학습 시작", RGB(0, 0, 255), false);
			// 학습하다 폼을 갱신하다.
			this->neuronForm->learningForm->Invalidate();
		}
		*dynamic_cast<Icon*>(this->recognizeButton) = Icon(this->recognizeButton->GetRect(), this->recognizeButton->GetColor(), this->recognizeButton->GetID(), false);
		this->isPaint = false;
	}
	else if (this->clearButton != NULL && this->clearButton->GetIsClicked() == TRUE) {
		*dynamic_cast<Icon*>(this->clearButton) = Icon(this->clearButton->GetRect(), this->clearButton->GetColor(), IDB_RESET, false);
		// 모두초기화 한다.
		this->imageDC.FillSolidRect(&imageRect, RGB(0, 0, 0));
		Long i = 0;
		while (i < this->image.GetLength()) {
			this->image.Modify(i, 255);
			i++;
		}
		this->isPaint = FALSE;
	}
	else if (isPaint == true && point.x > this->imageRect.left && point.x < this->imageRect.right && point.y > this->imageRect.top && point.y < this->imageRect.bottom && 
			this->neuronForm->isWorking == FALSE) {
		CPaintDC dc(this);
		this->imageDC.BitBlt(0, 0, this->imageRect.Width(), this->imageRect.Height(), &dc, this->imageRect.left, this->imageRect.top, SRCCOPY);

		CDC memoryDC;
		CBitmap bitmap;
		memoryDC.CreateCompatibleDC(&dc);
		bitmap.CreateCompatibleBitmap(&dc, this->imageRect.Width(), this->imageRect.Height());
		memoryDC.SelectObject(&bitmap);
		memoryDC.StretchBlt(0, 0, 28, 28, &this->imageDC, 1, 1, this->imageRect.Width() - 1, this->imageRect.Height() - 1, SRCCOPY);

		Long k = 0;
		Array<double> pixels(28 * 28);
		for (Long i = 0; i < 28; i++)
		{
			Long originY = i / (28 / (this->imageRect.Height()*1.0));
			for (Long j = 0; j < 28; j++)
			{
				Long originX = j / (28 / (this->imageRect.Width()*1.0));
				COLORREF pixel = this->imageDC.GetPixel(originX, originY);
				BYTE r = 255 - GetRValue(pixel);
				BYTE g = 255 - GetGValue(pixel);
				BYTE b = 255 - GetBValue(pixel);
				memoryDC.SetPixel(j, i, RGB(r, g, b));
				pixels.Store(k++, r);
			}
		}

		this->image = pixels;
#if 0
		Convolution convolution(1, 1, 1, 3);
		Neuron *filterCube = new FilterCube;
		Matrix<double> filter(3, 3);
		Long i = 0;
		while (i < filter.GetCapacity()) {
			filter.Store(i, 1 / 9.0);
			i++;
		}
		Neuron *convolutionFilter = new ConvolutionFilter(3, filter, filter, filter);
		filterCube->Add(convolutionFilter);
		convolution.Add(filterCube);
		this->image = convolution.Forward(this->image);
#endif

		Array<double> signals(this->image);

		Long j = 0;
		while (j < signals.GetLength()) {
			signals[j] = signals[j] / 255.0;
			j++;
		}
		this->recognizer->Recognize(signals);
	}

	// 3. 채점 버튼 영역일 때
	if (this->correctButton != NULL && this->wrongButton != NULL) {
		delete this->correctButton;
		this->correctButton = new Circle(CRect(120, 355, 160, 395), RGB(0, 102, 255), false);
		delete this->wrongButton;
		this->wrongButton = new Cross(CRect(190, 355, 230, 395), RGB(255, 0, 102), false);
		RECT correctRect = this->correctButton->GetRect();
		RECT wrongRect = this->wrongButton->GetRect();
		if (point.x >= correctRect.left && point.x <= correctRect.right && point.y >= correctRect.top && point.y <= correctRect.bottom) {
			// 3.1. 횟수를 센다.
			// 3.2. 정답개수를 센다.
			this->recognizationResult.count++;
			this->recognizationResult.answerCount++;
			this->recognizationResult.accuracy = this->recognizationResult.answerCount / (this->recognizationResult.count*1.0);
		}
		else if (point.x > wrongRect.left && point.x < wrongRect.right && point.y > wrongRect.top && point.y < wrongRect.bottom) {
			//2.1. 횟수를 센다.
			//2.2. 오답횟수를 센다.
			this->recognizationResult.count++;
			this->recognizationResult.wrongAnswerCount++;
			this->recognizationResult.accuracy = this->recognizationResult.answerCount / (this->recognizationResult.count*1.0);
		}
	}


	this->Invalidate();
}

void RecognizingForm::OnLButtonDown(UINT nFlags, CPoint point) {
	CRect rect;
	// 추론 버튼 영역일 때
	// Clear 버튼 영역일 때
	if (this->recognizeButton != NULL) {
		rect = this->recognizeButton->GetRect();
		if (point.x >= rect.left && point.x <= rect.right && point.y >= rect.top && point.y <= rect.bottom) {
			if (this->recognizeButton->GetID() == IDB_RECOGNIZE_OFF) {
				*dynamic_cast<Icon*>(this->recognizeButton) = Icon(rect, this->recognizeButton->GetColor(), IDB_RECOGNIZE_ON, true);
			}
			else if (this->recognizeButton->GetID() == IDB_RECOGNIZE_ON) {
				*dynamic_cast<Icon*>(this->recognizeButton) = Icon(rect, this->recognizeButton->GetColor(), IDB_RECOGNIZE_OFF, true);
			}
		}
	}// Stop 버튼 영역일 때
	if (this->clearButton != NULL) {
		rect = this->clearButton->GetRect();
		if (point.x >= rect.left && point.x <= rect.right && point.y >= rect.top && point.y <= rect.bottom) {
			*dynamic_cast<Icon*>(this->clearButton) = Icon(rect, this->clearButton->GetColor(), IDB_RESET_CLICKED, true);
		}
	}

	// 3. 채점 버튼 영역일 때
	if (this->correctButton != NULL && this->wrongButton != NULL) {
		RECT correctRect = this->correctButton->GetRect();
		RECT wrongRect = this->wrongButton->GetRect();
		if (point.x >= correctRect.left && point.x <= correctRect.right && point.y >= correctRect.top && point.y <= correctRect.bottom) {
			delete this->correctButton;
			this->correctButton = new Circle(CRect(120, 355, 160, 395), RGB(0, 102, 255), true);
		}
		else if (point.x > wrongRect.left && point.x < wrongRect.right && point.y > wrongRect.top && point.y < wrongRect.bottom) {
			delete this->wrongButton;
			this->wrongButton = new Cross(CRect(190, 355, 230, 395), RGB(255, 0, 102), true);
		}
	}

	// 4. 그리기 영역일 때
	rect = this->imageRect;
	if (point.x >= rect.left && point.x <= rect.right && point.y >= rect.top && point.y <= rect.bottom && this->neuronForm->isWorking == FALSE) {
		// 그리기 모드를 활성화 한다.
		this->isPaint = TRUE;
	}

	this->Invalidate();
}

void RecognizingForm::OnMouseMove(UINT nFlags, CPoint point) {
	if (isPaint == true && nFlags == MK_LBUTTON && point.x > this->imageRect.left && point.x < this->imageRect.right && point.y > this->imageRect.top && point.y < this->imageRect.bottom) {
		CClientDC dc(this);
		CPen pen;
		pen.CreatePen(PS_SOLID | PS_ALTERNATE, 11, RGB(0, 0, 0));
		CPen *oldPen = dc.SelectObject(&pen);
		dc.MoveTo(previousPoint);
		dc.LineTo(point);

		pen.DeleteObject();
		dc.SelectObject(oldPen);
	}
	this->previousPoint = point;

	CRect rect;
	if (this->recognizeButton != NULL) {
		rect = this->recognizeButton->GetRect();
		if (rect.left <= point.x && rect.right >= point.x && rect.top <= point.y && rect.bottom >= point.y) {
			SetCursor(LoadCursor(NULL, IDC_HAND));
		}
	}
	if (this->clearButton != NULL) {
		rect = this->clearButton->GetRect();
		if (rect.left <= point.x && rect.right >= point.x && rect.top <= point.y && rect.bottom >= point.y) {
			SetCursor(LoadCursor(NULL, IDC_HAND));
		}
	}
	if (this->correctButton != NULL) {
		rect = this->correctButton->GetRect();
		if (rect.left <= point.x && rect.right >= point.x && rect.top <= point.y && rect.bottom >= point.y) {
			SetCursor(LoadCursor(NULL, IDC_HAND));
		}
	}
	if (this->wrongButton != NULL) {
		rect = this->wrongButton->GetRect();
		if (rect.left <= point.x && rect.right >= point.x && rect.top <= point.y && rect.bottom >= point.y) {
			SetCursor(LoadCursor(NULL, IDC_HAND));
		}
	}

	CWnd::OnMouseMove(nFlags, point);
}