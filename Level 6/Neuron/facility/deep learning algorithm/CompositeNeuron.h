//CompositeNeuron.h
#ifndef _COMPOSITENEURON_H
#define _COMPOSITENEURON_H

#include "Neuron.h"
#include "Array.h"

typedef signed long int Long;

class CompositeNeuron : public Neuron {
public:
	CompositeNeuron(Long capacity = 32);
	CompositeNeuron(const CompositeNeuron& source);
	virtual ~CompositeNeuron() = 0;

	virtual Long Add(Neuron* neuron);
	virtual Long Add(Long index, Neuron *neuron);
	virtual Long Remove(Long index);
	virtual Long Move(Long index);
	virtual Neuron* GetAt(Long index);

	virtual string GetType();

	virtual Long GetCapacity() const;
	virtual Long GetLength() const;
	virtual Long GetCurrent() const;

	CompositeNeuron& operator =(const CompositeNeuron& source);
protected:
	Array<Neuron*> neurons;
	Long capacity;
	Long length;
	Long current;
};

inline Long CompositeNeuron::GetCapacity() const {
	return this->capacity;
}
inline Long CompositeNeuron::GetLength() const {
	return this->length;
}
inline Long CompositeNeuron::GetCurrent() const {
	return this->current;
}

#endif // !_COMPOSITENEURON_H
