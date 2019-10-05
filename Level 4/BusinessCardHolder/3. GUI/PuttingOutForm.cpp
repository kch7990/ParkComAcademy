#include "PuttingOutForm.h"
#include "BusinessCardHolderForm.h"
#include "BusinessCardHolder.h"
#include "IndexHolder.h"
#include <afxcmn.h>


BEGIN_MESSAGE_MAP(PuttingOutForm, CDialog)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

PuttingOutForm::PuttingOutForm(CWnd *parent)
	:CDialog(PuttingOutForm::IDD, parent)
{

}

BOOL PuttingOutForm::OnInitDialog()
{
	CDialog::OnInitDialog();

	BusinessCardHolderForm *businessCardHolderForm = (BusinessCardHolderForm*)CWnd::FindWindowA("#32770", "¸íÇÔÃ¸");

	BusinessCard *current = businessCardHolderForm->businessCardHolder->GetCurrent();
	BusinessCard businessCard = businessCardHolderForm->businessCardHolder->PutOut(current);
	businessCardHolderForm->Delete(&businessCard);

	CString companyName(businessCard.GetCompanyName().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_NAME)->SetWindowTextA(companyName);

	CString address(businessCard.GetAddress().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->SetWindowTextA(address);

	CString companyTelephoneNumber(businessCard.GetCompanyTelephoneNumber().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->SetWindowTextA(companyTelephoneNumber);

	CString faxNumber(businessCard.GetFaxNumber().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->SetWindowTextA(faxNumber);

	CString url(businessCard.GetUrl().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_URL)->SetWindowTextA(url);

	CString personalName(businessCard.GetPersonalName().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_NAME)->SetWindowTextA(personalName);

	CString personalTelephoneNumber(businessCard.GetPersonalTelephoneNumber().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_TELEPHONENUMBER)->SetWindowTextA(personalTelephoneNumber);

	CString emailAddress(businessCard.GetEmailAddress().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->SetWindowTextA(emailAddress);

	CString position(businessCard.GetPosition().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->SetWindowTextA(position);

	companyName = CString(businessCard.GetCompanyName().c_str());
	Index *indexLink = businessCardHolderForm->indexHolder->PutOut((LPCTSTR)companyName, current);
	HTREEITEM hName = ((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))
		->GetSelectedItem();
	HTREEITEM hCompany;
	if (indexLink == 0) {
		hCompany = ((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))
			->GetParentItem(hName);
		((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))
			->DeleteItem(hCompany);
	}
	else {
		((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))
			->DeleteItem(hName);
	}

	if (businessCardHolderForm->businessCardHolder->GetLength() > 0)
	{
		current = businessCardHolderForm->businessCardHolder->GetCurrent();
		companyName = CString(current->GetCompanyName().c_str());
		businessCardHolderForm->GetDlgItem(IDC_STATIC_COMPANY_NAME)->SetWindowText(companyName);

		address = CString(current->GetAddress().c_str());
		businessCardHolderForm->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->SetWindowText(address);

		companyTelephoneNumber = CString(current->GetCompanyTelephoneNumber().c_str());
		businessCardHolderForm->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->SetWindowText(companyTelephoneNumber);

		faxNumber = CString(current->GetFaxNumber().c_str());
		businessCardHolderForm->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->SetWindowText(faxNumber);

		url = CString(current->GetUrl().c_str());
		businessCardHolderForm->GetDlgItem(IDC_STATIC_COMPANY_URL)->SetWindowText(url);

		personalName = (current->GetPersonalName().c_str());
		businessCardHolderForm->GetDlgItem(IDC_STATIC_PERSONAL_NAME)->SetWindowText(personalName);

		personalTelephoneNumber = (current->GetPersonalTelephoneNumber().c_str());
		businessCardHolderForm->GetDlgItem(IDC_STATIC_PERSONAL_TELEPHONENUMBER)->SetWindowText(personalTelephoneNumber);

		emailAddress = (current->GetEmailAddress().c_str());
		businessCardHolderForm->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->SetWindowText(emailAddress);

		position = CString(current->GetPosition().c_str());
		businessCardHolderForm->GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->SetWindowText(position);

		companyName = CString(current->GetCompanyName().c_str());
		indexLink = businessCardHolderForm->indexHolder->Find((LPCTSTR)companyName);
		Long location = indexLink->Find(current);
		HTREEITEM hCompanies = ((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))
			->GetRootItem();
		hCompany = ((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))
			->GetChildItem(hCompanies);
		CString companyText = ((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))
			->GetItemText(hCompany);
		companyName = CString(indexLink->GetName().c_str());
		while (hCompany != NULL && companyText.Compare(companyName) != 0) {
			hCompany = ((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))
				->GetNextSiblingItem(hCompany);
			companyText = ((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))
				->GetItemText(hCompany);
		}
		hName = ((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))
			->GetChildItem(hCompany);
		Long i = 0;
		while (i < location) {
			hName = ((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))
				->GetNextSiblingItem(hName);
			i++;
		}

		((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))->Expand(hCompanies, TVE_EXPAND);
		((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))->Expand(hCompany, TVE_EXPAND);
		((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))->SelectItem(hName);
		((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))->SelectDropTarget(hName);

	}
	else
	{
		businessCardHolderForm->GetDlgItem(IDC_STATIC_COMPANY_NAME)->SetWindowText("");
		businessCardHolderForm->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->SetWindowText("");
		businessCardHolderForm->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->SetWindowText("");
		businessCardHolderForm->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->SetWindowText("");
		businessCardHolderForm->GetDlgItem(IDC_STATIC_COMPANY_URL)->SetWindowText("");

		businessCardHolderForm->GetDlgItem(IDC_STATIC_PERSONAL_NAME)->SetWindowText("");
		businessCardHolderForm->GetDlgItem(IDC_STATIC_PERSONAL_TELEPHONENUMBER)->SetWindowText("");
		businessCardHolderForm->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->SetWindowText("");
		businessCardHolderForm->GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->SetWindowText("");
	}

	return FALSE;
}

void PuttingOutForm::OnClose()
{
	int ret = MessageBox("³¢¿ì°Ú½À´Ï±î?", "³¢¿ì±â", MB_YESNOCANCEL);

	switch (ret)
	{
	case IDYES:
	{
		BusinessCardHolderForm *businessCardHolderForm = (BusinessCardHolderForm*)CWnd::FindWindowA("#32770", "¸íÇÔÃ¸");
		CString companyName;
		GetDlgItem(IDC_STATIC_COMPANY_NAME)->GetWindowTextA(companyName);

		CString address;
		GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->GetWindowTextA(address);

		CString companyTelephoneNumber;
		GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->GetWindowTextA(companyTelephoneNumber);

		CString faxNumber;
		GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->GetWindowTextA(faxNumber);

		CString url;
		GetDlgItem(IDC_STATIC_COMPANY_URL)->GetWindowTextA(url);

		CString personalName;
		GetDlgItem(IDC_STATIC_PERSONAL_NAME)->GetWindowTextA(personalName);

		CString personalTelephoneNumber;
		GetDlgItem(IDC_STATIC_PERSONAL_TELEPHONENUMBER)->GetWindowTextA(personalTelephoneNumber);

		CString emailAddress;
		GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->GetWindowTextA(emailAddress);

		CString position;
		GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->GetWindowTextA(position);

		BusinessCard businessCard((LPCTSTR)companyName, (LPCTSTR)address, (LPCTSTR)companyTelephoneNumber, (LPCTSTR)faxNumber, (LPCTSTR)url,
			(LPCTSTR)personalName, (LPCTSTR)personalTelephoneNumber, (LPCTSTR)emailAddress, (LPCTSTR)position);

		BusinessCard *current = businessCardHolderForm->businessCardHolder->PutIn(businessCard);
		businessCardHolderForm->Insert(current);

		companyName = CString(current->GetCompanyName().c_str());
		businessCardHolderForm->GetDlgItem(IDC_STATIC_COMPANY_NAME)->SetWindowText(companyName);

		address = CString(current->GetAddress().c_str());
		businessCardHolderForm->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->SetWindowText(address);

		companyTelephoneNumber = CString(current->GetCompanyTelephoneNumber().c_str());
		businessCardHolderForm->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->SetWindowText(companyTelephoneNumber);

		faxNumber = CString(current->GetFaxNumber().c_str());
		businessCardHolderForm->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->SetWindowText(faxNumber);

		url = CString(current->GetUrl().c_str());
		businessCardHolderForm->GetDlgItem(IDC_STATIC_COMPANY_URL)->SetWindowText(url);

		personalName = CString(current->GetPersonalName().c_str());
		businessCardHolderForm->GetDlgItem(IDC_STATIC_PERSONAL_NAME)->SetWindowText(personalName);

		personalTelephoneNumber = CString(current->GetPersonalTelephoneNumber().c_str());
		businessCardHolderForm->GetDlgItem(IDC_STATIC_PERSONAL_TELEPHONENUMBER)->SetWindowText(personalTelephoneNumber);

		emailAddress = CString(current->GetEmailAddress().c_str());
		businessCardHolderForm->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->SetWindowText(emailAddress);

		position = CString(current->GetPosition().c_str());
		businessCardHolderForm->GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->SetWindowText(position);

		Index *indexLink = businessCardHolderForm->indexHolder->PutIn(current);
		HTREEITEM hCompanies = ((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))->GetRootItem();
		HTREEITEM hCompany = ((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))->GetChildItem(hCompanies);
		companyName = CString(indexLink->GetName().c_str());
		CString companyText = ((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))->GetItemText(hCompany);
		while (hCompany != NULL && companyText.Compare(companyName) != 0) {
			hCompany = ((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))
				->GetNextSiblingItem(hCompany);
			companyText = ((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))
				->GetItemText(hCompany);
		}
		if (hCompany == NULL) {
			hCompany = ((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))
				->InsertItem(companyName, hCompanies, TVI_LAST);
		}
		personalName = CString(current->GetPersonalName().c_str());
		HTREEITEM hName = ((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))
			->InsertItem(personalName, hCompany, TVI_LAST);
		((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))->Expand(hCompanies, TVE_EXPAND);
		((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))->Expand(hCompany, TVE_EXPAND);
		((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))->SelectItem(hName);
		((CTreeCtrl*)businessCardHolderForm->GetDlgItem(IDC_TREE_INDEX))->SelectDropTarget(hName);

		EndDialog(0);
	}

	break;

	case IDNO:
		EndDialog(0);
		break;
	default:
		break;
	}

}
