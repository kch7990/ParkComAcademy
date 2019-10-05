//UpdatingForm.cpp
#include "UpdatingForm.h"
#include "FindingForm.h"
#include <afxcmn.h>
#include "AddressBook.h"

BEGIN_MESSAGE_MAP(UpdatingForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_RECORD, OnRecordButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_CORRECT, OnCorrectButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_ERASE, OnEraseButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_ARRANGE, OnArrangeButtonClicked)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PERSONALS, OnListViewItemDoubleClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

UpdatingForm::UpdatingForm(CWnd *parent)
	:CDialog(UpdatingForm::IDD, parent) {
	this->addressBook = NULL;
}

BOOL UpdatingForm::OnInitDialog() {
	CDialog::OnInitDialog(); //Overriding
	this->addressBook = new AddressBook(10000); //주소록을 만든다.

	//리스트뷰 컨트롤의 헤더를 만든다.
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(
		0, "번호", LVCFMT_LEFT, 50);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(
		1, "성명", LVCFMT_LEFT, 100);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(
		2, "주소", LVCFMT_LEFT, 250);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(
		3, "전화번호", LVCFMT_LEFT, 150);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(
		4, "이메일주소", LVCFMT_LEFT, 200);

	//리스트뷰 컨트롤에 전체 선택을 설정한다.
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//적재하다.
	Load();

	//적재되었으면 적재한 만큼 리스트뷰 컨트롤에 항목들을 추가한다.
	CString name;
	CString address;
	CString telephoneNumber;
	CString emailAddress;
	Long i = 0;
	while (i < this->addressBook->GetLength()) {
		CString number;
		number.Format("%d", i + 1);
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertItem(i, number);
		Personal personal = this->addressBook->GetAt(i);
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

	return FALSE;
}
void UpdatingForm::OnRecordButtonClicked() {
	CString name;
	CString address;
	CString telephoneNumber;
	CString emailAddress;
	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(name);
	GetDlgItem(IDC_EDIT_ADDRESS)->GetWindowText(address);
	GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->GetWindowText(telephoneNumber);
	GetDlgItem(IDC_EDIT_EMAILADDRESS)->GetWindowText(emailAddress);
	Long index = this->addressBook->Record((LPCSTR)name, (LPCSTR)address,
		(LPCSTR)telephoneNumber, (LPCSTR)emailAddress);

	Insert(index);

	CString number;
	number.Format("%d", index + 1);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertItem(index, number);
	Personal personal = this->addressBook->GetAt(index);
	name = CString(personal.GetName().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 1, name);

	address = CString(personal.GetAddress().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 2, address);

	telephoneNumber = CString(personal.GetTelephoneNumber().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 3, telephoneNumber);

	emailAddress = CString(personal.GetEmailAddress().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 4, emailAddress);
}
void UpdatingForm::OnFindButtonClicked() {
	FindingForm findingForm;
	findingForm.DoModal();
}
void UpdatingForm::OnCorrectButtonClicked() {
	CString address;
	CString telephoneNumber;
	CString emailAddress;

	GetDlgItem(IDC_EDIT_ADDRESS)->GetWindowText(address);
	GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->GetWindowText(telephoneNumber);
	GetDlgItem(IDC_EDIT_EMAILADDRESS)->GetWindowText(emailAddress);
	Long index = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetSelectionMark();
	index = this->addressBook->Correct(index, (LPCSTR)address, (LPCSTR)telephoneNumber,
		(LPCSTR)emailAddress);

	Modify(index);

	Personal personal = this->addressBook->GetAt(index);
	address = CString(personal.GetAddress().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 2, address);

	telephoneNumber = CString(personal.GetTelephoneNumber().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 3, telephoneNumber);

	emailAddress = CString(personal.GetEmailAddress().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 4, emailAddress);

}
void UpdatingForm::OnEraseButtonClicked() {
	CString number;
	Long index = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetSelectionMark();
	this->addressBook->Erase(index);

	Delete(index);

	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->DeleteItem(index);

	while (index < this->addressBook->GetLength()) {
		number.Format("%d", index + 1);
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 0, number);
		index++;
	}
}
void UpdatingForm::OnArrangeButtonClicked() {
	Long i = 0;
	Personal personal;
	CString number;
	CString name;
	CString address;
	CString telephoneNumber;
	CString emailAddress;

	this->addressBook->Arrange();
	this->Save();
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->DeleteAllItems();
	while (i < this->addressBook->GetLength()) {
		personal = this->addressBook->GetAt(i);
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
void UpdatingForm::OnListViewItemDoubleClicked(
	NMHDR *pNotifyStruct, LRESULT *result) {
	Long index = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetSelectionMark();
	CString name = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 1);
	CString address = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 2);
	CString telephoneNumber = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 3);
	CString emailAddress = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 4);

	GetDlgItem(IDC_EDIT_NAME)->SetWindowText(name);
	GetDlgItem(IDC_EDIT_ADDRESS)->SetWindowText(address);
	GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->SetWindowText(telephoneNumber);
	GetDlgItem(IDC_EDIT_EMAILADDRESS)->SetWindowText(emailAddress);
}
void UpdatingForm::OnClose() {
	if (this->addressBook != NULL) {
		this->Save();
		delete this->addressBook;
	}
	EndDialog(0);
}

