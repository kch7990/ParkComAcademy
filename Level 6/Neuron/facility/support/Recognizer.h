#ifndef _RECOGNIZER_H
#define _RECOGNIZER_H

#include <afxwin.h>
#include "Array.h"

class RecognizingForm;
class Recognizer {
public:
	Recognizer(RecognizingForm *recognizingForm = NULL);
	Recognizer(const Recognizer& source);
	~Recognizer();
	void Recognize();
	void Recognize(Array<double>& signals);
	void Stop();

	void AutoRecognize();
	Recognizer& operator=(const Recognizer& source);

	BOOL GetIsRecognizing() const;
private:
	static UINT AutoRecognizeThread(LPVOID pParam);
private:
	CWinThread *thread;
	RecognizingForm *recognizingForm;
	BOOL isRecognizing;
};

inline BOOL Recognizer::GetIsRecognizing() const {
	return this->isRecognizing;
}

#endif // !_RECOGNIZER_H
