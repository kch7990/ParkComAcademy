#include "CommandFactory.h"
#include "resource.h"
#include "RecognizeCommand.h"
#include "LearnCommand.h"
#include "RemoveLayerCommand.h"
#include "SaveCommand.h"
#include "OpenCommand.h"
#include "InsertLayerCommand.h"
#include "AddLayerCommand.h"
#include "ClearLayerCommand.h"
#if !defined(_AFXDLL)

#include <crtdbg.h>
#if defined(DEBUG) |defined(_DEBUG)
#if !defined(DEBUG_NEW)
#define DEBUG_NEW new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif
#endif
#endif
CommandFactory::CommandFactory(NeuronForm *neuronForm) {
	this->neuronForm = neuronForm;
}

CommandFactory::CommandFactory(const CommandFactory& source) {
	this->neuronForm = source.neuronForm;
}

CommandFactory::~CommandFactory() {

}

Command* CommandFactory::Make(int uID) {
	Command *command = 0;
	if (uID == IDM_PROCESS_RECOGNIZE) {
		command = new RecognizeCommand(this->neuronForm);
	}
	else if (uID == IDM_PROCESS_LEARN) {
		command = new LearnCommand(this->neuronForm);
	}
	else if (uID == IDM_CONTEXT_REMOVELAYER) {
		command = new RemoveLayerCommand(this->neuronForm);
	}
	else if (uID == IDM_CONTENT_INSERTLAYER) {
		command = new InsertLayerCommand(this->neuronForm);
	}
	else if (uID == IDM_FILE_SAVE) {
		command = new SaveCommand(this->neuronForm);
	}
	else if (uID == IDM_FILE_OPEN) {
		command = new OpenCommand(this->neuronForm);
	}
	else if (uID == IDM_EDIT_ADD) {
		command = new AddLayerCommand(this->neuronForm);
	}
	else if (uID == IDM_EDIT_CLEAR) {
		command = new ClearLayerCommand(this->neuronForm);
	}

	return command;
}

CommandFactory& CommandFactory::operator =(const CommandFactory& source) {
	this->neuronForm = source.neuronForm;

	return *this;
}