#ifndef _PUTTINGINFORM_H
#define _PUTTINGINFORM_H

#include <afxwin.h>
#include "resource.h"

class PuttingInForm :public CDialog {
public:
	enum { IDD = IDD_PUTTINGINFORM };
public:
	PuttingInForm(CWnd *parent = NULL);
	virtual BOOL OnInitDialog();
protected:
	afx_msg void OnCompanyNameKillFocus();
	afx_msg void OnPutInButtonClicked();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
};

#endif //_PUTTINGINFORM_H