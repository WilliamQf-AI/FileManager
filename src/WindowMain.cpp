#include "WindowMain.h"
#include <Windows.h>
#include <windowsx.h>
#include <dwmapi.h>
#include "include/core/SkBitmap.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkStream.h"
#include "include/encode/SkPngEncoder.h"
#include "yoga/YGNode.h"
#include "App.h"

WindowMain::WindowMain()
{
    initSize();
    initWindow();
}

WindowMain::~WindowMain()
{
}

void WindowMain::init()
{
    titleBar = std::make_shared<TitleBar>();
    titleBar->init(this);
    toolBar = std::make_shared<ToolBar>();
    toolBar->init(this);
    leftPanel = std::make_shared<LeftPanel>();
    leftPanel->init(this);
    contentPanel = std::make_shared<ContentPanel>();
    contentPanel->init(this);
    bottomBar = std::make_shared<BottomBar>();
    bottomBar->init(this);
}

LRESULT WindowMain::wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg)
    {
    case WM_LBUTTONDOWN:
    {
        isMouseDown = true;
        auto x = GET_X_LPARAM(lparam);
        auto y = GET_Y_LPARAM(lparam); 
        break;
    }
    case WM_LBUTTONDBLCLK:
    {
        auto x = GET_X_LPARAM(lparam);
        auto y = GET_Y_LPARAM(lparam);
        break;
    }
    case WM_LBUTTONUP:
    {
        isMouseDown = false;
        auto x = GET_X_LPARAM(lparam);
        auto y = GET_Y_LPARAM(lparam);
        break;
    }
    case WM_MOUSEMOVE:
    {
        auto x = GET_X_LPARAM(lparam);
        auto y = GET_Y_LPARAM(lparam);
        if (isMouseDown) {
        }
        else {
        }
        break;
    }
    case WM_RBUTTONDOWN:
    {
        auto x = GET_X_LPARAM(lparam);
        auto y = GET_Y_LPARAM(lparam);
        break;
    }
    case WM_KEYDOWN:
    {
        break;
    }
    case WM_CHAR: {        
    }
    case WM_MOUSEWHEEL: {
        int delta = GET_WHEEL_DELTA_WPARAM(wparam);
        break;
    }
    case WM_TIMER: {
        break;
    }
    default:
        break;
    }
    return DefWindowProc(hwnd, msg, wparam, lparam);
}

void WindowMain::paint(SkCanvas* canvas)
{
    SkPaint paint;
    paint.setColor(SK_ColorRED);
    paint.setStyle(SkPaint::kFill_Style);
    canvas->clear(SK_ColorWHITE);
    canvas->drawRect(SkRect::MakeLTRB(w - 150, h - 150, w - 10, h - 10), paint);
}

void WindowMain::initSize()
{
    x = 200;
    y = 200;
    w = 800;
    h = 600;
}
