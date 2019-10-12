#pragma once

#include "File.h"
#include "Array.h"
#include <string>
#include <iostream>

using namespace std;

class LabelFile : public File {
public:
	LabelFile();
	LabelFile(string name);
	LabelFile(const LabelFile& source);
	~LabelFile();
	virtual void ReadHeader();
	Array<Long> Load();
	Long GetAt(Long index);
	LabelFile& operator=(const LabelFile& source);
};
