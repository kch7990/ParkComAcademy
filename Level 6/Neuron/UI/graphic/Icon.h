#ifndef _ICON_H
#define _ICON_H

#include "Graph.h"

class Visitor;

class Icon : public Graph {
public:
	Icon();
	Icon(RECT rect, COLORREF color, UINT ID, bool isClicked);
	Icon(const Icon& source);
	virtual ~Icon();

	virtual void Accept(Visitor *visitor);
	virtual Graph* Clone();

	virtual RECT GetRect() const;
	virtual UINT GetID() const;
	virtual bool GetIsClicked() const;

	Icon& operator=(const Icon& source);
private:
	RECT rect;
	UINT ID;
	bool isClicked;
};

inline RECT Icon::GetRect() const {
	return this->rect;
}

inline UINT Icon::GetID() const {
	return this->ID;
}

inline bool Icon::GetIsClicked() const {
	return this->isClicked;
}

#endif //_ICON_H