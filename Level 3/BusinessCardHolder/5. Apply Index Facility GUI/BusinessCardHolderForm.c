// BusinessCardHolderForm.c
#include "BusinessCardHolderForm.h"
#include "PuttingInForm.h"
#include "FindingForm.h"
#include "PuttingOutForm.h"
#include "resource.h"
#include "BusinessCardHolder.h"
#include "IndexHolder.h"
#include "Index.h"
#include <stdlib.h>
#include <CommCtrl.h>
#include <string.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	int response = DialogBox(hInstance, MAKEINTRESOURCE(IDD_BUSINESSCARDHOLDERFORM), NULL, BusinessCardHolderFormProc);

	return response;
}

BOOL CALLBACK BusinessCardHolderFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;

	switch (message)
	{
	case WM_INITDIALOG:
		ret = BusinessCardHolderForm_OnInitDialog(hWnd, wParam, lParam);
		break;
	case WM_COMMAND:
		ret = BusinessCardHolderForm_OnCommand(hWnd, wParam, lParam);
		break;
	case WM_NOTIFY:
		ret = BusinessCardHolderForm_OnNotify(hWnd, wParam, lParam);
		break;
	case WM_CLOSE:
		ret = BusinessCardHolderForm_OnClose(hWnd, wParam, lParam);
		break;
	default:
		ret = FALSE;
		break;
	}

	return ret;
}

BOOL BusinessCardHolderForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BusinessCardHolder *businessCardHolder;
	IndexHolder *indexHolder;
	Long count;
	BusinessCard *businessCardLink;
	Index *indexLink;
	Long i;
	Long j;
	Index(*indexes);
	Long countIndex;
	Long location;
	BusinessCard *previous = NULL;
	TVINSERTSTRUCT tvItem = { 0, };
	HTREEITEM hCompanies;
	HTREEITEM hCompany;
	HTREEITEM hName;
	TCHAR companyName[64];

	//1. 윈도우가 생성될 때
	//1.1. 명함첩을 생성하다.
	businessCardHolder = (BusinessCardHolder*)malloc(sizeof(BusinessCardHolder));
	BusinessCardHolder_Create(businessCardHolder);
	SetWindowLong(hWnd, GWL_USERDATA, (LONG)businessCardHolder);

	//1.2. 색인첩을 생성하다.
	indexHolder = (IndexHolder*)malloc(sizeof(IndexHolder));
	IndexHolder_Create(indexHolder);
	SetProp(hWnd, "PROP_INDEXHOLDER", (HANDLE)indexHolder);

	//1.6. 트리뷰 컨트롤에서 회사들 항목을 추가하다.
	tvItem.item.mask = TVIF_TEXT | TVIF_HANDLE;
	tvItem.item.pszText = "회사들";
	tvItem.hInsertAfter = TVI_ROOT;
	hCompanies = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tvItem);

	//1.3. 명함첩을 적재하다.
	count = Load(businessCardHolder);

	if (count > 0) {
		//1.4. 적재된 만큼 색인첩에 색인을 끼운다.
		businessCardLink = BusinessCardHolder_First(businessCardHolder);
		while (businessCardLink != previous) {
			indexLink = IndexHolder_PutIn(indexHolder, businessCardLink);
			previous = businessCardLink;
			businessCardLink = BusinessCardHolder_Next(businessCardHolder);
		}
		//1.5. 색인첩에서 색인 리스트를 만든다.
		IndexHolder_MakeList(indexHolder, &indexes, &countIndex);
		//1.7. 색인 수만큼 반복한다.
		i = 0;
		while (i < countIndex) {
			//1.7.1. 트리뷰 컨트롤에서 회사들 항목의 자식으로 상호를 추가하다.
			indexLink = indexes + i;
			tvItem.item.pszText = indexLink->name;
			tvItem.hParent = hCompanies;
			tvItem.hInsertAfter = TVI_LAST;
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tvItem);
			//1.7.2. 트리뷰 컨트롤에서 상호 항목의 자식으로 명함 수만큼 이름을 추가하다.
			j = 0;
			while (j < indexLink->length) {
				businessCardLink = Index_GetAt(indexLink, j);
				tvItem.item.pszText = businessCardLink->personal.name;
				tvItem.hParent = hCompany;
				tvItem.hInsertAfter = TVI_LAST;
				SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tvItem);
				j++;
			}
			i++;
		}
		//1.8. 명함첩에서 처음으로 이동한다.
		businessCardLink = BusinessCardHolder_First(businessCardHolder);
		//1.9. 명함을 출력하다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.url);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.position);

		//1.10. 색인첩에서 처음 명함의 색인을 찾다.
		indexLink = IndexHolder_Find(indexHolder, businessCardLink->company.name);
		//1.11. 색인에서 처음 명함의 위치를 찾다.
		location = Index_Find(indexLink, businessCardLink);
		//1.12. 트리뷰 컨트롤에서 회사들 항목을 찾다.
		hCompanies = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)0);
		//1.13. 트리뷰 컨트롤의 회사들 항목에서 상호 항목을 찾는다.
		hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompanies);
		tvItem.item.hItem = hCompany;
		tvItem.item.pszText = companyName;
		tvItem.item.cchTextMax = 64;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem.item);
		while (hCompany != NULL && strcmp(companyName, indexLink->name) != 0) {
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hCompany);
			tvItem.item.hItem = hCompany;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem.item);
		}
		//1.14. 트리뷰 컨트롤의 상호 항목에서 이름 항목을 찾다.
		hName = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompany);
		i = 0;
		while (i < location) {
			hName = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hName);
			i++;
		}
		//1.15. 트리뷰 컨트롤의 회사들을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)hCompanies);
		//1.16. 트리뷰 컨트롤의 상호 항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)hCompany);
		//1.17. 트리뷰 컨트롤에서 이름 항목을 선택한다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)hName);
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_DROPHILITE, (LPARAM)hName);

		if (indexes != NULL) {
			free(indexes);
		}
	}

	return TRUE;
}

