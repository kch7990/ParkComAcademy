//GraphFactory.cpp
#include "GraphFactory.h"
#include "Affine.h"
#include "Node.h"
#include "CoordinateSystem.h"
#include "Point.h"
#include "Line.h"
#include "Texts.h"
#include "LayerBox.h"
#include "LayerBoxControl.h"
#include "Arrow.h"
#include "RectangleGraph.h"
#include "Cell.h"
#include "Layout.h"
#include "Table.h"
#include "LayerToolTip.h"
#include "Icon.h"
#include "Circle.h"
#include "Cross.h"

GraphFactory::GraphFactory() {
}

GraphFactory::GraphFactory(const GraphFactory& source) {
}

GraphFactory::~GraphFactory() {

}

Graph* GraphFactory::Make(GraphType graphType) {
	Graph *graph = 0;

	switch (graphType) {
		//집합의 집합
	case GRAPH_LAYOUT:
		graph = new Layout;
		break;
		//요소의 집합
	case GRAPH_COORDINATESYSTEM:
		graph = new CoordinateSystem;
		break;
	case GRAPH_LAYERBOXCONROL:
		graph = new LayerBoxControl;
		break;
	case GRAPH_TABLE:
		graph = new Table;
		break;
		//요소
	case GRAPH_HORIZONTALTEXT:
		graph = new HorizontalText;
		break;
	case GRAPH_VERTICALTEXT:
		graph = new VerticalText;
		break;
	case GRAPH_LINE:
		graph = new Line;
		break;
	case GRAPH_POINT:
		graph = new Point;
		break;
	case GRAPH_RECTANGLE:
		graph = new RectangleGraph;
		break;
	case GRAPH_LAYERBOX:
		graph = new LayerBox;
		break;
	case GRAPH_ARROW:
		graph = new Arrow;
		break;
	case GRAPH_CELL:
		graph = new Cell;
		break;
	case GRAPH_LAYERTOOLTIP:
		graph = new LayerToolTip;
		break;
	case GRAPH_ICON:
		graph = new Icon;
		break;
	case GRAPH_CIRCLE:
		graph = new Circle;
		break;
	case GRAPH_CROSS:
		graph = new Cross;
		break;

	default:
		break;
	}
	return graph;
}

GraphFactory& GraphFactory::operator =(const GraphFactory& source) {
	return *this;
}