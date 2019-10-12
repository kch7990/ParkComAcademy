#include "AddBox.h"
#include "Visitor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

AddBox::AddBox() {
	this->rect = { 0, };
	this->isClicked = false;
}

AddBox::AddBox(RECT rect, COLORREF color, bool isClicked)
	: Graph(color) {
	this->rect = rect;
	this->isClicked = isClicked;
}

AddBox::AddBox(const AddBox& source) 
	: Graph(source) {
	this->rect = source.rect;
	this->isClicked = source.isClicked;
}

AddBox::~AddBox() {

}

void AddBox::Accept(Visitor *visitor) {
	visitor->Visit(this);
}

Graph* AddBox::Clone() {
	return new AddBox(*this);
}

AddBox& AddBox::operator=(const AddBox& source) {
	Graph::operator=(source);
	this->rect = source.rect;
	this->isClicked = source.isClicked;

	return *this;
}