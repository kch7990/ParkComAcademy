#include "LabeFileForTesting.h"
#include <fstream>

LabelFileForTesting::LabelFileForTesting(string title)
:title(title){
	fstream fs;

	fs.open(this->title.c_str(), ios_base::in);
	if (fs.is_open()) {
		fs >> this->imageCount;
		fs.close();
	}
}

LabelFileForTesting::LabelFileForTesting(const LabelFileForTesting& source)
:title(source.title){
	this->imageCount = source.imageCount;
}

LabelFileForTesting::~LabelFileForTesting(){
}

Long LabelFileForTesting::GetAt(Long index){
	fstream fs;
	Long label;
	Long count;

	fs.open(this->title.c_str(), ios_base::in);
	if (fs.is_open()) {
		fs >> count;
		Long i = 1;
		Long repeatCount = index;
		while (i <= repeatCount){
			fs >> label;
			i++;
		}

		fs >> label;

		fs.close();
	}

	return label;
}

Array<Long> LabelFileForTesting::Load() {
	
	fstream fs;
	fs.open(this->title.c_str(), ios_base::in);
	Long count;
	fs >> count;
	Long label;

	Array<Long> results(count);

	Long i = 0;
	while (i < count) {
		fs >> label;
		results.Store(i, label);
		i++;
	}

	return results;
}