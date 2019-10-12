#include "Table.h"
#include "Graph.h"
#include "Visitor.h"
#include "DrawingVisitor.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


Table::Table() {
	this->rowCount = 0;
	this->columnCount = 0;
	this->width = 0;
	this->height = 0;
	this->rowInterval = 0;
	this->columnInterval = 0;
}

Table::Table(Long capacity, Long rowCount, Long columnCount, Long width,
	Long height, Long rowInterval, Long columnInterval)
:CompositeGraph(capacity){
	this->rowCount = rowCount;
	this->columnCount = columnCount;
	this->width = width;
	this->height = height;
	this->rowInterval = rowInterval;
	this->columnInterval = columnInterval;
}

Table::Table(const Table& source) 
:CompositeGraph(source){
	this->rowCount = source.rowCount;
	this->columnCount = source.columnCount;
	this->width = source.width;
	this->height = source.height;
	this->rowInterval = source.rowInterval;
	this->columnInterval = source.columnInterval;
}

Table::~Table() {

}

void Table::Accept(Visitor *visitor) {
	visitor->Visit(this);
}

Graph* Table::Clone() {
	return new Table(*this);
}

Table& Table::operator = (const Table& source) {
	CompositeGraph::operator=(source);
	this->rowCount = source.rowCount;
	this->columnCount = source.columnCount;
	this->width = source.width;
	this->height = source.height;
	this->rowInterval = source.rowInterval;
	this->columnInterval = source.columnInterval;

	return *this;
}