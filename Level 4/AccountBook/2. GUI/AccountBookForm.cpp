#include "AccountBookForm.h"
#include "FindingAndCalculatingForm.h"
#include "AccountBook.h"
#include "Date.h"
#include "Income.h"
#include "Outgo.h"
#include "resource.h"
#include <afxcmn.h> //CListCtrl
#include <afxdtctl.h> //CDateTimeCtrl

BEGIN_MESSAGE_MAP(AccountBookForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_RECORD, OnRecordButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_CORRECT, OnCorrectButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_CALCULATE, OnCalculateButtonClicked)
	ON_EN_KILLFOCUS(IDC_EDIT_AMOUNT, OnAmountEditKillFocus)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ACCOUNTS, OnListViewItemDoubleClicked)
	ON_BN_CLICKED(IDC_RADIO_INCOME, OnIncomeRadioButtonClicked)
	ON_BN_CLICKED(IDC_RADIO_OUTGO, OnOutgoRadioButtonClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

AccountBookForm::AccountBookForm(CWnd* parent)
	:CDialog(AccountBookForm::IDD, parent)
{
	this->accountBook = NULL;
}

BOOL AccountBookForm::OnInitDialog()
{
	CDialog::OnInitDialog();
	this->accountBook = new AccountBook;

	CListCtrl *listCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS);

	listCtrl->InsertColumn(0, "일과", LVCFMT_CENTER, 150);
	listCtrl->InsertColumn(1, "적요", LVCFMT_CENTER, 200);
	listCtrl->InsertColumn(2, "금액", LVCFMT_CENTER, 150);
	listCtrl->InsertColumn(3, "잔액", LVCFMT_CENTER, 150);
	listCtrl->InsertColumn(4, "비고", LVCFMT_CENTER, 200);

	((CButton*)GetDlgItem(IDC_RADIO_INCOME))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_OUTGO))->SetCheck(BST_CHECKED);

	listCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT);

	//적재하다.
	this->Load();

	Account *account;
	Date dateFormat;
	CString date;
	CString content;
	CString amount;
	CString balance;
	CString note;
	Long i = 0;
	while (i < this->accountBook->GetLength())
	{
		account = this->accountBook->GetAt(i);
		dateFormat = account->GetDate();
		date.Format("%4d-%02d-%02d", dateFormat.GetYear(), dateFormat.GetMonth(), dateFormat.GetDay());
		listCtrl->InsertItem(i, date);
		content = CString(account->GetContent().c_str());
		listCtrl->SetItemText(i, 1, content);
		amount = MakeCurrencyFormat(account->GetAmount());
		listCtrl->SetItemText(i, 2, amount);
		balance = MakeCurrencyFormat(account->GetBalance());
		listCtrl->SetItemText(i, 3, balance);
		note = CString(account->GetNote().c_str());
		listCtrl->SetItemText(i, 4, note);
		i++;
	}

	return FALSE;
}

void AccountBookForm::OnRecordButtonClicked()
{
	int selectedRadio = GetCheckedRadioButton(IDC_RADIO_INCOME, IDC_RADIO_OUTGO);

	SYSTEMTIME dateTime = { 0, };

	((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER_DATE))->GetTime(&dateTime);
	Date date(dateTime.wYear, static_cast<Month>(dateTime.wMonth), dateTime.wDay);

	CString content;
	GetDlgItem(IDC_EDIT_CONTENT)->GetWindowText(content);

	CString amount;
	GetDlgItem(IDC_EDIT_AMOUNT)->GetWindowTextA(amount);
	Currency amountCurrency = atof((LPCTSTR)amount);
	if (selectedRadio == IDC_RADIO_OUTGO)
	{
		amountCurrency *= -1;
	}

	CString note;
	GetDlgItem(IDC_EDIT_NOTE)->GetWindowTextA(note);

	Long index = this->accountBook->Record(date, (LPCTSTR)content, amountCurrency, (LPCTSTR)note);

	this->Insert(index);

	CListCtrl *listCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS);

	Account *account = this->accountBook->GetAt(index);
	Date dateFormat = account->GetDate();
	CString dateString;
	dateString.Format("%4d-%02d-%02d", dateFormat.GetYear(), dateFormat.GetMonth(), dateFormat.GetDay());

	listCtrl->InsertItem(index, dateString);

	content = CString(account->GetContent().c_str());
	listCtrl->SetItemText(index, 1, content);

	amount = MakeCurrencyFormat(account->GetAmount());
	listCtrl->SetItemText(index, 2, amount);

	CString balance = MakeCurrencyFormat(account->GetBalance());
	listCtrl->SetItemText(index, 3, balance);

	note = CString(account->GetNote().c_str());
	listCtrl->SetItemText(index, 4, note);
}

