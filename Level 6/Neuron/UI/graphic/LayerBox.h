#ifndef _LAYERBOX_H
#define _LAYERBOX_H

#include "Graph.h"
#include <afxwin.h>
#include <iostream>
using namespace std;
class Visitor;

class LayerBox : public Graph {
public:
	LayerBox();
	LayerBox(RECT rect, string type, COLORREF color);
	LayerBox(const LayerBox& source);
	virtual ~LayerBox();

	virtual void Accept(Visitor *visitor);
	virtual Graph* Clone();

	LayerBox& operator =(const LayerBox& source);

	virtual RECT GetRect() const;
	virtual string GetType() const;
private:
	RECT rect;
	string type;
};

inline RECT LayerBox::GetRect() const {
	return this->rect;
}
inline string LayerBox::GetType() const {
	return this->type;
}

#endif //_LAYERBOX_H