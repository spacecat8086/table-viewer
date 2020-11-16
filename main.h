#include <windows.h>
#include "reader.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void Resize(HWND hwnd);
void DrawTable(HDC dc);
void Scroll(HWND hwnd, int amount);