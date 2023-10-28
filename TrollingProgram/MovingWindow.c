#include "Payload.h"

#define DELAY 60

DWORD WINAPI MovingWindow(LPVOID lpParameter)
{
    const int offset[] = { 1, 1, 2, 2, 3, 3, 4, 4, 3, 3, 2, 2, 1, 1,
                          -1,-1,-2,-2,-3,-3,-4,-4,-3,-3,-2,-2,-1,-1 };
    const int nCount = sizeof(offset) / sizeof(void*);

    HWND hwnd;
    RECT rect;

    for (int i = 0, t = 0, delay = 0;;)
    {
        for (i = 0;; i = (nCount <= ++i) ? 0 : i)
        {
            if ((hwnd = GetForegroundWindow()) == NULL)
                break;

            for (t = 0, delay = DELAY / abs(offset[i]); t < abs(offset[i]); t++)
            {
                GetWindowRect(hwnd, &rect);
                MoveWindow(hwnd, rect.left, rect.top + (offset[i] < 0 ? -1 : 1), rect.right - rect.left, rect.bottom - rect.top, FALSE);
                Sleep(delay);
            }
        }
        Sleep(DELAY);
    }

    return 0;
}