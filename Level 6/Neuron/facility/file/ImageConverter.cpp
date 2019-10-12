#include "ImageConverter.h"

#include <math.h>

ImageConverter::ImageConverter() {

}

ImageConverter::ImageConverter(const ImageConverter& source) {

}

ImageConverter::~ImageConverter() {

}

Matrix<double> ImageConverter::Rotate(Matrix<double>& image, double degree) {
	double pi = 3.141592;
	double seta = pi / (180.0 / degree);
	Long row;
	Long column;
	Long j;
	Long centerX = image.GetColumn() / 2;
	Long centerY = image.GetRow() / 2;

	Matrix<double> output(image.GetRow(), image.GetColumn());

	Long i = 0;
	while (i < output.GetCapacity()) {
		output.Store(i, 0.0);
		i++;
	}

	i = 0;
	while (i < image.GetRow()) { // y
		j = 0;
		while (j < image.GetColumn()) { // x
			column = (i - centerY)*sin(seta) + (j - centerX)*cos(seta) + centerX;
			row = (i - centerY)*cos(seta) - (j - centerX) * sin(seta) + centerY;
			if (row >= 0 && row < image.GetRow() && column >= 0 && column < image.GetColumn()) {
				output.Modify(row, column, const_cast<Matrix<double>&>(image).GetAt(i, j));
			}
			j++;
		}
		i++;
	}


	return output;
}

Matrix<double> ImageConverter::LeftTop(Matrix<double>& image) {
	Long topSpace = image.GetRow();
	Long leftSpace = image.GetColumn();
	Long i = 0;
	Long j;
	Long row;
	Long column;
	double value;

	// 이미지 안에있는 숫자의 좌측 점과 상단 점을 찾는다.
	while (i < image.GetRow()) {
		j = 0;
		while (j < image.GetColumn()) {
			value = image.GetAt(i, j);
			if (value > 0 && i < topSpace) {
				topSpace = i;
			}
			if (value > 0 && j < leftSpace) {
				leftSpace = j;
			}
			j++;
		}
		i++;
	}

	Matrix<double> result(image.GetRow(), image.GetColumn());
	// 좌측 점 위치 크기만큼 좌측으로 이동 상단 점 크기만큼 상단으로 이동하여 복사한다.
	i = 0;
	while (i < result.GetRow()) {
		j = 0;
		while (j < result.GetColumn()) {
			row = i + topSpace;
			column = j + leftSpace;
			value = 0.0;
			if (row < image.GetRow() && column < image.GetColumn()) {
				value = image.GetAt(row, column);
			}
			result.Store(i, j, value);
			j++;
		}
		i++;
	}

	return result;
}

Matrix<double> ImageConverter::LeftBottom(Matrix<double>& image) {
	Long bottomSpace = 0;
	Long leftSpace = image.GetColumn();
	Long i = 0;
	Long j;
	Long row;
	Long column;
	double value;

	// 이미지 안에있는 숫자의 좌측 점과 상단 점을 찾는다.
	while (i < image.GetRow()) {
		j = 0;
		while (j < image.GetColumn()) {
			value = image.GetAt(i, j);
			if (value > 0 && i > bottomSpace) {
				bottomSpace = i;
			}
			if (value > 0 && j < leftSpace) {
				leftSpace = j;
			}
			j++;
		}
		i++;
	}
	bottomSpace = (image.GetRow() - 1) - bottomSpace;

	Matrix<double> result(image.GetRow(), image.GetColumn());
	// 좌측 점 위치 크기만큼 좌측으로 이동 하단 점 크기만큼 하단으로 이동하여 복사한다.
	i = 0;
	while (i < result.GetRow()) {
		j = 0;
		while (j < result.GetColumn()) {
			row = i - bottomSpace;
			column = j + leftSpace;
			value = 0.0;
			if (row >= 0 && column < image.GetColumn()) {
				value = image.GetAt(row, column);
			}
			result.Store(i, j, value);
			j++;
		}
		i++;
	}
	return result;
}
Matrix<double> ImageConverter::Left(Matrix<double>& image) {
	Long leftSpace = image.GetColumn();
	Long i = 0;
	Long j;
	Long row;
	Long column;
	double value;

	// 이미지 안에있는 숫자의 좌측 점을 찾는다.
	while (i < image.GetRow()) {
		j = 0;
		while (j < image.GetColumn()) {
			value = image.GetAt(i, j);
			if (value > 0 && j < leftSpace) {
				leftSpace = j;
			}
			j++;
		}
		i++;
	}
	Matrix<double> result(image.GetRow(), image.GetColumn());
	// 좌측 점 위치 크기만큼 좌측으로 이동 상단 점 크기만큼 상단으로 이동하여 복사한다.
	i = 0;
	while (i < result.GetRow()) {
		j = 0;
		while (j < result.GetColumn()) {
			row = i;
			column = j + leftSpace;
			value = 0.0;
			if (column < image.GetColumn()) {
				value = image.GetAt(row, column);
			}
			result.Store(i, j, value);
			j++;
		}
		i++;
	}


	return result;
}

