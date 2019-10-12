#ifndef _CONVOLUTION_H
#define _CONVOLUTION_H

#include "Layer.h"

class Convolution : public Layer {
public:
	Convolution(Long capacity = 32, Long pad = 0, Long stride = 1, Long filterSize = 3);
	Convolution(const Convolution& source);
	virtual ~Convolution();
	virtual Array<double> Forward(Array<double>& signals);
	virtual Array<Array<double>> BatchForward(Array<Array<double>>& signals);
	virtual Array<double> Backward(Array<double>& signals);
	virtual Array<Array<double>> BatchBackward(Array<Array<double>>& signals);
	virtual void Update(double learningRate);
	virtual void Update(double updatedLearningRate, double beta1, double beta2);
	virtual Neuron* Clone();
	virtual void MakeFilters(Long channel, Long filterCount, double deviation);
	virtual Long Save(fstream *fs);
	virtual Long Load(fstream *fs);

	virtual string GetType();
	

	Convolution& operator=(const Convolution& source);

	Long GetPad() const;
	Long GetStride() const;
	Long GetFilterSize() const;
	Long GetChannelCount() const;
	double GetDeviation() const;
private:
	Long pad;
	Long stride;
	Long filterSize;
	Long channelCount;
	double deviation;
	
};

inline Long Convolution::GetPad() const {
	return this->pad;
}

inline Long Convolution::GetStride() const {
	return this->stride;
}

inline Long Convolution::GetFilterSize() const {
	return this->filterSize;
}

inline Long Convolution::GetChannelCount() const {
	return this->channelCount;
}

inline double Convolution::GetDeviation() const {
	return this->deviation;
}

#endif // !_CONVOLUTION_H
