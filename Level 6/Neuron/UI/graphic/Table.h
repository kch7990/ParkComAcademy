#ifndef _TABLE_H
#define _TABLE_H

#include "CompositeGraph.h"

typedef signed long int Long;

class Visitor;
class Graph;
class Table : public CompositeGraph {
public:
	Table();
	Table(Long capacity, Long rowCount, Long columnCount, Long width,
		Long height, Long rowInterval, Long columnInterval);
	Table(const Table& source);
	virtual ~Table();
	virtual void Accept(Visitor *visitor);
	virtual Graph* Clone();
	Long GetRowCount() const;
	Long GetColumnCount() const;
	Long GetWidth() const;
	Long GetHeight() const;
	Long GetRowInterval() const;
	Long GetColumnInterval() const;

	Table& operator=(const Table& source);

private:
	Long rowCount;
	Long columnCount;
	Long width;
	Long height;
	Long rowInterval;
	Long columnInterval;
};

inline Long Table::GetRowCount() const {
	return this->rowCount;
}

inline Long Table::GetColumnCount() const {
	return this->columnCount;
}

inline Long Table::GetWidth() const {
	return this->width;
}

inline Long Table::GetHeight() const {
	return this->height;
}

inline Long Table::GetRowInterval() const {
	return this->rowInterval;
}

inline Long Table::GetColumnInterval() const {
	return this->columnInterval;
}


#endif // !_TABLE_H
