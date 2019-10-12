#include "NeuronFactory.h"
#include "AffineNode.h"
#include "Neuron.h"
#include "NeuralNetwork.h"
#include "Affine.h"
#include "ReLUNode.h"
#include "ReLU.h"
#include "Softmax.h"
#include "Dropout.h"
#include "DropoutNode.h"
#include "ConvolutionFilter.h"
#include "FilterCube.h"
#include "Convolution.h"
#include "Pooling.h"
#include "PoolingFilter.h"
#include "Sigmoid.h"
#include "SigmoidNode.h"
#include "SpatialTransformer.h"
#if !defined(_AFXDLL)

#include <crtdbg.h>
#if defined(DEBUG) |defined(_DEBUG)
#if !defined(DEBUG_NEW)
#define DEBUG_NEW new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif
#endif
#endif
NeuronFactory::NeuronFactory() {

}

NeuronFactory::NeuronFactory(const NeuronFactory& source) {

}

NeuronFactory::~NeuronFactory() {

}

Neuron* NeuronFactory::Make(NeuronType type) {
	Neuron *neuron=0;
	switch(type) {
	case NEURON_AFFINENODE:
		neuron = new AffineNode;
		break;
	case NEURON_AFFINE:
		neuron = new Affine;
		break;
	case NEURON_NEURALNETWORK:
		neuron = new NeuralNetwork;
		break;
	case NEURON_RELUNODE:
		neuron = new ReLUNode;
		break;
	case NEURON_RELU:
		neuron = new ReLU;
		break;
	case NEURON_SOFTMAX:
		neuron = new Softmax;
		break;
	case NEURON_DROPOUTNODE:
		neuron = new DropoutNode;
		break;
	case NEURON_DROPOUT:
		neuron = new Dropout;
		break;
	case NEURON_CONVOLUTIONFILTER:
		neuron = new ConvolutionFilter;
		break;
	case NEURON_FILTERCUBE:
		neuron = new FilterCube;
		break;
	case NEURON_CONVOLUTION:
		neuron = new Convolution;
		break;
	case NEURON_POOLINGFILTER:
		neuron = new PoolingFilter;
		break;
	case NEURON_POOLING:
		neuron = new Pooling;
		break;
	case NEURON_SIGMOID:
		neuron = new Sigmoid;
		break;
	case NEURON_SIGMOIDNODE:
		neuron = new SigmoidNode;
		break;
	case NEURON_SPATIALTRANSFORMER:
		neuron = new SpatialTransformer;
		break;
	default:
		break;
	}

	return neuron;
}