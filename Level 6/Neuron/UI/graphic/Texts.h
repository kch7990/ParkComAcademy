#ifndef _TEXTS_H
#define _TEXTS_H

#include "Graph.h"
#include <string>

using namespace std;

//Text
class Text : public Graph {
public:
	Text();
	Text(Long x, Long y, string content, COLORREF color);
	Text(const Text& source);
	virtual ~Text() = 0;
	Text& operator=(const Text& soure);

	virtual void Accept(Visitor *visitor) = 0;

	Long GetX() const;
	Long GetY() const;
	virtual string GetContent() const;
protected:
	Long x;
	Long y;
	string content;
};

inline Long Text::GetX() const {
	return this->x;
}

inline Long Text::GetY() const {
	return this->y;
}

inline string Text::GetContent() const {
	return this->content;
}

//HorizontalText
class HorizontalText : public Text {
public:
	HorizontalText();
	HorizontalText(Long x, Long y, string content, COLORREF color);
	HorizontalText(const HorizontalText& source);
	virtual ~HorizontalText();

	virtual void Accept(Visitor *visitor);
	virtual Graph* Clone();
	HorizontalText& operator=(const HorizontalText& source);
};

class VerticalText : public Text {
public:
	VerticalText();
	VerticalText(Long x, Long y, string content, COLORREF color);
	VerticalText(const VerticalText& source);
	virtual ~VerticalText();

	virtual void Accept(Visitor *visitor);
	virtual Graph* Clone();
	VerticalText& operator=(const VerticalText& source);
};

#endif // !_TEXTS_H
