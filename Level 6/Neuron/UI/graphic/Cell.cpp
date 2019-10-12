#include "Cell.h"
#include "Graph.h"
#include "Visitor.h"
#include "DrawingVisitor.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

Cell::Cell() 
: content(""){
	this->rect = { 0, };
	
}

Cell::Cell(RECT rect, string content, COLORREF color)
	: Graph(color), content(content){
	this->rect = rect;
}

Cell::Cell(const Cell& source) 
	: Graph(source), content(source.content) {
	this->rect = source.rect;
}

Cell::~Cell() {

}

void Cell::Accept(Visitor *visitor){
	visitor->Visit(this);
}

Graph* Cell::Clone(){
	return new Cell(*this);
}

Cell& Cell::operator=(const Cell& source) {
	Graph::operator=(source);
	this->rect = source.rect;
	this->content = source.content;

	return *this;
}