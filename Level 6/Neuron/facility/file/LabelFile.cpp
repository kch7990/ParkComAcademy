#include "LabelFile.h"
#include <fstream>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
typedef unsigned char UChar;

LabelFile::LabelFile()
	:File() {
}

LabelFile::LabelFile(string name)
	: File(name) {
}

LabelFile::LabelFile(const LabelFile& source)
	: File(source) {
}

LabelFile::~LabelFile() {

}

void LabelFile::ReadHeader() {
	ifstream ifs;
	ifs.open(this->name, ios::binary);

	if (ifs.is_open()) {
		ifs.read(reinterpret_cast<char*>(&this->magicNumber), sizeof(this->magicNumber));
		this->magicNumber = this->ReverseInteger(this->magicNumber);

		ifs.read(reinterpret_cast<char*>(&this->contentCount), sizeof(this->contentCount));
		this->contentCount = this->ReverseInteger(this->contentCount);

		ifs.close();
	}
}

Array<Long> LabelFile::Load() {
	ifstream ifs;
	ifs.open(this->name, ios::in | ios::binary);

	if (!ifs.is_open()) {
		return 0;
	}

	ifs.read(reinterpret_cast<char*>(&this->magicNumber), sizeof(this->magicNumber));
	this->magicNumber = this->ReverseInteger(this->magicNumber);

	ifs.read(reinterpret_cast<char*>(&this->contentCount), sizeof(this->contentCount));
	this->contentCount = this->ReverseInteger(this->contentCount);

	Array<Long> labels(this->contentCount);

	for (Long i = 0; i < contentCount; i++) {
		UChar temp = 0;
		ifs.read(reinterpret_cast<char*>(&temp), sizeof(temp));
		labels.Store(i, static_cast<Long>(temp));
	}

	ifs.close();

	return labels;
}

Long LabelFile::GetAt(Long index) {
	ifstream ifs;
	ifs.open(this->name, ios::in | ios::binary);
	Long label = 0;

	if (ifs.is_open()) {
		ifs.read(reinterpret_cast<char*>(&this->magicNumber), sizeof(this->magicNumber));
		this->magicNumber = this->ReverseInteger(this->magicNumber);

		ifs.read(reinterpret_cast<char*>(&this->contentCount), sizeof(this->contentCount));
		this->contentCount = this->ReverseInteger(this->contentCount);

		ifs.seekg(index, ios_base::cur);

		UChar temp = 0;
		ifs.read(reinterpret_cast<char*>(&temp), sizeof(temp));
		label = static_cast<Long>(temp);

		ifs.close();
	}

	return label;
}

LabelFile& LabelFile::operator=(const LabelFile& source) {
	File::operator=(source);

	return *this;
}
