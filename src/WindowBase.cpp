#include "WindowBase.h"
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


WindowBase::WindowBase()
{

}

WindowBase::~WindowBase()
{
}

void WindowBase::show()
{
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    SetCursor(LoadCursor(nullptr, IDC_ARROW));
}

void WindowBase::setTimeout(const unsigned int& id,const unsigned int& ms)
{
    SetTimer(hwnd, id, ms, (TIMERPROC)NULL);
}

void WindowBase::clearTimeout(const unsigned int& id)
{
    KillTimer(hwnd, id);
}

LRESULT CALLBACK WindowBase::RouteWindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_NCCREATE)
    {
        CREATESTRUCT *pCS = reinterpret_cast<CREATESTRUCT *>(lParam);
        LPVOID pThis = pCS->lpCreateParams;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
    }
    auto obj = reinterpret_cast<WindowBase *>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
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
            PAINTSTRUCT ps;
            auto dc = BeginPaint(hWnd, &ps);
            obj->paintWindow();
            BITMAPINFO* bmpInfo = reinterpret_cast<BITMAPINFO*>(obj->surfaceMemory.get());
            StretchDIBits(dc, 0, 0, obj->w, obj->h, 0, 0, obj->w, obj->h, bmpInfo->bmiColors, bmpInfo, DIB_RGB_COLORS, SRCCOPY);
            ReleaseDC(hWnd, dc);
            EndPaint(hWnd, &ps);
            obj->surfaceMemory.reset(0); //实践证明这样即节省内存，速度也不会慢
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
        case WM_DEBUG_MESSAGE: {
            return true;
        }
        default:
        {
            return obj->wndProc(hWnd, msg, wParam, lParam);
        }
        }
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}
int WindowBase::nctest(const int& x, const int& y)
{
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

        return HTCLIENT;
    }
}
void WindowBase::mouseMove(const int& x, const int& y)
{
    if (!isTrackMouseEvent) {
        TRACKMOUSEEVENT tme = {};
        tme.cbSize = sizeof(TRACKMOUSEEVENT);
        tme.dwFlags = TME_HOVER | TME_LEAVE;
        tme.hwndTrack = hwnd;
        tme.dwHoverTime = 1;
        isTrackMouseEvent = TrackMouseEvent(&tme);
    }
    SetCursor(LoadCursor(NULL, IDC_ARROW));
    if (isMouseDown) {
        for (auto& func : mouseDragHandlers)
        {
            func(x, y);
        }
    }
    else {
        for (auto& func : mouseMoveHandlers)
        {
            func(x, y);
        }
    }
}
void WindowBase::mouseLeave()
{
    TRACKMOUSEEVENT tme = {};
    tme.cbSize = sizeof(TRACKMOUSEEVENT);
    tme.dwFlags = TME_CANCEL | TME_HOVER | TME_LEAVE;
    tme.hwndTrack = hwnd;
    TrackMouseEvent(&tme);    
    isTrackMouseEvent = false;
    for (auto& func : mouseMoveHandlers)
    {
        func(-888, -888);
    }
}
void WindowBase::mouseDown(const int& x, const int& y)
{
    isMouseDown = true;
    for (auto& func : mouseDownHandlers)
    {
        func(x, y);
    }
}
void WindowBase::mouseUp(const int& x, const int& y)
{
    isMouseDown = false;
    for (auto& func : mouseUpHandlers)
    {
        func(x, y);
    }
}
void WindowBase::onClose()
{

}
void WindowBase::onSize(const int& w, const int& h)
{
    this->w = w;
    this->h = h;
    YGNodeStyleSetWidth(layout, w);
    YGNodeStyleSetHeight(layout, h);
    YGNodeCalculateLayout(layout, YGUndefined, YGUndefined, YGDirectionLTR);
}
void WindowBase::onGetMaxMinMizeInfo(MINMAXINFO* mminfo)
{
    RECT workArea;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0);    
    mminfo->ptMinTrackSize.x = 800;
    mminfo->ptMinTrackSize.y = 600;
    mminfo->ptMaxSize.x = workArea.right - workArea.left;
    mminfo->ptMaxSize.y = workArea.bottom - workArea.top;
    mminfo->ptMaxPosition.x = 0;
    mminfo->ptMaxPosition.y = 0;
}
void WindowBase::initWindow()
{
    static int num = 0;
    std::wstring className = std::format(L"FileManager{}", num++);
    auto hinstance = GetModuleHandle(NULL);
    WNDCLASSEX wcx{};
    wcx.cbSize = sizeof(wcx);
    wcx.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wcx.lpfnWndProc = &WindowBase::RouteWindowMessage;
    wcx.cbWndExtra = sizeof(WindowBase *);
    wcx.hInstance = hinstance;
    wcx.hIcon = LoadIcon(hinstance, IDI_APPLICATION);
    wcx.hCursor = LoadCursor(hinstance, IDC_ARROW);
    wcx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcx.lpszClassName = className.c_str();
    if (!RegisterClassEx(&wcx))
    {
        return;
    }
    RECT screenRect;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &screenRect, 0);
    auto x = (screenRect.right - w) / 2;
    auto y = (screenRect.bottom - h) / 2;
    this->hwnd = CreateWindowEx(WS_EX_APPWINDOW, className.c_str(), className.c_str(), WS_VISIBLE,
                                x, y, w, h, NULL, NULL, hinstance, static_cast<LPVOID>(this));    
    DWMNCRENDERINGPOLICY policy = DWMNCRP_ENABLED;
    DwmSetWindowAttribute(hwnd, DWMWA_NCRENDERING_POLICY, &policy, sizeof(policy));
    MARGINS margins = { 1,1,1,1 };
    DwmExtendFrameIntoClientArea(hwnd, &margins);
    hwndToolTip = CreateWindowEx(WS_EX_TOPMOST, TOOLTIPS_CLASS, NULL, WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hwnd, NULL, hinstance, NULL);
}

void WindowBase::paintWindow()
{
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
    surface = SkSurfaces::WrapPixels(info, pixels, sizeof(uint32_t) * w);
    SkCanvas* canvas = surface->getCanvas();
    paint(canvas);
}
