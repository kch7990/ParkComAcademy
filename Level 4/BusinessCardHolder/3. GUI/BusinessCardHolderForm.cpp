#include "BusinessCardHolderForm.h"
#include "PuttingInForm.h"
#include "FindingForm.h"
#include "PuttingOutForm.h"
#include "BusinessCardHolder.h"
#include "IndexHolder.h"
#include "afxcmn.h"

BEGIN_MESSAGE_MAP(BusinessCardHolderForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_PUTIN, OnPutInButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_PUTOUT, OnPutOutButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_ARRANGE, OnArrangeButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_FIRST, OnFirstButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_PREVIOUS, OnPreviousButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnNextButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_LAST, OnLastButtonClicked)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_INDEX, OnTreeViewItemDoubleClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

BusinessCardHolderForm::BusinessCardHolderForm(CWnd *parent)
	:CDialog(BusinessCardHolderForm::IDD, parent) {
	this->businessCardHolder = NULL;
	this->indexHolder = NULL;
}
BOOL BusinessCardHolderForm::OnInitDialog() {
	CDialog::OnInitDialog();
	//Create BusinesscardHolder
	this->businessCardHolder = new BusinessCardHolder;
	//Create IndexHolder
	this->indexHolder = new IndexHolder;
	//Insert TreeCtrl Item
	HTREEITEM hCompanies = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEX))->InsertItem("회사들", TVI_ROOT, TVI_LAST);

	this->Load();

	if (this->businessCardHolder->GetLength() > 0)
	{
		//PutIn Index
		Index *indexLink;
		BusinessCard *previous = NULL;
		BusinessCard *businessCardLink=this->businessCardHolder->First();
		while (businessCardLink != previous) {
			indexLink = this->indexHolder->PutIn(businessCardLink);
			previous = businessCardLink;
			businessCardLink = this->businessCardHolder->Next();
		}
		//MakeList of Indexes
		Index(*indexes);
		Long countIndex;
		CString name;
		Long j;
		CString personalName;
		HTREEITEM hCompany;
		this->indexHolder->MakeList(&indexes, &countIndex);
		Long i = 0;
		while (i < countIndex) {
			name = CString(indexes[i].GetName().c_str());
			hCompany = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEX))->InsertItem(name, hCompanies, TVI_LAST);
			j = 0;
			while (j < indexes[i].GetLength()) {
				businessCardLink = indexes[i].GetAt(j);
				personalName = CString(businessCardLink->GetPersonalName().c_str());
				((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEX))->InsertItem(personalName, hCompany, TVI_LAST);
				j++;
			}
			i++;
		}
		businessCardLink = this->businessCardHolder->First();
		
		CString companyName(businessCardLink->GetCompanyName().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_NAME)->SetWindowTextA(companyName);
		CString address(businessCardLink->GetAddress().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->SetWindowTextA(address);
		CString companyTelephoneNumber(businessCardLink->GetCompanyTelephoneNumber().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->SetWindowTextA(companyTelephoneNumber);
		CString faxNumber(businessCardLink->GetFaxNumber().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->SetWindowTextA(faxNumber);
		CString url(businessCardLink->GetUrl().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_URL)->SetWindowTextA(url);

		personalName = CString(businessCardLink->GetPersonalName().c_str());
		GetDlgItem(IDC_STATIC_PERSONAL_NAME)->SetWindowTextA(personalName);
		CString personalTelephoneNumber(businessCardLink->GetPersonalTelephoneNumber().c_str());
		GetDlgItem(IDC_STATIC_PERSONAL_TELEPHONENUMBER)->SetWindowTextA(personalTelephoneNumber);
		CString emailAddress(businessCardLink->GetEmailAddress().c_str());
		GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->SetWindowTextA(emailAddress);
		CString position(businessCardLink->GetPosition().c_str());
		GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->SetWindowTextA(position);

		indexLink = this->indexHolder->Find((LPCTSTR)companyName);
		
		Long location = indexLink->Find(businessCardLink);
		
		companyName = CString(indexLink->GetName().c_str());
		hCompany = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEX))->GetChildItem(hCompanies);
		CString companyText = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEX))->GetItemText(hCompany);
		while (hCompany != NULL && companyText.Compare(companyName)) {
			hCompany = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEX))->GetNextSiblingItem(hCompany);
			companyText = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEX))->GetItemText(hCompany);
		}

		HTREEITEM hName = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEX))->GetChildItem(hCompany);
		i = 0;
		while (i < location) {
			hName = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEX))->GetNextSiblingItem(hName);
			i++;
		}

		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEX))->Expand(hCompanies, TVE_EXPAND);
		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEX))->Expand(hCompany, TVE_EXPAND);
		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEX))->SelectItem(hName);
		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEX))->SelectDropTarget(hName);

		if (indexes != NULL) {
			delete[] indexes;
		}
	}
	return FALSE;
}
void BusinessCardHolderForm::OnPutInButtonClicked() {
	PuttingInForm puttingInForm;
	puttingInForm.DoModal();
}
void BusinessCardHolderForm::OnFindButtonClicked() {
	FindingForm findingForm;
	findingForm.DoModal();
}
void BusinessCardHolderForm::OnPutOutButtonClicked() {
	PuttingOutForm puttingOutForm;
	puttingOutForm.DoModal();
}
void BusinessCardHolderForm::OnArrangeButtonClicked() {
	this->indexHolder->Arrange();

	((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEX))->DeleteAllItems();

	Index(*indexes);
	Long countIndex;
	this->indexHolder->MakeList(&indexes, &countIndex);

	HTREEITEM hCompanies = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEX))->InsertItem("회사들", TVI_ROOT, TVI_LAST);

	HTREEITEM hCompany;
	CString name;
	Long j;
	BusinessCard *businessCardLink;
	CString personalName;
	Long i = 0;
	while (i < countIndex) {
		name = CString(indexes[i].GetName().c_str());
		hCompany = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEX))->InsertItem(name, hCompanies, TVI_LAST);
		j = 0;
		while (j < indexes[i].GetLength()) {
			businessCardLink = indexes[i].GetAt(j);
			personalName = CString(businessCardLink->GetPersonalName().c_str());
			((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEX))->InsertItem(personalName, hCompany, TVI_LAST);
			j++;
		}
		i++;
	}
	businessCardLink = this->businessCardHolder->First();
	CString companyName(businessCardLink->GetCompanyName().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_NAME)->SetWindowTextA(companyName);
	CString address(businessCardLink->GetAddress().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->SetWindowTextA(address);
	CString companyTelephoneNumber(businessCardLink->GetCompanyTelephoneNumber().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->SetWindowTextA(companyTelephoneNumber);
	CString faxNumber(businessCardLink->GetFaxNumber().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->SetWindowTextA(faxNumber);
	CString url(businessCardLink->GetUrl().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_URL)->SetWindowTextA(url);
	personalName= CString(businessCardLink->GetPersonalName().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_NAME)->SetWindowTextA(personalName);
	CString personalTelephoneNumber(businessCardLink->GetPersonalTelephoneNumber().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_TELEPHONENUMBER)->SetWindowTextA(personalTelephoneNumber);
	CString emailAddress(businessCardLink->GetEmailAddress().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->SetWindowTextA(emailAddress);
	CString position(businessCardLink->GetPosition().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->SetWindowTextA(position);

	Index *indexLink=this->indexHolder->Find((LPCTSTR)companyName);
	Long location = indexLink->Find(businessCardLink);
	companyName = CString(indexLink->GetName().c_str());
	hCompany = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEX))->GetChildItem(hCompanies);
	CString companyText = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEX))->GetItemText(hCompany);
	while (hCompany != NULL && companyText.Compare(companyName) != 0) {
		hCompany = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEX))->GetNextSiblingItem(hCompany);
		companyText = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEX))->GetItemText(hCompany);
	}
	HTREEITEM hName = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEX))->GetChildItem(hCompany);
	i = 0;
	while (i < location) {
		hName = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEX))->GetNextSiblingItem(hName);
		i++;
	}
	((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEX))->Expand(hCompanies, TVE_EXPAND);
	((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEX))->Expand(hCompany, TVE_EXPAND);
	((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEX))->SelectItem(hName);
	((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEX))->SelectDropTarget(hName);

	if (indexes != NULL) {
		delete[] indexes;
	}
}
void BusinessCardHolderForm::OnFirstButtonClicked()
{
	BusinessCard *businessCardLink = this->businessCardHolder->First();

	CString companyName(businessCardLink->GetCompanyName().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_NAME)->SetWindowText(companyName);

	CString address(businessCardLink->GetAddress().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->SetWindowText(address);

	CString companyTelephoneNumber(businessCardLink->GetCompanyTelephoneNumber().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->SetWindowText(companyTelephoneNumber);

	CString faxNumber(businessCardLink->GetFaxNumber().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->SetWindowText(faxNumber);

	CString url(businessCardLink->GetUrl().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_URL)->SetWindowText(url);

	CString personalName(businessCardLink->GetPersonalName().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_NAME)->SetWindowText(personalName);

	CString personalTelephoneNumber(businessCardLink->GetPersonalTelephoneNumber().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_TELEPHONENUMBER)->SetWindowText(personalTelephoneNumber);

	CString emailAddress(businessCardLink->GetEmailAddress().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->SetWindowText(emailAddress);

	CString position(businessCardLink->GetPosition().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->SetWindowText(position);

	Index *indexLink = this->indexHolder->Find((LPCTSTR)companyName);
	Long location = indexLink->Find(businessCardLink);

	CTreeCtrl *hTree = (CTreeCtrl*)GetDlgItem(IDC_TREE_INDEX);
	HTREEITEM hCompanies = hTree->GetRootItem();
	HTREEITEM hCompany = hTree->GetChildItem(hCompanies);
	CString companyText = hTree->GetItemText(hCompany);

	while (hCompany != NULL && companyText.Compare(indexLink->GetName().c_str()) != 0)
	{
		hCompany = hTree->GetNextSiblingItem(hCompany);
		companyText = hTree->GetItemText(hCompany);
	}

	HTREEITEM hName = hTree->GetChildItem(hCompany);

	Long i = 0;
	while (i < location)
	{
		hName = hTree->GetNextSiblingItem(hName);
		i++;
	}

	hTree->Expand(hCompanies, TVE_EXPAND);
	hTree->Expand(hCompany, TVE_EXPAND);
	hTree->SelectItem(hName);
	hTree->SelectDropTarget(hName);
}

void BusinessCardHolderForm::OnPreviousButtonClicked()
{
	BusinessCard *businessCardLink = this->businessCardHolder->Previous();

	CString companyName(businessCardLink->GetCompanyName().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_NAME)->SetWindowText(companyName);

	CString address(businessCardLink->GetAddress().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->SetWindowText(address);

	CString companyTelephoneNumber(businessCardLink->GetCompanyTelephoneNumber().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->SetWindowText(companyTelephoneNumber);

	CString faxNumber(businessCardLink->GetFaxNumber().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->SetWindowText(faxNumber);

	CString url(businessCardLink->GetUrl().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_URL)->SetWindowText(url);

	CString personalName(businessCardLink->GetPersonalName().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_NAME)->SetWindowText(personalName);

	CString personalTelephoneNumber(businessCardLink->GetPersonalTelephoneNumber().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_TELEPHONENUMBER)->SetWindowText(personalTelephoneNumber);

	CString emailAddress(businessCardLink->GetEmailAddress().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->SetWindowText(emailAddress);

	CString position(businessCardLink->GetPosition().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->SetWindowText(position);

	Index *indexLink = this->indexHolder->Find((LPCTSTR)companyName);
	Long location = indexLink->Find(businessCardLink);

	CTreeCtrl *hTree = (CTreeCtrl*)GetDlgItem(IDC_TREE_INDEX);
	HTREEITEM hCompanies = hTree->GetRootItem();
	HTREEITEM hCompany = hTree->GetChildItem(hCompanies);
	CString companyText = hTree->GetItemText(hCompany);

	while (hCompany != NULL && companyText.Compare(indexLink->GetName().c_str()) != 0)
	{
		hCompany = hTree->GetNextSiblingItem(hCompany);
		companyText = hTree->GetItemText(hCompany);
	}

	HTREEITEM hName = hTree->GetChildItem(hCompany);

	Long i = 0;
	while (i < location)
	{
		hName = hTree->GetNextSiblingItem(hName);
		i++;
	}

	hTree->Expand(hCompanies, TVE_EXPAND);
	hTree->Expand(hCompany, TVE_EXPAND);
	hTree->SelectItem(hName);
	((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEX))->SelectDropTarget(hName);
}

void BusinessCardHolderForm::OnNextButtonClicked()
{
	BusinessCard *businessCardLink = this->businessCardHolder->Next();

	CString companyName(businessCardLink->GetCompanyName().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_NAME)->SetWindowText(companyName);

	CString address(businessCardLink->GetAddress().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->SetWindowText(address);

	CString companyTelephoneNumber(businessCardLink->GetCompanyTelephoneNumber().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->SetWindowText(companyTelephoneNumber);

	CString faxNumber(businessCardLink->GetFaxNumber().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->SetWindowText(faxNumber);

	CString url(businessCardLink->GetUrl().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_URL)->SetWindowText(url);

	CString personalName(businessCardLink->GetPersonalName().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_NAME)->SetWindowText(personalName);

	CString personalTelephoneNumber(businessCardLink->GetPersonalTelephoneNumber().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_TELEPHONENUMBER)->SetWindowText(personalTelephoneNumber);

	CString emailAddress(businessCardLink->GetEmailAddress().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->SetWindowText(emailAddress);

	CString position(businessCardLink->GetPosition().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->SetWindowText(position);

	Index *indexLink = this->indexHolder->Find((LPCTSTR)companyName);
	Long location = indexLink->Find(businessCardLink);

	CTreeCtrl *hTree = (CTreeCtrl*)GetDlgItem(IDC_TREE_INDEX);
	HTREEITEM hCompanies = hTree->GetRootItem();
	HTREEITEM hCompany = hTree->GetChildItem(hCompanies);
	CString companyText = hTree->GetItemText(hCompany);

	while (hCompany != NULL && companyText.Compare(indexLink->GetName().c_str()) != 0)
	{
		hCompany = hTree->GetNextSiblingItem(hCompany);
		companyText = hTree->GetItemText(hCompany);
	}

	HTREEITEM hName = hTree->GetChildItem(hCompany);

	Long i = 0;
	while (i < location)
	{
		hName = hTree->GetNextSiblingItem(hName);
		i++;
	}

	hTree->Expand(hCompanies, TVE_EXPAND);
	hTree->Expand(hCompany, TVE_EXPAND);
	hTree->SelectItem(hName);
	((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEX))->SelectDropTarget(hName);
}

void BusinessCardHolderForm::OnLastButtonClicked()
{
	BusinessCard *businessCardLink = this->businessCardHolder->Last();

	CString companyName(businessCardLink->GetCompanyName().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_NAME)->SetWindowText(companyName);

	CString address(businessCardLink->GetAddress().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->SetWindowText(address);

	CString companyTelephoneNumber(businessCardLink->GetCompanyTelephoneNumber().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->SetWindowText(companyTelephoneNumber);

	CString faxNumber(businessCardLink->GetFaxNumber().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->SetWindowText(faxNumber);

	CString url(businessCardLink->GetUrl().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_URL)->SetWindowText(url);

	CString personalName(businessCardLink->GetPersonalName().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_NAME)->SetWindowText(personalName);

	CString personalTelephoneNumber(businessCardLink->GetPersonalTelephoneNumber().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_TELEPHONENUMBER)->SetWindowText(personalTelephoneNumber);

	CString emailAddress(businessCardLink->GetEmailAddress().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->SetWindowText(emailAddress);

	CString position(businessCardLink->GetPosition().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->SetWindowText(position);

	Index *indexLink = this->indexHolder->Find((LPCTSTR)companyName);
	Long location = indexLink->Find(businessCardLink);

	CTreeCtrl *hTree = (CTreeCtrl*)GetDlgItem(IDC_TREE_INDEX);
	HTREEITEM hCompanies = hTree->GetRootItem();
	HTREEITEM hCompany = hTree->GetChildItem(hCompanies);
	CString companyText = hTree->GetItemText(hCompany);

	while (hCompany != NULL && companyText.Compare(indexLink->GetName().c_str()) != 0)
	{
		hCompany = hTree->GetNextSiblingItem(hCompany);
		companyText = hTree->GetItemText(hCompany);
	}

	HTREEITEM hName = hTree->GetChildItem(hCompany);

	Long i = 0;
	while (i < location)
	{
		hName = hTree->GetNextSiblingItem(hName);
		i++;
	}

	hTree->Expand(hCompanies, TVE_EXPAND);
	hTree->Expand(hCompany, TVE_EXPAND);
	hTree->SelectItem(hName);
	((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEX))->SelectDropTarget(hName);
}
void BusinessCardHolderForm::OnTreeViewItemDoubleClicked(NMHDR *pNotifyStruct, LRESULT *result)
{
	CTreeCtrl *hTree = (CTreeCtrl*)GetDlgItem(IDC_TREE_INDEX);
	HTREEITEM hSelected = hTree->GetSelectedItem();
	HTREEITEM hCompany = hTree->GetParentItem(hSelected);
	CString companyName = hTree->GetItemText(hCompany);
	HTREEITEM hName = hTree->GetChildItem(hCompany);

	Long location = 0;
	while (hName != hSelected)
	{
		location++;
		hName = hTree->GetNextSiblingItem(hName);
	}
	((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEX))->SelectDropTarget(hName);


	Index *indexLink = this->indexHolder->Find((LPCTSTR)companyName);
	BusinessCard * businessCardLink = indexLink->GetAt(location);
	businessCardLink = this->businessCardHolder->Move(businessCardLink);

	companyName = CString(businessCardLink->GetCompanyName().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_NAME)->SetWindowTextA(companyName);

	CString address(businessCardLink->GetAddress().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->SetWindowText(address);

	CString companyTelephoneNumber(businessCardLink->GetCompanyTelephoneNumber().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->SetWindowText(companyTelephoneNumber);

	CString faxNumber(businessCardLink->GetFaxNumber().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->SetWindowText(faxNumber);

	CString url(businessCardLink->GetUrl().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_URL)->SetWindowText(url);

	CString personalName(businessCardLink->GetPersonalName().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_NAME)->SetWindowText(personalName);

	CString personalTelephoneNumber(businessCardLink->GetPersonalTelephoneNumber().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_TELEPHONENUMBER)->SetWindowText(personalTelephoneNumber);

	CString emailAddress(businessCardLink->GetEmailAddress().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->SetWindowText(emailAddress);

	CString position(businessCardLink->GetPosition().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->SetWindowText(position);
}
void BusinessCardHolderForm::OnClose() {
	if (this->businessCardHolder != NULL) {
		this->Save();
		delete this->businessCardHolder;
	}
	EndDialog(0);
}

#include <afxdb.h>

void BusinessCardHolderForm::Load()
{
	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Company.name, Company.address, Company.telephoneNumber, Company.faxNumber, Company.url, Personal.name, Personal.telephoneNumber, Personal.emailAddress, Personal.position "
		"FROM Personal INNER JOIN Company ON Company.companyCode=Personal.companyCode;";
	db.OpenEx("DSN=BusinessCardHolder;UID=root;PWD=preta27531@"); //Connection
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql); //SELECT Request/Response

	CString companyName;
	CString address;
	CString companyTelephoneNumber;
	CString faxNumber;
	CString url;
	CString personalName;
	CString personalTelephoneNumber;
	CString emailAddress;
	CString position;
	while (!rs.IsEOF())
	{
		rs.GetFieldValue((short)0, companyName);
		rs.GetFieldValue((short)1, address);
		rs.GetFieldValue((short)2, companyTelephoneNumber);
		rs.GetFieldValue((short)3, faxNumber);
		rs.GetFieldValue((short)4, url);
		rs.GetFieldValue((short)5, personalName);
		rs.GetFieldValue((short)6, personalTelephoneNumber);
		rs.GetFieldValue((short)7, emailAddress);
		rs.GetFieldValue((short)8, position);
		BusinessCard businessCard((LPCTSTR)companyName, (LPCTSTR)address, (LPCTSTR)companyTelephoneNumber, (LPCTSTR)faxNumber, (LPCTSTR)url,
			(LPCTSTR)personalName, (LPCTSTR)personalTelephoneNumber, (LPCTSTR)emailAddress, (LPCTSTR)position);
		this->businessCardHolder->PutIn(businessCard);
		rs.MoveNext();
	}
	rs.Close(); //Disconnection
	db.Close(); //Disconnection
}
void BusinessCardHolderForm::Save()
{
	CDatabase db;
	CRecordset rsCodes(&db);
	CRecordset rs(&db);
	CString sql;
	CString companyCode;
	CString personalCode;
	db.OpenEx("DSN=BusinessCardHolder;UID=root;PWD=preta27531@"); //connection
	sql = "SELECT Company.companyCode, Personal.code FROM Personal INNER JOIN Company ON Company.companyCode=Personal.companyCode;";
	rsCodes.Open(AFX_DB_USE_DEFAULT_TYPE, sql); //SELECT request/response

	sql = "DELETE FROM Personal;";
	db.ExecuteSQL(sql); //DELETE Request
	sql = "DELETE FROM Company;";
	db.ExecuteSQL(sql); //DELETE Request
	
	BusinessCard *previous = 0;
	BusinessCard *current = 0;
	if (this->businessCardHolder->GetLength() > 0)
	{
		current = this->businessCardHolder->First();
	}
	while (current!=previous)
	{
		rsCodes.GetFieldValue((short)0, companyCode);
		sql.Format("SELECT Company.companyCode FROM Company WHERE companyCode='%s';", (LPCTSTR)companyCode);
		rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql); //SELECT Request/Response
		if (rs.IsEOF())
		{
			sql.Format("INSERT INTO Company(companyCode, name, address, telephoneNumber, faxNumber, url) "
				"VALUES('%s', '%s', '%s', '%s', '%s', '%s');", (LPCTSTR)companyCode, current->GetCompanyName().c_str(),
				current->GetAddress().c_str(), current->GetCompanyTelephoneNumber().c_str(), current->GetFaxNumber().c_str(),
				current->GetUrl().c_str());
			db.ExecuteSQL(sql); //INSERT Request
		}
		rsCodes.GetFieldValue((short)1, personalCode);
		sql.Format("INSERT INTO Personal(code, name, telephoneNumber, emailAddress, position, companyCode) "
			"VALUES('%s', '%s', '%s', '%s', '%s', '%s');", (LPCTSTR)personalCode, current->GetPersonalName().c_str(),
			current->GetPersonalTelephoneNumber().c_str(), current->GetEmailAddress().c_str(), current->GetPosition().c_str(),
			(LPCTSTR)companyCode);
		db.ExecuteSQL(sql); //INSERT Request

		rs.Close(); //Disconnection for reconnection
		rsCodes.MoveNext();

		previous = current;
		current = this->businessCardHolder->Next();
	}
	rsCodes.Close(); //Disconnection
	db.Close(); //Disconnection
}
void BusinessCardHolderForm::Insert(BusinessCard *index)
{
	CDatabase db;
	CRecordset rs(&db);
	CString sql;
	CString companyCode;
	CString personalCode;
	sql.Format("SELECT Company.companyCode FROM Company WHERE name='%s' AND address='%s' AND telephoneNumber='%s' AND faxNumber='%s' AND url='%s';",
		index->GetCompanyName().c_str(), index->GetAddress().c_str(), index->GetCompanyTelephoneNumber().c_str(), index->GetFaxNumber().c_str(), index->GetUrl().c_str());
	db.OpenEx("DSN=BusinessCardHolder;UID=root;PWN=preta27531@");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql); //SELECT Request/Response
	if (rs.IsEOF())
	{
		companyCode = MakeCompanyCode();
		sql.Format("INSERT INTO Company(companyCode, name, address, telephoneNumber, faxNumber, url) "
			"VALUES('%s', '%s', '%s', '%s', '%s', '%s');", (LPCTSTR)companyCode, index->GetCompanyName().c_str(), index->GetAddress().c_str(), 
			index->GetCompanyTelephoneNumber().c_str(), index->GetFaxNumber().c_str(), index->GetUrl().c_str());
		db.ExecuteSQL(sql); //INSERT Request
	}
	else
	{
		rs.GetFieldValue((short)0, companyCode);
	}
	personalCode = MakePersonalCode();
	sql.Format("INSERT INTO Personal(code, name, telephoneNumber, emailAddress, position, companyCode) "
		"VALUES('%s', '%s', '%s', '%s', '%s', '%s');", (LPCTSTR)personalCode, index->GetPersonalName().c_str(), index->GetPersonalTelephoneNumber().c_str(), 
		index->GetEmailAddress().c_str(), index->GetPosition().c_str(), (LPCTSTR)companyCode);
	db.ExecuteSQL(sql); //INSERT Request

	rs.Close(); //Disconnection
	db.Close(); //Disconnection
}
void BusinessCardHolderForm::Delete(BusinessCard *index)
{
	CDatabase db;
	CRecordset rs(&db);
	CString sql;
	sql.Format("SELECT Personal.code, Personal.companyCode FROM Personal WHERE name='%s' AND telephoneNumber='%s' AND emailAddress='%s' "
		"AND position='%s';", index->GetPersonalName().c_str(), index->GetPersonalTelephoneNumber().c_str(), index->GetEmailAddress().c_str(),
		index->GetPosition().c_str());
	db.OpenEx("DSN=BusinessCardHolder;UID=root;PWD=preta27531@"); //Connection
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql); //SELECT Request

	CString personalCode;
	rs.GetFieldValue((short)0, personalCode);
	sql.Format("DELETE FROM Personal WHERE code='%s';", (LPCTSTR)personalCode);
	db.ExecuteSQL(sql); //DELETE Request

	CString companyCode;
	rs.GetFieldValue((short)1, companyCode);
	rs.Close(); //Close for 2nd SELECT Request
	sql.Format("SELECT Personal.code FROM Personal WHERE companyCode='%s';", (LPCTSTR)companyCode);
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql); //SELECT Request/Response
	
	if (rs.IsEOF())
	{
		sql.Format("DELETE FROM Company WHERE companyCode='%s';", (LPCTSTR)companyCode);
		db.ExecuteSQL(sql); //DELETE Request
	}
	rs.Close(); //Disconnection
	db.Close(); //Disconnection
}
CString BusinessCardHolderForm::MakePersonalCode()
{
	CString personalCode;
	int number = 1;
	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Personal.code FROM Personal ORDER BY code DESC;";
	db.OpenEx("DSN=BusinessCardHolder;UID=root;PWD=preta27531@"); //Connection
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql); //SELECT Request/Response

	if (!rs.IsEOF())
	{
		rs.GetFieldValue((short)0, personalCode);
		personalCode.Delete(0, 1);
		number = atoi((LPCTSTR)personalCode);
	}
	personalCode.Format("P%04d", number + 1);

	rs.Close(); //Disconnection
	db.Close(); //Disconnection

	return personalCode;
}
CString BusinessCardHolderForm::MakeCompanyCode()
{
	CString companyCode;
	int number = 1;
	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Company.companyCode FROM Company ORDER BY companyCode DESC;";
	db.OpenEx("DSN=BusinessCardHolder;UID=root;PWD=preta27531@"); //Connection
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql); //SELECT Request/Response

	if (!rs.IsEOF())
	{
		rs.GetFieldValue((short)0, companyCode);
		companyCode.Delete(0, 1);
		number = atoi((LPCTSTR)companyCode);
	}
	companyCode.Format("C%04d", number + 1);
	rs.Close(); //Disconnection
	db.Close(); //Disconnection

	return companyCode;
}