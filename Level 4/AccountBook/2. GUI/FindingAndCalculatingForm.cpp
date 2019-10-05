#include "FindingAndCalculatingForm.h"
#include "AccountBookForm.h"
#include "AccountBook.h"
#include "Date.h"
#include "Income.h"
#include "Outgo.h"
#include <afxcmn.h> //CListCtrl
#include <afxdtctl.h> //CDateTimeCtrl

BEGIN_MESSAGE_MAP(FindingAndCalculatingForm, CDialog)
	ON_BN_CLICKED(IDC_CHECK_CONTENT, OnContentCheckBoxClicked)
	ON_BN_CLICKED(IDC_CHECK_TERM, OnTermCheckBoxClicked)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_CALCULATE, OnCalculateButtonClicked)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ACCOUNTS, OnListViewItemDoubleClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

FindingAndCalculatingForm::FindingAndCalculatingForm(CWnd *parent)
	:CDialog(FindingAndCalculatingForm::IDD, parent)
{
	this->indexes = NULL;
	this->count = 0;
}
BOOL FindingAndCalculatingForm::OnInitDialog()
{
	CDialog::OnInitDialog();

	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(0, "일자", LVCFMT_CENTER, 150);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(1, "적요", LVCFMT_CENTER, 200);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(2, "금액", LVCFMT_CENTER, 150);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(3, "잔액", LVCFMT_CENTER, 150);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(4, "비고", LVCFMT_CENTER, 200);

	GetDlgItem(IDC_EDIT_CONTENT)->EnableWindow(FALSE);
	GetDlgItem(IDC_DATETIMEPICKER_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_DATETIMEPICKER_END)->EnableWindow(FALSE);

	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetExtendedStyle(LVS_EX_FULLROWSELECT);

	return FALSE;
}
void FindingAndCalculatingForm::OnContentCheckBoxClicked()
{
	int contentState = ((CButton*)GetDlgItem(IDC_CHECK_CONTENT))->GetCheck();
	if (contentState == BST_CHECKED)
	{
		GetDlgItem(IDC_EDIT_CONTENT)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_CALCULATE)->EnableWindow(FALSE);
	}
	else if (contentState==BST_UNCHECKED)
	{
		GetDlgItem(IDC_EDIT_CONTENT)->EnableWindow(FALSE);
		int termState = ((CButton*)GetDlgItem(IDC_CHECK_TERM))->GetCheck();
		if (termState == BST_CHECKED)
		{
			GetDlgItem(IDC_BUTTON_CALCULATE)->EnableWindow(TRUE);
		}
	}
}
void FindingAndCalculatingForm::OnTermCheckBoxClicked()
{
	int termState = ((CButton*)GetDlgItem(IDC_CHECK_TERM))->GetCheck();
	if (termState == BST_CHECKED)
	{
		GetDlgItem(IDC_DATETIMEPICKER_START)->EnableWindow(TRUE);
		GetDlgItem(IDC_DATETIMEPICKER_END)->EnableWindow(TRUE);
		int contentState = ((CButton*)GetDlgItem(IDC_CHECK_CONTENT))->GetCheck();
		if (contentState == BST_UNCHECKED)
		{
			GetDlgItem(IDC_BUTTON_CALCULATE)->EnableWindow(TRUE);
		}
	}
	else if (termState == BST_UNCHECKED)
	{
		GetDlgItem(IDC_DATETIMEPICKER_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATETIMEPICKER_END)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_CALCULATE)->EnableWindow(FALSE);
	}
}
void FindingAndCalculatingForm::OnFindButtonClicked()
{
	AccountBookForm *accountBookForm = (AccountBookForm*)CWnd::FindWindow("#32770", "가계부");
	int contentState = ((CButton*)GetDlgItem(IDC_CHECK_CONTENT))->GetCheck();
	int termState = ((CButton*)GetDlgItem(IDC_CHECK_TERM))->GetCheck();
	CString content;
	SYSTEMTIME startTime = { 0, };
	SYSTEMTIME endTime = { 0, };
	Date startDate;
	Date endDate;
	if (this->indexes != NULL)
	{
		delete[] this->indexes;
	}
	if (contentState == BST_CHECKED && termState == BST_UNCHECKED)
	{
		GetDlgItem(IDC_EDIT_CONTENT)->GetWindowTextA(content);
		accountBookForm->accountBook->Find(string((LPCTSTR)content), &this->indexes, &this->count);
	}
	else if (contentState == BST_UNCHECKED && termState == BST_CHECKED)
	{
		((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER_START))->GetTime(&startTime);
		startDate = Date(startTime.wYear, static_cast<Month>(startTime.wMonth), startTime.wDay);
		((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER_END))->GetTime(&endTime);
		endDate = Date(endTime.wYear, static_cast<Month>(endTime.wMonth), endTime.wDay);
		if (startDate == endDate)
		{
			accountBookForm->accountBook->Find(startDate, &this->indexes, &this->count);
		}
		else
		{
			accountBookForm->accountBook->Find(startDate, endDate, &this->indexes, &this->count);
		}
	}
	else if (contentState == BST_CHECKED && termState == BST_CHECKED)
	{
		GetDlgItem(IDC_EDIT_CONTENT)->GetWindowTextA(content);
		((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER_START))->GetTime(&startTime);
		startDate = Date(startTime.wYear, static_cast<Month>(startTime.wMonth), startTime.wDay);
		((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER_END))->GetTime(&endTime);
		endDate = Date(endTime.wYear, static_cast<Month>(endTime.wMonth), endTime.wDay);
		accountBookForm->accountBook->Find((LPCTSTR)content, startDate, endDate, &this->indexes, &this->count);
	}

	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->DeleteAllItems();

	Account *account;
	CString date;
	Date dateFormat;
	CString amount;
	CString balance;
	CString note;
	Long i = 0;
	while (i < this->count)
	{
		account = accountBookForm->accountBook->GetAt(this->indexes[i]);
		dateFormat = account->GetDate();
		date.Format("%4d-%02d-%02d", dateFormat.GetYear(), dateFormat.GetMonth(), dateFormat.GetDay());
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertItem(i, date);
		content = CString(account->GetContent().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(i, 1, content);
		amount = accountBookForm->MakeCurrencyFormat(account->GetAmount());
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(i, 2, amount);
		balance = accountBookForm->MakeCurrencyFormat(account->GetBalance());
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(i, 3, balance);
		note = CString(account->GetNote().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(i, 4, note);
		i++;
	}

	GetDlgItem(IDC_STATIC_CALCULATE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_INCOMESTATIC)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_OUTGOSTATIC)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DIFFERENCESTATIC)->ShowWindow(SW_HIDE);
}
void FindingAndCalculatingForm::OnCalculateButtonClicked() {
	SYSTEMTIME startTime = { 0, };
	SYSTEMTIME endTime = { 0, };
	((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER_START))->GetTime(&startTime);
	Date startDate(startTime.wYear, static_cast<Month>(startTime.wMonth), startTime.wDay);
	((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER_END))->GetTime(&endTime);
	Date endDate(endTime.wYear, static_cast<Month>(endTime.wMonth), endTime.wDay);

	AccountBookForm *accountBookForm = (AccountBookForm*)CWnd::FindWindow("#32770", "가계부");
	if (this->indexes != NULL) {
		delete[] this->indexes;
	}
	accountBookForm->accountBook->Find(startDate, endDate, &this->indexes, &this->count);
	CString date;
	Date dateFormat;
	CString content;
	CString amount;
	CString balance;
	CString note;
	Account *account;
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->DeleteAllItems();
	Long i = 0;
	while (i < this->count) {
		account = accountBookForm->accountBook->GetAt(this->indexes[i]);
		dateFormat = account->GetDate();
		date.Format("%4d-%02d-%02d", dateFormat.GetYear(), dateFormat.GetMonth(), dateFormat.GetDay());
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertItem(i, date);
		content = CString(account->GetContent().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(i, 1, content);
		amount = accountBookForm->MakeCurrencyFormat(account->GetAmount());
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(i, 2, amount);
		balance = accountBookForm->MakeCurrencyFormat(account->GetBalance());
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(i, 3, balance);
		note = CString(account->GetNote().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(i, 4, note);
		i++;
	}

	Currency sumOfIncome;
	Currency sumOfOutgo;
	Currency difference;
	accountBookForm->accountBook->Calculate(startDate, endDate, &sumOfIncome, &sumOfOutgo, &difference);
	CString income;
	CString outgo;
	CString differenceCString;

	GetDlgItem(IDC_STATIC_INCOME)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_OUTGO)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_DIFFERENCE)->ShowWindow(SW_SHOW);

	income = accountBookForm->MakeCurrencyFormat(sumOfIncome);
	GetDlgItem(IDC_STATIC_INCOME)->SetWindowTextA(income);
	outgo = accountBookForm->MakeCurrencyFormat(sumOfOutgo);
	GetDlgItem(IDC_STATIC_OUTGO)->SetWindowTextA(outgo);
	differenceCString = accountBookForm->MakeCurrencyFormat(difference);
	GetDlgItem(IDC_STATIC_DIFFERENCE)->SetWindowTextA(differenceCString);

	GetDlgItem(IDC_STATIC_CALCULATE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_INCOMESTATIC)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OUTGOSTATIC)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_DIFFERENCESTATIC)->ShowWindow(SW_SHOW);

}

