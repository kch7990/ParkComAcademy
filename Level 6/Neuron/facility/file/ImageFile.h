#pragma once

#include "File.h"
#include "Array.h"
#include <string>
#include <iostream>

typedef signed long int Long;

using namespace std;

class ImageFile : public File {
public:
	ImageFile();
	ImageFile(string name);
	ImageFile(const ImageFile& source);
	~ImageFile();
	virtual void ReadHeader();
	Array<Array<double>> Load(bool isNormalizing);
	Array<double> GetAt(Long index, bool isNormalizing);
	ImageFile& operator=(const ImageFile& source);
	Long GetRowCount() const;
	Long GetColumnCount() const;
	Long GetImageSize() const;
private:
	Long rowCount;
	Long columnCount;
	Long imageSize;
};

inline Long ImageFile::GetRowCount() const {
	return this->rowCount;
}

inline Long ImageFile::GetColumnCount() const {
	return this->columnCount;
}

inline Long ImageFile::GetImageSize() const {
	return this->imageSize;
}
