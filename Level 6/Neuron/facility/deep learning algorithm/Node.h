#ifndef _NODE_H
#define _NODE_H

#include "Neuron.h"

class Node : public Neuron {
public:
	Node();
	Node(const Node& source);
	virtual ~Node() = 0;
	
	virtual double Flow(Array<double>& signals); //AffineNode
	virtual double Flow(double signal); //ReLUNode
	virtual double Flow(double numerator, double sum); //SoftmaxNode
	virtual double Flow(double signal, bool isActive); //DropoutNode
	virtual Array<double> BatchFlow(Array<double>& nuemerators, Array<double>& sum);  // SoftmaxNode
	virtual Array<double> BatchFlow(Array<double>& signals, Array<bool>& isActives); // DropoutNode
	virtual Array<double> BatchFlow(Array<double>& signals);
	virtual Array<double> BatchBackFlow(Array<double>& signals); // //SoftmaxNode, DropoutNode, SigmoidNode
	virtual void BackFlow(double signal, Array<double>& inputs); //AffineNode
	virtual void BatchBackFlow(Array<double>& signals, Array<Array<double>>& inputs); //AffineNode
	virtual double BackFlow(double signal, double input); //ReLUNode
	virtual double BackFlow(double signal); //SoftmaxNode

	virtual double GetResult() const;

	virtual double GetWeight(Long index) const;
	virtual double GetBias() const;
	virtual double GetWeightGradient(Long index) const;
	virtual double GetBiasGradient() const;
	virtual double GetWeightMomentum(Long index) const;
	virtual double GetWeightVelocity(Long index) const;
	virtual double GetBiasMomentum() const;
	virtual double GetBiasVelocity() const;
	virtual Long GetCapacity() const;
	virtual Long GetLength() const;

	virtual bool GetIsActive() const;

	Node& operator=(const Node& source);
protected:
	double result;
};

inline double Node::GetResult() const {
	return this->result;
}

inline bool Node::GetIsActive() const {
	return false;
}
#endif // !_NODE_H
