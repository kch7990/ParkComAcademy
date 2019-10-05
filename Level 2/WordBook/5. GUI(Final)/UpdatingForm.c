#include "UpdatingForm.h"
#include "resource.h"
#include "FindingForm.h"
#include "WordBook.h"
#include <stdlib.h>
#include <stdio.h>
#include <commctrl.h>
#pragma warning(disable:4996)

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	int response = DialogBox(hInstance, MAKEINTRESOURCE(IDD_UPDATINGFORM), NULL, UpdatingFormProc);

	return response;
}
BOOL CALLBACK UpdatingFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (message) {
	case WM_INITDIALOG: ret = UpdatingForm_OnInitDialog(hWnd, wParam, lParam); break;
	case WM_COMMAND: ret = UpdatingForm_OnCommand(hWnd, wParam, lParam); break;
	case WM_NOTIFY: ret = UpdatingForm_OnNotify(hWnd, wParam, lParam); break;
	case WM_CLOSE: ret = UpdatingForm_OnClose(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}
BOOL UpdatingForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	WordBook *wordBook;
	Long count;
	LVCOLUMN column = { 0, };
	LVITEM item = { 0, };
	Long i;
	TCHAR number[64];
	EnglishWord englishWord;
	//1. 윈도우가 생성될 때

	//1.1. 단어장을 만든다.
	wordBook = (WordBook*)malloc(sizeof(WordBook));
	WordBook_Create(wordBook, 10000);
	SetWindowLong(hWnd, GWL_USERDATA, (Long)wordBook);

	//1.2. 적재하다.
	count = Load(wordBook);

	//1.3. 리스트뷰 컨트롤의 헤더를 만든다.
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

	//1.4. 리스트뷰 컨트롤에 전체 선택을 설정한다.
	SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETEXTENDEDLISTVIEWSTYLE, (WPARAM)0, (LPARAM)LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//1.5. 개수만큼 리스트뷰 컨트롤에 항목들을 추가한다.
	item.mask = LVIF_TEXT;
	i = 0;
	while (i < count) {
		item.iItem = i;
		sprintf(number, "%d", i + 1);
		englishWord = WordBook_GetAt(wordBook, i);

		item.iSubItem = 0;
		item.pszText = number;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_INSERTITEM, (WPARAM)0, (LPARAM)&item);

		item.iSubItem = 1;
		item.pszText = englishWord.word;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

		item.iSubItem = 2;
		item.pszText = englishWord.wordClass;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

		item.iSubItem = 3;
		item.pszText = englishWord.meaning;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

		item.iSubItem = 4;
		item.pszText = englishWord.example;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);
		i++;
	}

	return TRUE;
}
BOOL UpdatingForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (LOWORD(wParam)) {
	case IDC_BUTTON_RECORD: ret = UpdatingForm_OnRecordButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_FIND: ret = UpdatingForm_OnFindButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_CORRECT: ret = UpdatingForm_OnCorrectButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_ERASE: ret = UpdatingForm_OnEraseButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_ARRANGE: ret = UpdatingForm_OnArrangeButtonClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}
BOOL UpdatingForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (wParam) {
	case IDC_LIST_ENGLISHWORDS: ret = UpdatingForm_OnListViewItemDoubleClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}
