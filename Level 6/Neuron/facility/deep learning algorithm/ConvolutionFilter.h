#ifndef _CONVOLUTIONFILTER_H
#define _CONVOLUTIONFILTER_H

#include "Neuron.h"

#include "Matrix.h"

class ConvolutionFilter : public Neuron {
public:
	ConvolutionFilter();
	ConvolutionFilter(Long size, Matrix<double>& weights, Matrix<double>& weightMomentums, Matrix<double>& weightVelocities);
	ConvolutionFilter(const ConvolutionFilter& source);
	virtual ~ConvolutionFilter();

	Matrix<double> Flow(Matrix<double>& inputs, Long stride);
	Matrix<double> BackFlow(Matrix<double>& inputs, Matrix<double>& gradients, Long stride, Long pad);
	Matrix<double> BatchBackFlow(Matrix<double>& inputs, Matrix<double>& gradients, Long stride, Long pad); //입력 기울기
	void BatchBackFlow(Array<Matrix<double>>& inputs, Array<Matrix<double>>& gradients, Long stride, Long pad); //가중치 기울기
	virtual void Update(double learningRate);
	virtual void Update(double updatedLearningRate, double beta1, double beta2);

	double GetWeight(Long row, Long column) const;
	Long GetSize() const;
	double GetResult(Long row, Long column) const;
	Long GetResultsSize() const;
	double GetWeightGradient(Long row, Long column) const;
	double GetWeightMomentum(Long row, Long column) const;
	double GetWeightVelocity(Long row, Long column) const;

	virtual Neuron* Clone();
	ConvolutionFilter& operator =(const ConvolutionFilter& source);
private:
	Matrix<double> weights;
	Long size;
	Matrix<double> results;
	Long resultsSize;
	Matrix<double> weightGradients;
	Matrix<double> weightMomentums;
	Matrix<double> weightVelocities;
};

inline double ConvolutionFilter::GetWeight(Long row, Long column) const {
	return  const_cast<ConvolutionFilter*>(this)->weights.GetAt(row, column);
}

inline Long ConvolutionFilter::GetSize() const {
	return this->size;
}

inline double ConvolutionFilter::GetResult(Long row, Long column) const {
	return const_cast<ConvolutionFilter*>(this)->results.GetAt(row, column);
}

inline Long ConvolutionFilter::GetResultsSize() const {
	return this->resultsSize;
}

inline double ConvolutionFilter::GetWeightGradient(Long row, Long column) const {
	return const_cast<ConvolutionFilter*>(this)->weightGradients.GetAt(row, column);
}

inline double ConvolutionFilter::GetWeightMomentum(Long row, Long column) const {
	return  const_cast<ConvolutionFilter*>(this)->weightMomentums.GetAt(row, column);
}

inline double ConvolutionFilter::GetWeightVelocity(Long row, Long column) const {
	return  const_cast<ConvolutionFilter*>(this)->weightVelocities.GetAt(row, column);
}

#endif //_CONVOLUTIONFILTER_H