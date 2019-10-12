#ifndef _CLEARLAYERCOMMAND_H
#define _CLEARLAYERCOMMAND_H

#include "Command.h"

class NeuronForm;

class ClearLayerCommand : public Command {
public:
	ClearLayerCommand(NeuronForm *neuronForm = 0);
	ClearLayerCommand(const ClearLayerCommand& source);
	virtual ~ClearLayerCommand();

	virtual void Execute();

	ClearLayerCommand& operator =(const ClearLayerCommand& source);
};


#endif //_CLEARLAYERCOMMAND_H