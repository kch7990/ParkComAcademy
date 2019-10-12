#ifndef _ADDLAYERCOMMAND_H
#define _ADDLAYERCOMMAND_H

#include "Command.h"

class NeuronForm;

class AddLayerCommand : public Command {
public:
	AddLayerCommand(NeuronForm *neuronForm = 0);
	AddLayerCommand(const AddLayerCommand& source);
	virtual ~AddLayerCommand();
	virtual void Execute();

	AddLayerCommand& operator =(const AddLayerCommand& source);
};

#endif //_ADDLAYERCOMMAND_H