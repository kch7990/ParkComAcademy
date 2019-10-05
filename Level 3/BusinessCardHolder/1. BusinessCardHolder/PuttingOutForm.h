#ifndef _PUTTINGOUTFORM_H
#define _PUTTINGOUTFORM_H

#include <Windows.h>

BOOL CALLBACK PuttingOutFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL PuttingOutForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL PuttingOutForm_Onclose(HWND hWnd, WPARAM wParam, LPARAM lParam);

#endif