BOOL BusinessCardHolderForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;

	switch (LOWORD(wParam))
	{
	case IDC_BUTTON_PUTIN:
		ret = BusinessCardHolderForm_OnPutInButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_FIND:
		ret = BusinessCardHolderForm_OnFindButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_PUTOUT:
		ret = BusinessCardHolderForm_OnPutOutButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_ARRANGE:
		ret = BusinessCardHolderForm_OnArrangeButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_FIRST:
		ret = BusinessCardHolderForm_OnFirstButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_PREVIOUS:
		ret = BusinessCardHolderForm_OnPreviousButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_NEXT:
		ret = BusinessCardHolderForm_OnNextButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_LAST:
		BusinessCardHolderForm_OnLastButtonClicked(hWnd, wParam, lParam);
		break;
	default:
		ret = FALSE;
		break;
	}

	return TRUE;
}
BOOL BusinessCardHolderForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (wParam) {
	case IDC_TREE_INDEX: ret = BusinessCardHolderForm_OnTreeViewNameItemDoubleClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}

	return ret;
}
BOOL BusinessCardHolderForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BusinessCardHolder *businessCardHolder;
	IndexHolder *indexHolder;

	businessCardHolder = (BusinessCardHolder*)GetWindowLong(hWnd, GWL_USERDATA);
	indexHolder = (IndexHolder*)GetProp(hWnd, "PROP_INDEXHOLDER");

	//색인첩을 지우다.
	if (indexHolder != NULL) {
		IndexHolder_Destroy(indexHolder);
		free(indexHolder);
	}
	if (businessCardHolder != NULL)
	{
		Save(businessCardHolder);
		BusinessCardHolder_Destroy(businessCardHolder);
		free(businessCardHolder);
	}

	RemoveProp(hWnd, "PROP_INDEXHOLDER");

	EndDialog(hWnd, 0);

	return TRUE;
}

