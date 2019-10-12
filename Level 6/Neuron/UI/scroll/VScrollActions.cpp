#include "VScrollActions.h"
#include "NeuralNetworkForm.h"
#include "LayerInformationForm.h"
#include "ScrollControllers.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//VScrollAction
VScrollAction::VScrollAction(NeuralNetworkForm *neuralNetworkForm, LayerInformationForm *layerInformationForm) {
	this->neuralNetworkForm = neuralNetworkForm;
	this->layerInformationForm = layerInformationForm;
}

VScrollAction::VScrollAction(const VScrollAction& source) {
	this->neuralNetworkForm = source.neuralNetworkForm;
	this->layerInformationForm = source.layerInformationForm;
}

VScrollAction::~VScrollAction() {

}

VScrollAction& VScrollAction::operator=(const VScrollAction& source) {
	this->neuralNetworkForm = source.neuralNetworkForm;
	this->layerInformationForm = source.layerInformationForm;

	return *this;
}

//LineUpAction
LineUpAction::LineUpAction(NeuralNetworkForm *neuralNetworkForm, LayerInformationForm *layerInformationForm)
	: VScrollAction(neuralNetworkForm, layerInformationForm) {

}

LineUpAction::LineUpAction(const LineUpAction& source)
	: VScrollAction(source) {

}

LineUpAction::~LineUpAction() {

}

void LineUpAction::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	if (this->neuralNetworkForm != 0) {
		Long position = this->neuralNetworkForm->scrollController->Up();
		int previous = this->neuralNetworkForm->SetScrollPos(SB_VERT, position, TRUE);
		position = this->neuralNetworkForm->GetScrollPos(SB_VERT);
		this->neuralNetworkForm->scrollController->Move(position);
		this->neuralNetworkForm->ScrollWindow(0, previous - position);
	}
	else if (this->layerInformationForm != 0) {
		Long position = this->layerInformationForm->scrollController->Up();
		int previous = this->layerInformationForm->SetScrollPos(SB_VERT, position, TRUE);
		position = this->layerInformationForm->GetScrollPos(SB_VERT);
		this->layerInformationForm->scrollController->Move(position);
		this->layerInformationForm->ScrollWindow(0, previous - position);
	}
}

LineUpAction& LineUpAction::operator=(const LineUpAction& source) {
	VScrollAction::operator=(source);

	return *this;
}

//LineDownAction
LineDownAction::LineDownAction(NeuralNetworkForm *neuralNetworkForm, LayerInformationForm *layerInformationForm)
	: VScrollAction(neuralNetworkForm, layerInformationForm) {

}

LineDownAction::LineDownAction(const LineDownAction& source)
	: VScrollAction(source) {
}

LineDownAction::~LineDownAction() {

}

void LineDownAction::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	if (this->neuralNetworkForm != 0) {
		Long position = this->neuralNetworkForm->scrollController->Down();
		int previous = this->neuralNetworkForm->SetScrollPos(SB_VERT, position, TRUE);
		position = this->neuralNetworkForm->GetScrollPos(SB_VERT);
		this->neuralNetworkForm->scrollController->Move(position);
		this->neuralNetworkForm->ScrollWindow(0, previous - position);
	}
	else if (this->layerInformationForm != 0) {
		Long position = this->layerInformationForm->scrollController->Down();
		int previous = this->layerInformationForm->SetScrollPos(SB_VERT, position, TRUE);
		position = this->layerInformationForm->GetScrollPos(SB_VERT);
		this->layerInformationForm->scrollController->Move(position);
		this->layerInformationForm->ScrollWindow(0, previous - position);
	}
}

LineDownAction& LineDownAction::operator=(const LineDownAction& source) {
	VScrollAction::operator=(source);

	return *this;
}

//PageUpAction
PageUpAction::PageUpAction(NeuralNetworkForm *neuralNetworkForm, LayerInformationForm *layerInformationForm)
	: VScrollAction(neuralNetworkForm, layerInformationForm) {

}

PageUpAction::PageUpAction(const PageUpAction& source)
	: VScrollAction(source) {

}

