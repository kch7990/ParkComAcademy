#ifndef _LAYERINFORMATIONFORM_H
#define _LAYERINFORMATIONFORM_H

#include <afxwin.h>

class Graph;
class Neuron;
class ScrollController;

class LayerInformationForm : public CFrameWnd {
public:
	LayerInformationForm(Neuron *layer = 0);
	virtual int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	DECLARE_MESSAGE_MAP()
public:
	Neuron *layer;
	Graph *layout;
	ScrollController *scrollController;
};

#endif //_LAYERINFORMATIONFORM_H