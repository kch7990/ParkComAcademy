#ifndef _VSCROLLACTIONFACTORY_H
#define _VSCROLLACTIONFACTORY_H

#include <afxwin.h>

class VScrollAction;
class NeuralNetworkForm;
class LayerInformationForm;
class VScrollActionFactory {
public:
	VScrollActionFactory(NeuralNetworkForm *neuralNetworkForm = 0, LayerInformationForm *layerInformationForm = 0);
	VScrollActionFactory(const VScrollActionFactory& source);
	~VScrollActionFactory();

	VScrollAction* Make(UINT nSBCode);

	VScrollActionFactory& operator=(const VScrollActionFactory& source);
private:
	NeuralNetworkForm *neuralNetworkForm;
	LayerInformationForm *layerInformationForm;
};

#endif //_VSCROLLACTIONFACTORY_H