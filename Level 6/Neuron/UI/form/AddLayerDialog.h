#ifndef _ADDLAYERDIALOG_H
#define _ADDLAYERDIALOG_H

#include <afxwin.h>
#include "resource.h"
typedef signed long int Long;
class NeuralNetworkForm;
class AddLayerDialog : public CDialog {
public:
	enum { IDD = IDD_ADDLAYERDIALOG };
public:
	AddLayerDialog(CWnd *parent = NULL);
	virtual BOOL OnInitDialog();
protected:
	afx_msg void OnTypeComboBoxCloseUp();
	afx_msg void OnOKButtonClicked();
	afx_msg void OnCancelButtonClicked();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
private:
	NeuralNetworkForm *neuralNetworkForm;
};

#endif //_ADDLAYERDIALOG_H