BOOL UpdatingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	WordBook *wordBook;
	
	//8. 닫기 버튼을 클릭했을 때

	//8.1. 저장한다.
	wordBook = (WordBook*)GetWindowLong(hWnd, GWL_USERDATA);
	
	if (wordBook != NULL) {
		Save(wordBook);
		//8.2. 단어장을 없앤다.
		WordBook_Destroy(wordBook);
		free(wordBook);
	}
	//8.3. 윈도우를 닫는다.
	EndDialog(hWnd, 0);

	return TRUE;
}
BOOL UpdatingForm_OnRecordButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	WordBook *wordBook;
	TCHAR number[64];
	TCHAR word[64];
	TCHAR wordClass[11];
	TCHAR meaning[64];
	TCHAR example[128];
	Long index;
	LVITEM item = { 0, };
	//2. 기재하기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {
		//2.1. 영단어를 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_WORD), WM_GETTEXT, (WPARAM)64, (LPARAM)word);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_WORDCLASS), WM_GETTEXT, (WPARAM)11, (LPARAM)wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANING), WM_GETTEXT, (WPARAM)64, (LPARAM)meaning);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLE), WM_GETTEXT, (WPARAM)128, (LPARAM)example);
		
		//2.2. 단어장에서 기재한다.
		wordBook = (WordBook*)GetWindowLong(hWnd, GWL_USERDATA);
		index = Record(wordBook, word, wordClass, meaning, example);

		//2.3. 리스트뷰 컨트롤에 항목을 추가한다.
		item.mask = LVIF_TEXT;
		item.iItem = index;
		sprintf(number, "%d", index + 1);

		item.iSubItem = 0;
		item.pszText = number;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_INSERTITEM, (WPARAM)0, (LPARAM)&item);

		item.iSubItem = 1;
		item.pszText = word;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 2;
		item.pszText = wordClass;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 3;
		item.pszText = meaning;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 4;
		item.pszText = example;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
	}

	return TRUE;
}
BOOL UpdatingForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	//3. 찾기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {
		//3.1. 찾기 윈도우를 출력한다.
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_FINDINGFORM), NULL, FindingFormProc);
	}
	return TRUE;
}
BOOL UpdatingForm_OnCorrectButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	TCHAR wordClass[11];
	TCHAR meaning[64];
	TCHAR example[128];
	Long index;
	WordBook *wordBook;
	LVITEM item = { 0, };
	EnglishWord englishWord;

	//4. 고치기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {
		//4.1. 영단어를 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_WORDCLASS), WM_GETTEXT, (WPARAM)11, (LPARAM)wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANING), WM_GETTEXT, (WPARAM)64, (LPARAM)meaning);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLE), WM_GETTEXT, (WPARAM)128, (LPARAM)example);

		//4.2. 리스트뷰 컨트롤의 선택된 항목의 위치를 읽는다.
		index = (Long)SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_GETSELECTIONMARK, (WPARAM)0, (LPARAM)0);

		//4.3. 단어장에서 고치다.
		wordBook = (WordBook*)GetWindowLong(hWnd, GWL_USERDATA);
		index = Correct(wordBook, index, wordClass, meaning, example);

		//4.4. 리스트뷰 컨트롤의 항목을 고치다.
		item.mask = LVIF_TEXT;
		item.iItem = index;
		englishWord = WordBook_GetAt(wordBook, index);

		item.iSubItem = 2;
		item.pszText = englishWord.wordClass;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 3;
		item.pszText = englishWord.meaning;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 4;
		item.pszText = englishWord.example;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
	}
	return TRUE;
}
BOOL UpdatingForm_OnEraseButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	Long index;
	WordBook *wordBook;
	Long erased;
	LVITEM item = { 0, };
	Long i;
	TCHAR number[64];
	//5. 지우기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {
		//5.1. 리스트뷰 컨트롤의 선택된 항목의 위치를 읽는다.
		index = (Long)SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_GETSELECTIONMARK, (WPARAM)0, (LPARAM)0);
	
		//5.2. 단어장에서 지운다.
		wordBook = (WordBook*)GetWindowLong(hWnd, GWL_USERDATA);
		erased = Erase(wordBook, index);
		if (erased == -1) {
			//5.3. 리스트뷰 컨트롤의 항목을 지운다.
			SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_DELETEITEM, (WPARAM)index, (LPARAM)0);

			//5.4. 선택된 위치부터 마지막 줄까지 번호를 고친다.
			item.iSubItem = 0;
			i = index;
			while (i < wordBook->length) {
				sprintf(number, "%d", i + 1);
				item.iItem = index;
				item.pszText = number;
				SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
				i++;
			}
		}
	}
	return TRUE;
}
BOOL UpdatingForm_OnArrangeButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	WordBook *wordBook;
	Long i;
	TCHAR number[64];
	LVITEM item = { 0, };
	EnglishWord englishWord;

	//6. 정리하기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {
		//6.1. 단어장에서 정리한다.
		wordBook = (WordBook*)GetWindowLong(hWnd, GWL_USERDATA);
		Arrange(wordBook);

		//6.2. 리스트뷰 컨트롤의 모든 항목을 지운다.
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_DELETEALLITEMS, (WPARAM)0, (LPARAM)0);

		//6.3. 단어장에 적힌 줄 수만큼 리스트뷰 컨트롤의 항목을 추가한다.
		item.mask = LVIF_TEXT;
		i = 0;
		while (i < wordBook->length) {
			sprintf(number, "%d", i + 1);
			item.iItem = i;
			englishWord = WordBook_GetAt(wordBook, i);

			item.iSubItem = 0;
			item.pszText = number;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_INSERTITEM, (WPARAM)0, (LPARAM)&item);

			item.iSubItem = 1;
			item.pszText = englishWord.word;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

			item.iSubItem = 2;
			item.pszText = englishWord.wordClass;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

			item.iSubItem = 3;
			item.pszText = englishWord.meaning;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

			item.iSubItem = 4;
			item.pszText = englishWord.example;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

			i++;
		}
	}
	return TRUE;
}
BOOL UpdatingForm_OnListViewItemDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	Long index;
	LVITEM item = { 0, };
	TCHAR word[64];
	TCHAR wordClass[11];
	TCHAR meaning[64];
	TCHAR example[128];
	//7. 리스트뷰 컨트롤의 항목을 더블클릭했을 때
	if (((LPNMHDR)lParam)->code == NM_DBLCLK) {
		//7.1. 리스트뷰 컨트롤의 선택된 위치를 읽는다.
		index = (Long)SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_GETSELECTIONMARK, (WPARAM)0, (LPARAM)0);
		
		//7.2. 선택된 위치의 항목을 읽는다.
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

		//7.3. 영단어에 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_WORD), WM_SETTEXT, (WPARAM)0, (LPARAM)word);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_WORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)meaning);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLE), WM_SETTEXT, (WPARAM)0, (LPARAM)example);
	}
	return TRUE;
}