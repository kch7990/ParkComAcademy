#ifndef _VISITOR_H
#define _VISITOR_H

class NeuronForm;
class Point;
class CoordinateSystem;
class Line;
class HorizontalText;
class VerticalText;
class LayerBoxControl;
class Arrow;
class LayerBox;
class RectangleGraph;
class AddBox;
class Cell;
class Table;
class Layout;
class RoundRectangle;
class LayerToolTip;
class Icon;
class Circle;
class Cross;

class Visitor {
public:
	Visitor();
	Visitor(const Visitor& source);
	virtual ~Visitor() = 0;
	virtual void Visit(Point *point) = 0;
	virtual void Visit(CoordinateSystem *coordinateSystem) = 0;
	virtual void Visit(Line *line) = 0;
	virtual void Visit(HorizontalText *text) = 0;
	virtual void Visit(VerticalText *text) = 0;
	virtual void Visit(LayerBox *layerBox) = 0;
	virtual void Visit(RectangleGraph *rectangleGraph) = 0;
	virtual void Visit(LayerBoxControl * layerBoxControl) = 0;
	virtual void Visit(Arrow * arrow) = 0;
	virtual void Visit(AddBox* addBox) = 0;
	virtual void Visit(Cell* cell) = 0;
	virtual void Visit(Table* table) = 0;
	virtual void Visit(Layout *layout) = 0;
	virtual void Visit(RoundRectangle *roundRectangle) = 0;
	virtual void Visit(LayerToolTip *layerToolTip) = 0;
	virtual void Visit(Icon *icon) = 0;
	virtual void Visit(Circle *circle) = 0;
	virtual void Visit(Cross *cross) = 0;

	Visitor& operator=(const Visitor& source);
};

#endif // !_VISITOR_H
