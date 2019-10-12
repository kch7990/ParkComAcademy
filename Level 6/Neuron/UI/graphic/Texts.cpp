#include "Texts.h"
#include "Visitor.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//Text
Text::Text()
	: content("") {
	this->x = 0;
	this->y = 0;
}

Text::Text(Long x, Long y, string content, COLORREF color)
	: Graph(color), content(content) {
	this->x = x;
	this->y = y;
}

Text::Text(const Text& source)
	: Graph(source), content(source.content) {
	this->x = source.x;
	this->y = source.y;
}

Text::~Text() {

}

Text& Text::operator=(const Text& source) {
	Graph::operator=(source);

	this->x = source.x;
	this->y = source.y;
	this->content = source.content;

	return *this;
}

//HorizontalText
HorizontalText::HorizontalText()
	: Text() {

}

HorizontalText::HorizontalText(Long x, Long y, string content, COLORREF color)
	: Text(x, y, content, color) {

}

HorizontalText::HorizontalText(const HorizontalText& source)
	: Text(source) {

}

HorizontalText::~HorizontalText() {

}

HorizontalText& HorizontalText::operator=(const HorizontalText& source) {
	Text::operator=(source);

	return *this;
}

void HorizontalText::Accept(Visitor *visitor) {
	visitor->Visit(this);
}

Graph* HorizontalText::Clone() {
	return new HorizontalText(*this);
}

//VerticalText
VerticalText::VerticalText()
	: Text() {

}

VerticalText::VerticalText(Long x, Long y, string content, COLORREF color)
	: Text(x, y, content, color) {

}

VerticalText::VerticalText(const VerticalText& source)
	: Text(source) {

}

VerticalText::~VerticalText() {

}

VerticalText& VerticalText::operator=(const VerticalText& source) {
	Text::operator=(source);

	return *this;
}

void VerticalText::Accept(Visitor *visitor) {
	visitor->Visit(this);
}

Graph* VerticalText::Clone() {
	return new VerticalText(*this);
}