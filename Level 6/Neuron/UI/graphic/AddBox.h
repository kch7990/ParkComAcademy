#ifndef _ADDBOX_H
#define _ADDBOX_H

#include <afxwin.h>
#include "Graph.h"

class Visitor;
class AddBox : public Graph {
public:
	AddBox();
	AddBox(RECT rect, COLORREF color, bool isClicked);
	AddBox(const AddBox& source);
	~AddBox();
	virtual void Accept(Visitor *visitor);
	virtual Graph* Clone();
	AddBox& operator=(const AddBox& source);
	RECT GetRect() const;
	virtual bool GetIsClicked() const;
private:
	RECT rect;
	bool isClicked;
};

inline RECT AddBox::GetRect() const {
	return this->rect;
}

inline bool AddBox::GetIsClicked() const {
	return this->isClicked;
}

#endif // !_ADDBOX_H
