#ifndef _COMPOSITEGRAPH_H
#define _COMPOSITEGRAPH_H

#include "Array.h"
#include "Graph.h"

class Visitor;
class Graph;
typedef signed long int Long;

class CompositeGraph : public Graph {
public:
	CompositeGraph(Long capacity = 256);
	CompositeGraph(const CompositeGraph& source);
	virtual ~CompositeGraph() = 0;
	virtual void Accept(Visitor *visitor) = 0;
	virtual CompositeGraph& operator=(const CompositeGraph& source);
	virtual Graph* GetAt(Long index);
	virtual Long GetCapacity() const;
	virtual Long GetLength() const;
	virtual Long Add(Graph *graph);
protected:
	Array<Graph*> graphs;
	Long capacity;
	Long length;
};

inline Long CompositeGraph::GetCapacity() const {
	return this->capacity;
}

inline Long CompositeGraph::GetLength() const {
	return this->length;
}

#endif //_COMPOSITEGRAPH_H