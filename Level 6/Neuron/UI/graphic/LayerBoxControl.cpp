#include "LayerBoxControl.h"
#include "Visitor.h"
#include "DrawingVisitor.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

LayerBoxControl::LayerBoxControl(Long capacity, Long boxHeight, Long boxWidth, Long interval)
:CompositeGraph(capacity){
	this->boxHeight = boxHeight;
	this->boxWidth = boxWidth;
	this->interval = interval;
}

LayerBoxControl::LayerBoxControl(const LayerBoxControl& source)
:CompositeGraph(source){
	this->boxHeight = source.boxHeight;
	this->boxWidth = source.boxWidth;
	this->interval = source.interval;
}

LayerBoxControl::~LayerBoxControl() {

}

void LayerBoxControl::Accept(Visitor *visitor) {
	visitor->Visit(this);
}

Graph* LayerBoxControl::Clone() {
	return new LayerBoxControl(*this);
}

Graph* LayerBoxControl::GetAt(Long index) {
	return this->graphs.GetAt(index);
}

LayerBoxControl& LayerBoxControl::operator=(const LayerBoxControl& source) {
	CompositeGraph::operator=(source);
	this->boxHeight = source.boxHeight;
	this->boxWidth = source.boxWidth;
	this->interval = source.interval;
	return *this;
}