#ifndef _LINE_H
#define _LINE_H

#include "Graph.h"

class Line : public Graph {
public:
	Line();
	Line(Long startX, Long startY, Long endX, Long endY, COLORREF color);
	Line(const Line& source);
	virtual ~Line();

	virtual void Accept(Visitor *visitor);
	virtual Graph* Clone();

	Line& operator=(const Line& soure);

	Long GetStartX() const;
	Long GetStartY() const;
	Long GetEndX() const;
	Long GetEndY() const;
private:
	Long startX;
	Long startY;
	Long endX;
	Long endY;
};

inline Long Line::GetStartX() const {
	return this->startX;
}

inline Long Line::GetStartY() const {
	return this->startY;
}

inline Long Line::GetEndX() const {
	return this->endX;
}

inline Long Line::GetEndY() const {
	return this->endY;
}

#endif // !_LINE_H
