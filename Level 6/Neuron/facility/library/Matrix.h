#ifndef _MATRIX_H
#define _MATRIX_H

#include <assert.h>
#if !defined(_AFXDLL)

#include <crtdbg.h>
#if defined(DEBUG) |defined(_DEBUG)
#if !defined(DEBUG_NEW)
#define DEBUG_NEW new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif
#endif
#endif

typedef signed long int Long;

template<typename T>
class Matrix {
public:
	Matrix(Long row = 16, Long column = 16); //
	Matrix(const Matrix&source); //
	~Matrix(); //
	Long Store(Long rowIndex, Long columnIndex, T object); //
	Long Store(Long index, T object); //
	Long Modify(Long rowIndex, Long columnIndex, T object); //
	Long Modify(Long index, T object); //
	T GetAt(Long rowIndex, Long columnIndex); //
	T GetAt(Long index); //
	Matrix<T>& Plus(const Matrix& other); //
	Matrix<T>& Plus(T object); //
	Matrix<T>& Substract(const Matrix& other); //
	Matrix<T>& Substract(T object); //
	Matrix<T>& Multiply(const Matrix& other); //
	Matrix<T>& Multiply(T object); //
	static Matrix<T> Multiply(const Matrix& one, const Matrix& other); //
	Matrix<T>& Divide(const Matrix& other); //
	Matrix<T>& Divide(T object); //
	Matrix<T> Reverse();
	Matrix<T> AddPadding(Long pad);
	Matrix<T> CutEdge(Long length);

	Matrix<T> operator+(const Matrix& other);//
	Matrix<T> operator+(T object); //
	Matrix<T> operator-(const Matrix& other);//
	Matrix<T> operator-(T object); //
	Matrix<T> operator*(const Matrix& other);//
	Matrix<T> operator*(T object);//
	Matrix<T> operator/(const Matrix& other); //
	Matrix<T> operator/(T object); //
	Matrix<T>& operator=(const Matrix& source); //
	T operator[](Long index); //

	Long GetRow() const; //
	Long GetColumn() const; //

	Long GetCapacity() const; //
	Long GetLength() const; //

private:
	T *(*front);
	Long row;
	Long column;
	Long capacity;
	Long length;
};

template<typename T>
inline Long Matrix<T>::GetRow() const {
	return this->row;
}

template<typename T>
inline Long Matrix<T>::GetColumn() const {
	return this->column;
}

template<typename T>
inline Long Matrix<T>::GetCapacity() const {
	return this->capacity;
}

template<typename T>
inline Long Matrix<T>::GetLength() const {
	return this->length;
}

template<typename T>
Matrix<T>::Matrix(Long row, Long column) {
	this->front = new T*[row];
	Long i = 0;
	while (i < row)
	{
		this->front[i] = new T[column];
		i++;
	}

	this->row = row;
	this->column = column;
	this->capacity = row * column;
	this->length = 0;
}

template<typename T>
Matrix<T>::Matrix(const Matrix&source) {
	this->front = new T*[source.row];

	Long i = 0;
	while (i < source.row)
	{
		this->front[i] = new T[source.column];
		Long j = 0;
		while (j < source.column)
		{
			this->front[i][j] = source.front[i][j];
			j++;
		}
		i++;
	}

	this->row = source.row;
	this->column = source.column;
	this->capacity = source.capacity;
	this->length = source.length;
}

template<typename T>
Matrix<T>::~Matrix() {
	Long i = 0;
	while (i < this->row)
	{
		delete[] this->front[i];
		i++;
	}

	delete[] this->front;
}

template<typename T>
Long Matrix<T>::Store(Long rowIndex, Long columnIndex, T object) {
	this->front[rowIndex][columnIndex] = object;
	Long index = rowIndex * this->column + columnIndex;

	this->length++;

	return index;
}

template<typename T>
Long Matrix<T>::Store(Long index, T object) {
	Long rowIndex = index / this->column;
	Long columnIndex = index % this->column;
	this->front[rowIndex][columnIndex] = object;

	this->length++;

	return index;
}

