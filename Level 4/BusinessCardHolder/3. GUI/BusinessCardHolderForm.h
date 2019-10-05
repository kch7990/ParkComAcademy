#ifndef _BUSINESSCARDHOLDERFORM_H
#define _BUSINESSCARDHOLDERFORM_H

#include <afxwin.h>
#include "resource.h"

class BusinessCard;
class BusinessCardHolder;
class IndexHolder;
class BusinessCardHolderForm :public CDialog {
public:
	enum { IDD = IDD_BUSINESSCARDHOLDERFORM };
public:
	BusinessCardHolderForm(CWnd *parent = NULL);
	virtual BOOL OnInitDialog();
public:
	BusinessCardHolder *businessCardHolder;
	IndexHolder *indexHolder;
	void Load();
	void Save();
	void Insert(BusinessCard *index);
	void Delete(BusinessCard *index);
	CString MakePersonalCode();
	CString MakeCompanyCode();
protected:
	afx_msg void OnPutInButtonClicked();
	afx_msg void OnFindButtonClicked();
	afx_msg void OnPutOutButtonClicked();
	afx_msg void OnArrangeButtonClicked();
	afx_msg void OnFirstButtonClicked();
	afx_msg void OnPreviousButtonClicked();
	afx_msg void OnNextButtonClicked();
	afx_msg void OnLastButtonClicked();
	afx_msg void OnTreeViewItemDoubleClicked(NMHDR *nNotifyStruct, LRESULT *result);
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
};

#endif //_BUSINESSCARDHOLDERFORM_H