#ifndef _ARROW_H
#define _ARROW_H

#include <afxwin.h>
#include "Graph.h"

class Visitor;
class Arrow : public Graph {
public:
	Arrow();
	Arrow(RECT rect, COLORREF color);
	Arrow(const Arrow& source);
	~Arrow();
	virtual void Accept(Visitor *visitor);
	virtual Graph* Clone();
	Arrow& operator=(const Arrow& source);
	RECT GetRect() const;
private:
	RECT rect;
};

inline RECT Arrow::GetRect() const {
	return this->rect;
}
#endif // !_ARROW_H
