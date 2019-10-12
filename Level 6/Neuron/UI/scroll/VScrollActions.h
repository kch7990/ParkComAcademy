#ifndef _VSCROLLACTIONS_H
#define _VSCROLLACTIONS_H

#include <afxwin.h>
typedef signed long int Long;

class NeuralNetworkForm;
class LayerInformationForm;
class VScrollAction {
public:
	VScrollAction(NeuralNetworkForm *neuralNetworkForm = 0, LayerInformationForm *layerInformationForm=0);
	VScrollAction(const VScrollAction& source);
	virtual ~VScrollAction() = 0;

	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) = 0;
	
	VScrollAction& operator=(const VScrollAction& source);
protected:
	NeuralNetworkForm *neuralNetworkForm;
	LayerInformationForm *layerInformationForm;
};


class LineUpAction : public VScrollAction {
public:
	LineUpAction(NeuralNetworkForm *neuralNetworkForm = 0, LayerInformationForm *layerInformationForm = 0);
	LineUpAction(const LineUpAction& source);
	virtual ~LineUpAction();

	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	
	LineUpAction& operator=(const LineUpAction& source);
};

class LineDownAction : public VScrollAction {
public:
	LineDownAction(NeuralNetworkForm *neuralNetworkForm = 0, LayerInformationForm *layerInformationForm = 0);
	LineDownAction(const LineDownAction& source);
	virtual ~LineDownAction();

	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	
	LineDownAction& operator=(const LineDownAction& source);
};

class PageUpAction : public VScrollAction {
public:
	PageUpAction(NeuralNetworkForm *neuralNetworkForm = 0, LayerInformationForm *layerInformationForm = 0);
	PageUpAction(const PageUpAction& source);
	virtual ~PageUpAction();

	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	
	PageUpAction& operator=(const PageUpAction& source);
};

class PageDownAction : public VScrollAction {
public:
	PageDownAction(NeuralNetworkForm *neuralNetworkForm = 0, LayerInformationForm *layerInformationForm = 0);
	PageDownAction(const PageDownAction& source);
	virtual ~PageDownAction();

	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	
	PageDownAction& operator=(const PageDownAction& source);
};

class ThumbTrackVScrollAction : public VScrollAction {
public:
	ThumbTrackVScrollAction(NeuralNetworkForm *neuralNetworkForm = 0, LayerInformationForm *layerInformationForm = 0);
	ThumbTrackVScrollAction(const ThumbTrackVScrollAction& source);
	virtual ~ThumbTrackVScrollAction();

	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	
	ThumbTrackVScrollAction& operator=(const ThumbTrackVScrollAction& source);
};

#endif //_VSCROLLACTIONS_H