Matrix<double> ImageConverter::Top(Matrix<double>& image) {
	Long topSpace = image.GetRow();
	Long i = 0;
	Long j;
	Long row;
	Long column;
	double value;

	// 이미지 안에있는 숫자의 좌측 점과 상단 점을 찾는다.
	while (i < image.GetRow()) {
		j = 0;
		while (j < image.GetColumn()) {
			value = image.GetAt(i, j);

			if (value > 0 && i < topSpace) {
				topSpace = i;
			}
			j++;
		}
		i++;
	}

	Matrix<double> result(image.GetRow(), image.GetColumn());
	// 좌측 점 위치 크기만큼 좌측으로 이동 상단 점 크기만큼 상단으로 이동하여 복사한다.
	i = 0;
	while (i < result.GetRow()) {
		j = 0;
		while (j < result.GetColumn()) {
			row = i + topSpace;
			column = j;
			value = 0.0;
			if (row < image.GetRow()) {
				value = image.GetAt(row, column);
			}
			result.Store(i, j, value);
			j++;
		}
		i++;
	}

	return result;
}

Matrix<double> ImageConverter::Bottom(Matrix<double>& image) {
	Long bottomSpace = 0;
	Long i = 0;
	Long j;
	Long row;
	Long column;
	double value;

	// 이미지 안에있는 숫자의 좌측 점과 상단 점을 찾는다.
	while (i < image.GetRow()) {
		j = 0;
		while (j < image.GetColumn()) {
			value = image.GetAt(i, j);
			if (value > 0 && i > bottomSpace) {
				bottomSpace = i;
			}
			j++;
		}
		i++;
	}
	bottomSpace = (image.GetRow() - 1) - bottomSpace;

	Matrix<double> result(image.GetRow(), image.GetColumn());
	// 좌측 점 위치 크기만큼 좌측으로 이동 하단 점 크기만큼 하단으로 이동하여 복사한다.
	i = 0;
	while (i < result.GetRow()) {
		j = 0;
		while (j < result.GetColumn()) {
			row = i - bottomSpace;
			column = j;
			value = 0.0;
			if (row >= 0) {
				value = image.GetAt(row, column);
			}
			result.Store(i, j, value);
			j++;
		}
		i++;
	}
	return result;
}

Matrix<double> ImageConverter::Right(Matrix<double>& image) {
	Long rightSpace = 0;
	Long i = 0;
	Long j;
	Long row;
	Long column;
	double value;

	// 이미지 안에있는 숫자의 좌측 점과 상단 점을 찾는다.
	while (i < image.GetRow()) {
		j = 0;
		while (j < image.GetColumn()) {
			value = image.GetAt(i, j);
			if (value > 0 && j > rightSpace) {
				rightSpace = j;
			}
			j++;
		}
		i++;
	}
	rightSpace = (image.GetColumn() - 1) - rightSpace;

	Matrix<double> result(image.GetRow(), image.GetColumn());
	// 좌측 점 위치 크기만큼 좌측으로 이동 하단 점 크기만큼 하단으로 이동하여 복사한다.
	i = 0;
	while (i < result.GetRow()) {
		j = 0;
		while (j < result.GetColumn()) {
			row = i;
			column = j - rightSpace;
			value = 0.0;
			if (column >= 0) {
				value = image.GetAt(row, column);
			}
			result.Store(i, j, value);
			j++;
		}
		i++;
	}
	return result;
}


