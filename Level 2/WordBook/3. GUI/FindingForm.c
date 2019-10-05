#include "FindingForm.h"
#include "resource.h"
#include "WordBook.h"
#include <stdio.h>
#include <stdlib.h>
#include <commctrl.h>
#pragma warning(disable:4996)

BOOL CALLBACK FindingFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (message) {
	case WM_INITDIALOG: ret = FindingForm_OnInitDialog(hWnd, wParam, lParam); break;
	case WM_COMMAND: ret = FindingForm_OnCommand(hWnd, wParam, lParam); break;
	case WM_NOTIFY: ret = FindingForm_OnNotify(hWnd, wParam, lParam); break;
	case WM_CLOSE: ret = FindingForm_OnClose(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}
BOOL FindingForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	LVCOLUMN column = { 0, };
	//1. 찾기 윈도우가 생성될 때

	//1.1. 리스트뷰 컨트롤의 헤더를 만든다.
	column.mask = LVCF_WIDTH | LVCF_TEXT;

	column.cx = 50;
	column.pszText = "번호";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_INSERTCOLUMN, (WPARAM)0, (LPARAM)&column);

	column.cx = 150;
	column.pszText = "단어";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_INSERTCOLUMN, (WPARAM)1, (LPARAM)&column);

	column.cx = 100;
	column.pszText = "품사";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_INSERTCOLUMN, (WPARAM)2, (LPARAM)&column);

	column.cx = 200;
	column.pszText = "의미";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_INSERTCOLUMN, (WPARAM)3, (LPARAM)&column);

	column.cx = 250;
	column.pszText = "예문";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_INSERTCOLUMN, (WPARAM)4, (LPARAM)&column);

	//1.2. 리스트뷰 컨트롤에 전체 선택을 설정한다.
	SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETEXTENDEDLISTVIEWSTYLE, (WPARAM)0, (LPARAM)LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	
	return TRUE;
}
BOOL FindingForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (LOWORD(wParam)) {
	case IDC_BUTTON_FIND: ret = FindingForm_OnFindButtonClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}
BOOL FindingForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (wParam) {
	case IDC_LIST_ENGLISHWORDS: ret = FindingForm_OnListViewItemDoubleClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}
BOOL FindingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	Long(*indexes);

	indexes = (Long(*))GetWindowLong(hWnd, GWL_USERDATA);
	//4. 닫기 버튼을 클릭했을 때
	
	//4.1. 찾기 윈도우를 닫는다.
	if (indexes != NULL) {
		free(indexes);
	}
	EndDialog(hWnd, 0);

	return TRUE;
}
BOOL FindingForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	TCHAR word[64];
	HWND updatingForm;
	WordBook *wordBook;
	Long(*indexes);
	Long count;
	LVITEM item = { 0, };
	Long i;
	TCHAR number[64];
	Long index;
	//2. 찾기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {
		//2.1. 단어를 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_WORD), WM_GETTEXT, (WPARAM)64, (LPARAM)word);

		//2.2. 단어장 윈도우를 찾는다.
		updatingForm = FindWindow("#32770", "단어장");
		wordBook = (WordBook*)GetWindowLong(updatingForm, GWL_USERDATA);

		//2.3. 단어장 윈도우의 단어장에서 찾는다.
		indexes = (Long(*))GetWindowLong(hWnd, GWL_USERDATA);
		if (indexes != NULL) {
			free(indexes);
		}
		Find(wordBook, word, &indexes, &count);
		SetWindowLong(hWnd, GWL_USERDATA, (LONG)indexes);

		//2.4. 리스트뷰 컨트롤의 모든 항목을 지운다.
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_DELETEALLITEMS, (WPARAM)0, (LPARAM)0);

		//2.5. 리스트뷰 컨트롤에 찾은 개수만큼 항목을 추가한다.
		item.mask = LVIF_TEXT;
		i = 0;
		while (i < count) {
			index = indexes[i];
			sprintf(number, "%d", i + 1);
			item.iItem = i;

			item.iSubItem = 0;
			item.pszText = number;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_INSERTITEM, (WPARAM)0, (LPARAM)&item);

			item.iSubItem = 1;
			item.pszText = wordBook->englishWords[index].word;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

			item.iSubItem = 2;
			item.pszText = wordBook->englishWords[index].wordClass;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

			item.iSubItem = 3;
			item.pszText = wordBook->englishWords[index].meaning;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

			item.iSubItem = 4;
			item.pszText = wordBook->englishWords[index].example;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

			i++;
		}
	}
	return TRUE;
}
BOOL FindingForm_OnListViewItemDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	Long index;
	LVITEM item = { 0, };
	TCHAR word[64];
	TCHAR wordClass[11];
	TCHAR meaning[64];
	TCHAR example[128];
	HWND updatingForm;
	Long(*indexes);

	//3. 리스트뷰 컨트롤의 항목을 더블클릭했을 때
	if (((LPNMHDR)lParam)->code == NM_DBLCLK) {
		//3.1. 리스트뷰 컨트롤의 선택된 항목의 위치를 읽는다.
		index = SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_GETSELECTIONMARK, (WPARAM)0, (LPARAM)0);

		//3.2. 선택된 위치의 항목을 읽는다.
		item.mask = LVIF_TEXT;
		item.iItem = index;

		item.iSubItem = 1;
		item.pszText = word;
		item.cchTextMax = 64;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 2;
		item.pszText = wordClass;
		item.cchTextMax = 11;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		
		item.iSubItem = 3;
		item.pszText = meaning;
		item.cchTextMax = 64;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		
		item.iSubItem = 4;
		item.pszText = example;
		item.cchTextMax = 128;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		//3.3. 단어장 윈도우를 찾는다.
		updatingForm = FindWindow("#32770", "단어장");

		//3.4. 단어장 윈도우의 영단어에 출력한다.
		SendMessage(GetDlgItem(updatingForm, IDC_EDIT_WORD), WM_SETTEXT, (WPARAM)0, (LPARAM)word);
		SendMessage(GetDlgItem(updatingForm, IDC_EDIT_WORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)wordClass);
		SendMessage(GetDlgItem(updatingForm, IDC_EDIT_MEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)meaning);
		SendMessage(GetDlgItem(updatingForm, IDC_EDIT_EXAMPLE), WM_SETTEXT, (WPARAM)0, (LPARAM)example);

		//3.5. 단어장 윈도우의 리스트뷰 컨트롤의 항목을 선택한다.
		indexes = (Long(*))GetWindowLong(hWnd, GWL_USERDATA);
		index = indexes[index];
		SendMessage(GetDlgItem(updatingForm, IDC_LIST_ENGLISHWORDS), LVM_SETSELECTIONMARK, (WPARAM)0, (LPARAM)index);

		//3.6. 찾기 윈도우를 닫는다.
		if (indexes != NULL) {
			free(indexes);
		}
		EndDialog(hWnd, 0);
	}
	return TRUE;
}