#ifndef _CIRCLE_H
#define _CIRCLE_H

#include "Graph.h"

class Circle : public Graph {
public:
	Circle();
	Circle(RECT rect, COLORREF color, bool isClicked);
	Circle(const Circle& source);
	virtual ~Circle();
	virtual void Accept(Visitor *visitor);
	virtual Graph* Clone();

	virtual RECT GetRect() const;
	virtual bool GetIsClicked() const;

	Circle& operator =(const Circle& source);
private:
	RECT rect;
	bool isClicked;
};

inline RECT Circle::GetRect() const {
	return this->rect;
}

inline bool Circle::GetIsClicked() const {
	return this->isClicked;
}

#endif //_CIRCLE_H