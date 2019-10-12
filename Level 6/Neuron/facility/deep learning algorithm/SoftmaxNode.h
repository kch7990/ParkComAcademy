#ifndef _SOFTMAXNODE_H
#define _SOFTMAXNODE_H

#include "Node.h"

class Neuron;
class SoftmaxNode :public Node {
public:
	SoftmaxNode();
	SoftmaxNode(const SoftmaxNode& source);
	virtual ~SoftmaxNode();

	virtual double Flow(double numerator, double sum);
	virtual Array<double> BatchFlow(Array<double> &nuemerators, Array<double> &sum);
	virtual double BackFlow(double signal);
	virtual Array<double> BatchBackFlow(Array<double> &signals);
	
	virtual Neuron* Clone();

	SoftmaxNode& operator =(const SoftmaxNode& source);
private:
	Array<double> batchResults;
};

#endif // !_SOFTMAXNODE_H
