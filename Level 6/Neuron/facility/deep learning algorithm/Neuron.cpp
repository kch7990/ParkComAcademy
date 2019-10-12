#include "Neuron.h"
#include "Affine.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
using namespace std;

Neuron::Neuron() {
}

Neuron::Neuron(const Neuron& source) {
}

Neuron::~Neuron() {
}

Long Neuron::Remove(Long index) {
	return -1;
}

Long Neuron::Add(Neuron *neuron) {
	return -1;
}

Long Neuron::Add(Long index, Neuron *neuron) {
	return -1;
}

Long Neuron::Move(Long index) {
	return -1;
}

void Neuron::ReSynchronization() {

}

Neuron* Neuron::GetAt(Long index) {
	return 0;
}

Array<double>  Neuron::Recognize(Array<double>& signals, bool isTraining) {
	return -1;
}

Array<Array<double>> Neuron::BatchRecognize(Array<Array<double>>& signals, bool isTraining) {
	return 0;
}

void Neuron::Learn(Array<double>& targets, double learningRate) {

}

void Neuron::Learn(Array<double>& targets, double learningRate, double beta1, double beta2) {

}

void Neuron::BatchLearn(Array<Array<double>>& targets, double learningRate) {

}
void Neuron::BatchLearn(Array<Array<double>>& targets, double learningRate, double beta1, double beta2) {

}

void Neuron::Update(double learningRate){
}

void Neuron::Update(double updatedLearningRate, double beta1, double beta2) {

}

Long Neuron::GetOutputCount() {
	return -1;
}

Long Neuron::GetChannelCount() {
	return -1;
}

Long Neuron::Save(fstream *fs) {
	return -1;
}

Long Neuron::Load(fstream *fs) {
	return -1;
}

double Neuron::GetCrossEntropy(Array<double>& results, Array<double>& targets) {
	return -1.0;
}

double Neuron::GetBatchCrossEntropy(Array<Array<double>>& results, Array<Array<double>>& targets) {
	return -1.0;
}

Long Neuron::GetCapacity() const {
	return -1;
}

Long Neuron::GetLength() const {
	return -1;
}

Long  Neuron::GetCurrent() const {
	return -1;
}

Neuron& Neuron::operator =(const Neuron& source) {
	return *this;
}


