#ifndef _LEARNINGFORM_H
#define _LEARNINGFORM_H

#include <afxwin.h>
#include <afxcmn.h>
#include "Array.h"

class Trainer;
class NeuronForm;
class Graph;
class LearningForm : public CWnd {
public:
	NeuronForm *neuronForm;
	CProgressCtrl progressBar;
	Graph *lossCoordinateSystem;
	Graph *accuracyCoordinateSystem;
	Trainer *trainer;
	Graph *startButton;
	Graph *stopButton;
	Graph *reStartButton;
	Graph *endButton;
	Graph *timeText;
public:
	LearningForm(NeuronForm* neuronForm = 0);
	~LearningForm();
	virtual int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#endif // !_LEARNINGFORM_H
