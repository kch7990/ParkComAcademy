// FindingForm.h
#ifndef _FINDINGFORM_H
#define _FINDINGFORM_H

#include <Windows.h>
BOOL CALLBACK FindingFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lparam);
BOOL FindingForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindingForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindingForm_OnSelectButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindingForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindingForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindingForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindingForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);




#endif