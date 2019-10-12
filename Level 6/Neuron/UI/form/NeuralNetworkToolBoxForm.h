#ifndef _NEURALNETWORKTOOLBOXFORM_H
#define _NEURALNETWORKTOOLBOXFORM_H

#include <afxwin.h>

class NeuronForm;
class Graph;

class NeuralNetworkToolBoxForm : public CWnd {
public:
	NeuralNetworkToolBoxForm(NeuronForm *neuronForm = 0);
	virtual int OnCreate(LPCREATESTRUCT lpCreateStruct);
	~NeuralNetworkToolBoxForm();
protected:
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
private:
	Graph *newIcon;
	Graph *openIcon;
	Graph *saveIcon;
public:
	NeuronForm *neuronForm;
};

#endif //_NEURALNETWORKTOOLBOXFORM_H