#ifndef _LEARNCOMMAND_H
#define _LEARNCOMMAND_H

#include "Command.h"
class NeuronForm;
class LearnCommand :public Command{
public:
	LearnCommand(NeuronForm *neuronForm);
	LearnCommand(const LearnCommand& source);
	virtual ~LearnCommand();
	virtual void Execute();
	LearnCommand& operator=(const LearnCommand& source);
};


#endif // !_LEARNCOMMAND_H
