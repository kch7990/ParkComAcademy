#include "VScrollActionFactory.h"
#include "VScrollActions.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
VScrollActionFactory::VScrollActionFactory(NeuralNetworkForm *neuralNetworkForm, LayerInformationForm *layerInformationForm) {
	this->neuralNetworkForm = neuralNetworkForm;
	this->layerInformationForm = layerInformationForm;
}

VScrollActionFactory::VScrollActionFactory(const VScrollActionFactory& source) {
	this->neuralNetworkForm = source.neuralNetworkForm;
	this->layerInformationForm = source.layerInformationForm;
}

VScrollActionFactory::~VScrollActionFactory() {

}

VScrollAction* VScrollActionFactory::Make(UINT nSBCode) {
	VScrollAction *vScrollAction = 0;

	switch (nSBCode) {
	case SB_LINEUP:
		vScrollAction = new LineUpAction(this->neuralNetworkForm, this->layerInformationForm);
		break;
	case SB_LINEDOWN:
		vScrollAction = new LineDownAction(this->neuralNetworkForm, this->layerInformationForm);
		break;
	case SB_PAGEUP:
		vScrollAction = new PageUpAction(this->neuralNetworkForm, this->layerInformationForm);
		break;
	case SB_PAGEDOWN:
		vScrollAction = new PageDownAction(this->neuralNetworkForm, this->layerInformationForm);
		break;
	case SB_THUMBTRACK:
		vScrollAction = new ThumbTrackVScrollAction(this->neuralNetworkForm, this->layerInformationForm);
		break;
	default:
		break;
	}

	return vScrollAction;
}

VScrollActionFactory& VScrollActionFactory::operator=(const VScrollActionFactory& source) {
	this->neuralNetworkForm = source.neuralNetworkForm;
	this->layerInformationForm = source.layerInformationForm;

	return *this;
}