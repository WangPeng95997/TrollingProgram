#include <Windows.h>
#include "Payload.h"

#define ID_BUTTON       1001
#define ID_BUTTON2      1002
#define ID_BUTTON3      1003

HFONT g_hFont = NULL;
HINSTANCE g_hInstance = NULL;
HWND g_mainWindow = NULL;
LPCSTR g_windowClassName = "MainWindow";

void OnCommand(HWND hwnd, WPARAM wParam)
{
    switch (LOWORD(wParam))
    {
    case ID_BUTTON:
        if (HIWORD(wParam) == BN_CLICKED)
        {
            if (SendMessage(GetDlgItem(hwnd, ID_BUTTON), BM_GETCHECK, 0, 0) == BST_CHECKED)
            {
                g_hThreads[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ScreenMelting, NULL, 0, NULL);
            }
            else if(g_hThreads[0])
            {
                TerminateThread(g_hThreads[0], 0);
                CloseHandle(g_hThreads[0]);
            }
        }
        break;

    case ID_BUTTON2:
        if (HIWORD(wParam) == BN_CLICKED)
        {
            if (SendMessage(GetDlgItem(hwnd, ID_BUTTON2), BM_GETCHECK, 0, 0) == BST_CHECKED)
            {
                g_hThreads[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MovingWindow, NULL, 0, NULL);
            }
            else if (g_hThreads[1])
            {
                TerminateThread(g_hThreads[1], 0);
                CloseHandle(g_hThreads[1]);
            }
        }
        break;

    case ID_BUTTON3:
        if (HIWORD(wParam) == BN_CLICKED)
        {
            if (SendMessage(GetDlgItem(hwnd, ID_BUTTON3), BM_GETCHECK, 0, 0) == BST_CHECKED)
            {
                g_hThreads[2] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ScreenGlitch, NULL, 0, NULL);
            }
            else if (g_hThreads[2])
            {
                TerminateThread(g_hThreads[2], 0);
                CloseHandle(g_hThreads[2]);
            }
        }
        break;

    }
}

void OnCreate(HWND hwnd)
{
    g_hFont = CreateFont(20, 0, 0, 1800, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, "consola");

    HWND button = CreateWindowEx(0, "BUTTON", "Screnn Melting", BS_AUTOCHECKBOX | BS_PUSHLIKE | WS_VISIBLE | WS_CHILD, 20, 20, 120, 40, hwnd, (HMENU)ID_BUTTON, g_hInstance, NULL);
    SendMessage(button, WM_SETFONT, (WPARAM)g_hFont, TRUE);

    button = CreateWindowEx(0, "BUTTON", "Moving Window", BS_AUTOCHECKBOX | BS_PUSHLIKE | WS_VISIBLE | WS_CHILD, 20, 80, 120, 40, hwnd, (HMENU)ID_BUTTON2, g_hInstance, NULL);
    SendMessage(button, WM_SETFONT, (WPARAM)g_hFont, TRUE);

    button = CreateWindowEx(0, "BUTTON", "Screen Glitch", BS_AUTOCHECKBOX | BS_PUSHLIKE | WS_VISIBLE | WS_CHILD, 20, 140, 120, 40, hwnd, (HMENU)ID_BUTTON3, g_hInstance, NULL);
    SendMessage(button, WM_SETFONT, (WPARAM)g_hFont, TRUE);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        OnCreate(hwnd);
        break;

    case WM_COMMAND:
        OnCommand(hwnd, wParam);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

ATOM RegisterWindowClass(HINSTANCE hInstance, WNDPROC lpWndProc, LPCSTR lpClassName)
{
    WNDCLASSEX WndEx;
    WndEx.cbSize = sizeof(WNDCLASSEX);
    WndEx.style = CS_HREDRAW | CS_VREDRAW;
    WndEx.lpfnWndProc = lpWndProc;
    WndEx.cbClsExtra = 0;
    WndEx.cbWndExtra = 0;
    WndEx.hInstance = hInstance;
    WndEx.hIcon = NULL;
    WndEx.hCursor = NULL;
    WndEx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    WndEx.lpszMenuName = NULL;
    WndEx.lpszClassName = lpClassName;
    WndEx.hIconSm = NULL;

    return RegisterClassEx(&WndEx);
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    g_hInstance = hInstance;

    if (!RegisterWindowClass(hInstance, (WNDPROC)WindowProc, g_windowClassName))
        return MessageBox(NULL, "window class register failed", "Trolling Program", MB_OK);

    g_mainWindow = CreateWindowEx(0, "MainWindow", "Trolling Program", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 400, 300, NULL, NULL, hInstance, NULL);
    ShowWindow(g_mainWindow, SW_SHOW);
    UpdateWindow(g_mainWindow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    UnregisterClass(g_windowClassName, hInstance);

    return 0;
}