void AccountBookForm::OnCorrectButtonClicked()
{
	int selectedRadio = GetCheckedRadioButton(IDC_RADIO_INCOME, IDC_RADIO_OUTGO);

	CString amount;
	GetDlgItem(IDC_EDIT_AMOUNT)->GetWindowTextA(amount);
	Currency amountCurrency = atof((LPCTSTR)amount);
	if (selectedRadio == IDC_RADIO_OUTGO)
	{
		amountCurrency *= -1;
	}

	CString note;
	GetDlgItem(IDC_EDIT_NOTE)->GetWindowTextA(note);

	CListCtrl *listCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS);

	Long index = listCtrl->GetSelectionMark();

	index = this->accountBook->Correct(index, amountCurrency, (LPCTSTR)note);

	this->Modify(index);

	Account *account = this->accountBook->GetAt(index);
	amount = MakeCurrencyFormat(account->GetAmount());
	listCtrl->SetItemText(index, 2, amount);

	CString balance = MakeCurrencyFormat(account->GetBalance());
	listCtrl->SetItemText(index, 3, balance);

	note = CString(account->GetNote().c_str());
	listCtrl->SetItemText(index, 4, note);

	Long i = index + 1;
	while (i < this->accountBook->GetLength())
	{
		account = this->accountBook->GetAt(i);
		balance = MakeCurrencyFormat(account->GetBalance());
		listCtrl->SetItemText(i, 3, balance);
		i++;
	}
}

void AccountBookForm::OnFindButtonClicked()
{
	FindingAndCalculatingForm findingAndCalculatingForm;
	findingAndCalculatingForm.DoModal();
}

void AccountBookForm::OnCalculateButtonClicked()
{
	FindingAndCalculatingForm findingAndCalculatingForm;
	findingAndCalculatingForm.DoModal();
}

