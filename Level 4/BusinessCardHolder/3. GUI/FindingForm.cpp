#include "FindingForm.h"
#include "BusinessCardHolderForm.h"
#include "BusinessCardHolder.h"
#include "IndexHolder.h"
#include <afxcmn.h> //CTreeCtrl

BEGIN_MESSAGE_MAP(FindingForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_SELECT, OnSelectButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_FIRST, OnFirstButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_PREVIOUS, OnPreviousButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnNextButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_LAST, OnLastButtonClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

FindingForm::FindingForm(CWnd *parent)
	:CDialog(FindingForm::IDD, parent)
{
	this->indexes = NULL;
	this->count = 0;
	this->current = -1;
}

void FindingForm::OnFindButtonClicked()
{
	CString name;

	GetDlgItem(IDC_EDIT_NAME)->GetWindowTextA(name);
	BusinessCardHolderForm *businessCardHolderForm = (BusinessCardHolderForm*)CWnd::FindWindowA("#32770", "¸íÇÔÃ¸");

	if (this->indexes != NULL)
	{
		delete[] this->indexes;
	}

	businessCardHolderForm->businessCardHolder->Find((LPCTSTR)name, &this->indexes, &this->count);

	if (this->count > 0)
	{
		this->current = 0;

		CString companyName(this->indexes[this->current]->GetCompanyName().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_NAME)->SetWindowTextA(companyName);

		CString address(this->indexes[this->current]->GetAddress().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->SetWindowTextA(address);

		CString companyTelephoneNumber(this->indexes[this->current]->GetCompanyTelephoneNumber().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->SetWindowTextA(companyTelephoneNumber);

		CString faxNumber(this->indexes[this->current]->GetFaxNumber().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->SetWindowTextA(faxNumber);

		CString url(this->indexes[this->current]->GetUrl().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_URL)->SetWindowTextA(url);

		CString personalName(this->indexes[this->current]->GetPersonalName().c_str());
		GetDlgItem(IDC_STATIC_PERSONAL_NAME)->SetWindowTextA(personalName);

		CString personalTelephoneNumber(this->indexes[this->current]->GetPersonalTelephoneNumber().c_str());
		GetDlgItem(IDC_STATIC_PERSONAL_TELEPHONENUMBER)->SetWindowTextA(personalTelephoneNumber);

		CString emailAddress(this->indexes[this->current]->GetEmailAddress().c_str());
		GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->SetWindowTextA(emailAddress);

		CString position(this->indexes[this->current]->GetPosition().c_str());
		GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->SetWindowTextA(position);
	}
	else
	{
		GetDlgItem(IDC_STATIC_COMPANY_NAME)->SetWindowTextA("");
		GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->SetWindowTextA("");
		GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->SetWindowTextA("");
		GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->SetWindowTextA("");
		GetDlgItem(IDC_STATIC_COMPANY_URL)->SetWindowTextA("");

		GetDlgItem(IDC_STATIC_PERSONAL_NAME)->SetWindowTextA("");
		GetDlgItem(IDC_STATIC_PERSONAL_TELEPHONENUMBER)->SetWindowTextA("");
		GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->SetWindowTextA("");
		GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->SetWindowTextA("");
	}
}

void FindingForm::OnSelectButtonClicked()
{
	BusinessCardHolderForm *businessCardHolderForm = (BusinessCardHolderForm*)CWnd::FindWindowA("#32770", "¸íÇÔÃ¸");

	BusinessCard *businessCardLink = businessCardHolderForm->businessCardHolder->Move(this->indexes[this->current]);

	CString companyName(businessCardLink->GetCompanyName().c_str());
	businessCardHolderForm->GetDlgItem(IDC_STATIC_COMPANY_NAME)->SetWindowTextA(companyName);

	CString address(businessCardLink->GetAddress().c_str());
	businessCardHolderForm->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->SetWindowTextA(address);

	CString companyTelephoneNumber(businessCardLink->GetCompanyTelephoneNumber().c_str());
	businessCardHolderForm->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->SetWindowTextA(companyTelephoneNumber);

	CString faxNumber(businessCardLink->GetFaxNumber().c_str());
	businessCardHolderForm->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->SetWindowTextA(faxNumber);

	CString url(businessCardLink->GetUrl().c_str());
	businessCardHolderForm->GetDlgItem(IDC_STATIC_COMPANY_URL)->SetWindowTextA(url);

	CString personalName(businessCardLink->GetPersonalName().c_str());
	businessCardHolderForm->GetDlgItem(IDC_STATIC_PERSONAL_NAME)->SetWindowTextA(personalName);

	CString personalTelephoneNumber(businessCardLink->GetPersonalTelephoneNumber().c_str());
	businessCardHolderForm->GetDlgItem(IDC_STATIC_PERSONAL_TELEPHONENUMBER)->SetWindowTextA(personalTelephoneNumber);

	CString emailAddress(businessCardLink->GetEmailAddress().c_str());
	businessCardHolderForm->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->SetWindowTextA(emailAddress);

	CString position(businessCardLink->GetPosition().c_str());
	businessCardHolderForm->GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->SetWindowTextA(position);

	Index *indexLink = businessCardHolderForm->indexHolder->Find((LPCTSTR)companyName);

	Long location = indexLink->Find(businessCardLink);

	HTREEITEM hCompanies = ((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))->GetRootItem();

	companyName = CString(indexLink->GetName().c_str());

	HTREEITEM hCompany = ((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))->GetChildItem(hCompanies);
	CString companyText = ((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))->GetItemText(hCompany);
	while (hCompany != NULL && companyText.Compare((LPCTSTR)companyName) != 0) {
		hCompany = ((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))->GetNextSiblingItem(hCompany);
		companyText = ((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))->GetItemText(hCompany);
	}

	HTREEITEM hName = ((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))->GetChildItem(hCompany);
	Long i = 0;
	while (i < location) {
		hName = ((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))->GetNextSiblingItem(hName);
		i++;
	}

	((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))->Expand(hCompanies, TVE_EXPAND);
	((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))->Expand(hCompany, TVE_EXPAND);
	((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))->SelectItem(hName);
	((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))->SelectDropTarget(hName);


	if (this->indexes != NULL)
	{
		delete[] this->indexes;
	}

	EndDialog(0);
}

void FindingForm::OnFirstButtonClicked()
{
	this->current = 0;

	CString companyName(indexes[this->current]->GetCompanyName().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_NAME)->SetWindowText(companyName);

	CString address(indexes[this->current]->GetAddress().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->SetWindowText(address);

	CString companyTelephoneNumber(indexes[this->current]->GetCompanyTelephoneNumber().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->SetWindowText(companyTelephoneNumber);

	CString faxNumber(indexes[this->current]->GetFaxNumber().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->SetWindowText(faxNumber);

	CString url(indexes[this->current]->GetUrl().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_URL)->SetWindowText(url);

	CString personalName(indexes[this->current]->GetPersonalName().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_NAME)->SetWindowText(personalName);

	CString personalTelephoneNumber(indexes[this->current]->GetPersonalTelephoneNumber().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_TELEPHONENUMBER)->SetWindowText(personalTelephoneNumber);

	CString emailAddress(indexes[this->current]->GetEmailAddress().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->SetWindowText(emailAddress);

	CString position(indexes[this->current]->GetPosition().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->SetWindowText(position);
}

void FindingForm::OnPreviousButtonClicked()
{
	this->current--;

	if (this->current < 0)
	{
		this->current = 0;
	}

	CString companyName(indexes[this->current]->GetCompanyName().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_NAME)->SetWindowText(companyName);

	CString address(indexes[this->current]->GetAddress().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->SetWindowText(address);

	CString companyTelephoneNumber(indexes[this->current]->GetCompanyTelephoneNumber().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->SetWindowText(companyTelephoneNumber);

	CString faxNumber(indexes[this->current]->GetFaxNumber().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->SetWindowText(faxNumber);

	CString url(indexes[this->current]->GetUrl().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_URL)->SetWindowText(url);

	CString personalName(indexes[this->current]->GetPersonalName().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_NAME)->SetWindowText(personalName);

	CString personalTelephoneNumber(indexes[this->current]->GetPersonalTelephoneNumber().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_TELEPHONENUMBER)->SetWindowText(personalTelephoneNumber);

	CString emailAddress(indexes[this->current]->GetEmailAddress().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->SetWindowText(emailAddress);

	CString position(indexes[this->current]->GetPosition().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->SetWindowText(position);
}

void FindingForm::OnNextButtonClicked()
{
	this->current++;

	if (this->current >= this->count)
	{
		this->current = this->count - 1;
	}

	CString companyName(indexes[this->current]->GetCompanyName().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_NAME)->SetWindowText(companyName);

	CString address(indexes[this->current]->GetAddress().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->SetWindowText(address);

	CString companyTelephoneNumber(indexes[this->current]->GetCompanyTelephoneNumber().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->SetWindowText(companyTelephoneNumber);

	CString faxNumber(indexes[this->current]->GetFaxNumber().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->SetWindowText(faxNumber);

	CString url(indexes[this->current]->GetUrl().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_URL)->SetWindowText(url);

	CString personalName(indexes[this->current]->GetPersonalName().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_NAME)->SetWindowText(personalName);

	CString personalTelephoneNumber(indexes[this->current]->GetPersonalTelephoneNumber().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_TELEPHONENUMBER)->SetWindowText(personalTelephoneNumber);

	CString emailAddress(indexes[this->current]->GetEmailAddress().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->SetWindowText(emailAddress);

	CString position(indexes[this->current]->GetPosition().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->SetWindowText(position);
}

void FindingForm::OnLastButtonClicked()
{
	this->current = this->count - 1;

	CString companyName(indexes[this->current]->GetCompanyName().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_NAME)->SetWindowText(companyName);

	CString address(indexes[this->current]->GetAddress().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->SetWindowText(address);

	CString companyTelephoneNumber(indexes[this->current]->GetCompanyTelephoneNumber().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->SetWindowText(companyTelephoneNumber);

	CString faxNumber(indexes[this->current]->GetFaxNumber().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->SetWindowText(faxNumber);

	CString url(indexes[this->current]->GetUrl().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_URL)->SetWindowText(url);

	CString personalName(indexes[this->current]->GetPersonalName().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_NAME)->SetWindowText(personalName);

	CString personalTelephoneNumber(indexes[this->current]->GetPersonalTelephoneNumber().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_TELEPHONENUMBER)->SetWindowText(personalTelephoneNumber);

	CString emailAddress(indexes[this->current]->GetEmailAddress().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->SetWindowText(emailAddress);

	CString position(indexes[this->current]->GetPosition().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->SetWindowText(position);
}

void FindingForm::OnClose()
{
	if (this->indexes != NULL)
	{
		delete[] this->indexes;
	}

	EndDialog(0);
}

