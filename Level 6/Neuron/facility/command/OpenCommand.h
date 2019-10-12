#ifndef _OPENCOMMAND_H
#define _OPENCOMMAND_H

#include "Command.h"

class NeuronForm;
class OpenCommand : public Command {
public:
	OpenCommand(NeuronForm *neuronForm = 0);
	OpenCommand(const OpenCommand& source);
	virtual ~OpenCommand();
	virtual void Execute();
	OpenCommand& operator=(const OpenCommand& source);
};

#endif // !_OPENCOMMAND_H
