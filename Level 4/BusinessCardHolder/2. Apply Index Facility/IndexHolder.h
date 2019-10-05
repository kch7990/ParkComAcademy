#ifndef _INDEXHOLDER_H
#define _INDEXHOLDER_H

#include "Index.h"
#include "BinaryTree.h"
#include <string>

using namespace std;

class BusinessCard;
class IndexHolder {
public:
	IndexHolder();
	IndexHolder(const IndexHolder& source);
	~IndexHolder();
	Index* PutIn(BusinessCard *businessCardLink);
	Index* Find(string companyName);
	Index* PutOut(string companyName, BusinessCard *businessCardLink);
	void MakeList(Index* (*indexes), Long *count);
	void Arrange();

	IndexHolder& operator =(const IndexHolder& source);
	
	Long GetLength() const;

private:
	BinaryTree<Index> indexes;
	Long length;
};
inline Long IndexHolder::GetLength() const {
	return this->length;
}
int CompareIndexes(void *one, void *other);

#endif //_INDEXHOLDER_H