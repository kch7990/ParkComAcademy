#include "ImageFile.h"
#include <fstream>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
typedef unsigned char UChar;

ImageFile::ImageFile()
	:File() {
	this->rowCount = 0;
	this->columnCount = 0;
	this->imageSize = 0;
}

ImageFile::ImageFile(string name)
	: File(name) {
	this->rowCount = 0;
	this->columnCount = 0;
	this->imageSize = 0;
}

ImageFile::ImageFile(const ImageFile& source)
	: File(source) {
	this->rowCount = source.rowCount;
	this->columnCount = source.columnCount;
	this->imageSize = source.imageSize;
}

ImageFile::~ImageFile() {

}

void ImageFile::ReadHeader() {
	ifstream ifs;
	ifs.open(this->name, ios::binary);

	if (ifs.is_open()) {
		ifs.read(reinterpret_cast<char*>(&this->magicNumber), sizeof(this->magicNumber));
		this->magicNumber = this->ReverseInteger(this->magicNumber);

		ifs.read(reinterpret_cast<char*>(&this->contentCount), sizeof(this->contentCount));
		this->contentCount = this->ReverseInteger(this->contentCount);

		ifs.read(reinterpret_cast<char*>(&this->rowCount), sizeof(this->rowCount));
		this->rowCount = this->ReverseInteger(this->rowCount);

		ifs.read(reinterpret_cast<char*>(&this->columnCount), sizeof(this->columnCount));
		this->columnCount = this->ReverseInteger(this->columnCount);

		this->imageSize = this->rowCount * this->columnCount;

		ifs.close();
	}
}

Array<Array<double>> ImageFile::Load(bool isNormalizing) {
	ifstream ifs;
	ifs.open(this->name, ios::in | ios::binary);

	if (!ifs.is_open()) {
		return 0;
	}

	ifs.read(reinterpret_cast<char*>(&this->magicNumber), sizeof(this->magicNumber));
	this->magicNumber = this->ReverseInteger(this->magicNumber);

	ifs.read(reinterpret_cast<char*>(&this->contentCount), sizeof(this->contentCount));
	this->contentCount = this->ReverseInteger(this->contentCount);

	ifs.read(reinterpret_cast<char*>(&this->rowCount), sizeof(this->rowCount));
	this->rowCount = this->ReverseInteger(this->rowCount);

	ifs.read(reinterpret_cast<char*>(&this->columnCount), sizeof(this->columnCount));
	this->columnCount = this->ReverseInteger(this->columnCount);

	this->imageSize = this->rowCount * this->columnCount;

	Array<Array<double>> images(this->contentCount);

	double normalization = 1.0;
	if (isNormalizing == true) {
		normalization = 255.0;
	}

	for (Long i = 0; i < this->contentCount; i++) {
		Array<double> image(this->imageSize);
		for (Long row = 0; row < rowCount; row++) {
			for (Long column = 0; column < columnCount; column++) {
				UChar temp = 0;
				ifs.read(reinterpret_cast<char*>(&temp), sizeof(temp));
				image.Store(row * this->columnCount + column, static_cast<double>(temp) / normalization);
			}
		}

		images.Store(i, image);
	}

	ifs.close();

	return images;
}

Array<double> ImageFile::GetAt(Long index, bool isNormalizing) {
	ifstream ifs;
	ifs.open(this->name, ios::in | ios::binary);

	if (!ifs.is_open()) {
		return 0;
	}

	ifs.read(reinterpret_cast<char*>(&this->magicNumber), sizeof(this->magicNumber));
	this->magicNumber = this->ReverseInteger(this->magicNumber);

	ifs.read(reinterpret_cast<char*>(&this->contentCount), sizeof(this->contentCount));
	this->contentCount = this->ReverseInteger(this->contentCount);

	ifs.read(reinterpret_cast<char*>(&this->rowCount), sizeof(this->rowCount));
	this->rowCount = this->ReverseInteger(this->rowCount);

	ifs.read(reinterpret_cast<char*>(&this->columnCount), sizeof(this->columnCount));
	this->columnCount = this->ReverseInteger(this->columnCount);

	this->imageSize = this->rowCount * this->columnCount;

	ifs.seekg(index * this->imageSize, ios_base::cur);

	Array<double> image(this->imageSize);

	double normalization = 1.0;
	if (isNormalizing == true) {
		normalization = 255.0;
	}

	for (Long row = 0; row < this->rowCount; row++) {
		for (Long column = 0; column < this->columnCount; column++) {
			UChar temp = 0;
			ifs.read(reinterpret_cast<char*>(&temp), sizeof(temp));
			image.Store(row * this->columnCount + column, static_cast<double>(temp) / normalization);
		}
	}

	ifs.close();

	return image;
}

ImageFile& ImageFile::operator=(const ImageFile& source) {
	File::operator=(source);

	this->rowCount = source.rowCount;
	this->columnCount = source.columnCount;

	return *this;
}