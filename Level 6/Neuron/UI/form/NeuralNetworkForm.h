#ifndef _NEURALNETWORKFORM_H
#define _NEURALNETWORKFORM_H

#include <afxwin.h>
class NeuronForm;
class LayerInformationForm;
class Graph;
class ScrollController;
class NeuralNetworkForm : public CWnd {
public:
	NeuralNetworkForm(NeuronForm *neuronForm = 0);
	virtual int OnCreate(LPCREATESTRUCT lpCreateStruct);
	~NeuralNetworkForm();
public:
	Graph *layerToolTip;
	NeuronForm *neuronForm;
	Graph *layerBoxControl;
	Graph *current; //현재 선택되어있는 계층 상자를 뜻함 : rbuttonup에서 지정
	ScrollController *scrollController;
protected:
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnCommandRange(UINT uID);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()
private:
	LayerInformationForm *layerInformationForm;
};

#endif //_NEURALNETWORKFORM_H