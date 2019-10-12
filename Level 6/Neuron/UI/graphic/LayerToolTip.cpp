#include "LayerToolTip.h"
#include "Visitor.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
LayerToolTip::LayerToolTip(Long capacity)
	: CompositeGraph(capacity) {

}

LayerToolTip::LayerToolTip(const LayerToolTip& source)
	: CompositeGraph(source) {

}

LayerToolTip::~LayerToolTip() {

}

void LayerToolTip::Accept(Visitor *visitor) {
	visitor->Visit(this);
}

Graph* LayerToolTip::Clone() {
	return new LayerToolTip(*this);
}

LayerToolTip& LayerToolTip::operator=(const LayerToolTip& source) {
	CompositeGraph::operator=(source);

	return *this;
}