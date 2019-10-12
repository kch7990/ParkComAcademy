#ifndef _NEURONFORM_H
#define _NEURONFORM_H

#include <afxwin.h>

//class LearningForm;
class NeuralNetworkToolBoxForm;
class RecognizingForm;
class NeuralNetworkForm;
class NeuralNetwork;
class LearningForm;
class Neuron;
class NeuronForm : public CFrameWnd {
public:
	NeuronForm();
	virtual int OnCreate(LPCREATESTRUCT lpCreateStruct); //CFrameWnd »ó¼Ó
public:
	Neuron *neuralNetwork;
	RecognizingForm *recognizingForm;
	NeuralNetworkForm *neuralNetworkForm;
	LearningForm *learningForm;
	NeuralNetworkToolBoxForm *neuralNetworkToolBoxForm;
	BOOL isWorking;

protected:
	afx_msg void OnClose();
	afx_msg void OnCommandRange(UINT uID);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	DECLARE_MESSAGE_MAP()
private:
	CMenu menu;
};

#endif //_NEURONFORM_H