#include "Cross.h"
#include "Visitor.h"

Cross::Cross() {
	this->rect.left = 0;
	this->rect.right = 0;
	this->rect.top = 0;
	this->rect.bottom = 0;
	this->isClicked = false;
}

Cross::Cross(RECT rect, COLORREF color, bool isClicked)
	: Graph(color) {
	this->rect = rect;
	this->isClicked = isClicked;
}

Cross::Cross(const Cross& source)
	: Graph(source) {
	this->rect = source.rect;
	this->isClicked = source.isClicked;
}

Cross::~Cross() {

}

void Cross::Accept(Visitor *visitor) {
	visitor->Visit(this);
}

Graph* Cross::Clone() {
	return new Cross(*this);
}

Cross& Cross::operator=(const Cross& source) {
	Graph::operator=(source);
	this->rect = source.rect;
	this->isClicked = source.isClicked;

	return *this;
}