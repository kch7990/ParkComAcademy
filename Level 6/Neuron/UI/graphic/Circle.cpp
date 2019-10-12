#include "Circle.h"
#include "Visitor.h"

Circle::Circle() {
	this->rect.left = 0;
	this->rect.right = 0;
	this->rect.top = 0;
	this->rect.bottom = 0;
	this->isClicked = false;
}

Circle::Circle(RECT rect, COLORREF color, bool isClicked)
	: Graph(color) {
	this->rect = rect;
	this->isClicked = isClicked;
}

Circle::Circle(const Circle& source)
	: Graph(source) {
	this->rect = source.rect;
	this->isClicked = source.isClicked;
}

Circle::~Circle() {

}

void Circle::Accept(Visitor *visitor) {
	visitor->Visit(this);
}

Graph* Circle::Clone() {
	return new Circle(*this);
}

Circle& Circle::operator=(const Circle& source) {
	Graph::operator=(source);
	this->rect = source.rect;
	this->isClicked = source.isClicked;

	return *this;
}