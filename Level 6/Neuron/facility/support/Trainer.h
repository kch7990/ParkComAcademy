//Trainer.h
#ifndef  _TRAINER_H
#define _TRAINER_H

#include <afxwin.h>

typedef signed long int Long;

class LearningForm;
class Trainer {
public:
	Trainer(LearningForm *learningForm = 0);
	Trainer(const Trainer& source);
	~Trainer();
	void Train(Long batchSize, Long repeatCount, double learningRate);
	void Train(Long batchSize, Long repeatCount, double learningRate, double beta1, double beta2);
	void Pause();
	void Resume();
	void End();
	Trainer& operator=(const Trainer& source);

	Long GetBatchSize() const;
	Long GetRepeatCount() const;
	double GetLearningRate() const;
	double GetBeta1() const;
	double GetBeta2() const;
	BOOL GetIsTraining() const;
	BOOL GetIsPausing() const;

private:
	static UINT TrainForSGDThread(LPVOID pParam);
	static UINT TrainForAdamThread(LPVOID pParam);
private:
	LearningForm *learningForm;
	CWinThread *thread;
	Long batchSize;
	Long repeatCount;
	double learningRate;
	double beta1;
	double beta2;
	BOOL isTraining;
	BOOL isPausing;
};

inline Long Trainer::GetBatchSize() const {
	return this->batchSize;
}

inline Long Trainer::GetRepeatCount() const {
	return this->repeatCount;
}

inline double Trainer::GetLearningRate() const {
	return this->learningRate;
}

inline double Trainer::GetBeta1() const {
	return this->beta1;
}

inline double Trainer::GetBeta2() const {
	return this->beta2;
}

inline BOOL Trainer::GetIsTraining() const {
	return this->isTraining;
}

inline BOOL Trainer::GetIsPausing() const {
	return this->isPausing;
}



#endif // ! _TRAINER_H




