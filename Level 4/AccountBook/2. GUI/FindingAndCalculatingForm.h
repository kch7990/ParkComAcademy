#ifndef _FINDINGANDCALCULATINGFORM_H
#define _FINDINGANDCALCULATINGFORM_H

#include <afxwin.h>
#include "resource.h"

typedef signed long int Long;
class FindingAndCalculatingForm : public CDialog
{
public:
	enum { IDD = IDD_FINDINGANDCALCULATINGFORM };
public:
	FindingAndCalculatingForm(CWnd *parent = NULL);
	virtual BOOL OnInitDialog();
protected:
	afx_msg void OnContentCheckBoxClicked();
	afx_msg void OnTermCheckBoxClicked();
	afx_msg void OnFindButtonClicked();
	afx_msg void OnCalculateButtonClicked();
	afx_msg void OnListViewItemDoubleClicked(NMHDR *pNotifyStruct, LRESULT *result);
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
private:
	Long (*indexes);
	Long count;
};

#endif //_FINDINGANDCALCULATINGFORM_H