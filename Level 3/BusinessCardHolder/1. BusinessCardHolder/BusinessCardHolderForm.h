#ifndef _BUSINESSCARDHOLDERFORM_H
#define _BUSINESSCARDHOLDERFORM_H

#include <Windows.h>

BOOL CALLBACK BusinessCardHolderFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardHolderForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardHolderForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardHolderForm_OnCLose(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardHolderForm_OnPutInButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardHolderForm_OnFindButtoneClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardHolderForm_OnPutOutButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardHolderForm_OnArrangeButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardHolderForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardHolderForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardHolderForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardHolderForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);

#endif //_BUSINESSCARDHOLDERFORM_H