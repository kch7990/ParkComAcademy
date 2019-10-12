//Graph.cpp
#include "Graph.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
Graph::Graph() {
	this->color = RGB(0, 0, 0);
}

Graph::Graph(COLORREF color) {
	this->color = color;
}

Graph::Graph(const Graph& source) {
	this->color = source.color;
}

Graph::~Graph() {
}

Graph& Graph::operator=(const Graph& source) {
	this->color = source.color;
	
	return *this;
}

Graph* Graph::operator[](Long index) {
	return 0;
}

Long Graph::Add(Graph *graph) {
	return -1;
}

Graph* Graph::GetAt(Long index) {
	return 0;
}

Long Graph::GetCapacity() const {
	return -1;
}

Long Graph::GetLength() const {
	return -1;
}

RECT Graph::GetRect() const {
	RECT rect = { 0, };
	return rect;
}

string Graph::GetType() const {
	return "";
}