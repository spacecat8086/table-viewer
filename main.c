#include "main.h"

TABLE table;
RECT clientRect;
HFONT hFont;
const wchar_t *ClassName = L"MyClass";
int yOrigin;
int contentHeight;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR pCmdLine, int nCmdShow)
{
    WNDCLASSEX wc = { };

    wc.cbSize = sizeof (WNDCLASSEX);
    wc.hInstance = hInstance;
    wc.lpszClassName = ClassName;
    wc.hbrBackground = ((HBRUSH)(0));
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpfnWndProc = WindowProc;

    RegisterClassEx(&wc);

    HWND hWnd = CreateWindowEx(
        0,
        ClassName,
        L"Table viewer",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
        NULL,
        NULL,
        hInstance,
        NULL);

    if (hWnd == NULL)
    {
            MessageBox((HWND)NULL, L"Can't create window", (LPWSTR)NULL, MB_ICONWARNING);
        return 42;
    }
    
    ShowWindow(hWnd, nCmdShow);
    
    MSG msg;

    while(GetMessage(&msg, NULL, 0, 0) > 0)
    {
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    //SCROLLINFO si;
    int wheelRotation;

    switch (uMsg)
    {
    case WM_DESTROY :
        PostQuitMessage(0);
        return 0;
        
    case WM_CREATE :
        if (ReadFromFile("table.txt", &table))
        {
            MessageBox((HWND)NULL, L"Invalid file", (LPWSTR)NULL, MB_ICONWARNING);
        }
        GetClientRect(hwnd, &clientRect);
        //SetFont(hwnd);
        hFont = CreateFont(24,8,0,0,FW_NORMAL,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
                CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,L"Times New Roman");
        return 0;

    case WM_SIZE :
        Resize(hwnd);
        return 0;

    case WM_MOUSEWHEEL :
        wheelRotation = GET_WHEEL_DELTA_WPARAM(wParam);
        Scroll(hwnd, wheelRotation);
        return 0;

    case WM_PAINT :
    {
        PAINTSTRUCT ps;
        HDC dc = BeginPaint(hwnd, &ps);
        
        SelectObject(dc,hFont);

        FillRect(dc, &clientRect, (HBRUSH)0);
        
        SetWindowOrgEx(dc, 0, yOrigin, NULL);
        //OffsetRect(&ps.rcPaint, 0, yOrigin);

        DrawTable(dc);

        EndPaint(hwnd, &ps);
        
        return 0;
    }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void Resize(HWND hwnd)
{
    GetClientRect(hwnd, &clientRect); 
    InvalidateRect(hwnd, NULL, FALSE);
}

void DrawTable(HDC dc)
{
    DRAWTEXTPARAMS dt = { };

    int rowY = 0;
    float columnWidth = clientRect.right / table.columns;

    for (int i = 0; i < table.rows; i++)
    {
        int rowHeight = 0;

        for (int j = 0; j < table.columns; j++)
        {
            RECT drawRect;

            drawRect.top = rowY;
            drawRect.bottom = clientRect.bottom + yOrigin;
            drawRect.left = (int)(clientRect.left + columnWidth * j);
            drawRect.right = (int)(clientRect.left + columnWidth * (j + 1));

            int height = DrawTextEx(dc, table.cells[i][j], -1, &drawRect, DT_WORDBREAK | DT_WORD_ELLIPSIS | DT_CENTER | DT_NOPREFIX, NULL);
            rowHeight = height > rowHeight ? height : rowHeight;
        }
        rowY += rowHeight;
    }
    contentHeight = rowY;
}

void Scroll(HWND hwnd, int amount)
{
    int yOriginOld = yOrigin;
       
    yOrigin -= amount;

    // Avoid scrolling too far
    yOrigin = yOrigin > contentHeight - clientRect.bottom ? contentHeight - clientRect.bottom : yOrigin;
    yOrigin = yOrigin < 0 ? 0 : yOrigin;

    if (yOrigin != yOriginOld)
    {
        InvalidateRect(hwnd, NULL, TRUE);
    }
}