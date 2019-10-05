#include "PuttingOutForm.h"
#include "BusinessCardHolder.h"
#include "resource.h"
#include "Index.h"
#include "IndexHolder.h"
#include <Commctrl.h>


BOOL CALLBACK PuttingOutFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (message) {
	case WM_INITDIALOG: ret = PuttingOutForm_OnInitDialog(hWnd, wParam, lParam); break;
	case WM_CLOSE: ret = PuttingOutForm_OnClose(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}

	return ret;
}
BOOL PuttingOutForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	HWND businessCardHolderForm;
	BusinessCardHolder *businessCardHolder;
	BusinessCard businessCard;
	BusinessCard *businessCardLink;
	IndexHolder *indexHolder;
	Index *indexLink;
	HTREEITEM hName;
	HTREEITEM hCompany;
	HTREEITEM hCompanies;
	Long location;
	TVITEM tvi = { 0, };
	TCHAR companyName[64];
	Long i;

	//1. 들어내기 윈도우가 생성될 때
	//1.1. 명함첩 윈도우를 찾는다.
	businessCardHolderForm = FindWindow("#32770", "명함첩");
	businessCardHolder = (BusinessCardHolder*)GetWindowLong(businessCardHolderForm, GWL_USERDATA);
	//1.2. 명함첩 윈도우의 명함첩에서 들어낼 명함의 위치를 읽는다.
	businessCardLink = businessCardHolder->current;
	//1.3. 명함첩 윈도우의 명함첩에서 명함을 들어내다.
	businessCard = PutOut(businessCardHolder, businessCardLink);
	//1.4. 들어내기 윈도우에 명함을 출력한다.
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.name);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.address);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.telephoneNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.faxNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.url);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.name);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.telephoneNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.emailAddress);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.position);
	//1.5. 들어낼 명함의 상호를 읽는다.
	//1.6. 명함첩 윈도우의 색인첩에서 색인을 들어낸다.
	indexHolder = (IndexHolder*)GetProp(businessCardHolderForm, "PROP_INDEXHOLDER");
	indexLink = IndexHolder_PutOut(indexHolder, businessCard.company.name, businessCardLink);
	//1.7. 명함첩 윈도우의 트리뷰 컨트롤에서 선택된 이름항목을 읽는다.
	hName = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETNEXTITEM,
		(WPARAM)TVGN_CARET, (LPARAM)0);
	//1.8. 명함첩 윈도우의 색인첩에서 색인을 들어냈으면
	if (indexLink == NULL) {
		//1.8.1. 트리뷰 컨트롤의 선택된 이름 항목의 상위 항목을 읽는다.
		hCompany = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_PARENT, (LPARAM)hName);
		//1.8.2. 트리뷰 컨트롤의 상위항목을 지운다.
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_DELETEITEM,
			(WPARAM)0, (LPARAM)hCompany);
	}
	else { // 1.9. 명함첩윈도우의 색인첩에서 색인을 들어내지 않았으면 트리뷰 컨트롤의 선택된 이름항목을 지운다.
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_DELETEITEM,
			(WPARAM)0, (LPARAM)hName);
	}
	//1.10. 명함첩 윈도우의 명함이 있으면
	if (businessCardHolder->length > 0) {
		businessCardLink = businessCardHolder->current;
		//1.10.1. 명함첩 윈도우의 명함을 출력한다.
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.name);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.address);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.telephoneNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.faxNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.url);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.name);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.telephoneNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.emailAddress);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.position);
	
		//1.10.2. 명함첩 윈도우의 명함의 위치를 읽는다.
		//1.10.3. 명함의 상호를 읽는다.
		//1.10.4. 명함의 윈도우의 색인첩에서 찾는다
		indexLink = IndexHolder_Find(indexHolder, businessCardLink->company.name);
		//1.10.5. 찾은 색인에서 명함의 위치를 찾는다.
		location = Index_Find(indexLink, businessCardLink);
		//1.10.6. 명함첩 윈도우의 트리뷰 컨트롤에서 회사들 항목을 찾는다.
		hCompanies = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX),
			TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)0);
		//1.10.7. 명함첩 윈도우의 트리뷰 컨트롤에서 상호 항목을 찾다.
		hCompany = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hCompanies);
		tvi.mask = TVIF_TEXT | TVIF_HANDLE;
		tvi.hItem = hCompany;
		tvi.pszText = companyName;
		tvi.cchTextMax = 64;
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETITEM,
			(WPARAM)0, (LPARAM)&tvi);
		while (hCompany != NULL && strcmp(companyName, indexLink->name) != 0) {
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hCompany);
			tvi.hItem = hCompany;
			SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETITEM,
				(WPARAM)0, (LPARAM)&tvi);
		}
		//1.10.8. 명함첩 윈도우의 트리뷰 컨트롤의 상호항목에서 이름 항목을 찾는다.
		hName = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hCompany);
		i = 0;
		while (i < location) {
			hName = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hName);
			i++;
		}
		//1.10.9 트리뷰 컨트롤의 회사들을 펼친다.
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hCompanies);
		//1.10.10 트리뷰 컨트롤의 회사들에서 상호항목을 펼치다.
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hCompany);
		//1.10.11 트리뷰 컨트롤의 상호에서 이름을 선택한다.
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)hName);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_DROPHILITE,
			(LPARAM)hName);
	}
	else {	//1.5. 명함첩 윈도우의 명함첩에 명함이 없으면 공란을 출력한다.
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
	}
	return TRUE;
}
BOOL PuttingOutForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	int ret;
	BusinessCard businessCard;
	HWND businessCardHolderForm;
	BusinessCardHolder *businessCardHolder;
	IndexHolder *indexHolder;
	Index *indexLink;
	BusinessCard *businessCardLink;
	TVITEM tvi = { 0, };
	TVINSERTSTRUCT tvins = { 0, };
	HTREEITEM hCompanies;
	HTREEITEM hCompany;
	HTREEITEM hName;
	TCHAR companyName[64];
	

	//2. 닫기 버튼을 클릭했을 때
	//2.1. 메시지 박스를 출력한다.
	ret = MessageBox(hWnd, (LPCWSTR)"끼우시겠습니까?", (LPCWSTR)"끼우기", MB_YESNOCANCEL);
	switch (ret) {
		//2.2. 예 버튼을 클릭했을 때
	case IDYES:
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.url);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_GETTEXT, (WPARAM)11, (LPARAM)businessCard.personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_GETTEXT, (WPARAM)16, (LPARAM)businessCard.personal.position);
		//2.2.1. 명함첩 윈도우를 찾는다.
		businessCardHolderForm = FindWindow("#32770", "명함첩");
		businessCardHolder = (BusinessCardHolder*)GetWindowLong(businessCardHolderForm, GWL_USERDATA);
		indexHolder = (IndexHolder *)GetProp(businessCardHolderForm, "PROP_INDEXHOLDER");
		//2.2.2. 명함첩 윈도우의 명함첩에 끼운다.
		businessCardLink = PutIn(businessCardHolder, businessCard);
		//2.2.3. 명함첩 윈도우에 명함을 출력한다.
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.name);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.address);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.telephoneNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.faxNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.url);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.name);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.telephoneNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.emailAddress);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.position);
		//2.2.4. 명함첩 윈도우의 명함첩에 끼운 명함의 위치를 읽는다.
		//2.2.5. 명함첩 윈도우의 색인첩에 색인을 끼운다.
		indexLink = IndexHolder_PutIn(indexHolder, businessCardLink);
		//2.2.6. 명함첩윈도우의 트리뷰 컨트롤에서 회사들 항목을 찾는다.
		hCompanies = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX),
			TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)0);
		//2.2.7. 명함첩 윈도우의 트리뷰 컨트롤의 회사들 항목에서 상호 항목을 찾는다.
		hCompany = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hCompanies);
		tvi.mask = TVIF_TEXT | TVIF_HANDLE;
		tvi.hItem = hCompany;
		tvi.pszText = companyName;
		tvi.cchTextMax = 64;
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETITEM,
			(WPARAM)0, (LPARAM)&tvi);
		while (hCompany != NULL && strcmp(companyName, indexLink->name) != 0) {
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hCompany);
			tvi.hItem = hCompany;
			SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETITEM,
				(WPARAM)0, (LPARAM)&tvi);
		}
		tvins.item.mask = TVIF_TEXT | TVIF_HANDLE;
		//2.2.8. 못 찾았으면 트리뷰 컨트롤의 회사들 항목에 상호항목을 추가한다.
		if (hCompany == NULL) {
			tvins.item.pszText = indexLink->name;
			tvins.hParent = hCompanies;
			tvins.hInsertAfter = TVI_SORT;
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_INSERTITEM,
				(WPARAM)0, (LPARAM)&tvins);
		}
		//2.2.9. 명함첩 윈도우의 트리뷰 컨트롤의 상호항목에 이름을 추가한다.
		tvins.item.pszText = businessCardLink->personal.name;
		tvins.hParent = hCompany;
		tvins.hInsertAfter = TVI_LAST;
		hName = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_INSERTITEM,
			(WPARAM)0, (LPARAM)&tvins);

	   // 트리뷰 컨트롤의 회사들을 펼친다.
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hCompanies);
		// 트리뷰 컨트롤의 회사들에서 상호항목을 펼치다.
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hCompany);
		// 트리뷰 컨트롤의 상호에서 이름을 선택한다.
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)hName);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_DROPHILITE,
			(LPARAM)hName);
	
		//2.13 들어내기 윈도우를 닫는다.
		EndDialog(hWnd, 0);
		break;
		//2.3. 아니오 버튼을 클릭했을 때
	case IDNO:
		//2.3.1. 들어내기 윈도우를 닫는다.
		EndDialog(hWnd, 0);
		break;
	default:
		break;
	}

	return TRUE;
}