void AccountBookForm::OnAmountEditKillFocus()
{
	CString amountString;
	GetDlgItem(IDC_EDIT_AMOUNT)->GetWindowText(amountString);
	Currency balance = 0.0;
	Account *account = 0;

	if (this->accountBook->GetLength() > 0)
	{
		Long index = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->GetSelectionMark();
		if (index != -1) {
			account = this->accountBook->GetAt(index); //고치기
		}
		else {
			account = this->accountBook->GetAt(this->accountBook->GetLength() - 1); //기입하기
		}
		balance = account->GetBalance();
	}
	int checkOfIncome = ((CButton*)GetDlgItem(IDC_RADIO_INCOME))->GetCheck();
	Currency amount = atof((LPCTSTR)amountString);
	SYSTEMTIME dateTime = { 0, };
	CString content;
	Date date;
	((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER_DATE))->GetTime(&dateTime);
	date = Date(dateTime.wYear, static_cast<Month>(dateTime.wMonth), dateTime.wDay);
	GetDlgItem(IDC_EDIT_CONTENT)->GetWindowTextA(content);
	
	if (account != 0 && account->GetDate() == date && account->GetContent().compare((LPCTSTR)content) == 0) {
		if (checkOfIncome == BST_CHECKED)
		{
			balance -= (account->GetAmount() - amount);
		}
		else
		{
			balance += (account->GetAmount() - amount);
		}
	}
	else {
		if (checkOfIncome == BST_CHECKED)
		{
			balance += amount;
		}
		else
		{
			balance -= amount;
		}
	}
	CString balanceString = MakeCurrencyFormat(balance);
	GetDlgItem(IDC_STATIC_BALANCE)->SetWindowTextA(balanceString);
}
void AccountBookForm::OnListViewItemDoubleClicked(NMHDR* pNotifyStruct, LRESULT *result) {
	Long index = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->GetSelectionMark();
	CString dateString = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->GetItemText(index, 0);
	dateString.Remove('-');
	Date date((LPCTSTR)dateString);
	CString content = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->GetItemText(index, 1);
	CString amount = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->GetItemText(index, 2);
	amount.Remove(',');
	CString balance = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->GetItemText(index, 3);
	balance.Remove(',');
	CString note = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->GetItemText(index, 4);

	Account *account = this->accountBook->GetAt(index);

	if (dynamic_cast<Income*>(account)) {
		((CButton*)GetDlgItem(IDC_RADIO_INCOME))->SetCheck(BST_CHECKED);
		((CButton*)GetDlgItem(IDC_RADIO_OUTGO))->SetCheck(BST_UNCHECKED);
	}
	else if (dynamic_cast<Outgo*>(account)) {
		((CButton*)GetDlgItem(IDC_RADIO_OUTGO))->SetCheck(BST_CHECKED);
		((CButton*)GetDlgItem(IDC_RADIO_INCOME))->SetCheck(BST_UNCHECKED);
	}
	SYSTEMTIME dateTime = { 0, };
	dateTime.wYear = date.GetYear();
	dateTime.wMonth = date.GetMonth();
	dateTime.wDay = date.GetDay();

	((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER_DATE))->SetTime(&dateTime);
	GetDlgItem(IDC_EDIT_CONTENT)->SetWindowText(content);
	GetDlgItem(IDC_EDIT_AMOUNT)->SetWindowText(amount);
	GetDlgItem(IDC_STATIC_BALANCE)->SetWindowText(balance);
	GetDlgItem(IDC_EDIT_NOTE)->SetWindowText(note);

}
void AccountBookForm::OnIncomeRadioButtonClicked()
{
	CString amountString;
	GetDlgItem(IDC_EDIT_AMOUNT)->GetWindowText(amountString);
	Currency balance = 0.0;
	Account *account;

	if (this->accountBook->GetLength() > 0)
	{
		account = this->accountBook->GetAt(this->accountBook->GetLength() - 1);
		balance = account->GetBalance();
	}

	int checkOfIncome = ((CButton*)GetDlgItem(IDC_RADIO_INCOME))->GetCheck();
	Currency amount = atof(amountString);

	if (checkOfIncome == BST_CHECKED)
	{
		balance += amount;
	}
	else
	{
		balance -= amount;
	}

	CString balanceString;
	balanceString.Format("%.0lf", balance);
	GetDlgItem(IDC_STATIC_BALANCE)->SetWindowTextA(balanceString);
}
void AccountBookForm::OnOutgoRadioButtonClicked()
{
	CString amountString;
	GetDlgItem(IDC_EDIT_AMOUNT)->GetWindowText(amountString);
	Currency balance = 0.0;
	Account *account;

	if (this->accountBook->GetLength() > 0)
	{
		account = this->accountBook->GetAt(this->accountBook->GetLength() - 1);
		balance = account->GetBalance();
	}

	int checkOfIncome = ((CButton*)GetDlgItem(IDC_RADIO_INCOME))->GetCheck();
	Currency amount = atof(amountString);

	if (checkOfIncome == BST_CHECKED)
	{
		balance += amount;
	}
	else
	{
		balance -= amount;
	}

	CString balanceString;
	balanceString.Format("%.0lf", balance);
	GetDlgItem(IDC_STATIC_BALANCE)->SetWindowTextA(balanceString);
}

void AccountBookForm::OnClose()
{
	if (this->accountBook != NULL)
	{
		this->Save();
		delete this->accountBook;
	}
	EndDialog(0);
}

#include <afxdb.h>