PageUpAction::~PageUpAction() {

}

void PageUpAction::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	if (this->neuralNetworkForm != 0) {
		Long position = this->neuralNetworkForm->scrollController->PageUp();
		int previous = this->neuralNetworkForm->SetScrollPos(SB_VERT, position, TRUE);
		position = this->neuralNetworkForm->GetScrollPos(SB_VERT);
		this->neuralNetworkForm->scrollController->Move(position);
		this->neuralNetworkForm->ScrollWindow(0, previous - position);
	}
	else if (this->layerInformationForm != 0) {
		Long position = this->layerInformationForm->scrollController->PageUp();
		int previous = this->layerInformationForm->SetScrollPos(SB_VERT, position, TRUE);
		position = this->layerInformationForm->GetScrollPos(SB_VERT);
		this->layerInformationForm->scrollController->Move(position);
		this->layerInformationForm->ScrollWindow(0, previous - position);
	}
}

PageUpAction& PageUpAction::operator=(const PageUpAction& source) {
	VScrollAction::operator=(source);

	return *this;
}

//PageDownAction
PageDownAction::PageDownAction(NeuralNetworkForm *neuralNetworkForm, LayerInformationForm *layerInformationForm)
	: VScrollAction(neuralNetworkForm, layerInformationForm) {

}

PageDownAction::PageDownAction(const PageDownAction& source)
	: VScrollAction(source) {
}

PageDownAction::~PageDownAction() {

}

void PageDownAction::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	if (this->neuralNetworkForm != 0) {
		Long position = this->neuralNetworkForm->scrollController->PageDown();
		int previous = this->neuralNetworkForm->SetScrollPos(SB_VERT, position, TRUE);
		position = this->neuralNetworkForm->GetScrollPos(SB_VERT);
		this->neuralNetworkForm->scrollController->Move(position);
		this->neuralNetworkForm->ScrollWindow(0, previous - position);
	}
	else if (this->layerInformationForm != 0) {
		Long position = this->layerInformationForm->scrollController->PageDown();
		int previous = this->layerInformationForm->SetScrollPos(SB_VERT, position, TRUE);
		position = this->layerInformationForm->GetScrollPos(SB_VERT);
		this->layerInformationForm->scrollController->Move(position);
		this->layerInformationForm->ScrollWindow(0, previous - position);
	}
}

PageDownAction& PageDownAction::operator=(const PageDownAction& source) {
	VScrollAction::operator=(source);

	return *this;
}

//ThumbTrackVScrollAction
ThumbTrackVScrollAction::ThumbTrackVScrollAction(NeuralNetworkForm *neuralNetworkForm, LayerInformationForm *layerInformationForm)
	: VScrollAction(neuralNetworkForm, layerInformationForm) {

}

ThumbTrackVScrollAction::ThumbTrackVScrollAction(const ThumbTrackVScrollAction& source)
	: VScrollAction(source) {

}

ThumbTrackVScrollAction::~ThumbTrackVScrollAction() {

}

void ThumbTrackVScrollAction::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	if (this->neuralNetworkForm != 0) {
		Long position = this->neuralNetworkForm->scrollController->Move(nPos);
		int previous = this->neuralNetworkForm->SetScrollPos(SB_VERT, position, TRUE);
		position = this->neuralNetworkForm->GetScrollPos(SB_VERT);
		this->neuralNetworkForm->scrollController->Move(position);
		this->neuralNetworkForm->ScrollWindow(0, previous - position);
	}
	else if (this->layerInformationForm != 0) {
		Long position = this->layerInformationForm->scrollController->Move(nPos);
		int previous = this->layerInformationForm->SetScrollPos(SB_VERT, position, TRUE);
		position = this->layerInformationForm->GetScrollPos(SB_VERT);
		this->layerInformationForm->scrollController->Move(position);
		this->layerInformationForm->ScrollWindow(0, previous - position);
	}
}

ThumbTrackVScrollAction& ThumbTrackVScrollAction::operator=(const ThumbTrackVScrollAction& source) {
	VScrollAction::operator=(source);

	return *this;
}