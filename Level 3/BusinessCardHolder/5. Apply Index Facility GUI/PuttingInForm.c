#include "PuttingInForm.h"
#include "resource.h"
#include "BusinessCardHolder.h"
#include "IndexHolder.h"
#include "Index.h"
#include <stdio.h> //sprintf
#include <string.h>
#include <CommCtrl.h>

BOOL CALLBACK PuttingInFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (message) {
	case WM_INITDIALOG: ret = PuttingInForm_OnInitDialog(hWnd, wParam, lParam); break;
	case WM_COMMAND: ret = PuttingInForm_OnCommand(hWnd, wParam, lParam); break;
	case WM_CLOSE: ret = PuttingInForm_OnClose(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}

	return ret;
}
BOOL PuttingInForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	//1. 끼우기 윈도우가 생성될 때
	//1.1. 도메인 목록을 만든다.
	SendMessage(GetDlgItem(hWnd, IDC_COMBO_DOMAIN), CB_ADDSTRING, (WPARAM)0, (LPARAM)"naver.com");
	SendMessage(GetDlgItem(hWnd, IDC_COMBO_DOMAIN), CB_ADDSTRING, (WPARAM)0, (LPARAM)"gmail.com");
	SendMessage(GetDlgItem(hWnd, IDC_COMBO_DOMAIN), CB_ADDSTRING, (WPARAM)0, (LPARAM)"nate.com");
	SendMessage(GetDlgItem(hWnd, IDC_COMBO_DOMAIN), CB_ADDSTRING, (WPARAM)0, (LPARAM)"daum.net");
	//1.2. 직책 목록을 만든다.
	SendMessage(GetDlgItem(hWnd, IDC_COMBO_POSITION), CB_ADDSTRING, (WPARAM)0, (LPARAM)"사장");
	SendMessage(GetDlgItem(hWnd, IDC_COMBO_POSITION), CB_ADDSTRING, (WPARAM)0, (LPARAM)"부장");
	SendMessage(GetDlgItem(hWnd, IDC_COMBO_POSITION), CB_ADDSTRING, (WPARAM)0, (LPARAM)"과장");
	SendMessage(GetDlgItem(hWnd, IDC_COMBO_POSITION), CB_ADDSTRING, (WPARAM)0, (LPARAM)"대리");
	SendMessage(GetDlgItem(hWnd, IDC_COMBO_POSITION), CB_ADDSTRING, (WPARAM)0, (LPARAM)"사원");

	return TRUE;
}
BOOL PuttingInForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (LOWORD(wParam)) {
	case IDC_EDIT_COMPANY_NAME: ret = PuttingInForm_OnCompanyNameKillFocus(hWnd, wParam, lParam); break;
	case IDC_BUTTON_PUTIN: ret = PuttingInForm_OnPutInButtonClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}
