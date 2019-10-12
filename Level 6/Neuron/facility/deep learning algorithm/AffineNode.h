#ifndef _AFFINENODE_H
#define _AFFINENODE_H

#include "Array.h"
#include "Node.h"

class AffineNode : public Node {
public:
	AffineNode(Long capacity = 32);
	AffineNode(const Array<double>& weights, double bias,
		const Array<double>& weightMomentums, const Array<double>& weightVelocities, double biasMomentum, double biasVelocity); //매개변수를 갖는 생성자 : Affine의 MakeAffineNodes에 쓰임
	AffineNode(const AffineNode& source);
	virtual ~AffineNode();

	virtual double Flow(Array<double>& signals);
	virtual void BackFlow(double signal, Array<double>& inputs);
	virtual void BatchBackFlow(Array<double>& signals, Array<Array<double>>& inputs);
	virtual void Update(double learningRate);
	virtual void Update(double updatedLearningRate, double beta1, double beta2);

	virtual Neuron* Clone();

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

	AffineNode& operator =(const AffineNode& source);
private:
	Array<double> weights;
	double bias;
	Array<double> weightGradients;
	double biasGradient;
	Array<double> weightMomentums;
	Array<double> weightVelocities;
	double biasMomentum;
	double biasVelocity;
	Long capacity;
	Long length;
};

inline double AffineNode::GetWeight(Long index) const {
	return const_cast<Array<double>&>(this->weights).GetAt(index);
}

inline double AffineNode::GetBias() const {
	return this->bias;
}

inline double AffineNode::GetWeightGradient(Long index) const {
	return const_cast<Array<double>&>(this->weightGradients).GetAt(index);
}

inline double AffineNode::GetBiasGradient() const {
	return this->biasGradient;
}

inline double AffineNode::GetWeightMomentum(Long index) const {
	return const_cast<Array<double>&>(this->weightMomentums).GetAt(index);
}

inline double AffineNode::GetWeightVelocity(Long index) const {
	return const_cast<Array<double>&>(this->weightVelocities).GetAt(index);
}

inline double AffineNode::GetBiasMomentum() const {
	return this->biasMomentum;
}

inline double AffineNode::GetBiasVelocity() const {
	return this->biasVelocity;
}

inline Long AffineNode::GetCapacity() const {
	return this->capacity;
}

inline Long AffineNode::GetLength() const {
	return this->length;
}

#endif //_AFFINENODE_H
