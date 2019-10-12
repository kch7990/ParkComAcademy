#ifndef _REMOVELAYERCOMMAND_H
#define _REMOVELAYERCOMMAND_H

#include "Command.h"

class RemoveLayerCommand : public Command {
public:
	RemoveLayerCommand(NeuronForm *neuronForm = 0);
	RemoveLayerCommand(const RemoveLayerCommand& source);
	virtual ~RemoveLayerCommand();

	virtual void Execute();

	RemoveLayerCommand& operator=(const RemoveLayerCommand& source);
};

#endif //_REMOVELAYERCOMMAND_H