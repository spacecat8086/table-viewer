#ifndef _MAIN_
#define _MAIN_

#include <windows.h>
#include "reader.h"

#define LINE_OFFSET 10

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void Resize(HWND hwnd);
void DrawTable(HDC dc);
void Scroll(HWND hwnd, int amount);

#endif