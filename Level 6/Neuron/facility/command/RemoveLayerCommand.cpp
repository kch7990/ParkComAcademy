#include "RemoveLayerCommand.h"
#include "NeuronForm.h"
#include "NeuralNetworkForm.h"
#include "Graph.h"
#include "GraphMaker.h"
#include "NeuralNetwork.h"
#include "Neuron.h"
#include "Affine.h"
#include "Layer.h"
#include "Softmax.h"
#include "ReLU.h"
#include "Convolution.h"
#include "Pooling.h"
#include "Dropout.h"
#include "ScrollControllers.h"
#include <string>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
using namespace std;

RemoveLayerCommand::RemoveLayerCommand(NeuronForm *neuronForm)
	: Command(neuronForm) {

}

RemoveLayerCommand::RemoveLayerCommand(const RemoveLayerCommand& source)
	: Command(source) {

}

RemoveLayerCommand::~RemoveLayerCommand() {

}

void RemoveLayerCommand::Execute() {
	GraphMaker graphMaker;
	Long index;
	Graph *layerBox = this->neuronForm->neuralNetworkForm->current;
	string type = layerBox->GetType();
	if (type == "Conv" || type == "Affine" || type == "Pooling") {
		CString messageText;
		messageText.Format("%s 계층을 빼면 가중치가 모두 초기화됩니다. 그래도 빼시겠습니까?", type.c_str());
		int ret = this->neuronForm->neuralNetworkForm->MessageBox((LPCTSTR)messageText, "경고", MB_OKCANCEL | MB_ICONWARNING);
		if (ret == IDOK) {
			index = this->neuronForm->neuralNetwork->GetCurrent();
			this->neuronForm->neuralNetwork->Remove(index);
			this->neuronForm->neuralNetwork->ReSynchronization();

			if (this->neuronForm->neuralNetworkForm->layerBoxControl != 0) {
				delete this->neuronForm->neuralNetworkForm->layerBoxControl;
			}
			this->neuronForm->neuralNetworkForm->layerBoxControl = graphMaker.Make(dynamic_cast<NeuralNetwork*>(this->neuronForm->neuralNetwork), 20, 30, false);
		}
	}
	else {
		index = this->neuronForm->neuralNetwork->GetCurrent();
		this->neuronForm->neuralNetwork->Remove(index);
		if (this->neuronForm->neuralNetworkForm->layerBoxControl != 0) {
			delete this->neuronForm->neuralNetworkForm->layerBoxControl;
		}
		this->neuronForm->neuralNetworkForm->layerBoxControl = graphMaker.Make(dynamic_cast<NeuralNetwork*>(this->neuronForm->neuralNetwork), 20, 30, false);
	}
	this->neuronForm->neuralNetworkForm->scrollController->Update();
	this->neuronForm->neuralNetworkForm->Invalidate();
}

RemoveLayerCommand& RemoveLayerCommand::operator=(const RemoveLayerCommand& source) {
	Command::operator=(source);

	return *this;
}