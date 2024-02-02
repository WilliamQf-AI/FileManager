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
    YGNodeFreeRecursive(layout);
}

void WindowMain::init()
{

}

LRESULT WindowMain::wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg)
    {
    case WM_LBUTTONDBLCLK:
    {
        auto x = GET_X_LPARAM(lparam);
        auto y = GET_Y_LPARAM(lparam);
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
    canvas->clear(SK_ColorWHITE);
    titleBar->paint(canvas);
    leftPanel->paint(canvas);
}

void WindowMain::initSize()
{
    x = 200;
    y = 200;
    w = 800;
    h = 600;
   
    layout = YGNodeNew();
    YGNodeStyleSetFlexDirection(layout, YGFlexDirectionColumn);

    auto contentLayout = YGNodeNew();
    YGNodeStyleSetFlexDirection(contentLayout, YGFlexDirectionRow);
    YGNodeStyleSetWidthAuto(contentLayout);
    YGNodeStyleSetFlexGrow(contentLayout, 1.f);

    titleBar = std::make_shared<TitleBar>(this);
    toolBar = std::make_shared<ToolBar>(this);
    leftPanel = std::make_shared<LeftPanel>(this);
    contentPanel = std::make_shared<ContentPanel>(this);

    YGNodeInsertChild(layout, titleBar->layout, 0);
    YGNodeInsertChild(layout, toolBar->layout, 1);
    YGNodeInsertChild(layout, contentLayout, 2);
    
    YGNodeInsertChild(contentLayout, leftPanel->layout, 0);
    YGNodeInsertChild(contentLayout, contentPanel->layout, 1);
}
