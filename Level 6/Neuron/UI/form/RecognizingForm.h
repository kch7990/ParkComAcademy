#ifndef _RECOGNIZINGFORM_H
#define _RECOGNIZINGFORM_H

#include <afxwin.h>
#include "Array.h"
#include "ImageFile.h"
#include "LabelFile.h"

#define TEST_IMAGE_FILE_NAME "t10k-images.idx3-ubyte"
#define TEST_LABEL_FILE_NAME "t10k-labels.idx1-ubyte"
#define MULTIPLE 6

typedef signed long int Long;

struct RecognizationResult {
	Long answerCount;
	Long wrongAnswerCount;
	Long count;
	double accuracy;
};

class NeuronForm;
class Recognizer;
class Graph;
class RecognizingForm : public CWnd {
public:
	NeuronForm *neuronForm;
	Long index;
	CRect imageRect;
	CRect accuracyBarRect;
	Long recognizingNumber;
	Array<double> results;
	ImageFile imageFile;
	LabelFile labelFile;
	Array<double> image;
	Long label;
	RecognizationResult recognizationResult;
	CPoint previousPoint;
	Graph *recognizeButton;
	Graph *clearButton;
	CDC imageDC;
	CBitmap imageBitmap;
	bool isPaint;
	Recognizer *recognizer;
	Graph *correctButton;
	Graph *wrongButton;
public:
	RecognizingForm(NeuronForm *neuronForm = NULL);
	~RecognizingForm();
	virtual int OnCreate(LPCREATESTRUCT lpCreateStruct);

protected:
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()
	
};

#endif //_RECOGNIZINGFORM_H