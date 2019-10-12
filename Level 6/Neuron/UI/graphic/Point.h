#ifndef _POINT_H
#define _POINT_H

#include "Graph.h"

class Visitor;

class Point : public Graph {
public:
	Point();
	Point(Long x, Long y, COLORREF color);
	Point(const Point& source);
	virtual ~Point();
	virtual void Accept(Visitor *visitor);
	virtual Graph* Clone();

	Point& operator =(const Point& source);

	Long GetX() const;
	Long GetY() const;
private:
	Long x;
	Long y;
};

inline Long Point::GetX() const {
	return this->x;
}

inline Long Point::GetY() const {
	return this->y;
}
#endif //_POINT_H