#ifndef _DROPOUTNODE_H
#define _DROPOUTNODE_H

#include "Node.h"

typedef signed long int Long;

class Neuron;
class DropoutNode : public Node {
public:
	DropoutNode(bool isActive = true);
	DropoutNode(const DropoutNode& source);
	virtual ~DropoutNode();
	virtual double Flow(double signal, bool isActive);
	virtual Array<double> BatchFlow(Array<double>& signals, Array<bool>& isActives);
	virtual double BackFlow(double signal);
	virtual Array<double> BatchBackFlow(Array<double>& signals);
	virtual Neuron* Clone();

	DropoutNode& operator=(const DropoutNode& source);

	virtual bool GetIsActive() const;
private:
	bool isActive;
	Array<bool> batchIsActive;
	Array<double> batchResults;
};

inline bool DropoutNode::GetIsActive() const {
	return this->isActive;
}

#endif // !_DROPOUTNODE_H
