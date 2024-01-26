#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <vector>
#include "include/core/SkSurface.h"
#include "src/base/SkAutoMalloc.h"

#define WM_FLASH_CURSOR (WM_APP+4)

class WindowBase
{
public:
    WindowBase();
    virtual ~WindowBase();
    void Show();
    void SetTimeout(const unsigned int& id,const unsigned int& ms);
    void ClearTimeout(const unsigned int& id);
    void Close(const int &exitCode);
    HWND hwnd;
    HWND hwndToolTip;
    int x, y, w, h;
    bool IsMouseDown{false};
    sk_sp<SkSurface> surfaceBase;
    SkPixmap* pixBase{nullptr};

protected:
    virtual LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) = 0;
    virtual void paintCanvas(SkCanvas* canvas) = 0;
    void initWindow();
    void initSurface();
    HDC hCompatibleDC = NULL;
    HBITMAP bottomHbitmap;

private:
    static LRESULT CALLBACK RouteWindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    SkAutoMalloc surfaceMemory;
    sk_sp<SkSurface> surface;
    void paint();
    int nctest(const int& x,const int& y);
};