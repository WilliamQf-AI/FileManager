#include "WindowMain.h"
#include <Windows.h>
#include <windowsx.h>
#include <dwmapi.h>
#include "include/core/SkBitmap.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkStream.h"
#include "include/encode/SkPngEncoder.h"
#include "App.h"

WindowMain::WindowMain()
{
    initWindow();
}

WindowMain::~WindowMain()
{
}

void WindowMain::init()
{

}

LRESULT WindowMain::wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg)
    {
    case WM_KEYDOWN:
    {
        break;
    }
    case WM_CHAR: {        
    }
    case WM_TIMER: {
        break;
    }
    default:
        break;
    }
    return DefWindowProc(hwnd, msg, wparam, lparam);
}