BOOL BusinessCardHolderForm_OnPutInButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if (HIWORD(wParam) == BN_CLICKED)
	{
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_PUTTINGINFORM), NULL, PuttingInFormProc);
	}

	return TRUE;
}

BOOL BusinessCardHolderForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if (HIWORD(wParam) == BN_CLICKED)
	{
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_FINDINGFORM), NULL, FindingFormProc);
	}

	return TRUE;
}

BOOL BusinessCardHolderForm_OnPutOutButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if (HIWORD(wParam) == BN_CLICKED)
	{
		DialogBox((HINSTANCE)GetWindow(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_PUTTINGOUTFORM), NULL, PuttingOutFormProc);
	}

	return TRUE;
}

BOOL BusinessCardHolderForm_OnArrangeButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BusinessCardHolder *businessCardHolder;
	IndexHolder *indexHolder;
	BusinessCard *businessCardLink;
	BusinessCard *previous = NULL;
	Long i;
	Long j;
	Index(*indexes);
	Index *indexLink;
	Long indexCount;
	Long location;
	TVINSERTSTRUCT tvItem = { 0, };
	HTREEITEM hCompanies;
	HTREEITEM hCompany;
	HTREEITEM hName;
	TCHAR companyName[64];

	//5. 정리하기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		businessCardHolder = (BusinessCardHolder*)GetWindowLong(hWnd, GWL_USERDATA);
		indexHolder = (IndexHolder*)GetProp(hWnd, "PROP_INDEXHOLDER");
		//5.1. 색인첩에서 정리하다.
		IndexHolder_Arrange(indexHolder);
		//5.2. 트리뷰 컨트롤의 모든 항목을 지우다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_DELETEITEM, (WPARAM)0, (LPARAM)TVGN_ROOT);
		//5.3. 트리뷰 컨트롤에서 회사들 항목을 추가하다.
		tvItem.item.mask = TVIF_TEXT | TVIF_HANDLE;
		tvItem.item.pszText = "회사들";
		tvItem.hInsertAfter = TVI_FIRST;
		tvItem.hParent = TVI_ROOT;
		hCompanies = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tvItem);
		//5.4. 색인첩에서 색인리스트를 만들다.
		IndexHolder_MakeList(indexHolder, &indexes, &indexCount);
		//5.5. 색인 수만큼 반복하다.
		i = 0;
		while (i < indexCount) {
			//5.5.1. 트리뷰 컨트롤의 회사들 항목에서 상호를 추가하다.
			indexLink = indexes + i;
			tvItem.item.pszText = indexLink->name;
			tvItem.hParent = hCompanies;
			tvItem.hInsertAfter = TVI_LAST;
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tvItem);
			//5.5.2. 트리뷰 컨트롤의 상호 항목에 명함 수만큼 이름을 추가하다.
			j = 0;
			while (j < indexLink->length) {
				businessCardLink = Index_GetAt(indexLink, j);
				tvItem.item.pszText = businessCardLink->personal.name;
				tvItem.hParent = hCompany;
				tvItem.hInsertAfter = TVI_LAST;
				SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tvItem);
				j++;
			}
			i++;
		}
		//5.6. 처음 명함으로 이동하다.
		businessCardLink = BusinessCardHolder_First(businessCardHolder);
		//5.7. 명함을 출력하다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.url);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.position);
		//5.8. 색인첩에서 색인을 찾다.
		indexLink = IndexHolder_Find(indexHolder, businessCardLink->company.name);
		//5.9. 색인에서 명함의 위치를 찾다.
		location = Index_Find(indexLink, businessCardLink);
		//5.10. 트리뷰 컨트롤에서 회사들 항목을 찾다.

		//5.11. 트리뷰 컨트롤의 회사들 항목에서 상호를 찾다.
		hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompanies);
		tvItem.item.hItem = hCompany;
		tvItem.item.pszText = companyName;
		tvItem.item.cchTextMax = 64;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem.item);
		while (hCompany != NULL && strcmp(companyName, indexLink->name) != 0) {
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hCompany);
			tvItem.item.hItem = hCompany;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem.item);
		}
		//5.12. 트리뷰 컨트롤의 상호 항목에서 이름 항목을 찾다.
		hName = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompany);
		i = 0;
		while (i < location) {
			hName = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hName);
			i++;
		}
		//5.13. 트리뷰 컨트롤의 회사들을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)hCompanies);
		//5.14. 트리뷰 컨트롤의 상호 항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)hCompany);
		//5.15. 트리뷰 컨트롤에서 이름 항목을 선택한다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)hName);
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_DROPHILITE, (LPARAM)hName);

		if (indexes != NULL) {
			free(indexes);
		}
	}
	return TRUE;
}

