#ifndef _LAYOUT_H
#define _LAYOUT_H

#include "CompositeGraph.h"

class Visitor;
class Graph;
class Layout : public CompositeGraph {
public:
	Layout(Long capacity = 256);
	Layout(const Layout& source);
	virtual ~Layout();
	virtual void Accept(Visitor *visitor);
	virtual Graph* Clone();

	Layout& operator=(const Layout& source);
};

#endif // _LAYOUT_H
