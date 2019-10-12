#include "ClearLayerCommand.h"
#include "NeuronForm.h"
#include "NeuralNetwork.h"
#include "ScrollControllers.h"
#include "NeuralNetworkForm.h"
#include "GraphMaker.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
ClearLayerCommand::ClearLayerCommand(NeuronForm *neuronForm) {
	this->neuronForm = neuronForm;
}

ClearLayerCommand::ClearLayerCommand(const ClearLayerCommand& source) {
	this->neuronForm = source.neuronForm;
}

ClearLayerCommand::~ClearLayerCommand() {

}

void ClearLayerCommand::Execute() {
	int ret = this->neuronForm->MessageBox("정말로 초기화하시겠습니까?", "계층 초기화", MB_OKCANCEL);
	if (ret == IDOK) {
		if (this->neuronForm->neuralNetwork != 0) {
			delete this->neuronForm->neuralNetwork;
		}
		this->neuronForm->neuralNetwork = new NeuralNetwork;
		GraphMaker graphMaker;
		this->neuronForm->neuralNetworkForm->layerBoxControl = graphMaker.Make(dynamic_cast<NeuralNetwork*>(this->neuronForm->neuralNetwork), 20, 30, false);
	}
	this->neuronForm->neuralNetworkForm->scrollController->Update();
	this->neuronForm->neuralNetworkForm->Invalidate();
}

ClearLayerCommand& ClearLayerCommand::operator=(const ClearLayerCommand& source) {
	this->neuronForm = source.neuronForm;

	return *this;
}