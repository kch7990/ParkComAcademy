#ifndef _LEARNINGDIALOG_H
#define _LEARNINGDIALOG_H

#include "Array.h"
#include "resource.h"
#include <afxwin.h>

class NeuronForm;
class LearningDialog : public CDialog {
public:
	enum { IDD = IDD_LEARNDIALOG};
public:
	LearningDialog(CWnd *parent = NULL);
	virtual BOOL OnInitDialog();
protected:
	afx_msg void OnOKButtonClicked();
	afx_msg void OnCancelButtonClicked();
	afx_msg void OnSGDRadioButtonClicked();
	afx_msg void OnAdamRadioButtonClicked();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
private:
	NeuronForm *neuronForm;

};

#endif  //_LEARNINGDIALOG_H