void FindingAndCalculatingForm::OnListViewItemDoubleClicked(NMHDR *pNotifyStruct, LRESULT *result) {
	Long index = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->GetSelectionMark();
	AccountBookForm *accountBookForm = (AccountBookForm*)CWnd::FindWindow("#32770", "가계부");
	Account *account = accountBookForm->accountBook->GetAt(this->indexes[index]);
	if (dynamic_cast<Income*>(account)) {
		((CButton*)accountBookForm->GetDlgItem(IDC_RADIO_INCOME))->SetCheck(BST_CHECKED);
		((CButton*)accountBookForm->GetDlgItem(IDC_RADIO_OUTGO))->SetCheck(BST_UNCHECKED);
	}
	else if (dynamic_cast<Outgo*>(account)) {
		((CButton*)accountBookForm->GetDlgItem(IDC_RADIO_OUTGO))->SetCheck(BST_CHECKED);
		((CButton*)accountBookForm->GetDlgItem(IDC_RADIO_INCOME))->SetCheck(BST_UNCHECKED);
	}
	Date date(account->GetDate());
	SYSTEMTIME dateTime = { 0, };
	dateTime.wYear = date.GetYear();
	dateTime.wMonth = date.GetMonth();
	dateTime.wDay = date.GetDay();

	((CDateTimeCtrl*)accountBookForm->GetDlgItem(IDC_DATETIMEPICKER_DATE))->SetTime(&dateTime);
	CString content(account->GetContent().c_str());
	accountBookForm->GetDlgItem(IDC_EDIT_CONTENT)->SetWindowText(content);
	CString amount;
	amount = accountBookForm->MakeCurrencyFormat(account->GetAmount());
	accountBookForm->GetDlgItem(IDC_EDIT_AMOUNT)->SetWindowText(amount);
	CString balance;
	balance = accountBookForm->MakeCurrencyFormat(account->GetBalance());
	accountBookForm->GetDlgItem(IDC_STATIC_BALANCE)->SetWindowText(balance);
	CString note(account->GetNote().c_str());
	accountBookForm->GetDlgItem(IDC_EDIT_NOTE)->SetWindowText(note);
	((CListCtrl*)accountBookForm->GetDlgItem(IDC_LIST_ACCOUNTS))->SetSelectionMark(this->indexes[index]);
	if (this->indexes != NULL) {
		delete[] this->indexes;
	}
	EndDialog(0);
}

void FindingAndCalculatingForm::OnClose() {
	if (this->indexes != NULL) {
		delete[] this->indexes;
	}
	EndDialog(0);
}