#include "ImageFileForTesting.h"
#include <fstream>

ImageFileForTesting::ImageFileForTesting(string title )
:title(title){
	fstream fs;
	fs.open(this->title.c_str(), ios_base::in);
	if (fs.is_open()) {
		fs >> this->imageCount;
		fs.close();
	}
}


ImageFileForTesting::ImageFileForTesting(const ImageFileForTesting& source){
	this->title = source.title;
	this->imageCount = source.imageCount;
}

ImageFileForTesting::~ImageFileForTesting(){
}

Array<double> ImageFileForTesting::GetAt(Long index){
	Array<double> result(784);
	fstream fs;

	fs.open(this->title.c_str(), ios_base::in);
	double value;

	if (fs.is_open()) {
		string temp;
		getline(fs, temp);

		Long repeatCount = 29 * index;
		Long i = 1;
		while (i <= repeatCount) {
			getline(fs, temp);
			i++;
		}

		i = 0;
		while (i < 784) {
			fs >> value;
			result.Store(i, value);
			i++;
		}

		fs.close();
	}
	return result;
}

Array<Array<double>> ImageFileForTesting::Load() {
	fstream fs;

	fs.open(this->title.c_str(), ios_base::in);
	Long count;
	fs >> count;
	Array<Array<double>> results(count);

	double value;
	Long i = 0;
	while (i < count) {
		Array<double> temp(784);
		Long j = 0;
		while (j < 784) {
			fs >> value;
			temp.Store(j, value);
			j++;
		}
		results.Store(i, temp);
		i++;
	}

	return results;
}