#include <afxdb.h>

void UpdatingForm::Load() {
	CDatabase db; //Connection, INSERT, DELETE, MODIFY Request, Disconnection
	CRecordset rs(&db); //SELECT Request/Response
	CString sql = "SELECT Personal.name, Personal.address, Personal.telephoneNumber, Personal.emailAddress FROM Personal;";
	db.OpenEx("DSN=AddressBook;UID=root;PWD=preta27531@;"); //Connection
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql); //SELECT Request/Response
	CString name;
	CString address;
	CString telephoneNumber;
	CString emailAddress;
	while (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, name);
		rs.GetFieldValue((short)1, address);
		rs.GetFieldValue((short)2, telephoneNumber);
		rs.GetFieldValue((short)3, emailAddress);
		this->addressBook->Record((LPCTSTR)name, (LPCTSTR)address, (LPCTSTR)telephoneNumber, (LPCTSTR)emailAddress);
		rs.MoveNext();
	}
	rs.Close(); //Disconnection
	db.Close(); //Disconnection
}
void UpdatingForm::Save() {
	CDatabase db;
	CRecordset rs(&db);
	Long i = 0;
	Personal personal;
	CString code;
	int codeNumber;

	CString sql = "SELECT Personal.code FROM Personal;";
	db.OpenEx("DSN=AddressBook;UID=root;PWD=preta27531@"); //Connection
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql); //SELECT Request/Response
	sql.Format("DELETE FROM Personal;");
	db.ExecuteSQL(sql); //DELETE Request

	while (!rs.IsEOF()) {
		personal = this->addressBook->GetAt(i);
		rs.GetFieldValue((short)0, code);  //디스크 파일에서 코드를 가져온다.
		sql.Format("INSERT INTO Personal(code, name, address, telephoneNumber, emailAddress) VALUES('%s', '%s', '%s', '%s', '%s');",
			(LPCTSTR)code, personal.GetName().c_str(), personal.GetAddress().c_str(), personal.GetTelephoneNumber().c_str(), personal.GetEmailAddress().c_str());
		db.ExecuteSQL(sql); //INSERT Request
		i++;
		rs.MoveNext();
	}
	rs.Close();
	db.Close();
}
void UpdatingForm::Insert(Long index) {
	Personal personal = this->addressBook->GetAt(index);
	CString code = MakeCode();
	CDatabase db;
	CString sql;
	sql.Format("INSERT INTO Personal(code, name, address, telephoneNumber, emailAddress) VALUES('%s', '%s', '%s', '%s', '%s');",
		(LPCTSTR)code, personal.GetName().c_str(), personal.GetAddress().c_str(), personal.GetTelephoneNumber().c_str(), personal.GetEmailAddress().c_str());
	db.OpenEx("DSN=AddressBook;UID=root;PWD=preta27531@");
	db.ExecuteSQL(sql);
	db.Close();
}
void UpdatingForm::Delete(Long index) {
	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Personal.code FROM Personal;";  //SELECT Request/Response
	CString code;
	db.OpenEx("DSN=AddressBook;UID=root;PWD=preta27531@"); //Connection
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql); //SELECT Request/Response
	rs.Move(index);
	rs.GetFieldValue((short)0, code);
	sql.Format("DELETE FROM Personal WHERE code='%s'", (LPCTSTR)code);
	db.ExecuteSQL(sql); //DELETE Request
	
	rs.Close(); //Disconnection
	db.Close(); //Disconnection
}
void UpdatingForm::Modify(Long index) {
	Personal personal = this->addressBook->GetAt(index);
	CDatabase db;
	CRecordset rs(&db);
	CString code;
	CString sql = "SELECT Personal.code FROM Personal;";
	db.OpenEx("DSN=AddressBook;UID=root;PWD=preta27531@"); //Connection
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql); //SELECT Request/Response
	
	rs.Move(index);
	rs.GetFieldValue((short)0, code);
	sql.Format("UPDATE Personal SET address='%s', telephoneNumber='%s', emailAddress='%s' WHERE Personal.code='%s';",
		personal.GetAddress().c_str(), personal.GetTelephoneNumber().c_str(), personal.GetEmailAddress().c_str(), (LPCTSTR)code);
	db.ExecuteSQL(sql); //UPDATE Request

	rs.Close(); //Disconnection
	db.Close(); //Disconnection
}
CString UpdatingForm::MakeCode() {
	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Personal.code FROM Personal ORDER BY code DESC;";
	CString code = "P0001";
	int codeNumber;

	db.OpenEx("DSN=AddressBook;UID=root;PWD=preta27531@"); //Connection
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql); //SELECT Request/Response

	if (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, code);  //디스크 파일에서 코드를 가져온다.
		code.Remove('P'); //가져온 코드에서 P를 제거한다.
		codeNumber = atoi((LPCTSTR)code); //P를 제거한 코드를 정수형으로 바꾼다.
		code.Format("P%04d", codeNumber + 1); //코드를 만든다.
	}
	rs.Close(); //Disconnection
	db.Close(); //Disconnection
	
	return code;
}