#ifndef _LAYERTOOLTIP_H
#define _LAYERTOOLTIP_H

#include "CompositeGraph.h"

class Visitor;

class LayerToolTip : public CompositeGraph {
public:
	LayerToolTip(Long capacity=256);
	LayerToolTip(const LayerToolTip& source);
	virtual ~LayerToolTip();

	virtual void Accept(Visitor *visitor);

	virtual Graph* Clone();

	LayerToolTip& operator=(const LayerToolTip& source);
};

#endif //_LAYERTOOLTIP_H