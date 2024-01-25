#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include "include/core/SkSurface.h"
#include <vector>

#define WM_REFRESH (WM_APP+1)
#define WM_FLASH_CURSOR (WM_APP+4)

class WindowBase
{
public:
    WindowBase();
    virtual ~WindowBase();
    void Show();
    void Refresh();
    void refresh();
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
    virtual void paintCanvas() = 0;
    void initWindow();
    HDC hCompatibleDC = NULL;
    HBITMAP bottomHbitmap;

private:
    static LRESULT CALLBACK RouteWindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};