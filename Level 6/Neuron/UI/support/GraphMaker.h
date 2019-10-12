#ifndef _GRAPHMAKER_H
#define _GRAPHMAKER_H

#include "Array.h"
#include <afxwin.h>
#include <string>
using namespace std;
typedef signed long int Long;

class NeuralNetwork;
class Graph;
class Affine;
class ReLU;
class Softmax;
class Dropout;
class Convolution;
class Pooling;
class Sigmoid;
class SpatialTransformer;

class GraphMaker {
public:
	GraphMaker();
	GraphMaker(const GraphMaker& source);
	~GraphMaker();

	Graph* Make(string titleX, string titleY, RECT rect, Long xMax, Long yMax); //CoordinateSystem
	Graph* Make(NeuralNetwork *neuralNetwork, Long x, Long y, bool isClicked); //LayerBoxControl
	Graph* Make(Convolution *convolution, Long x, Long y);
	Graph* Make(Pooling *pooling, Long x, Long y);
	Graph* Make(SpatialTransformer *spatialTransformer, Long x, Long y);
	Graph* Make(Affine *affine, RECT rect); //LayerToolTip
	Graph* Make(ReLU *relu, RECT rect); //LayerToolTip
	Graph* Make(Softmax *softmax, RECT rect); //LayerToolTip
	Graph* Make(Dropout *dropout, RECT rect); //LayerToolTip
	Graph* Make(Convolution *convolution, RECT rect); //LayerToolTip
	Graph* Make(Pooling *pooling, RECT rect); //LayerToolTip
	Graph* Make(Sigmoid *sigmoid, RECT rect);

	Graph* Make(Array<double>& axisX, Array<Long>& axisY, Long left, Long top, Long right, Long bottom); //CoordinateSystem
	Graph* Make(Array<Long>& axisX, Array<double>& axisY, RECT rect);
	Graph* Make(Affine *affine, Long x, Long y); //AffineLayout
	Graph* Make(ReLU *relu, Long x, Long y); //ReLULayout
	Graph* Make(Softmax *softmax, Long x, Long y); //SoftmaxLayout
	Graph* Make(Dropout *dropout, Long x, Long y); //Dropout

	GraphMaker& operator =(const GraphMaker& source);
};

int CompareLong(void *one, void *ohter);
#endif // !GRAPHMAKER_H
