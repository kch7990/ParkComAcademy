#include "InsertLayerCommand.h"
#include "AddLayerDialog.h"
#include "NeuronForm.h"
#include "NeuralNetworkForm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
InsertLayerCommand::InsertLayerCommand(NeuronForm *neuronForm)
:Command(neuronForm){
}

InsertLayerCommand::InsertLayerCommand(const InsertLayerCommand& source)
:Command(source){
}

InsertLayerCommand::~InsertLayerCommand(){
}

void InsertLayerCommand::Execute(){
	CString messageText;
	messageText.Format("계층을 삽입하면 가중치가 모두 초기화됩니다. 그래도 삽입 하시겠습니까?");
	int ret = this->neuronForm->neuralNetworkForm->MessageBox((LPCTSTR)messageText, "경고", MB_OKCANCEL | MB_ICONWARNING);

	if (ret == IDOK) {
		AddLayerDialog addLayerDialog((CWnd*)this->neuronForm->neuralNetworkForm);
		addLayerDialog.DoModal();
	}
}

InsertLayerCommand& InsertLayerCommand::operator=(const InsertLayerCommand& source){
	Command::operator=(source);
	return *this;
}