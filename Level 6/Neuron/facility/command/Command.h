#ifndef _COMMAND_H
#define _COMMAND_H

class NeuronForm;
class Command {
public:
	Command(NeuronForm *neuronForm = 0);
	Command(const Command& source);
	virtual ~Command() = 0;
	virtual void Execute() = 0;

	Command& operator =(const Command& source);
protected:
	NeuronForm *neuronForm;
};



#endif //_COMMAND_H