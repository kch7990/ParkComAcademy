#ifndef _ROUNDRECTANGLE_H
#define _ROUNDRECTANGLE_H

#include "Graph.h"

class Visitor;
class RoundRectangle : public Graph {
public:
	RoundRectangle();
	RoundRectangle(RECT rect, string content, COLORREF color, bool isClicked);
	RoundRectangle(const RoundRectangle& source);
	virtual ~RoundRectangle();

	virtual void Accept(Visitor *visitor);
	virtual Graph* Clone();

	virtual RECT GetRect() const;
	virtual string GetContent() const;
	virtual bool GetIsClicked() const;

	RoundRectangle& operator=(const RoundRectangle& source);
private:
	RECT rect;
	string content;
	bool isClicked;
};

inline RECT RoundRectangle::GetRect() const {
	return this->rect;
}
inline string RoundRectangle::GetContent() const {
	return this->content;
}
inline bool RoundRectangle::GetIsClicked() const {
	return this->isClicked;
}

#endif //_ROUNDRECTANGLE_H
