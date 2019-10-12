#include "Sampler.h"
#include <cmath>

Sampler::Sampler(){
	
}

Sampler::Sampler(const Sampler& source)
:rows(source.rows), columns(source.columns){
}

Sampler::~Sampler(){
}

Array<double> Sampler::Forward(Array<double> &image, Array<double> &sampleRows, Array<double> &sampleColumns){
	Array<double> outputs(image.GetLength());
	Long size = sqrt(image.GetLength());
	Long i = 0;
	Long n;
	Long m;
	double sum;
	this->rows = sampleRows;
	this->columns = sampleColumns;

	while (i < image.GetLength()) {
		sum = 0.0;
		n = 0;
		while (n < size) {
			m = 0;
			while (m < size) {
				sum += image.GetAt(n * size + m) * fmax(0.0, 1 - abs(this->columns[i] - m)) * fmax(0.0, 1 - abs(this->rows[i] - n));
				m++;
			}
			n++;
		}
		outputs.Store(i, sum);
		i++;
	}
	return outputs;
}

Array<Array<double>> Sampler::BatchForward(Array<Array<double>> &batchImage, Array<Array<double>> &batchSampleRows, Array<Array<double>> &batchSampleColumns) {
	Array<Array<double>> outputs(batchImage.GetLength());
	Long size = sqrt(batchImage[0].GetLength());
	Long i ;
	Long n;
	Long m;
	double sum;
	this->batchRows = batchSampleRows;
	this->batchColumns = batchSampleColumns;
	Long j = 0;
	while (j < batchImage.GetLength()) {
		Array<double> image(batchImage[j]);
		Array<double> output(batchImage[j].GetLength());
		i = 0;
		while (i < batchImage[0].GetLength()) {
			sum = 0.0;
			n = 0;
			while (n < size) {
				m = 0;
				while (m < size) {
					sum += image.GetAt(n * size + m) * fmax(0.0, 1 - abs(this->batchColumns[j][i] - m)) * fmax(0.0, 1 - abs(this->batchRows[j][i] - n));
					m++;
				}
				n++;
			}
			output.Store(i, sum);
			i++;
		}
		outputs.Store(j, output);
		j++;
	}
	return outputs;
}

void Sampler::Backward(Array<double> &image, Array<double> &backSignals, Array<double> *rowGradients, Array<double> *columnGradients, Array<double> *imageGradients){
	*imageGradients = Array<double>(image.GetLength());
	*rowGradients = Array<double>(this->rows.GetLength());
	*columnGradients = Array<double>(this->columns.GetLength());

	Long n;
	Long m;
	Long conditionValueX;
	Long conditionValueY;
	double rowGradient;
	double columnGradient;
	double imageGradient;
	Long size = sqrt(image.GetLength());

	Long i = 0; 
	while (i < image.GetLength()) {
		imageGradient = 0.0;
		rowGradient = 0.0;
		columnGradient = 0.0;
		n = 0;
		while (n < size) {
			if (abs(n - this->rows[i]) >= 1) {
				conditionValueY = 0;
			}
			else if (n >= this->rows[i]) {
				conditionValueY = 1;
			}
			else {
				conditionValueY = -1;
			}

			m = 0;
			while (m < size) {
				imageGradient += fmax(0.0, 1 - abs(this->columns[i] - m)) * fmax(0.0, 1 - abs(this->rows[i] - n)) * backSignals[i];
				if (abs(m - this->columns[i]) >= 1) {
					conditionValueX = 0;
				}
				else if (m >= this->columns[i]) {
						conditionValueX = 1;
				}
				else {
					conditionValueX = -1;
				}
				columnGradient += image.GetAt(n*size + m) * fmax(0.0, 1 - abs(this->rows[i] - n)) * conditionValueX * backSignals[i];
				rowGradient += image.GetAt(n*size+ m) * fmax(0.0, 1 - abs(this->columns[i] - m)) * conditionValueY *backSignals[i];
				m++;
			}
			n++;
		}
		imageGradients->Store(i, imageGradient);
		columnGradients->Store(i, columnGradient);
		rowGradients->Store(i, rowGradient);
		i++;
	}
}

void Sampler::BatchBackward(Array<Array<double>> &batchImage, Array<Array<double>> &batchBackSignals, Array<Array<double>> *batchRowGradients,
	Array<Array<double>> *batchColumnGradients, Array<Array<double>> *batchImageGradients) {
	*batchImageGradients = Array<Array<double>>(batchBackSignals.GetLength());
	*batchRowGradients = Array<Array<double>>(this->batchRows.GetLength());
	*batchColumnGradients = Array<Array<double>>(this->batchColumns.GetLength());

	Long n;
	Long m;
	Long conditionValueX;
	Long conditionValueY;
	double rowGradient;
	double columnGradient;
	double imageGradient;
	Long size = sqrt(batchBackSignals[0].GetLength());
	Long j = 0;
	while (j < batchBackSignals.GetLength()) {
		Array<double> image(batchImage[j]);
		Array<double> backSignals(batchBackSignals[j]);
		Array<double> imageGradients(batchImage[0].GetLength());
		Array<double> rowGradients(this->batchRows[0].GetLength());
		Array<double> columnGradients(this->batchColumns[0].GetLength());

		Long i = 0;
		while (i < batchBackSignals[0].GetLength()) {
			imageGradient = 0.0;
			rowGradient = 0.0;
			columnGradient = 0.0;
			n = 0;
			while (n < size) {
				if (abs(n - this->batchRows[j][i]) >= 1) {
					conditionValueY = 0;
				}
				else if (n >= this->batchRows[j][i]) {
					conditionValueY = 1;
				}
				else {
					conditionValueY = -1;
				}

				m = 0;
				while (m < size) {
					imageGradient += fmax(0.0, 1 - abs(this->batchColumns[j][i] - m)) * fmax(0.0, 1 - abs(this->batchRows[j][i] - n)) * backSignals[i];
					if (abs(m - this->batchColumns[j][i]) >= 1) {
						conditionValueX = 0;
					}
					else if (m >= this->batchColumns[j][i]) {
						conditionValueX = 1;
					}
					else {
						conditionValueX = -1;
					}
					columnGradient += image.GetAt(n*size + m) * fmax(0.0, 1 - abs(this->batchRows[j][i] - n)) * conditionValueX * backSignals[i];
					rowGradient += image.GetAt(n*size + m) * fmax(0.0, 1 - abs(this->batchColumns[j][i] - m)) * conditionValueY *backSignals[i];
					m++;
				}
				n++;
			}
			imageGradients.Store(i, imageGradient);
			columnGradients.Store(i, columnGradient);
			rowGradients.Store(i, rowGradient);
			i++;
		}
		batchImageGradients->Store(j, imageGradients);
		batchRowGradients->Store(j, rowGradients);
		batchColumnGradients->Store(j, columnGradients);

		j++;
	}

}

Sampler& Sampler::operator=(const Sampler& source){
	this->rows = source.rows;
	this->columns = source.columns;
	return *this;
}
