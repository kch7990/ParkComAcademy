//PuttingInForm.cpp

#include "PuttingInForm.h"
#include "BusinessCardHolderForm.h"
#include "BusinessCardHolder.h"
#include "IndexHolder.h"
#include <afxcmn.h>



BEGIN_MESSAGE_MAP(PuttingInForm, CDialog)
	ON_EN_KILLFOCUS(IDC_EDIT_COMPANY_NAME, OnCompanyNameKillFocus)
	ON_BN_CLICKED(IDC_BUTTON_PUTIN, OnPutInButtonClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

PuttingInForm::PuttingInForm(CWnd* parent)
	:CDialog(PuttingInForm::IDD, parent) {

}

BOOL PuttingInForm::OnInitDialog() {
	CDialog::OnInitDialog();
	((CComboBox*)GetDlgItem(IDC_COMBO_DOMAIN))->AddString((LPCTSTR)"naver.com");
	((CComboBox*)GetDlgItem(IDC_COMBO_DOMAIN))->AddString((LPCTSTR)"daum.net");
	((CComboBox*)GetDlgItem(IDC_COMBO_DOMAIN))->AddString((LPCTSTR)"gmail.com");
	((CComboBox*)GetDlgItem(IDC_COMBO_DOMAIN))->AddString((LPCTSTR)"nate.com");

	((CComboBox*)GetDlgItem(IDC_COMBO_POSITION))->AddString((LPCTSTR)"사원");
	((CComboBox*)GetDlgItem(IDC_COMBO_POSITION))->AddString((LPCTSTR)"주임");
	((CComboBox*)GetDlgItem(IDC_COMBO_POSITION))->AddString((LPCTSTR)"대리");
	((CComboBox*)GetDlgItem(IDC_COMBO_POSITION))->AddString((LPCTSTR)"차장");
	((CComboBox*)GetDlgItem(IDC_COMBO_POSITION))->AddString((LPCTSTR)"부장");
	((CComboBox*)GetDlgItem(IDC_COMBO_POSITION))->AddString((LPCTSTR)"이사");
	((CComboBox*)GetDlgItem(IDC_COMBO_POSITION))->AddString((LPCTSTR)"사장");
	((CComboBox*)GetDlgItem(IDC_COMBO_POSITION))->AddString((LPCTSTR)"회장");

	return FALSE;
}
void PuttingInForm::OnCompanyNameKillFocus() {
	CString companyName;
	GetDlgItem(IDC_EDIT_COMPANY_NAME)->GetWindowText(companyName);
	BusinessCardHolderForm *businessCardHolderForm =
		(BusinessCardHolderForm*)CWnd::FindWindow("#32770", "명함첩");

	Index *indexLink = businessCardHolderForm->indexHolder->Find((LPCTSTR)companyName);
	if (indexLink != NULL) {
		BusinessCard *businessCardLink = indexLink->GetAt(0);
		CString address(businessCardLink->GetAddress().c_str());
		CString companyTelephoneNumber(businessCardLink->GetCompanyTelephoneNumber().c_str());
		CString faxNumber(businessCardLink->GetFaxNumber().c_str());
		CString url(businessCardLink->GetUrl().c_str());
		GetDlgItem(IDC_EDIT_COMPANY_ADDRESS)->SetWindowText(address);
		GetDlgItem(IDC_EDIT_COMPANY_TELEPHONENUMBER)->SetWindowText(companyTelephoneNumber);
		GetDlgItem(IDC_EDIT_COMPANY_FAXNUMBER)->SetWindowText(faxNumber);
		GetDlgItem(IDC_EDIT_COMPANY_URL)->SetWindowText(url);
	}


}
void PuttingInForm::OnPutInButtonClicked() {
	CString companyName;
	CString address;
	CString companyTelephoneNumber;
	CString faxNumber;
	CString url;
	CString personalName;
	CString personalTelephoneNumber;
	CString emailAddress;
	CString position;
	CString emailId;
	CString domain;

	GetDlgItem(IDC_EDIT_COMPANY_NAME)->GetWindowText(companyName);
	GetDlgItem(IDC_EDIT_COMPANY_ADDRESS)->GetWindowText(address);
	GetDlgItem(IDC_EDIT_COMPANY_TELEPHONENUMBER)->GetWindowText(companyTelephoneNumber);
	GetDlgItem(IDC_EDIT_COMPANY_FAXNUMBER)->GetWindowText(faxNumber);
	GetDlgItem(IDC_EDIT_COMPANY_URL)->GetWindowText(url);
	GetDlgItem(IDC_EDIT_PERSONAL_NAME)->GetWindowText(personalName);
	GetDlgItem(IDC_EDIT_PERSONAL_TELEPHONENUMBER)->GetWindowText(personalTelephoneNumber);
	GetDlgItem(IDC_EDIT_PERSONAL_EMAILID)->GetWindowText(emailId);
	GetDlgItem(IDC_COMBO_DOMAIN)->GetWindowText(domain);
	GetDlgItem(IDC_COMBO_POSITION)->GetWindowText(position);
	emailAddress.Format(("%s@%s"), (LPCTSTR)emailId, (LPCTSTR)domain);

	BusinessCard businessCard((LPCTSTR)companyName, (LPCTSTR)address, (LPCTSTR)companyTelephoneNumber,
		(LPCTSTR)faxNumber, (LPCTSTR)url, (LPCTSTR)personalName, (LPCTSTR)personalTelephoneNumber,
		(LPCTSTR)emailAddress, (LPCTSTR)position);

	BusinessCardHolderForm *businessCardHolderForm =
		(BusinessCardHolderForm*)CWnd::FindWindow("#32770", "명함첩");
	BusinessCard *businessCardLink = businessCardHolderForm->businessCardHolder->PutIn(businessCard);
	businessCardHolderForm->Insert(businessCardLink);

	companyName = CString(businessCardLink->GetCompanyName().c_str());
	businessCardHolderForm->GetDlgItem(IDC_STATIC_COMPANY_NAME)->SetWindowText(companyName);

	address = CString(businessCardLink->GetAddress().c_str());
	businessCardHolderForm->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->SetWindowText(address);

	companyTelephoneNumber = CString(businessCardLink->GetCompanyTelephoneNumber().c_str());
	businessCardHolderForm->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->SetWindowText(companyTelephoneNumber);

	faxNumber = CString(businessCardLink->GetFaxNumber().c_str());
	businessCardHolderForm->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->SetWindowText(faxNumber);

	url = CString(businessCardLink->GetUrl().c_str());
	businessCardHolderForm->GetDlgItem(IDC_STATIC_COMPANY_URL)->SetWindowText(url);

	personalName = CString(businessCardLink->GetPersonalName().c_str());
	businessCardHolderForm->GetDlgItem(IDC_STATIC_PERSONAL_NAME)->SetWindowText(personalName);

	personalTelephoneNumber = CString(businessCardLink->GetPersonalTelephoneNumber().c_str());
	businessCardHolderForm->GetDlgItem(IDC_STATIC_PERSONAL_TELEPHONENUMBER)->SetWindowText(personalTelephoneNumber);

	emailAddress = CString(businessCardLink->GetEmailAddress().c_str());
	businessCardHolderForm->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->SetWindowText(emailAddress);

	position = CString(businessCardLink->GetPosition().c_str());
	businessCardHolderForm->GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->SetWindowText(position);

	Index *indexLink = businessCardHolderForm->indexHolder->PutIn(businessCardLink);
	HTREEITEM hCompanies =
		((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))->GetRootItem();

	HTREEITEM hCompany = ((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))->GetChildItem(hCompanies);
	CString companyText;
	if (hCompany != NULL) {
		companyText = ((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))->GetItemText(hCompany);
	}
	companyName = CString(indexLink->GetName().c_str());

	while (hCompany != NULL && companyText.Compare((LPCTSTR)companyName) != 0) {
		hCompany = ((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))->GetNextSiblingItem(hCompany);
		companyText = ((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))->GetItemText(hCompany);
	}

	if (hCompany == NULL) {
		hCompany = ((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))->InsertItem((LPCTSTR)companyName, hCompanies, TVI_LAST);
	}
	personalName = CString(businessCardLink->GetPersonalName().c_str());
	HTREEITEM hName = ((CTreeCtrl*)businessCardHolderForm->
		GetDlgItem(IDC_TREE_INDEX))->InsertItem((LPCTSTR)personalName, hCompany, TVI_LAST);

	((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))->Expand(hCompanies, TVE_EXPAND);
	((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))->Expand(hCompany, TVE_EXPAND);
	((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))->SelectItem(hName);
	((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))->SelectDropTarget(hName);

	EndDialog(0);

}
void PuttingInForm::OnClose() {
	EndDialog(0);
}
