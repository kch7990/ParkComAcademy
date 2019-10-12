#include "OpenCommand.h"
#include "NeuronForm.h"
#include "Neuron.h"
#include "NeuralNetwork.h"
#include "NeuralNetworkForm.h"
#include "Graph.h"
#include "GraphMaker.h"
#include "ScrollControllers.h"
#include <afxdlgs.h>
#include <fstream>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
using namespace std;

OpenCommand::OpenCommand(NeuronForm *neuronForm) 
:Command(neuronForm){
}

OpenCommand::OpenCommand(const OpenCommand& source)
:Command(source){
}

OpenCommand::~OpenCommand(){
}

void OpenCommand::Execute(){
	//1. 불러오다 메뉴가 클릭 됐을 때
	//	1.1.파일 다이얼로그를 출력한다.
	CFileDialog fileDialog(TRUE);
	int ret = fileDialog.DoModal();
	if (ret == IDOK) { //	1.2.열기 버튼을 눌렀을 때
		CString pathName = fileDialog.GetPathName(); 	//	1.2.1.파일 이름을 읽는다.
		fstream fs;
		fs.open((LPCTSTR)pathName, ios_base::in);
		if (fs.is_open()) {
			// 1.2.2.파일을 연다.

			if (this->neuronForm->neuralNetwork != NULL) {//	1.2.3.뉴런폼의 신경망을 지우다.
				delete this->neuronForm->neuralNetwork;
			}
			this->neuronForm->neuralNetwork = new NeuralNetwork;//	1.2.4.뉴런폼의 신경망을 만들다.
			this->neuronForm->neuralNetwork->Load(&fs);//	1.2.5.뉴런폼의 신경망에서 불러온다.
			fs.close();
		}
		
		//	1.3.뉴런폼의 뉴럴네트워크폼의 레이어박스컨트롤을 다시만들다.
		if (this->neuronForm->neuralNetworkForm->layerBoxControl != NULL) {
			delete this->neuronForm->neuralNetworkForm->layerBoxControl;
		}
		GraphMaker graphMaker;
		this->neuronForm->neuralNetworkForm->layerBoxControl = graphMaker.Make(dynamic_cast<NeuralNetwork*>(this->neuronForm->neuralNetwork), 20, 30, false);
		this->neuronForm->neuralNetworkForm->scrollController->Update();
		this->neuronForm->neuralNetworkForm->Invalidate();//	1.4.뉴런폼의 뉴럴네트워크폼을 갱신하다.
	}
}

OpenCommand& OpenCommand::operator=(const OpenCommand& source){
	Command::operator=(source);
	return *this;

}