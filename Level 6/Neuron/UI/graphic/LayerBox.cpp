#include "LayerBox.h"
#include "Visitor.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
LayerBox::LayerBox() 
	:type("") {
	this->rect.left = 0;
	this->rect.right = 0;
	this->rect.top = 0;
	this->rect.bottom = 0;
}

LayerBox::LayerBox(RECT rect, string type, COLORREF color)
	: Graph(color), type(type) {
	this->rect = rect;
}

LayerBox::LayerBox(const LayerBox& source)
	: Graph(source), type(source.type) {
	this->rect = source.rect;
}

LayerBox::~LayerBox() {

}

void LayerBox::Accept(Visitor *visitor) {
	visitor->Visit(this);
}

Graph* LayerBox::Clone() {
	return new LayerBox(*this);
}

LayerBox& LayerBox::operator =(const LayerBox& source) {
	Graph::operator=(source);
	this->rect = source.rect;
	this->type = source.type;

	return *this;
}