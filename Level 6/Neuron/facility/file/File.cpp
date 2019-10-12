#include "File.h"
#include <fstream>
#include <string>
#if !defined(_AFXDLL)

#include <crtdbg.h>
#if defined(DEBUG) |defined(_DEBUG)
#if !defined(DEBUG_NEW)
#define DEBUG_NEW new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif
#endif
#endif
typedef unsigned char UChar;

File::File()
	:name("") {
	this->magicNumber = 0;
	this->contentCount = 0;
	this->current = 0;
}

File::File(string name)
	: name(name) {
	this->magicNumber = 0;
	this->contentCount = 0;
	this->current = 0;
}

File::File(const File& source)
	: name(source.name) {
	this->magicNumber = source.magicNumber;
	this->contentCount = source.contentCount;
	this->current = source.current;
}

File::~File() {

}

Long File::ReverseInteger(Long integer) {
	UChar first;
	UChar second;
	UChar third;
	UChar fourth;

	first = integer & 255;
	second = (integer >> 8) & 255;
	third = (integer >> 16) & 255;
	fourth = (integer >> 24) & 255;

	integer = static_cast<Long>(first << 24) + static_cast<Long>(second << 16) + static_cast<Long>(third << 8) + fourth;

	return integer;
}

Long File::First() {
	this->current = 0;

	return this->current;
}

Long File::Previous() {
	this->current--;

	if (this->current < 0) {
		this->current = 0;
	}

	return this->current;
}

Long File::Next() {
	this->current++;

	if (this->current >= this->contentCount) {
		this->current = this->contentCount - 1;
	}

	return this->current;
}

Long File::Last() {
	this->current = this->contentCount - 1;

	return this->current;
}

Long File::Move(Long index) {
	this->current = index;

	return this->current;
}

File& File::operator=(const File& source) {
	this->name = source.name;
	this->magicNumber = source.magicNumber;
	this->contentCount = source.contentCount;
	this->current = source.current;

	return *this;
}

#if 0

#include "ImageFile.h"
#include "LabelFile.h"
#include "Array.h"

int main(int argc, char *argv[]) {
	ImageFile trainImageFile("train-images.idx3-ubyte");
	LabelFile trainLabelFile("train-labels.idx1-ubyte");

	Array<Array<double>> images = trainImageFile.Load();

	for (Long i = 0; i < images.GetLength(); i++) {
		double label = trainLabelFile.GetAt(i);
		cout << label << endl;

		string imagesString("");
		for (int row = 0; row < trainImageFile.GetRowCount(); row++)
		{
			for (int column = 0; column < trainImageFile.GetColumnCount(); column++) {
				if (images[i][row * trainImageFile.GetColumnCount() + column] != 0.0F) {
					imagesString += "*";
				}
				else {
					imagesString += "-";
				}
			}

			imagesString += "\n";
		}

		cout << imagesString << endl;
	}

	for (Long i = trainLabelFile.First(); i < 10; i = trainLabelFile.Next()) {
		double label = trainLabelFile.GetAt(i);
		cout << label << " ";
	}

	for (Long i = 0; i < 10; i++) {
		double label = trainLabelFile.GetAt(i);
		cout << label << " " << endl;

		string imagesString("");
		Array<double> image = trainImageFile.GetAt(i);
		for (int row = 0; row < trainImageFile.GetRowCount(); row++) {
			for (int column = 0; column < trainImageFile.GetColumnCount(); column++) {
				if (image.GetAt(row * trainImageFile.GetColumnCount() + column) != 0.0F) {
					imagesString += "*";
				}
				else {
					imagesString += "-";
				}
			}

			imagesString += "\n";
		}

		cout << imagesString << endl;
	}

	return 0;
}

#endif // 0
