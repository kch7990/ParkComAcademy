#ifndef _CELL_H
#define _CELL_H

#include <string>
#include <afxwin.h>
#include "Graph.h"

using namespace std;


class Visitor;

class Cell :public Graph{
public:
	Cell();
	Cell(RECT rect, string content, COLORREF color);
	Cell(const Cell& source);
	virtual ~Cell();
	virtual void Accept(Visitor *visitor);
	virtual Graph* Clone();
	Cell& operator=(const Cell& source);

	virtual RECT GetRect() const;
	virtual string GetContent() const;
private:
	RECT rect;
	string content;
};

inline RECT Cell::GetRect() const {
	return this->rect;
}

inline string Cell::GetContent() const {
	return this->content;
}

#endif // !_CELL_H
