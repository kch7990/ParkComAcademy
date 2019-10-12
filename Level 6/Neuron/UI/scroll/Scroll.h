#ifndef _SCROLL_H
#define _SCROLL_H

typedef signed long int Long;
#include <afxwin.h>
class Scroll {
public:
	Scroll();
	Scroll(Long position, Long minimum, Long maximum, Long lineSize, Long pageSize);
	Scroll(const Scroll& source);
	~Scroll();

	Long Up();
	Long Down();
	Long PageUp();
	Long PageDown();
	Long Move(Long position);
	Long Rotate(short delta);

	SCROLLINFO GetScrollInfo();

	Long GetPosition() const;
	Long GetMinimum() const;
	Long GetMaximum() const;
	Long GetLineSize() const;
	Long GetPageSize() const;

	Scroll& operator =(const Scroll& source);
private:
	Long position;
	Long minimum;
	Long maximum;
	Long lineSize;
	Long pageSize;
};

inline Long Scroll::GetPosition() const {
	return this->position;
}

inline Long Scroll::GetMinimum() const {
	return this->minimum;
}

inline Long Scroll::GetMaximum() const {
	return this->maximum;
}

inline Long Scroll::GetLineSize() const {
	return this->lineSize;
}

inline Long Scroll::GetPageSize() const {
	return this->pageSize;
}

#endif //_SCROLL_H