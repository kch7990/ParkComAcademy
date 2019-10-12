#pragma once

#include "Array.h"
#include <string>
#include <iostream>

typedef signed long int Long;

using namespace std;

class File {
public:
	File();
	File(string name);
	File(const File& source);
	~File();
	virtual void ReadHeader() = 0;
	Long First();
	Long Previous();
	Long Next();
	Long Last();
	Long Move(Long index);
	Long ReverseInteger(Long integer);
	File& operator=(const File& source);
	string& GetName() const;
	Long GetMagicNumber() const;
	Long GetContentCount() const;
	Long GetCurrent() const;
protected:
	string name;
	Long magicNumber;
	Long contentCount;
	Long current;
};

inline string& File::GetName() const {
	return const_cast<string&>(this->name);
}

inline Long File::GetMagicNumber() const {
	return this->magicNumber;
}

inline Long File::GetContentCount() const {
	return this->contentCount;
}

inline Long File::GetCurrent() const {
	return this->current;
}
