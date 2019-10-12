#include "RoundRectangle.h"
#include "Visitor.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
RoundRectangle::RoundRectangle() 
	: content(""){
	this->rect.left = 0;
	this->rect.right = 0;
	this->rect.top = 0;
	this->rect.bottom = 0;
	this->isClicked = false;
}

RoundRectangle::RoundRectangle(RECT rect, string content, COLORREF color, bool isClicked)
	: Graph(color), content(content) {
	this->rect = rect;
	this->isClicked = isClicked;
}

RoundRectangle::RoundRectangle(const RoundRectangle& source)
	: Graph(source), content(source.content) {
	this->rect = source.rect;
	this->isClicked = source.isClicked;
}

RoundRectangle::~RoundRectangle() {

}

void RoundRectangle::Accept(Visitor *visitor) {
	visitor->Visit(this);
}

Graph* RoundRectangle::Clone() {
	return new RoundRectangle(*this);
}

RoundRectangle& RoundRectangle::operator=(const RoundRectangle& source) {
	Graph::operator=(source);
	this->rect = source.rect;
	this->content = source.content;
	this->isClicked = source.isClicked;

	return *this;
}