#include "AddLayerDialog.h"
#include "NeuronFactory.h"
#include "NeuralNetworkForm.h"
#include "NeuralNetwork.h"
#include "NeuronForm.h"
#include "Graph.h"
#include "LayerBoxControl.h"
#include "LayerBox.h"
#include "GraphMaker.h"
#include "Layer.h"
#include "Convolution.h"
#include "Affine.h"
#include "ReLU.h"
#include "Softmax.h"
#include "Dropout.h"
#include "Pooling.h"
#include "ScrollControllers.h"
#include "Sigmoid.h"
#include "GridGenerator.h"
#include "SpatialTransformer.h"
#include "Sampler.h"
#include "AffineNode.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
BEGIN_MESSAGE_MAP(AddLayerDialog, CDialog)
	ON_CBN_CLOSEUP(IDC_COMBO_TYPE, OnTypeComboBoxCloseUp)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnOKButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnCancelButtonClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

AddLayerDialog::AddLayerDialog(CWnd *parent)
	: CDialog(AddLayerDialog::IDD, parent) {
	this->neuralNetworkForm = (NeuralNetworkForm*)parent;
}

BOOL AddLayerDialog::OnInitDialog() {
	CDialog::OnInitDialog();

	((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->AddString((LPCTSTR)"Affine");
	((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->AddString((LPCTSTR)"ReLU");
	((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->AddString((LPCTSTR)"Softmax");
	((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->AddString((LPCTSTR)"Dropout");
	((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->AddString((LPCTSTR)"Convolution");
	((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->AddString((LPCTSTR)"Pooling");
	((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->AddString((LPCTSTR)"Sigmoid");
	
	if (this->neuralNetworkForm->neuronForm->neuralNetwork->GetLength() < 1) {
		((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->AddString((LPCTSTR)"Spatial Transformer");
	}

	((CComboBox*)GetDlgItem(IDC_COMBO_INITIALVALUE))->AddString((LPCTSTR)"He");
	((CComboBox*)GetDlgItem(IDC_COMBO_INITIALVALUE))->AddString((LPCTSTR)"Xavier");

	return FALSE;
}

void AddLayerDialog::OnTypeComboBoxCloseUp() {//1.타입콤보박스가 닫힐 때
	CString type;
	GetDlgItem(IDC_COMBO_TYPE)->GetWindowText(type);

	GetDlgItem(IDC_STATIC_NODECOUNT)->ShowWindow(SW_HIDE); //1.1.노드 개수 스태틱을 감추다.
	GetDlgItem(IDC_EDIT_NODECOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_FILTERSIZE)->ShowWindow(SW_HIDE);//1.4.필터 크기 스태틱을 감추다.
	GetDlgItem(IDC_EDIT_FILTERSIZE)->ShowWindow(SW_HIDE);//1.5.필터 크기 에딧을 감추다.
	GetDlgItem(IDC_STATIC_STRIDE)->ShowWindow(SW_HIDE);//1.6.스트라이드 스태틱을 감추다.
	GetDlgItem(IDC_EDIT_STRIDE)->ShowWindow(SW_HIDE);//1.7.스트라이드 에딧을 감추다.
	GetDlgItem(IDC_STATIC_PADDING)->ShowWindow(SW_HIDE);//1.8.패딩 스태틱을 감추다.
	GetDlgItem(IDC_EDIT_PADDING)->ShowWindow(SW_HIDE);//1.9.패딩 에딧을 감추다.
	GetDlgItem(IDC_STATIC_INITIALVALUE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO_INITIALVALUE)->ShowWindow(SW_HIDE);//1.10.초깃값 콤보 박스를 감추다.


	if (type == "Affine") {//2. 타입이 Affine일 때
		//노드 개수 에딧이 비활성화 되어있으면 활성화한다.
		GetDlgItem(IDC_STATIC_INITIALVALUE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_INITIALVALUE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_NODECOUNT)->SetWindowTextA("노드 개수");
		GetDlgItem(IDC_STATIC_NODECOUNT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_NODECOUNT)->ShowWindow(SW_SHOW);
	}
	else if (type == "Convolution") {//4. 타입이 Conv 일 때
		GetDlgItem(IDC_STATIC_INITIALVALUE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_INITIALVALUE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_NODECOUNT)->SetWindowTextA("필터 개수");//4.1.노드 개수 스태틱을 필터 개수로 바꾼다.
		GetDlgItem(IDC_STATIC_NODECOUNT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_NODECOUNT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_FILTERSIZE)->ShowWindow(SW_SHOW);//4.4.필터 크기 스태틱을 보여준다.
		GetDlgItem(IDC_EDIT_FILTERSIZE)->ShowWindow(SW_SHOW);//4.5.필터 크기 에딧을 보여준다.
		GetDlgItem(IDC_STATIC_STRIDE)->ShowWindow(SW_SHOW);//4.6.스트라이드 스태틱을 보여준다.
		GetDlgItem(IDC_EDIT_STRIDE)->ShowWindow(SW_SHOW);//4.7.스트라이드 에딧을 보여준다.
		GetDlgItem(IDC_STATIC_PADDING)->ShowWindow(SW_SHOW);//4.8.패딩 스태틱을 보여준다.
		GetDlgItem(IDC_EDIT_PADDING)->ShowWindow(SW_SHOW);//4.9.패딩 에딧을 보여준다.
	}
	else if (type == "Pooling") {
		GetDlgItem(IDC_STATIC_FILTERSIZE)->ShowWindow(SW_SHOW);//4.4.필터 크기 스태틱을 보여준다.
		GetDlgItem(IDC_EDIT_FILTERSIZE)->ShowWindow(SW_SHOW);//4.5.필터 크기 에딧을 보여준다.
	}
	else if (type == "Dropout") {
		GetDlgItem(IDC_STATIC_NODECOUNT)->SetWindowTextA("삭제 비율");//5.1.노드 개수 스태틱을 삭제 비율로 바꾼다.
		GetDlgItem(IDC_STATIC_NODECOUNT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_NODECOUNT)->ShowWindow(SW_SHOW);
	}
}

void AddLayerDialog::OnOKButtonClicked() {
	CString type;
	CString filterCount;
	CString filterSize;
	CString stride;
	CString pad;
	CString initialValue;
	Long channelCount = 1;
	GetDlgItem(IDC_COMBO_TYPE)->GetWindowTextA(type);

	CString nodeCount;
	NeuronType neuronType;
	Long outputCount;
	Long current = this->neuralNetworkForm->neuronForm->neuralNetwork->GetCurrent();
	CString ratio;

	if (type == "Affine") { //Affine일때만 노드 개수를 입력받음
		neuronType = NEURON_AFFINE;
		GetDlgItem(IDC_EDIT_NODECOUNT)->GetWindowTextA(nodeCount);
		GetDlgItem(IDC_COMBO_INITIALVALUE)->GetWindowTextA(initialValue);
	}
	else if (type == "ReLU") {
		neuronType = NEURON_RELU;
	}
	else if (type == "Softmax") {
		neuronType = NEURON_SOFTMAX;
	}
	else if (type == "Sigmoid") {
		neuronType = NEURON_SIGMOID;
	}
	else if (type == "Dropout") {
		neuronType = NEURON_DROPOUT;
		GetDlgItem(IDC_EDIT_NODECOUNT)->GetWindowTextA(ratio);
	}
	else if (type == "Convolution") {
		neuronType = NEURON_CONVOLUTION;
		GetDlgItem(IDC_EDIT_NODECOUNT)->GetWindowTextA(filterCount);
		GetDlgItem(IDC_EDIT_FILTERSIZE)->GetWindowTextA(filterSize);
		GetDlgItem(IDC_EDIT_STRIDE)->GetWindowTextA(stride);
		GetDlgItem(IDC_EDIT_PADDING)->GetWindowTextA(pad);
		GetDlgItem(IDC_COMBO_INITIALVALUE)->GetWindowTextA(initialValue);
		channelCount = this->neuralNetworkForm->neuronForm->neuralNetwork->GetChannelCount();
	}
	else if (type == "Pooling") {
		neuronType = NEURON_POOLING;
		GetDlgItem(IDC_EDIT_FILTERSIZE)->GetWindowTextA(filterSize);
		channelCount = this->neuralNetworkForm->neuronForm->neuralNetwork->GetChannelCount();
	}
	else if (type == "Spatial Transformer") {
		neuronType = NEURON_SPATIALTRANSFORMER;
	}

	NeuronFactory neuronFactory;
	Neuron *layer = neuronFactory.Make(neuronType);

	if (current >= 0) {
		Long inputSize;
		outputCount = 28 * 28;
		Neuron *layer;
		Long i = 0;
		while (i < current) {
			layer = this->neuralNetworkForm->neuronForm->neuralNetwork->GetAt(i);
			if (dynamic_cast<Affine*>(layer)) {
				channelCount = 1;
				outputCount = layer->GetLength();
			}
			else if (dynamic_cast<ReLU*>(layer) ||
				dynamic_cast<Softmax*>(layer) || dynamic_cast<Dropout*>(layer) || dynamic_cast<Sigmoid*>(layer)) {
				outputCount = layer->GetLength();
			}
			else if (dynamic_cast<Convolution*>(layer)) {
				inputSize = sqrt(outputCount / dynamic_cast<Convolution*>(layer)->GetChannelCount());
				outputCount = pow((inputSize - dynamic_cast<Convolution*>(layer)->GetFilterSize() +
					2 * dynamic_cast<Convolution*>(layer)->GetPad()) / dynamic_cast<Convolution*>(layer)->GetStride() + 1, 2)*
					layer->GetLength();
				channelCount = layer->GetLength();
			}
			else if (dynamic_cast<Pooling*>(layer)) {
				inputSize = sqrt(outputCount / layer->GetLength());
				outputCount = pow((inputSize - dynamic_cast<Pooling*>(layer)->GetSize()) / dynamic_cast<Pooling*>(layer)->GetStride() + 1, 2) *
					layer->GetLength();
			}
			i++;
		}
	}
	else {
		outputCount = this->neuralNetworkForm->neuronForm->neuralNetwork->GetOutputCount();
		channelCount = this->neuralNetworkForm->neuronForm->neuralNetwork->GetChannelCount();
	}

	double deviation;

	if (dynamic_cast<Affine*>(layer)) {
		if (initialValue == "He") {
			deviation = sqrt(2.0 / outputCount);
		}
		else if (initialValue == "Xavier") {
			deviation = 1 / sqrt(outputCount);
		}
		dynamic_cast<Layer*>(layer)->MakeNodes(outputCount, atoi(nodeCount), deviation);
	}
	else if (dynamic_cast<ReLU*>(layer) || dynamic_cast<Softmax*>(layer) || dynamic_cast<Sigmoid*>(layer)) {
		dynamic_cast<Layer*>(layer)->MakeNodes(outputCount, outputCount);
	}
	else if (dynamic_cast<Dropout*>(layer)) {
		*dynamic_cast<Dropout*>(layer) = Dropout(outputCount, atof(ratio));
		dynamic_cast<Layer*>(layer)->MakeNodes(outputCount, outputCount);
	}
	else if (dynamic_cast<Convolution*>(layer)) {
		if (initialValue == "He") {
			deviation = sqrt(2.0 / (channelCount * atoi(filterSize) * atoi(filterSize)));
		}
		else if (initialValue == "Xavier") {
			deviation = 1 / sqrt(channelCount * atoi(filterSize) * atoi(filterSize));
		}
		*dynamic_cast<Convolution*>(layer) = Convolution(atoi(filterCount), atoi(pad), atoi(stride), atoi(filterSize));
		dynamic_cast<Layer*>(layer)->MakeFilters(channelCount, atoi(filterCount), deviation);
	}
	else if (dynamic_cast<Pooling*>(layer)) {
		*dynamic_cast<Pooling*>(layer) = Pooling(channelCount, atoi(filterSize), atoi(filterSize));
		dynamic_cast<Layer*>(layer)->MakeFilters(channelCount, channelCount);
	}
	else if (dynamic_cast<SpatialTransformer*>(layer)) {
		//Conv 채널 1 패딩 1필터수 8 커널사이즈 7x7 출력수 24x24x8
		double std = sqrt(2.0 / (7.0 * 7.0));
		Neuron *neuron = new Convolution(8, 1, 1, 7);
		dynamic_cast<Layer*>(neuron)->MakeFilters(1, 8, std);
		layer->Add(neuron);

		//Pooling 채널 8 사이즈 2x2 출력수 12x12x8
		neuron = new Pooling(8, 2, 2);
		dynamic_cast<Layer*>(neuron)->MakeFilters(8, 8);
		layer->Add(neuron);

		//ReLU 11x11x8
		neuron = new ReLU(12 * 12 * 8);
		dynamic_cast<Layer*>(neuron)->MakeNodes(12 * 12 * 8, 12 * 12 * 8);
		layer->Add(neuron);

		//Conv 채널 8 필터수 10 커널 5x5 출력수8*8*10 

		std = sqrt(2.0 / (5.0 * 5.0 * 8.0));
		neuron = new Convolution(10, 0, 1, 5);
		dynamic_cast<Layer*>(neuron)->MakeFilters(8, 10, std);
		layer->Add(neuron);

		//Pool 채널 10 출력수4x4x10
		neuron = new Pooling(10, 2, 2);
		dynamic_cast<Layer*>(neuron)->MakeFilters(10, 10);
		layer->Add(neuron);

		//Affine 가중치수 4x4x10
		std = sqrt(2.0 / (10.0 * 4.0 * 4.0));
		neuron = new Affine(32);
		dynamic_cast<Layer*>(neuron)->MakeNodes(10 * 4 * 4, 32, std);
		layer->Add(neuron);

		//ReLU 32
		neuron = new ReLU(32);
		dynamic_cast<Layer*>(neuron)->MakeNodes(32, 32);
		layer->Add(neuron);

		//Affine
		neuron = new Affine(6, 32);
		Neuron *node;
		Array<double> weights(32);
		// 20개의 0.0을가진 배열을만든다.
		Long h = 0;
		while (h < weights.GetCapacity()) {
			weights.Store(h, 0.0);
			h++;
		}
		//Affine
		// 첫번째 노드를만든다. 바이어스 1
		node = new AffineNode(weights, 1.0, weights, weights, 0.0, 0.0);
		neuron->Add(node);
		// 두번째 바이어스 0
		node = new AffineNode(weights, 0.0, weights, weights, 0.0, 0.0);
		neuron->Add(node);
		// 세번쨰 바이어스 0
		node = new AffineNode(weights, 0.0, weights, weights, 0.0, 0.0);
		neuron->Add(node);
		// 4번째 바이어스 0
		node = new AffineNode(weights, 0.0, weights, weights, 0.0, 0.0);
		neuron->Add(node);
		// 5번째 바이어스 1
		node = new AffineNode(weights, 1.0, weights, weights, 0.0, 0.0);
		neuron->Add(node);
		// 6번째 바이어스 0
		node = new AffineNode(weights, 0.0, weights, weights, 0.0, 0.0);
		neuron->Add(node);
		// 각가 어파인에 넌다.

		layer->Add(neuron);
	}

	if (current >= 0) { // 계층 삽입이면
		this->neuralNetworkForm->neuronForm->neuralNetwork->Add(current, layer);
		this->neuralNetworkForm->neuronForm->neuralNetwork->ReSynchronization();
	}
	else { // 계층을 맨 뒤에 추가하면
		this->neuralNetworkForm->neuronForm->neuralNetwork->Add(layer);
	}

	if (this->neuralNetworkForm->layerBoxControl != NULL) {
		delete this->neuralNetworkForm->layerBoxControl;
	}
	GraphMaker graphMaker;
	this->neuralNetworkForm->layerBoxControl =
		graphMaker.Make(dynamic_cast<NeuralNetwork*>(this->neuralNetworkForm->neuronForm->neuralNetwork), 20, 30, false);

	this->neuralNetworkForm->scrollController->Update();
	this->neuralNetworkForm->Invalidate();
	EndDialog(0);
	CDialog::OnClose();
}

void AddLayerDialog::OnCancelButtonClicked() {
	EndDialog(0);
	CDialog::OnClose();
}

void AddLayerDialog::OnClose() {
	EndDialog(0);
	CDialog::OnClose();
}