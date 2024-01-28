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

}

void WindowMain::mousemove(const int& x, const int& y)
{
    titleBar->mousemove(x, y);
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
        SetCursor(LoadCursor(NULL, IDC_ARROW));
        auto x = GET_X_LPARAM(lparam);
        auto y = GET_Y_LPARAM(lparam);

        if (isMouseDown) {
        }
        else {

            mousemove(x, y);
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
   
    YGNodeStyleSetFlexDirection(layout, YGFlexDirectionColumn);
    titleBar = std::make_shared<TitleBar>();
    this->addLayoutChild(titleBar.get());
    toolBar = std::make_shared<ToolBar>();
    this->addLayoutChild(toolBar.get());

    auto contentLayout = new Layout();
    YGNodeStyleSetFlexDirection(contentLayout->layout, YGFlexDirectionRow);
    YGNodeStyleSetWidthAuto(contentLayout->layout);
    YGNodeStyleSetFlexGrow(contentLayout->layout, 1.f);

    leftPanel = std::make_shared<LeftPanel>();
    contentLayout->addLayoutChild(leftPanel.get());

    contentPanel = std::make_shared<ContentPanel>();
    contentLayout->addLayoutChild(contentPanel.get());

    this->addLayoutChild(contentLayout);
}