BOOL BusinessCardHolderForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BusinessCardHolder * businessCardHolder;
	BusinessCard *businessCardLink;
	IndexHolder *indexHolder;
	Index *indexLink;
	Long location;
	HTREEITEM hCompanies;
	HTREEITEM hCompany;
	HTREEITEM hName;
	Long i;
	TCHAR companyName[64];
	TVINSERTSTRUCT tvItem = { 0, };

	//6. 처음 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		businessCardHolder = (BusinessCardHolder*)GetWindowLong(hWnd, GWL_USERDATA);
		indexHolder = (IndexHolder*)GetProp(hWnd, "PROP_INDEXHOLDER");
		//6.1. 명함첩에서 처음으로 이동하다.
		businessCardLink = BusinessCardHolder_First(businessCardHolder);
		//6.2. 명함을 출력하다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.url);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.position);
		//6.3. 색인첩에서 색인을 찾다.
		indexLink = IndexHolder_Find(indexHolder, businessCardLink->company.name);
		//6.4. 찾은 색인에서 명함의 위치를 찾다.
		location = Index_Find(indexLink, businessCardLink);
		//6.5. 트리뷰 컨트롤에서 회사들 항목을 찾는다.
		hCompanies = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)0);
		//6.6. 트리뷰 컨트롤의 회사들 항목에서 상호 항목을 찾는다.
		hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompanies);
		tvItem.item.mask = TVIF_TEXT | TVIF_HANDLE;
		tvItem.item.hItem = hCompany;
		tvItem.item.pszText = companyName;
		tvItem.item.cchTextMax = 64;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem.item);
		while (hCompany != NULL && strcmp(companyName, indexLink->name) != 0) {
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hCompany);
			tvItem.item.hItem = hCompany;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem.item);
		}
		//6.7. 트리뷰 컨트롤의 상호 항목에서 이름 항목을 찾다.
		hName = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompany);
		i = 0;
		while (i < location) {
			hName = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hName);
			i++;
		}
		//6.8. 트리뷰 컨트롤의 회사들을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)hCompanies);
		//6.9. 트리뷰 컨트롤의 상호 항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)hCompany);
		//6.10. 트리뷰 컨트롤에서 이름 항목을 선택한다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)hName);
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_DROPHILITE, (LPARAM)hName);

	}

	return TRUE;
}

