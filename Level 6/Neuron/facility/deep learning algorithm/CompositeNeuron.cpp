//CompositeNeuron.cpp

#include "CompositeNeuron.h"
#if !defined(_AFXDLL)

#include <crtdbg.h>
#if defined(DEBUG) |defined(_DEBUG)
#if !defined(DEBUG_NEW)
#define DEBUG_NEW new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif
#endif
#endif
CompositeNeuron::CompositeNeuron(Long capacity)
	: neurons(capacity) {
	this->capacity = capacity;
	this->length = 0;
	this->current = -1;
}

CompositeNeuron::CompositeNeuron(const CompositeNeuron& source)
	: neurons(source.neurons) {
	// source.neurons[i]번째 하나씩 꺼내서 Clone후 Modify
	Neuron *neuron;
	Long i = 0;
	while (i < source.length) {
		neuron = const_cast<CompositeNeuron&>(source).neurons[i]; //const_cast해제 후 neurons에 접근
		this->neurons.Modify(i, neuron->Clone());
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
	this->current = source.current;
}

CompositeNeuron::~CompositeNeuron() {
	Neuron *neuron;
	Long i = 0;
	while (i < this->length) { //neurons의 요소들이 포인터 : 할당 해제
		neuron = this->neurons[i];
		if (neuron != 0) {
			delete neuron;
		}
		i++;
	}
}

Long CompositeNeuron::Add(Neuron* neuron) {
	Long index;
	if (this->length < this->capacity) {
		index = this->neurons.Store(this->length, neuron);
	}
	else {
		index = this->neurons.AppendFromRear(neuron);
		this->capacity++;
	}
	this->current = index;
	this->length++;

	return index;
}

Long CompositeNeuron::Add(Long index, Neuron *neuron) {
	this->neurons.Insert(index, neuron);
	this->current = index;
	this->capacity++;
	this->length++;

	return index;
}

Long CompositeNeuron::Remove(Long index) {
	this->current = index - 1;
	index = this->neurons.Delete(index);
	this->capacity--;
	this->length--;

	return index;
}

Long CompositeNeuron::Move(Long index) {
	this->current = index;
	return this->current;
}

Neuron* CompositeNeuron::GetAt(Long index) {
	return this->neurons.GetAt(index);
}

CompositeNeuron& CompositeNeuron::operator =(const CompositeNeuron& source) {
	Long i = 0;
	while (i < this->length) {
		if (this->neurons[i] != 0) {
			delete this->neurons[i];
		}
		i++;
	}
	this->neurons = source.neurons;

	i = 0;
	while (i < source.length) {
		this->neurons.Modify(i, (const_cast<CompositeNeuron&>(source)).neurons[i]->Clone());
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
	this->current = source.current;

	return *this;
}

string CompositeNeuron::GetType() {
	return "";
}