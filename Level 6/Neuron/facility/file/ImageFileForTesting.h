#ifndef _IMAGEFILEFORTESTING_H


#include "Array.h"
#include <string>
typedef signed long int Long;

using namespace std;

class ImageFileForTesting {
public:
	ImageFileForTesting(string title = "");
	ImageFileForTesting(const ImageFileForTesting& source);
	~ImageFileForTesting();
	Array<double> GetAt(Long index);
	Array<Array<double>> Load();

	string& GetTitle() const;
	Long GetImageCount() const;

private:
	string title;
	Long imageCount;
};

inline string& ImageFileForTesting::GetTitle() const {
	return const_cast<string&>(this->title);
}

inline Long ImageFileForTesting::GetImageCount() const {
	return this->imageCount;
}



#endif // !_IMAGEFILEFORTESTING_H
