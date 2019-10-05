#ifndef _ACCOUNTBOOKFORM_H
#define _ACCOUNTBOOKFORM_H

#include "Date.h"
#include "resource.h"
#include <afxwin.h>

typedef signed long int Long;
typedef double Currency;
class AccountBook;
class AccountBookForm :public CDialog
{
public:
	enum { IDD = IDD_ACCOUNTBOOKFORM };
public:
	AccountBookForm(CWnd *parent = NULL);
	virtual BOOL OnInitDialog();
public:
	AccountBook *accountBook;
public:
	afx_msg void OnRecordButtonClicked();
	afx_msg void OnCorrectButtonClicked();
	afx_msg void OnFindButtonClicked();
	afx_msg void OnCalculateButtonClicked();
	afx_msg void OnAmountEditKillFocus();
	afx_msg void OnListViewItemDoubleClicked(NMHDR *pNotifyStruct, LRESULT *result);
	afx_msg void OnIncomeRadioButtonClicked();
	afx_msg void OnOutgoRadioButtonClicked();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP();
public:
	void Load();
	void Save();
	void Insert(Long index);
	void Modify(Long index);
	CString MakeCode(const Date& date);
	CString MakeCurrencyFormat(Currency currency);
};
#endif // !_ACCOUNTBOOKFORM_H
