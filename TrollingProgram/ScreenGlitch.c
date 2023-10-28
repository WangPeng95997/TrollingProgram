#include "Payload.h"
#include "utils.h"

// ºì, ³È, »Æ, ÂÌ, Çà, À¶, ×Ï
#define RGBCOUNT        7
const COLORREF Colors[RGBCOUNT][3] = { {255, 0, 0}, {255, 128, 0}, {255, 255, 0}, {0, 255, 0}, {0, 255, 255}, {0, 0, 255}, {128, 0, 128} };
#define MINVALUE_X      320
#define MINVALUE_Y      240

DWORD WINAPI ScreenGlitch(LPVOID lpParameter)
{
    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);

    HWND hwnd = GetDesktopWindow();
    HDC hdc = GetDC(hwnd);
    HDC hdcCopy = CreateCompatibleDC(hdc);

    int x, y, rgb, delay, length;
    BOOLEAN bVector;
    HBITMAP hBitmap;
    HGDIOBJ hGdiobj;

    for (;;)
    {
        while ((delay = (Random() % 10000)) < 7000) {}
        bVector = Random() % 2;
        rgb = Random() % RGBCOUNT;

        if (Random() % 2)
        {
            while ((length = (Random() % (width / 2))) < MINVALUE_X) {}
            delay /= length;

            y = Random() % (height / 10) + (height / 200);
            hBitmap = CreateCompatibleBitmap(hdc, width, y);
            hGdiobj = SelectObject(hdcCopy, hBitmap);
            SetPixel(hdcCopy, 0, 0, RGB(Colors[rgb][0], Colors[rgb][1], Colors[rgb][2]));
            StretchBlt(hdcCopy, 0, 0, width, y, hdcCopy, 0, 0, 1, 1, SRCCOPY);

            for (int i = 0, ix = Random() % width, iy = Random() % height; i < length; i++)
            {
                if (bVector)
                    BitBlt(hdc, ix + i, iy, 1, y, hdcCopy, 0, 0, SRCCOPY);
                else
                    BitBlt(hdc, ix - i, iy, 1, y, hdcCopy, 0, 0, SRCCOPY);

                Sleep(delay);
            }
        }
        else
        {
            while ((length = (Random() % (height / 2))) < MINVALUE_Y) {}
            delay /= length;

            x = Random() % (width / 10) + (width / 200);
            hBitmap = CreateCompatibleBitmap(hdc, x, height);
            hGdiobj = SelectObject(hdcCopy, hBitmap);
            SetPixel(hdcCopy, 0, 0, RGB(Colors[rgb][0], Colors[rgb][1], Colors[rgb][2]));
            StretchBlt(hdcCopy, 0, 0, x, height, hdcCopy, 0, 0, 1, 1, SRCCOPY);

            for (int i = 0, ix = Random() % width, iy = Random() % height; i < length; i++)
            {
                if (bVector)
                    BitBlt(hdc, ix, iy + i, x, 1, hdcCopy, 0, 0, SRCCOPY);
                else
                    BitBlt(hdc, ix, iy - i, x, 1, hdcCopy, 0, 0, SRCCOPY);

                Sleep(delay);
            }
        }
        SelectObject(hdcCopy, hGdiobj);
        DeleteObject(hBitmap);
    }
    DeleteDC(hdcCopy);
    ReleaseDC(hwnd, hdc);

    return 0;
}