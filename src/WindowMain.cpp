#include "WindowMain.h"
#include <windowsx.h>
#include <dwmapi.h>
#include <sstream>
#include <string>
#include "include/core/SkPath.h"
#include "include/core/SkStream.h"
#include "include/encode/SkPngEncoder.h"
#include "include/core/SkPaint.h"
#include "include/core/SkCanvas.h"
#include "App.h"
#include "ControlBase.h"
#include "TitleBar.h"
#include "ToolBar.h"
#include "LeftPanel.h"
#include "ContentPanel.h"
#include "TitleBar.h"
#include "ToolBar.h"
#include "LeftPanel.h"
#include "ContentPanel.h"


WindowMain::WindowMain()
{
    titleBar = std::make_shared<TitleBar>(this);
    toolBar = std::make_shared<ToolBar>(this);
    leftPanel = std::make_shared<LeftPanel>(this);
    contentPanel = std::make_shared<ContentPanel>(this);
    initWindow();
}

WindowMain::~WindowMain()
{
}

void WindowMain::show()
{
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    SetCursor(LoadCursor(nullptr, IDC_ARROW));
}

void WindowMain::setTimeout(const unsigned int& id,const unsigned int& ms)
{
    SetTimer(hwnd, id, ms, (TIMERPROC)NULL);
}

void WindowMain::clearTimeout(const unsigned int& id)
{
    KillTimer(hwnd, id);
}