template<typename T>
Long Matrix<T>::Modify(Long rowIndex, Long columnIndex, T object) {
	this->front[rowIndex][columnIndex] = object;
	Long index = rowIndex * this->column + columnIndex;

	return index;
}

template<typename T>
Long Matrix<T>::Modify(Long index, T object) {
	Long rowIndex = index / this->column;
	Long columnIndex = index % this->column;
	this->front[rowIndex][columnIndex] = object;

	return index;
}

template<typename T>
T Matrix<T>::GetAt(Long rowIndex, Long columnIndex) {
	return this->front[rowIndex][columnIndex];
}

template<typename T>
T Matrix<T>::GetAt(Long index) {
	Long rowIndex = index / this->column;
	Long columnIndex = index % this->column;

	return this->front[rowIndex][columnIndex];
}



template<typename T>
Matrix<T>& Matrix<T>::Plus(const Matrix& other) {
	Long i = 0;
	while (i < this->row) {
		Long j = 0;
		while (j < this->column) {
			this->front[i][j] += other.front[i][j];
			j++;
		}
		i++;
	}
	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::Plus(T object) {
	Long i = 0;
	Long j;
	//1. 오브젝트를 입력받는다.

	while (i < this->row) {//2. row만큼 반복한다.
		j = 0;
		while (j < this->column) {//2.1.column만큼 반복한다.
			this->front[i][j] += object;//2.1.1.수를 더한다.
			//2.1.2.결과를 적는다.
			j++;
		}
		i++;
	}
	//3. 끝내다.
	return *this;
}


template<typename T>
Matrix<T>& Matrix<T>::Substract(const Matrix& other) {
	Long i = 0;
	while (i < this->row) {
		Long j = 0;
		while (j < this->column) {
			this->front[i][j] -= other.front[i][j];
			j++;
		}
		i++;
	}
	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::Substract(T object) {
	Long i = 0;
	Long j;
	//1. 오브젝트를 입력받는다.
	while (i < this->row) {//2. row만큼 반복한다.
		j = 0;
		while (j < this->column) {//2.1.column만큼 반복한다.
			this->front[i][j] -= object;//2.1.1.수를 더한다.
			//2.1.2.결과를 적는다.
			j++;
		}
		i++;
	}
	//3. 끝내다.
	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::Multiply(const Matrix& other) {
	Long i = 0;
	while (i < this->row) {
		Long j = 0;
		while (j < this->column) {
			this->front[i][j] *= other.front[i][j];
			j++;
		}
		i++;
	}
	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::Multiply(T object) {
	Long i = 0;
	Long j;
	//1. 오브젝트를 입력받는다.

	while (i < this->row) {//2. row만큼 반복한다.
		j = 0;
		while (j < this->column) {//2.1.column만큼 반복한다.
			this->front[i][j] *= object;//2.1.1.수를 곱한다.
			//2.1.2.결과를 적는다.
			j++;
		}
		i++;
	}
	//3. 끝내다.
	return *this;
}

template <typename T>
Matrix<T> Matrix<T>::Multiply(const Matrix& one, const Matrix& other) {
	//1. 두개의 행렬을 입력받는다.
	//2. 행렬을 만든다.
	Matrix<T> result(one.GetRow(), other.GetColumn());
	Long i = 0;
	Long j;
	Long k;
	T sum;

	while (i < one.GetRow()) {//3. 첫번째 행렬의 행 수 만큼 반복한다. (i)
		j = 0;
		while (j < other.GetColumn()) {//3.1.두번째 행렬의 열 수 만큼 반복한다. (j)
			k = 0;
			sum = 0;
			while (k < one.GetColumn()) {//3.1.1.첫번째 행렬의 열 수 만큼 반복한다. (k)
			   //3.1.1.1.첫번째 행렬의(i, k) 번째 수를 가져온다.
			   //3.1.1.2.두번째 행렬의(k, j) 번째 수를 가져온다.
			   //3.1.1.3.두 개의 수를 곱한다.
			   //3.1.1.4.합을 구한다.
				sum += one.front[i][k] * other.front[k][j];
				k++;
			}
			//3.1.2.행렬에(i, j) 에 적는다.
			result.Store(i, j, sum);
			j++;
		}
		i++;
	}
	//4. 행렬을 출력한다.
	return result;
}

template <typename T>
Matrix<T>& Matrix<T>::Divide(const Matrix& other) {
	Long i = 0;
	Long j;
	//1. 행렬을 입력받는다.
	//2. row만큼 반복한다.
	while (i < this->row) {
		j = 0;
		while (j < this->column) {//2.1.column만큼 반복한다.
		   //2.1.1.수를 나눈다.
		   //2.1.2.결과를 적는다.
			this->front[i][j] /= other.front[i][j];
			j++;
		}
		i++;
	}
	//3. 끝내다.
	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::Divide(T object) {
	Long i = 0;
	Long j;

	//1. 행렬을 입력받는다.
	//2. row만큼 반복한다.
	while (i < this->row) {
		j = 0;
		while (j < this->column) {//2.1.column만큼 반복한다.
		   //2.1.1.수를 나눈다.
		   //2.1.2.결과를 적는다.
			this->front[i][j] /= object;
			j++;
		}
		i++;
	}
	//3. 끝내다.
	return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix& other) {
	Long i = 0;
	Long j;
	Matrix<T> results(this->row, this->column);

	//1. 행렬을 입력받는다.
	//2. row만큼 반복한다.
	while (i < this->row) {
		j = 0;
		while (j < this->column) {//2.1.column만큼 반복한다.
		   //2.1.1.수를 더하다.
		   //2.1.2.결과를 적는다.
			results.front[i][j] = this->front[i][j] +other.front[i][j];
			results.length++;
			j++;
		}
		i++;
	}
	//3. 끝내다.
	return results;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(T object) {
	Long i = 0;
	Long j;
	Matrix<T> results(this->row, this->column);
	//1. 오브젝트를 입력받는다.

	while (i < this->row) {//2. row만큼 반복한다.
		j = 0;
		while (j < this->column) {//2.1.column만큼 반복한다.
			results.front[i][j] = this->front[i][j] + object;//2.1.1.수를 더한다.
			//2.1.2.결과를 적는다.
			results.length++;
			j++;
		}
		i++;
	}
	//3. 끝내다.
	return results;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix& other) {
	Long i = 0;
	Long j;
	Matrix<T> results(this->row, this->column);
	//1. 행렬을 입력받는다.
	//2. row만큼 반복한다.
	while (i < this->row) {
		j = 0;
		while (j < this->column) {//2.1.column만큼 반복한다.
		   //2.1.1.수를 뺀다.
		   //2.1.2.결과를 적는다.
			results.front[i][j] = this->front[i][j] -other.front[i][j];
			results.length++;
			j++;
		}
		i++;
	}
	//3. 끝내다.
	return results;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(T object) {
	Long i = 0;
	Long j;
	Matrix<T> results(this->row, this->column);
	//1. 오브젝트를 입력받는다.

	while (i < this->row) {//2. row만큼 반복한다.
		j = 0;
		while (j < this->column) {//2.1.column만큼 반복한다.
			results.front[i][j] = this->front[i][j] - object;//2.1.1.수를 뺀다.
			//2.1.2.결과를 적는다.
			results.length++;
			j++;
		}
		i++;
	}
	//3. 끝내다.
	return results;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix& other) {
	Long i = 0;
	Long j;
	Matrix<T> results(this->row, this->column);
	//1. 행렬을 입력받는다.
	//2. row만큼 반복한다.
	while (i < this->row) {
		j = 0;
		while (j < this->column) {//2.1.column만큼 반복한다.
		   //2.1.1.수를 곱한다.
		   //2.1.2.결과를 적는다.
			results.front[i][j] = this->front[i][j] * other.front[i][j];
			results.length++;
			j++;
		}
		i++;
	}
	//3. 끝내다.
	return results;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(T object) {
	Long i = 0;
	Long j;
	Matrix<T> results(this->row, this->column);
	//1. 오브젝트를 입력받는다.

	while (i < this->row) {//2. row만큼 반복한다.
		j = 0;
		while (j < this->column) {//2.1.column만큼 반복한다.
			results.front[i][j] = this->front[i][j] * object;//2.1.1.수를 곱하다.
			results.length++;//2.1.2.결과를 적는다.
			j++;
		}
		i++;
	}
	//3. 끝내다.
	return results;
}

template<typename T>
Matrix<T> Matrix<T>::operator/(const Matrix& other) {
	Long i = 0;
	Long j;
	Matrix<T> results(this->row, this->column);
	//1. 행렬을 입력받는다.
	//2. row만큼 반복한다.
	while (i < this->row) {
		j = 0;
		while (j < this->column) {//2.1.column만큼 반복한다.
		   //2.1.1.수를 나눈다.
		   //2.1.2.결과를 적는다.
			results.front[i][j] = this->front[i][j] / other.front[i][j];
			results.length++;
			j++;
		}
		i++;
	}
	//3. 끝내다.
	return results;
}

template<typename T>
Matrix<T> Matrix<T>::operator/(T object) {
	Long i = 0;
	Long j;
	Matrix<T> results(this->row, this->column);

	//1. 행렬을 입력받는다.
	//2. row만큼 반복한다.
	while (i < this->row) {
		j = 0;
		while (j < this->column) {//2.1.column만큼 반복한다.
		   //2.1.1.수를 나눈다.
		   //2.1.2.결과를 적는다.
			results.front[i][j] = this->front[i][j] / object;
			results.length++;
			j++;
		}
		i++;
	}
	//3. 끝내다.
	return results;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& source) {
	Long i = 0;
	while (i < this->row)
	{
		delete[] this->front[i];
		i++;
	}

	delete[] this->front;

	this->front = new T*[source.row];

	i = 0;
	while (i < source.row)
	{
		this->front[i] = new T[source.column];
		Long j = 0;
		while (j < source.column)
		{
			this->front[i][j] = source.front[i][j];
			j++;
		}
		i++;
	}

	this->row = source.row;
	this->column = source.column;
	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}

template<typename T>
T Matrix<T>::operator[](Long index) {
	Long rowIndex = index / this->column;
	Long columnIndex = index % this->column;

	return this->front[rowIndex][columnIndex];
}

template<typename T>
Matrix<T> Matrix<T>::Reverse() {
	Matrix<T> reversedMatrix(this->row, this->column);

	Long front = 0;
	Long rear = this->length - 1;
	while (front <= rear)
	{
		Long frontRow = front / this->column;
		Long frontColumn = front % this->column;
		Long rearRow = rear / this->column;
		Long rearColumn = rear % this->column;

		reversedMatrix.front[frontRow][frontColumn] = this->front[rearRow][rearColumn];
		reversedMatrix.front[rearRow][rearColumn] = this->front[frontRow][frontColumn];

		front++;
		rear--;
	}
	reversedMatrix.length = this->length;

	return reversedMatrix;
}

template<typename T>
Matrix<T> Matrix<T>::AddPadding(Long pad) {
	Long row = this->row + pad * 2;
	Long column = this->column + pad * 2;

	Matrix<T> paddingMatrix(row, column);
	Long i = 0;
	while (i < row)
	{
		Long j = 0;
		while (j < column)
		{
			if (i >= pad && j >= pad && i < row - pad && j < column - pad)
			{
				paddingMatrix.front[i][j] = this->front[i - pad][j - pad];
			}
			else
			{
				paddingMatrix.front[i][j] = 0;
			}
			paddingMatrix.length++;
			j++;
		}

		i++;
	}

	return paddingMatrix;
}

template<typename T>
Matrix<T> Matrix<T>::CutEdge(Long length) {
	Matrix<T> cuttingMatrix(this->row - length * 2, this->column - length * 2);

	Long i = 0;
	while (i < cuttingMatrix.row)
	{
		Long j = 0;
		while (j < cuttingMatrix.column)
		{
			cuttingMatrix.front[i][j] = this->front[i + length][j + length];
			cuttingMatrix.length++;
			j++;
		}

		i++;
	}

	return cuttingMatrix;
}

#endif //_MATRIX_H
