#ifndef _COMMANDFACTORY_H
#define _COMMANDFACTORY_H

class NeuronForm;
class Command;

class CommandFactory {
public:
	CommandFactory(NeuronForm *neuronForm = 0);
	CommandFactory(const CommandFactory& source);
	~CommandFactory();

	Command* Make(int uID);
	
	CommandFactory& operator =(const CommandFactory& source);
private:
	NeuronForm *neuronForm;
};

#endif //_COMMANDFACTORY_H