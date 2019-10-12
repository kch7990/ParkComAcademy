#ifndef _GRAPH_H
#define _GRAPH_H

#include <afxwin.h>
#include <iostream>
using namespace std;
typedef signed long int Long;

class Visitor;

class Graph {
public:
	Graph();
	Graph(COLORREF color);
	Graph(const Graph& source);
	virtual ~Graph() = 0;
	virtual void Accept(Visitor *visitor) = 0;
	virtual Graph* GetAt(Long index);
	virtual Long Add(Graph *graph);
	virtual Graph* Clone() = 0;

	virtual bool GetIsClicked() const;

	virtual Long GetCapacity() const;
	virtual Long GetLength() const;
	virtual RECT GetRect() const;
	virtual string GetType() const;
	virtual string GetContent() const;
	virtual Long GetBoxHeight() const;
	virtual Long GetBoxWidth() const;
	virtual Long GetInterval() const;
	virtual UINT GetID() const;

	Graph& operator =(const Graph& source);
	virtual Graph* operator[](Long index);

	COLORREF GetColor() const;

protected:
	COLORREF color;
};

inline bool Graph::GetIsClicked() const {
	return false;
}


inline Long Graph::GetBoxHeight() const {
	return -1;
}

inline Long Graph::GetBoxWidth() const {
	return -1;
}

inline Long Graph::GetInterval() const {
	return -1;
}

inline string Graph::GetContent() const {
	return "";
}

inline COLORREF Graph::GetColor() const {
	return this->color;
}

inline UINT Graph::GetID() const {
	return 0;
}

#endif // !_GRAPH_H