BOOL BusinessCardHolderForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BusinessCardHolder * businessCardHolder;
	BusinessCard *businessCardLink;
	IndexHolder *indexHolder;
	Index *indexLink;
	Long location;
	HTREEITEM hCompanies;
	HTREEITEM hCompany;
	HTREEITEM hName;
	Long i;
	TCHAR companyName[64];
	TVINSERTSTRUCT tvItem = { 0, };

	//7. 이전 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		businessCardHolder = (BusinessCardHolder*)GetWindowLong(hWnd, GWL_USERDATA);
		indexHolder = (IndexHolder*)GetProp(hWnd, "PROP_INDEXHOLDER");
		//7.1. 명함첩에서 이전으로 이동하다.
		businessCardLink = BusinessCardHolder_Previous(businessCardHolder);
		//7.2. 명함을 출력하다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.url);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.position);
		//7.3. 색인첩에서 색인을 찾다.
		indexLink = IndexHolder_Find(indexHolder, businessCardLink->company.name);
		//7.4. 찾은 색인에서 명함의 위치를 찾다.
		location = Index_Find(indexLink, businessCardLink);
		//7.5. 트리뷰 컨트롤에서 회사들 항목을 찾는다.
		hCompanies = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)0);
		//7.6. 트리뷰 컨트롤의 회사들 항목에서 상호 항목을 찾는다.
		hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompanies);
		tvItem.item.mask = TVIF_TEXT | TVIF_HANDLE;
		tvItem.item.hItem = hCompany;
		tvItem.item.pszText = companyName;
		tvItem.item.cchTextMax = 64;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem.item);
		while (hCompany != NULL && strcmp(companyName, indexLink->name) != 0) {
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hCompany);
			tvItem.item.hItem = hCompany;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem.item);
		}
		//7.7. 트리뷰 컨트롤의 상호 항목에서 이름 항목을 찾다.
		hName = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompany);
		i = 0;
		while (i < location) {
			hName = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hName);
			i++;
		}
		//7.8. 트리뷰 컨트롤의 회사들을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)hCompanies);
		//7.9. 트리뷰 컨트롤의 상호 항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)hCompany);
		//7.10. 트리뷰 컨트롤에서 이름 항목을 선택한다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)hName);
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_DROPHILITE, (LPARAM)hName);

	}
	return TRUE;
}

BOOL BusinessCardHolderForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BusinessCardHolder * businessCardHolder;
	BusinessCard *businessCardLink;
	IndexHolder *indexHolder;
	Index *indexLink;
	Long location;
	HTREEITEM hCompanies;
	HTREEITEM hCompany;
	HTREEITEM hName;
	Long i;
	TCHAR companyName[64];
	TVINSERTSTRUCT tvItem = { 0, };

	//8. 다음 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		businessCardHolder = (BusinessCardHolder*)GetWindowLong(hWnd, GWL_USERDATA);
		indexHolder = (IndexHolder*)GetProp(hWnd, "PROP_INDEXHOLDER");
		//8.1. 명함첩에서 다음으로 이동하다.
		businessCardLink = BusinessCardHolder_Next(businessCardHolder);
		//8.2. 명함을 출력하다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.url);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.position);
		//8.3. 색인첩에서 색인을 찾다.
		indexLink = IndexHolder_Find(indexHolder, businessCardLink->company.name);
		//8.4. 찾은 색인에서 명함의 위치를 찾다.
		location = Index_Find(indexLink, businessCardLink);
		//8.5. 트리뷰 컨트롤에서 회사들 항목을 찾는다.
		hCompanies = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)0);
		//8.6. 트리뷰 컨트롤의 회사들 항목에서 상호 항목을 찾는다.
		hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompanies);
		tvItem.item.mask = TVIF_TEXT | TVIF_HANDLE;
		tvItem.item.hItem = hCompany;
		tvItem.item.pszText = companyName;
		tvItem.item.cchTextMax = 64;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem.item);
		while (hCompany != NULL && strcmp(companyName, indexLink->name) != 0) {
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hCompany);
			tvItem.item.hItem = hCompany;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem.item);
		}
		//8.7. 트리뷰 컨트롤의 상호 항목에서 이름 항목을 찾다.
		hName = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompany);
		i = 0;
		while (i < location) {
			hName = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hName);
			i++;
		}
		//8.8. 트리뷰 컨트롤의 회사들을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)hCompanies);
		//8.9. 트리뷰 컨트롤의 상호 항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)hCompany);
		//8.10. 트리뷰 컨트롤에서 이름 항목을 선택한다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)hName);
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_DROPHILITE, (LPARAM)hName);

	}

	return TRUE;
}

