#ifndef _UPDATINGFORM_H
#define _UPDATINGFORM_H
#include <afxwin.h>
#include "resource.h"

typedef signed long int Long;
class AddressBook; // 전방 선언
class UpdatingForm :public CDialog {
public:
	enum { IDD = IDD_UPDATINGFORM };
public:
	UpdatingForm(CWnd *parent = NULL);
	virtual BOOL OnInitDialog();
public:
	AddressBook *addressBook;
protected:
	afx_msg void OnRecordButtonClicked();
	afx_msg void OnFindButtonClicked();
	afx_msg void OnCorrectButtonClicked();
	afx_msg void OnEraseButtonClicked();
	afx_msg void OnArrangeButtonClicked();
	afx_msg void OnListViewItemDoubleClicked(
		NMHDR *pNotifyStruct, LRESULT *result);
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
	void Load();
	void Save();
	void Insert(Long index);
	void Delete(Long index);
	void Modify(Long index);
	CString MakeCode();
};


#endif //_UPDATINGFORM_H
