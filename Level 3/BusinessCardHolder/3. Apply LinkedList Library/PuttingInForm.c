#include "PuttingInForm.h"
#include "resource.h"
#include "BusinessCardHolder.h"
#include <stdio.h> //sprintf

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
	BusinessCard *businessCard = NULL;

	//2. 상호 에딧의 포커스를 잃었을 때
	if (HIWORD(wParam) == EN_KILLFOCUS) {
		//2.1. 상호를 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_NAME), WM_GETTEXT, (WPARAM)64, (LPARAM)companyName);
		//2.2. 명함첩 윈도우를 찾는다.
		businessCardHolderForm = FindWindow("#32770", "명함첩");
		businessCardHolder = (BusinessCardHolder*)GetWindowLong(businessCardHolderForm, GWL_USERDATA);
		//2.3. 명함첩 윈도우의 명함첩에서 찾는다.

		businessCard = FindByCompanyName(businessCardHolder, companyName);
		//2.4. 찾았으면 회사를 출력한다.
		if (businessCard != NULL) {
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.address);
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.telephoneNumber);
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.faxNumber);
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.url);
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
	BusinessCard *index;

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
		//3.3. 명함첩 윈도우의 명함첩에 끼운다.
		index = PutIn(businessCardHolder, businessCard);
		//3.4. 명함첩 윈도우에 명함을 출력한다.
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.name);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.address);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.telephoneNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.faxNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.url);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.name);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.telephoneNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.emailAddress);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.position);
		//3.5. 끼우기 윈도우를 닫는다.
		EndDialog(hWnd, 0);
	}

	return TRUE;
}