BOOL BusinessCardHolderForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BusinessCardHolder * businessCardHolder;
	BusinessCard *businessCardLink;
	IndexHolder *indexHolder;
	Index *indexLink;
	Long location;
	HTREEITEM hCompanies;
	HTREEITEM hCompany;
	HTREEITEM hName;
	Long i;
	TCHAR companyName[64];
	TVINSERTSTRUCT tvItem = { 0, };

	//9. 마지막 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		businessCardHolder = (BusinessCardHolder*)GetWindowLong(hWnd, GWL_USERDATA);
		indexHolder = (IndexHolder*)GetProp(hWnd, "PROP_INDEXHOLDER");
		//9.1. 명함첩에서 마지막으로 이동하다.
		businessCardLink = BusinessCardHolder_Last(businessCardHolder);
		//9.2. 명함을 출력하다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.url);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.position);
		//9.3. 색인첩에서 색인을 찾다.
		indexLink = IndexHolder_Find(indexHolder, businessCardLink->company.name);
		//9.4. 찾은 색인에서 명함의 위치를 찾다.
		location = Index_Find(indexLink, businessCardLink);
		//9.5. 트리뷰 컨트롤에서 회사들 항목을 찾는다.
		hCompanies = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)0);
		//9.6. 트리뷰 컨트롤의 회사들 항목에서 상호 항목을 찾는다.
		hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompanies);
		tvItem.item.mask = TVIF_TEXT | TVIF_HANDLE;
		tvItem.item.hItem = hCompany;
		tvItem.item.pszText = companyName;
		tvItem.item.cchTextMax = 64;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem.item);
		while (hCompany != NULL && strcmp(companyName, indexLink->name) != 0) {
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hCompany);
			tvItem.item.hItem = hCompany;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem.item);
		}
		//9.7. 트리뷰 컨트롤의 상호 항목에서 이름 항목을 찾다.
		hName = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompany);
		i = 0;
		while (i < location) {
			hName = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hName);
			i++;
		}
		//9.8. 트리뷰 컨트롤의 회사들을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)hCompanies);
		//9.9. 트리뷰 컨트롤의 상호 항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)hCompany);
		//9.10. 트리뷰 컨트롤에서 이름 항목을 선택한다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)hName);
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_DROPHILITE, (LPARAM)hName);
	}

	return TRUE;
}
BOOL BusinessCardHolderForm_OnTreeViewNameItemDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCardHolder * businessCardHolder;
	BusinessCard *businessCardLink;
	IndexHolder *indexHolder;
	Index *indexLink;
	Long location;
	HTREEITEM hSelected;
	HTREEITEM hCompany;
	HTREEITEM hName;
	TCHAR companyName[64];
	TVITEM tvItem = { 0, };

	//10. 트리뷰 컨트롤의 이름 항목을 더블클릭했을 때
	if (((LPNMHDR)lParam)->code == NM_DBLCLK)
	{
		businessCardHolder = (BusinessCardHolder*)GetWindowLong(hWnd, GWL_USERDATA);
		indexHolder = (IndexHolder*)GetProp(hWnd, "PROP_INDEXHOLDER");
		//10.1. 트리뷰 컨틀로에서 선택된 이름 항목을 읽는다.
		hSelected = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_CARET, (LPARAM)0);
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_DROPHILITE, (LPARAM)hSelected);
		//10.2. 트리뷰 컨트롤에서 선택된 이름 항목의 부모 상호를 찾는다.
		hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_PARENT, (LPARAM)hSelected);
		//10.3. 트리뷰 컨트롤에서 선택된 이름 항목의 위치를 찾는다.
		location = 0;
		hName = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompany);
		while (hName != hSelected) {
			location++;
			hName = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hName);

		}
		//10.4. 색인첩에서 색인을 찾다.
		tvItem.mask = TVIF_TEXT | TVIF_HANDLE;
		tvItem.hItem = hCompany;
		tvItem.pszText = companyName;
		tvItem.cchTextMax = 64;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem);
		indexLink = IndexHolder_Find(indexHolder, companyName);
		//10.5. 색인에서 명함을 찾다.
		businessCardLink = Index_GetAt(indexLink, location);
		//10.6. 명함첩에서 이동하다.
		businessCardLink = BusinessCardHolder_Move(businessCardHolder, businessCardLink);
		//10.7. 명함을 출력하다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.url);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.position);
	}
	return TRUE;
}