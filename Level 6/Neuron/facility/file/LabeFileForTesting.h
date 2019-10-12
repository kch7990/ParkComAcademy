#ifndef _LABELFILEFORTESTING_H
#define _LABELFILEFORTESTING_H

#include "Array.h"
#include <string>
typedef signed long int Long;

using namespace std;
class LabelFileForTesting {
public:
	LabelFileForTesting(string title = "");
	LabelFileForTesting(const LabelFileForTesting& source);
	~LabelFileForTesting();
	Long GetAt(Long index);
	Array<Long> Load();

	string& GetTitle() const;
	Long GetImageCount() const;
private:
	string title;
	Long imageCount;
};

inline string& LabelFileForTesting::GetTitle() const {
	return const_cast<string&>(this->title);
}

inline Long LabelFileForTesting::GetImageCount() const {
	return this->imageCount;
}


#endif // !_LABELFILEFORTESTING_H
