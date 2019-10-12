#include "CompositeGraph.h"
#include "Point.h"
#include "Graph.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
CompositeGraph::CompositeGraph(Long capacity)
	: graphs(capacity) {
	this->capacity = capacity;
	this->length = 0;
}

CompositeGraph::CompositeGraph(const CompositeGraph& source)
	: graphs(source.graphs) {
	Graph *graph;
	Long i = 0;
	while (i < source.length) {
		graph = const_cast<CompositeGraph&>(source).graphs.GetAt(i);
		this->graphs.Modify(i, graph->Clone());
		i++;
	}

	this->capacity = source.capacity;
	this->length = source.length;
}

CompositeGraph::~CompositeGraph() {
	Long i = 0;
	while (i < this->length) {
		if (this->graphs[i] != 0) {
			delete this->graphs[i];
		}

		i++;
	}
}

CompositeGraph& CompositeGraph::operator=(const CompositeGraph& source) {
	Long i = 0;
	while (i < this->length) {
		if (this->graphs[i] != 0) {
			delete this->graphs[i];
		}

		i++;
	}

	this->graphs = source.graphs;
	Graph *graph;

	i = 0;
	while (i < source.length) {
		graph = const_cast<CompositeGraph&>(source).graphs.GetAt(i);
		this->graphs.Modify(i, graph->Clone());
		i++;
	}

	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}

Long CompositeGraph::Add(Graph *graph) {
	Long index;

	if (this->length < this->capacity) {
		index = this->graphs.Store(this->length, graph);
	}
	else {
		index = this->graphs.AppendFromRear(graph);
		this->capacity++;
	}

	this->length++;

	return index;
}

Graph* CompositeGraph::GetAt(Long index) {
	return this->graphs.GetAt(index);
}