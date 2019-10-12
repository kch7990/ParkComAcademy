#include "SaveCommand.h"
#include "NeuronForm.h"
#include "Neuron.h"
#include <afxdlgs.h>
#include <fstream>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;

SaveCommand::SaveCommand(NeuronForm *neuronForm)
:Command(neuronForm){
}

SaveCommand::SaveCommand(const SaveCommand& source)
:Command(source){
}

SaveCommand::~SaveCommand(){
}

void SaveCommand::Execute(){
	//저장하다 메뉴를 눌렀을 때
	//1.1.파일 다이얼로그를 출력한다.
	CFileDialog fileDialog(FALSE);
	int ret = fileDialog.DoModal();
	if (ret == IDOK) {//1.2.파일 다이얼로그에서 확인 버튼을 눌렀을 때
		CString pathName = fileDialog.GetPathName(); //1.2.1.파일 이름을 읽는다.
		fstream fs;
		fs.open((LPCTSTR)pathName, ios_base::out); //1.2.2.파일을 만든다.

		if (fs.is_open()) {
			if (this->neuronForm->neuralNetwork->GetLength() > 0) {
				this->neuronForm->neuralNetwork->Save(&fs); //1.2.3.뉴런폼의 뉴럴네크워크에서 저장한다.
			}
			fs.close(); //1.2.3.파일을 닫는다.
		}
	}

}

SaveCommand& SaveCommand::operator=(const SaveCommand& source){
	Command::operator=(source);
	return *this;
}