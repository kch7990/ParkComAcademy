#ifndef _CROSS_H
#define _CROSS_H

#include "Graph.h"

class Cross : public Graph {
public:
	Cross();
	Cross(RECT rect, COLORREF color, bool isClicked);
	Cross(const Cross& source);
	virtual ~Cross();
	virtual void Accept(Visitor *visitor);
	virtual Graph* Clone();

	virtual RECT GetRect() const;
	virtual bool GetIsClicked() const;

	Cross& operator =(const Cross& source);
private:
	RECT rect;
	bool isClicked;
};

inline RECT Cross::GetRect() const {
	return this->rect;
}

inline bool Cross::GetIsClicked() const {
	return this->isClicked;
}

#endif //_CROSS_H