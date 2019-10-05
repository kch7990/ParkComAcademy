#ifndef _FINDINGFORM_H
#define _FINDINGFORM_H

#include <afxwin.h>
#include "resource.h"

typedef signed long int Long;

class BusinessCard;

class FindingForm : public CDialog
{
public:
	enum { IDD = IDD_FINDINGFORM };

public:
	FindingForm(CWnd *parent = NULL);

protected:
	afx_msg void OnFindButtonClicked();
	afx_msg void OnSelectButtonClicked();
	afx_msg void OnFirstButtonClicked();
	afx_msg void OnPreviousButtonClicked();
	afx_msg void OnNextButtonClicked();
	afx_msg void OnLastButtonClicked();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()

private:
	BusinessCard* (*indexes);
	Long count;
	Long current;
};

#endif // !_BUSINESSCARD_H
