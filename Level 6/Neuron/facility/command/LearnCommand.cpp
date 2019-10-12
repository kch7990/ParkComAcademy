#include "LearnCommand.h"
#include "NeuronForm.h"
#include "LearningDialog.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
LearnCommand::LearnCommand(NeuronForm *neuronForm) 
:Command(neuronForm){

}

LearnCommand::LearnCommand(const LearnCommand& source) 
:Command(source){

}

LearnCommand::~LearnCommand() {

}

void LearnCommand::Execute() {
	LearningDialog learningDialog((CWnd*)this->neuronForm);
	learningDialog.DoModal();
}

LearnCommand& LearnCommand::operator=(const LearnCommand& source) {
	Command::operator=(source);
	return *this;
}