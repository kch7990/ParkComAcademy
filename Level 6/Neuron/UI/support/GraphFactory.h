#ifndef _GRAPHFACTORY_H
#define _GRAPHFACTORY_H

typedef enum _graphType {
	GRAPH_HORIZONTALTEXT = 0, GRAPH_VERTICALTEXT = 11, GRAPH_LINE = 1, GRAPH_POINT = 2, GRAPH_COORDINATESYSTEM = 3,
	GRAPH_RECTANGLE = 4, GRAPH_LAYERBOX = 5, GRAPH_LAYERBOXCONROL = 6, GRAPH_ARROW = 7, GRAPH_CELL = 8, GRAPH_TABLE = 9,
	GRAPH_LAYOUT = 10, GRAPH_LAYERTOOLTIP = 12, GRAPH_ICON = 13, GRAPH_CIRCLE = 14, GRAPH_CROSS = 15
} GraphType;

class Layer;
class Graph;
class GraphFactory {
public:
	GraphFactory();
	GraphFactory(const GraphFactory& source);
	~GraphFactory();
	Graph* Make(GraphType graphType);

	GraphFactory& operator =(const GraphFactory& source);
};



#endif // !_GRAPHFACTORY_H
