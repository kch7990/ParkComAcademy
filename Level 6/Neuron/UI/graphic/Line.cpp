#include "Line.h"
#include "Visitor.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
Line::Line() {
	this->startX = 0;
	this->startY = 0;
	this->endX = 0;
	this->endY = 0;
}

Line::Line(Long startX, Long startY, Long endX, Long endY, COLORREF color) 
	: Graph(color) {
	this->startX = startX;
	this->startY = startY;
	this->endX = endX;
	this->endY = endY;
}

Line::Line(const Line& source) 
	: Graph(source) {
	this->startX = source.startX;
	this->startY = source.startY;
	this->endX = source.endX;
	this->endY = source.endY;
}

Line::~Line() {

}

Line& Line::operator=(const Line& source) {
	Graph::operator=(source);
	this->startX = source.startX;
	this->startY = source.startY;
	this->endX = source.endX;
	this->endY = source.endY;

	return *this;
}

void Line::Accept(Visitor *visitor) {
	visitor->Visit(this);
}

Graph* Line::Clone() {
	return new Line(*this);
}