LRESULT CALLBACK WindowMain::RouteWindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_NCCREATE)
    {
        CREATESTRUCT *pCS = reinterpret_cast<CREATESTRUCT *>(lParam);
        LPVOID pThis = pCS->lpCreateParams;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
    }
    auto obj = reinterpret_cast<WindowMain*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    if (obj)
    {        
        switch (msg)
        {
        case WM_NCCALCSIZE:
        {
            return false;
        }
        case WM_ERASEBKGND: {
            return false;
        }
        case WM_PAINT: {            
            obj->paintWindow();
            return true;
        }
        case WM_NCHITTEST: {
            POINT pt;
            pt.x = GET_X_LPARAM(lParam);
            pt.y = GET_Y_LPARAM(lParam);
            ScreenToClient(hWnd, &pt);
            return obj->nctest(pt.x, pt.y);           
        }
        case WM_GETMINMAXINFO:
        {
            obj->onGetMaxMinMizeInfo((PMINMAXINFO)lParam);
            return true;
        }
        case WM_SIZE: {
            obj->onSize(LOWORD(lParam), HIWORD(lParam));
            return true;
        }
        case WM_LBUTTONDOWN:
        {            
            obj->mouseDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            break;
        }
        case WM_LBUTTONUP:
        {
            obj->mouseUp(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            break;
        }
        case WM_MOUSELEAVE: {
            obj->mouseLeave();
            return true;
        }
        case WM_MOUSEMOVE:
        {
            obj->mouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            break;
        }
        case WM_CLOSE: {
            App::removeWindow(hWnd);
            return true;
        }
        case WM_MOUSEWHEEL: {
            POINT pt;
            pt.x = GET_X_LPARAM(lParam);
            pt.y = GET_Y_LPARAM(lParam);
            ScreenToClient(hWnd, &pt);
            obj->mouseWheel(pt.x, pt.y, GET_WHEEL_DELTA_WPARAM(wParam));
            break;
        }
        case WM_DEBUG_MESSAGE: {
            return true;
        }
        default:
        {
            break;
        }
        }
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}
int WindowMain::nctest(const int& x, const int& y)
{
    if (isMouseDown) {
        return HTCLIENT;
    }
    int size{ 6 };
    if (x < size && y < size) {
        return HTTOPLEFT;
    }
    else if (x > size && y < size && x < w - size) {
        return HTTOP;
    }
    else if (y < size && x > w - size) {
        return HTTOPRIGHT;
    }
    else if (y > size && y<h-size && x > w - size) {
        return HTRIGHT;
    }
    else if (y > h-size && x>w - size) {
        return HTBOTTOMRIGHT;
    }
    else if (x > size && y>h - size && x < w - size) {
        return HTBOTTOM;
    }
    else if (x < size && y > h - size) {
        return HTBOTTOMLEFT;
    }
    else if (x < size && y < h - size && y>size) {
        return HTLEFT;
    }
    else {
        if (!isTrackMouseEvent) {
            SetCursor(LoadCursor(nullptr, IDC_ARROW));
        }
        return HTCLIENT;
    }
}
void WindowMain::mouseMove(const int& x, const int& y)
{
    if (!isTrackMouseEvent) {
        TRACKMOUSEEVENT tme = {};
        tme.cbSize = sizeof(TRACKMOUSEEVENT);
        tme.dwFlags = TME_HOVER | TME_LEAVE;
        tme.hwndTrack = hwnd;
        tme.dwHoverTime = 1;
        isTrackMouseEvent = TrackMouseEvent(&tme);
    }
    if (isMouseDown) {
        for (auto& obj : ctrls)
        {
            obj->mouseDrag(x, y);
        }
    }
    else {
        for (auto& obj : ctrls)
        {
            obj->mouseMove(x, y);
        }
    }
}
void WindowMain::mouseLeave()
{
    if (!isMouseDown) {
        TRACKMOUSEEVENT tme = {};
        tme.cbSize = sizeof(TRACKMOUSEEVENT);
        tme.dwFlags = TME_CANCEL | TME_HOVER | TME_LEAVE;
        tme.hwndTrack = hwnd;
        TrackMouseEvent(&tme);
        isTrackMouseEvent = false;
    }
    for (auto& obj : ctrls)
    {
        obj->mouseMove(-888, -888);
    }
}
void WindowMain::mouseDown(const int& x, const int& y)
{
    isMouseDown = true;
    //避免执行最后一个元素的mouseDown事件，因为最后一个元素可能是刚刚添加的，构造函数还没有执行完
    auto size = ctrls.size(); 
    //auto iter = ctrls.end();
    //auto flag = false;
    for (size_t i = 0; i < size; i++)
    {
        ctrls[i]->mouseDown(x, y);
    }
    std::erase_if(ctrls, [](auto& item) { return item->isDel; });
    //if (flag) {
    //    ctrls.erase(iter);
    //}
    
}
void WindowMain::mouseUp(const int& x, const int& y)
{
    isMouseDown = false;
    for (auto& obj : ctrls)
    {
        obj->mouseUp(x, y);
    }
}
void WindowMain::mouseWheel(const int& x, const int& y,const int& delta)
{
    for (auto& obj : ctrls)
    {
        obj->mouseWheel(x,y,delta);
    }
}
void WindowMain::onClose()
{

}
void WindowMain::onSize(const int& w, const int& h)
{
    this->w = w;
    this->h = h;
    surface.reset();
    size_t bmpSize = sizeof(BITMAPINFOHEADER) + w * h * sizeof(uint32_t);
    surfaceMemory.reset(bmpSize);
    BITMAPINFO* bmpInfo = reinterpret_cast<BITMAPINFO*>(surfaceMemory.get());
    ZeroMemory(bmpInfo, sizeof(BITMAPINFO));
    bmpInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmpInfo->bmiHeader.biWidth = w;
    bmpInfo->bmiHeader.biHeight = -h; // negative means top-down bitmap. Skia draws top-down.
    bmpInfo->bmiHeader.biPlanes = 1;
    bmpInfo->bmiHeader.biBitCount = 32;
    bmpInfo->bmiHeader.biCompression = BI_RGB;
    void* pixels = bmpInfo->bmiColors;
    SkImageInfo info = SkImageInfo::MakeN32Premul(w, h);
    auto temp = SkCanvas::MakeRasterDirect(info, pixels, 4 * w);
    canvas = std::move(temp);
    for (size_t i = 0; i < ctrls.size(); i++)
    {
        ctrls[i]->resize(w, h);
    }
}

void WindowMain::paintWindow()
{
    PAINTSTRUCT ps;
    auto dc = BeginPaint(hwnd, &ps);
    auto c = canvas.get();
    for (size_t i = 0; i < ctrls.size(); i++)
    {
        ctrls[i]->paint(c);
    }
    BITMAPINFO* bmpInfo = reinterpret_cast<BITMAPINFO*>(surfaceMemory.get());
    StretchDIBits(dc, 0, 0, w, h, 0, 0, w, h, bmpInfo->bmiColors, bmpInfo, DIB_RGB_COLORS, SRCCOPY);
    ReleaseDC(hwnd, dc);
    EndPaint(hwnd, &ps);
    //surfaceMemory.reset(0); //实践证明这样即节省内存，速度也不会慢
}

void WindowMain::onGetMaxMinMizeInfo(MINMAXINFO* mminfo)
{
    RECT workArea;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0);    
    mminfo->ptMinTrackSize.x = 960;
    mminfo->ptMinTrackSize.y = 660;
    mminfo->ptMaxSize.x = workArea.right - workArea.left;
    mminfo->ptMaxSize.y = workArea.bottom - workArea.top;
    mminfo->ptMaxPosition.x = 0;
    mminfo->ptMaxPosition.y = 0;
}
void WindowMain::initWindow()
{
    static int num = 0;
    std::wstring winName = L"FileManager";
    auto clsName = std::format(L"{}_{}", winName, num++);
    auto hinstance = GetModuleHandle(NULL);
    WNDCLASSEX wcx{};
    wcx.cbSize = sizeof(wcx);
    wcx.style = CS_HREDRAW | CS_VREDRAW; // | CS_DBLCLKS
    wcx.lpfnWndProc = &WindowMain::RouteWindowMessage;
    wcx.cbWndExtra = sizeof(WindowMain*);
    wcx.hInstance = hinstance;
    wcx.hIcon = LoadIcon(hinstance, IDI_APPLICATION);
    wcx.hCursor = LoadCursor(hinstance, IDC_ARROW);
    wcx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcx.lpszClassName = clsName.c_str();
    if (!RegisterClassEx(&wcx))
    {
        return;
    }
    RECT screenRect;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &screenRect, 0);
    auto x = (screenRect.right - w) / 2;
    auto y = (screenRect.bottom - h) / 2;
    this->hwnd = CreateWindowEx(WS_EX_APPWINDOW, clsName.c_str(), winName.c_str(), WS_VISIBLE ,
                                x, y, w, h, NULL, NULL, hinstance, static_cast<LPVOID>(this));    
    DWMNCRENDERINGPOLICY policy = DWMNCRP_ENABLED;
    DwmSetWindowAttribute(hwnd, DWMWA_NCRENDERING_POLICY, &policy, sizeof(policy));
    MARGINS margins = { 1,1,1,1 };
    DwmExtendFrameIntoClientArea(hwnd, &margins);
    hwndToolTip = CreateWindowEx(WS_EX_TOPMOST, TOOLTIPS_CLASS, NULL, WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hwnd, NULL, hinstance, NULL);
}
