#include "Command.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
Command::Command(NeuronForm *neuronForm) {
	this->neuronForm = neuronForm;
}

Command::Command(const Command& source) {
	this->neuronForm = source.neuronForm;
}

Command::~Command() {

}

Command& Command::operator =(const Command& source) {
	this->neuronForm = source.neuronForm;

	return *this;
}