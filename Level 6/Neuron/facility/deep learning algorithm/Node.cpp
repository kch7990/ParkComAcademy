#include "Node.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
Node::Node() {
	this->result = 0;
}

Node::Node(const Node& source) {
	this->result = source.result;
}

Node::~Node() {
}

double Node::Flow(Array<double>& signals) {
	return -1.0;
}

double Node::Flow(double signal) {
	return -1.0;
}

double Node::Flow(double numerator, double sum) {
	return -1.0;
}

double Node::Flow(double signal, bool isActive) {
	return -1.0;
}

Array<double> Node::BatchFlow(Array<double> &nuemerators, Array<double> &sum){
	return 0;
}

Array<double> Node::BatchFlow(Array<double>& signals, Array<bool>& isActives) {
	return 0;
}

Array<double> Node::BatchFlow(Array<double>& signals) {
	return 0;
}

void Node::BackFlow(double signal, Array<double>& inputs) {

}

Array<double> Node::BatchBackFlow(Array<double> &signals){
	return 0;
}

void Node::BatchBackFlow(Array<double>& signals, Array<Array<double>>& inputs) {

}

double Node::BackFlow(double signal, double input) {
	return -1.0;
}

double Node::BackFlow(double signal) {
	return -1.0;
}

double Node::GetWeight(Long index) const {
	return -1.0;
}

double Node::GetBias() const {
	return -1.0;
}

double Node::GetWeightGradient(Long index) const {
	return -1.0;
}

double Node::GetBiasGradient() const {
	return -1.0;
}

double Node::GetWeightMomentum(Long index) const {
	return -1.0;
}

double Node::GetWeightVelocity(Long index) const {
	return -1.0;
}

double Node::GetBiasMomentum() const {
	return -1.0;
}

double Node::GetBiasVelocity() const {
	return -1.0;
}

Long Node::GetCapacity() const {
	return -1;
}

Long Node::GetLength() const {
	return -1;
}

Node& Node::operator=(const Node& source) {
	this->result = source.result;

	return *this;
}