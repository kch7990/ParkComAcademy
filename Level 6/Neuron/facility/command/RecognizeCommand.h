#ifndef _RECOGNIZECOMMAND_H
#define _RECOGNIZECOMMAND_H

#include "Command.h"

class NeuronForm;

class RecognizeCommand : public Command {
public:
	RecognizeCommand(NeuronForm *neuronForm = 0);
	RecognizeCommand(const RecognizeCommand& source);
	virtual ~RecognizeCommand();

	virtual void Execute();

	RecognizeCommand& operator =(const RecognizeCommand& source);
};

#endif //_RECOGNIZECOMMAND_H