BOOL PuttingInForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	//4. 닫기 버튼을 클릭했을 때
	//4.1. 끼우기 윈도우를 닫다.
	EndDialog(hWnd, 0);

	return TRUE;
}
BOOL PuttingInForm_OnCompanyNameKillFocus(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	TCHAR companyName[64];
	HWND businessCardHolderForm;
	BusinessCardHolder *businessCardHolder;
	BusinessCard *businessCardLink;
	IndexHolder *indexHolder;
	Index *indexLink;

	//2. 상호 에딧의 포커스를 잃었을 때
	if (HIWORD(wParam) == EN_KILLFOCUS) {
		//2.1. 상호를 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_NAME), WM_GETTEXT, (WPARAM)64, (LPARAM)companyName);
		//2.2. 명함첩 윈도우를 찾는다.
		businessCardHolderForm = FindWindow("#32770", "명함첩");
		businessCardHolder = (BusinessCardHolder*)GetWindowLong(businessCardHolderForm, GWL_USERDATA);
		indexHolder=(IndexHolder*)GetProp(businessCardHolderForm, "PROP_INDEXHOLDER");
		//2.3. 명함첩 윈도우의 색인첩에서 찾는다.
		indexLink = IndexHolder_Find(indexHolder, companyName);
		//2.4. 찾았으면 회사를 출력한다.
		if (indexLink != NULL) {
			businessCardLink = Index_GetAt(indexLink, 0);
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.address);
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.telephoneNumber);
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.faxNumber);
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.url);
		}
	}

	return TRUE;
}
BOOL PuttingInForm_OnPutInButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCard businessCard;
	TCHAR emailID[32];
	TCHAR domain[32];
	HWND businessCardHolderForm;
	BusinessCardHolder *businessCardHolder;
	BusinessCard *businessCardLink;
	IndexHolder *indexHolder;
	Index *indexLink;
	HTREEITEM hCompanies;
	HTREEITEM hCompany;
	TCHAR companyName[64];
	TVINSERTSTRUCT tvItem = { 0, };
	HTREEITEM hName;

	//3. 끼우기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {
		//3.1. 명함을 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_NAME), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.name);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_ADDRESS), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.address);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_TELEPHONENUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_FAXNUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_URL), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.url);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_PERSONAL_NAME), WM_GETTEXT, (WPARAM)11, (LPARAM)businessCard.personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_PERSONAL_TELEPHONENUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_PERSONAL_EMAILID), WM_GETTEXT, (WPARAM)32, (LPARAM)emailID);
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_DOMAIN), WM_GETTEXT, (WPARAM)32, (LPARAM)domain);
		sprintf(businessCard.personal.emailAddress, "%s@%s", emailID, domain);
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_POSITION), WM_GETTEXT, (WPARAM)16, (LPARAM)businessCard.personal.position);
		//3.2. 명함첩 윈도우를 찾는다.
		businessCardHolderForm = FindWindow("#32770", "명함첩");
		businessCardHolder = (BusinessCardHolder*)GetWindowLong(businessCardHolderForm, GWL_USERDATA);
		indexHolder = (IndexHolder*)GetProp(businessCardHolderForm, "PROP_INDEXHOLDER");
		//3.3. 명함첩 윈도우의 명함첩에 끼운다.
		businessCardLink = PutIn(businessCardHolder, businessCard);
		//3.4. 명함첩 윈도우에 명함을 출력한다.
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.name);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.address);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.telephoneNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.faxNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.url);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.name);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.telephoneNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.emailAddress);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.position);
		//3.5. 명함첩 윈도우의 명함첩에 끼운 명함의 위치를 읽는다.
		//3.6. 명함첩 윈도우의 색인첩에서 끼운다.
		indexLink = IndexHolder_PutIn(indexHolder, businessCardLink);
		//3.7. 명함첩 윈도우의 트리뷰 컨트롤의 회사들 항목을 찾는다.
		hCompanies = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)0);
		//3.8. 명함첩 윈도우의 트리뷰 컨트롤의 회사들 항목에서 상호 항목을 찾는다.
		hCompany = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompanies);
		tvItem.item.mask = TVIF_TEXT | TVIF_HANDLE;
		tvItem.item.hItem = hCompany;
		tvItem.item.pszText = companyName;
		tvItem.item.cchTextMax = 64;
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem.item);
		while (hCompany != NULL && strcmp(companyName, indexLink->name) != 0) {
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hCompany);
			tvItem.item.hItem = hCompany;
			SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem.item);
		}
		//3.9. 못찾았으면 명함첩 윈도우의 트리뷰 컨트롤의 회사들 항목에 상호 항목을 추가한다.
		if (hCompany == NULL) {
			tvItem.item.pszText = indexLink->name;
			tvItem.hParent = hCompanies;
			tvItem.hInsertAfter = TVI_SORT;
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tvItem);
		}
		//3.10. 명함첩 윈도우의 트리뷰 컨트롤의 상호 항목에 이름 항목을 추ㅏㄱ한다.
		tvItem.item.pszText = businessCardLink->personal.name;
		tvItem.hParent = hCompany;
		tvItem.hInsertAfter = TVI_LAST;
		hName = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tvItem);
		//3.11. 명함첩 윈도우의 트리뷰 컨트롤의 회사들 항목을 펼친다.
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)hCompanies);
		//3.12. 명함첩 윈도우의 트리뷰 컨트롤의 상호 항목을 펼친다.
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)hCompany);
		//3.13. 명함첩 윈도우의 트리뷰 컨트롤에서 추가한 이름 항목을 선택한다.
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)hName);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_DROPHILITE, (LPARAM)hName);
		//3.14. 끼우기 윈도우를 닫는다.
		EndDialog(hWnd, 0);
	}

	return TRUE;
}