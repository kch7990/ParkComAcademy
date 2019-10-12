#include "CoordinateSystem.h"
#include "CompositeGraph.h"
#include "Visitor.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
CoordinateSystem::CoordinateSystem()
	: CompositeGraph() {
	this->magnificationX = 0.0f;
	this->magnificationY = 0.0f;
	this->originX = 0;
	this->originY = 0;
}

CoordinateSystem::CoordinateSystem(Long capacity, double magnificationX, double magnificationY, Long originX, Long originY)
	:CompositeGraph(capacity) {
	this->magnificationX = magnificationX;
	this->magnificationY = magnificationY;
	this->originX = originX;
	this->originY = originY;
}


CoordinateSystem::CoordinateSystem(const CoordinateSystem& source)
	:CompositeGraph(source) {
	this->magnificationX = source.magnificationX;
	this->magnificationY = source.magnificationY;
	this->originX = source.originX;
	this->originY = source.originY;
}

CoordinateSystem::~CoordinateSystem() {

}

void CoordinateSystem::Accept(Visitor *visitor) {
	visitor->Visit(this);
}

Graph* CoordinateSystem::GetAt(Long index) {
	return this->graphs.GetAt(index);
}

CoordinateSystem& CoordinateSystem::operator=(const CoordinateSystem& source) {
	CompositeGraph::operator=(source);
	this->magnificationX = source.magnificationX;
	this->magnificationY = source.magnificationY;
	this->originX = source.originX;
	this->originY = source.originY;

	return *this;
}

Graph* CoordinateSystem::operator[](Long index) {
	return this->graphs[index];
}

Graph* CoordinateSystem::Clone() {
	return new CoordinateSystem(*this);
}