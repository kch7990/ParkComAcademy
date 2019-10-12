#ifndef _RECTANGLE_GRAPH
#define _RECTANGLE_GRAPH

#include "Graph.h"

class RectangleGraph : public Graph {
public:
	RectangleGraph();
	RectangleGraph(RECT rect, COLORREF color);
	RectangleGraph(const RectangleGraph& source);
	virtual ~RectangleGraph();
	RectangleGraph& operator=(const RectangleGraph& source);

	virtual void Accept(Visitor *visitor);
	virtual Graph* Clone();
	virtual RECT GetRect() const;

private:
	RECT rect;
};

inline RECT RectangleGraph::GetRect() const {
	return this->rect;
}

#endif // !_RECTANGLE_GRAPH