Matrix<double> ImageConverter::RightTop(Matrix<double>& image) {
	Long topSpace = image.GetRow();
	Long rightSpace = 0;
	Long i = 0;
	Long j;
	Long row;
	Long column;
	double value;

	// 이미지 안에있는 숫자의 좌측 점과 상단 점을 찾는다.
	while (i < image.GetRow()) {
		j = 0;
		while (j < image.GetColumn()) {
			value = image.GetAt(i, j);
			if (value > 0 && i < topSpace) {
				topSpace = i;
			}
			if (value > 0 && j > rightSpace) {
				rightSpace = j;
			}
			j++;
		}
		i++;
	}
	rightSpace = (image.GetColumn() - 1) - rightSpace;

	Matrix<double> result(image.GetRow(), image.GetColumn());
	// 좌측 점 위치 크기만큼 좌측으로 이동 하단 점 크기만큼 하단으로 이동하여 복사한다.
	i = 0;
	while (i < result.GetRow()) {
		j = 0;
		while (j < result.GetColumn()) {
			row = i + topSpace;
			column = j - rightSpace;
			value = 0.0;
			if (row < image.GetRow() && column >= 0) {
				value = image.GetAt(row, column);
			}
			result.Store(i, j, value);
			j++;
		}
		i++;
	}
	return result;
}


Matrix<double> ImageConverter::RightBottom(Matrix<double>& image) {
	Long bottomSpace = 0;
	Long rightSpace = 0;
	Long i = 0;
	Long j;
	Long row;
	Long column;
	double value;

	// 이미지 안에있는 숫자의 좌측 점과 상단 점을 찾는다.
	while (i < image.GetRow()) {
		j = 0;
		while (j < image.GetColumn()) {
			value = image.GetAt(i, j);
			if (value > 0 && i > bottomSpace) {
				bottomSpace = i;
			}
			if (value > 0 && j > rightSpace) {
				rightSpace = j;
			}
			j++;
		}
		i++;
	}
	bottomSpace = (image.GetRow() - 1) - bottomSpace;
	rightSpace = (image.GetColumn() - 1) - rightSpace;

	Matrix<double> result(image.GetRow(), image.GetColumn());
	// 좌측 점 위치 크기만큼 좌측으로 이동 하단 점 크기만큼 하단으로 이동하여 복사한다.
	i = 0;
	while (i < result.GetRow()) {
		j = 0;
		while (j < result.GetColumn()) {
			row = i - bottomSpace;
			column = j - rightSpace;
			value = 0.0;
			if (row >= 0 && column >= 0) {
				value = image.GetAt(row, column);
			}
			result.Store(i, j, value);
			j++;
		}
		i++;
	}
	return result;
}

Matrix<double> ImageConverter::Reduce(Matrix<double>& source, double multiple) {
	Long k = 0;
	Matrix<double> image(source.GetRow() * multiple, source.GetColumn() * multiple);
	for (Long row = 0; row < image.GetRow(); row++)
	{
		Long originY = row / (image.GetRow() / (source.GetRow() * 1.0));
		for (Long column = 0; column < image.GetColumn(); column++)
		{
			Long originX = column / (image.GetColumn() / (source.GetColumn() * 1.0));
			image.Store(row, column, source.GetAt(originY, originX));
		}
	}

	Matrix<double> output(source.GetRow(), source.GetColumn());
	for (Long i = 0; i < output.GetRow(); i++)
	{
		for (Long j = 0; j < output.GetColumn(); j++)
		{
			output.Store(i, j, 0);
		}
	}

	Long center = (source.GetRow() - image.GetRow()) / 2;
	for (Long row = 0; row < image.GetRow(); row++)
	{
		for (Long column = 0; column < image.GetColumn(); column++)
		{
			output.Modify(row + center, column + center, image.GetAt(row, column));
		}
	}

	return output;
}

ImageConverter& ImageConverter::operator=(const ImageConverter& source) {
	return *this;
}