#include "Payload.h"
#include "utils.h"

#define SIZE_X      30
#define SIZE_Y      8
#define DELAY       50
#define PI          3.1415926

DWORD WINAPI ScreenMelting(LPVOID lpParameter)
{
    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);

    HWND hwnd = GetDesktopWindow();
    HDC hdc = GetDC(hwnd);
    HDC hdcCopy = CreateCompatibleDC(hdc);
    HBITMAP hBitmap = CreateCompatibleBitmap(hdc, SIZE_X, height);
    HGDIOBJ hObject = SelectObject(hdcCopy, hBitmap);

    for (;;)
    {
        for (int i = 0; i < 10; i++)
        {
            int x = Random() % width - SIZE_X / 2;
            BitBlt(hdcCopy, 0, 0, SIZE_X, height, hdc, x, 0, SRCCOPY);

            for (int ix = 0, depth = 0; ix < SIZE_X; ix++)
            {
                depth = (int)(sin(ix / (double)SIZE_X * PI) * SIZE_Y);
                StretchBlt(hdcCopy, ix, 0, 1, depth, hdcCopy, ix, 0, 1, 1, SRCCOPY);
                BitBlt(hdcCopy, ix, 0, 1, height, hdcCopy, ix, -depth, SRCCOPY);
            }
            BitBlt(hdc, x, 0, SIZE_X, height, hdcCopy, 0, 0, SRCCOPY);
            Sleep(DELAY);
        }
    }
    SelectObject(hdcCopy, hObject);
    DeleteObject(hBitmap);
    DeleteDC(hdcCopy);
    ReleaseDC(hwnd, hdc);

    return 0;
}