void AccountBookForm::Load()
{
	CDatabase db;
	CRecordset rs(&db);

	db.OpenEx("DSN=AccountBook;UID=root;PWD=preta27531@"); //Connection
	CString sql = "SELECT Account.date, Account.content, Account.amount, Account.note FROM Account;";
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql); //SELECT Request/Response

	CDBVariant date;
	CString content;
	CString amount;
	CString note;
	while (!rs.IsEOF())
	{
		rs.GetFieldValue((short)0, date);
		rs.GetFieldValue((short)1, content);
		rs.GetFieldValue((short)2, amount);
		rs.GetFieldValue((short)3, note);

		this->accountBook->Record(Date(date.m_pdate->year, static_cast<Month>(date.m_pdate->month), date.m_pdate->day), (LPCTSTR)content,
			atof((LPCTSTR)amount), (LPCTSTR)note);
		rs.MoveNext();
	}
	rs.Close();
	db.Close(); //Disconnection
}
void AccountBookForm::Save()
{
	CDatabase db;
	CRecordset rs(&db);
	CString code;
	Date date;
	Account *account;
	Currency amount;

	CString sql = "SELECT Account.code FROM Account;";
	db.OpenEx("DSN=AccountBook;UID=root;PWD=preta27531@"); //Connection
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql); //SELECT Request/Response

	sql = "DELETE FROM Account;";
	db.ExecuteSQL(sql); //DELETE Request

	Long i = 0;
	while (i < this->accountBook->GetLength())
	{
		rs.GetFieldValue((short)0, code);
		rs.MoveNext();
		account = this->accountBook->GetAt(i);
		amount = account->GetAmount();
		if (dynamic_cast<Outgo*>(account)) {
			amount *= -1.0;
		}
		date = account->GetDate();
		sql.Format("INSERT INTO Account(code, date, content, amount, note) VALUES('%s', '%4d-%02d-%02d', '%s', %.0lf, '%s');",
			code, date.GetYear(), date.GetMonth(), date.GetDay(), account->GetContent().c_str(), amount, account->GetNote().c_str());
		db.ExecuteSQL(sql); //INSERT Request
		i++;
	}
	rs.Close();
	db.Close(); //Disconnection
}
void AccountBookForm::Insert(Long index)
{
	CDatabase db;
	Account *account = this->accountBook->GetAt(index);
	Currency amount = account->GetAmount();
	if (dynamic_cast<Outgo*>(account)) {
		amount *= -1.0;
	}
	Date date(account->GetDate());
	CString code = MakeCode(account->GetDate());
	CString sql;
	sql.Format("INSERT INTO Account(code, date, content, amount, note) VALUES('%s', '%4d-%02d-%02d', '%s', '%.0lf', '%s');",
		(LPCTSTR)code, date.GetYear(), date.GetMonth(), date.GetDay(), account->GetContent().c_str(), amount, account->GetNote().c_str());
	db.OpenEx("DSN=AccountBook;UID=root;PWD=preta27531@"); //Connection
	db.ExecuteSQL(sql); //INSERT Request
	db.Close(); //Disconnection
}
void AccountBookForm::Modify(Long index)
{
	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Account.code FROM Account;";
	Account *account = this->accountBook->GetAt(index);
	Currency amount = account->GetAmount();
	if (dynamic_cast<Outgo*>(account)) {
		amount *= -1.0;
	}

	db.OpenEx("DSN=AccountBook;UID=root;PWD=preta27531@");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);

	rs.Move(index);
	CString code;
	rs.GetFieldValue((short)0, code);
	sql.Format("UPDATE Account SET amount=%0.1lf, note = '%s' WHERE code = '%s';", amount, account->GetNote().c_str(), (LPCTSTR)code);
	db.ExecuteSQL(sql);

	rs.Close();
	db.Close();
}

CString AccountBookForm::MakeCode(const Date& date)
{
	CDatabase db;
	CRecordset rs(&db);
	CString sql;
	CString code;
	Long codeNumber = 0;

	sql.Format("SELECT Account.code FROM Account WHERE date = '%4d-%02d-%02d' ORDER BY code DESC;", date.GetYear(), date.GetMonth(), date.GetDay());
	db.OpenEx("DSN=AccountBook;UID=root;PWD=preta27531@");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);

	if (!rs.IsEOF())
	{
		rs.GetFieldValue((short)0, code);
		codeNumber = atoi((LPCTSTR)code.Right(3));
	}
	code.Format("%4d%02d%02d%03d", date.GetYear(), date.GetMonth(), date.GetDay(), codeNumber + 1);
	rs.Close();
	db.Close();

	return code;
}
CString AccountBookForm::MakeCurrencyFormat(Currency currency)
{
	CString condition;
	condition.Format("%.0lf", currency);
	CString currencyFormat = "";
	CString comma = ",";
	Long i = 1;
	Long remainder;
	Long digit;
	Long dividend = static_cast<Long>(currency);
	while (dividend > 0) {
		digit = dividend % 10;
		currencyFormat.Format("%d%s", digit, (LPCTSTR)currencyFormat);
		remainder = i % 3;
		if (remainder == 0 && i < condition.GetLength()) {
			currencyFormat.Format("%s%s", (LPCTSTR)comma, (LPCTSTR)currencyFormat);
		}
		i++;
		dividend /= 10;
	}
	return currencyFormat;
}