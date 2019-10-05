#include "FindingForm.h"
#include "UpdatingForm.h"
#include "AddressBook.h"
#include <afxcmn.h> //CListCtrl

BEGIN_MESSAGE_MAP(FindingForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PERSONALS, OnListViewItemDoubleClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

FindingForm::FindingForm(CWnd *parent)
	:CDialog(FindingForm::IDD, parent) {
	this->indexes = NULL;
	this->count = 0;
}
BOOL FindingForm::OnInitDialog() {
	CDialog::OnInitDialog();

	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(0, "锅龋", LVCFMT_LEFT, 50);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(1, "己疙", LVCFMT_CENTER, 100);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(2, "林家", LVCFMT_CENTER, 250);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(3, "傈拳锅龋", LVCFMT_CENTER, 150);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(4, "捞皋老林家", LVCFMT_CENTER, 200);

	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	return FALSE;
}
void FindingForm::OnFindButtonClicked() {
	CString name;
	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(name);

	UpdatingForm *updatingForm;
	updatingForm = (UpdatingForm*)CWnd::FindWindow("#32770", "林家废");
	
	if (indexes != NULL) {
		delete[] indexes;
	}
	updatingForm->addressBook->Find((LPCTSTR)name, &this->indexes, &this->count);

	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->DeleteAllItems();

	Personal personal;
	CString number;
	CString address;
	CString telephoneNumber;
	CString emailAddress;
	Long i = 0;
	while (i < this->count) {
		personal = updatingForm->addressBook->GetAt(this->indexes[i]);
		number.Format("%d", i + 1);
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertItem(i, number);
		name = CString(personal.GetName().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(i, 1, name);
		address = CString(personal.GetAddress().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(i, 2, address);
		telephoneNumber = CString(personal.GetTelephoneNumber().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(i, 3, telephoneNumber);
		emailAddress = CString(personal.GetEmailAddress().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(i, 4, emailAddress);
		i++;
	}
}
void FindingForm::OnListViewItemDoubleClicked(NMHDR *pNotifyStruct, LRESULT *result) {
	Long index = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetSelectionMark();

	CString name = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 1);
	CString address = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 2);
	CString telephoneNumber = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 3);
	CString emailAddress = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 4);

	UpdatingForm *updatingForm;
	updatingForm = (UpdatingForm*)CWnd::FindWindow("#32770", "林家废");

	updatingForm->GetDlgItem(IDC_EDIT_NAME)->SetWindowText(name);
	updatingForm->GetDlgItem(IDC_EDIT_ADDRESS)->SetWindowText(address);
	updatingForm->GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->SetWindowText(telephoneNumber);
	updatingForm->GetDlgItem(IDC_EDIT_EMAILADDRESS)->SetWindowText(emailAddress);

	((CListCtrl*)updatingForm->GetDlgItem(IDC_LIST_PERSONALS))->SetSelectionMark(this->indexes[index]);

	if (this->indexes != NULL) {
		delete[] this->indexes;
	}

	EndDialog(0);
}
void FindingForm::OnClose() {
	if (this->indexes != NULL) {
		delete[] this->indexes;
	}

	EndDialog(0);
}