#include "Icon.h"
#include "Visitor.h"

Icon::Icon()  {
	this->rect = { 0, };
	this->ID = 0;
	this->isClicked = false;
}

Icon::Icon(RECT rect, COLORREF color, UINT ID, bool IsClicked)  {
	this->rect = rect;
	this->color = color;
	this->ID = ID;
	this->isClicked = IsClicked;
}

Icon::Icon(const Icon& source) {
	this->rect = source.rect;
	this->color = source.color;
	this->ID = source.ID;
	this->isClicked = source.isClicked;
}

Icon::~Icon() {

}

void Icon::Accept(Visitor *visitor) {
	visitor->Visit(this);
}

Graph* Icon::Clone() {
	return new Icon(*this);
}

Icon& Icon::operator=(const Icon& source) {
	this->rect = source.rect;
	this->color = source.color;
	this->ID = source.ID;
	this->isClicked = source.isClicked;

	return *this;
}