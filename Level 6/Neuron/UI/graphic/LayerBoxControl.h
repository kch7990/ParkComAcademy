#ifndef _LAYERBOXCONTROL_H
#define _LAYERBOXCONTROL_H

#include "CompositeGraph.h"

typedef signed long int Long;

class Graph;
class Visitor;
class LayerBoxControl : public CompositeGraph{
public:
	//LayerBoxControl(Long capacity = 256, Long boxHeight = 200, Long boxWidth = 100, Long interval = 50);
	LayerBoxControl(Long capacity = 256, Long boxHeight = 40, Long boxWidth = 130, Long interval = 20);
	LayerBoxControl(const LayerBoxControl& source);
	virtual ~LayerBoxControl();
	virtual void Accept(Visitor *visitor);
	virtual Graph* Clone();
	LayerBoxControl& operator=(const LayerBoxControl& source);

	Graph* GetAt(Long index);
	virtual Long GetBoxHeight() const;
	virtual Long GetBoxWidth() const;
	virtual Long GetInterval() const;

private:
	Long boxHeight;
	Long boxWidth;
	Long interval;
};

inline Long LayerBoxControl::GetBoxHeight() const {
	return this->boxHeight;
}

inline Long LayerBoxControl::GetBoxWidth() const {
	return this->boxWidth;
}

inline Long LayerBoxControl::GetInterval() const {
	return this->interval;
}


#endif // !_LAYERBOXCONTROL_H
