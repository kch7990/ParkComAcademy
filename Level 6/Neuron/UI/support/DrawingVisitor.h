#ifndef _DRAWINGVISITOR_H
#define _DRAWINGVISITOR_H

#include "Visitor.h"
#include <afxwin.h>

class ScrollController;

class DrawingVisitor : public Visitor {
public:
	DrawingVisitor(CDC *dc = 0, ScrollController *scrollController = 0);
	DrawingVisitor(const DrawingVisitor& source);
	virtual ~DrawingVisitor();

	virtual void Visit(Point *point);
	virtual void Visit(CoordinateSystem *coordintateSystem);	
	virtual void Visit(Line *line);
	virtual void Visit(HorizontalText *text);
	virtual void Visit(VerticalText *text);
	virtual void Visit(LayerBox *layerBox);
	virtual void Visit(RectangleGraph *rectangleGraph);
	virtual void Visit(LayerBoxControl *layerBoxControl);
	virtual void Visit(Arrow * arrow);
	virtual void Visit(AddBox* addBox);
	virtual void Visit(Cell* cell);
	virtual void Visit(Table* table);
	virtual void Visit(Layout *layout);
	virtual void Visit(RoundRectangle *roundRectangle);
	virtual void Visit(LayerToolTip *layerToolTip);
	virtual void Visit(Icon *icon);
	virtual void Visit(Circle *circle);
	virtual void Visit(Cross *cross);

	DrawingVisitor& operator=(const DrawingVisitor& source);
private:
	CDC *dc;
	ScrollController *scrollController;
};

#endif