#ifndef _RELUNODE_H
#define _RELUNODE_H

#include "Node.h"

class Neuron;
class ReLUNode :public Node {
public:
	ReLUNode();
	ReLUNode(const ReLUNode& source);
	virtual ~ReLUNode();
	
	virtual double Flow(double signal); //입력 하나당 출력 하나
	virtual double BackFlow(double signal, double input);

	virtual Neuron* Clone();

	ReLUNode& operator =(const ReLUNode& source);
};

#endif // !_RELUNODE_H
