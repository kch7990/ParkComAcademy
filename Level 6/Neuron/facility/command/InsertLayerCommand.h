#ifndef _INSERTLAYERCOMMAND_H
#define _INSERTLAYERCOMMAND_H

#include "Command.h"

class InsertLayerCommand : public Command {
public:
	InsertLayerCommand(NeuronForm *neuronForm = 0);
	InsertLayerCommand(const InsertLayerCommand& source);
	virtual ~InsertLayerCommand();
	virtual void Execute();
	InsertLayerCommand& operator=(const InsertLayerCommand& source);
};

#endif // !1
