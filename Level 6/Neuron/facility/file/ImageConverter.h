#ifndef _IMAGECONVERTER_H
#define _IMAGECONVERTER_H

#include "Matrix.h"

class ImageConverter {
public:
	ImageConverter();
	ImageConverter(const ImageConverter& source);
	~ImageConverter();
	Matrix<double> Rotate(Matrix<double>& image, double degree);
	Matrix<double> LeftTop(Matrix<double>& image);
	Matrix<double> LeftBottom(Matrix<double>& image);
	Matrix<double> Left(Matrix<double>& image);
	Matrix<double> Top(Matrix<double>& image);
	Matrix<double> Bottom(Matrix<double>& image);
	Matrix<double> Right(Matrix<double>& image);
	Matrix<double> RightTop(Matrix<double>& image);
	Matrix<double> RightBottom(Matrix<double>& image);
	Matrix<double> Reduce(Matrix<double>& source, double multiple);

	ImageConverter& operator=(const ImageConverter& source);

};

#endif