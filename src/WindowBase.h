#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <vector>
#include "include/core/SkSurface.h"
#include "src/base/SkAutoMalloc.h"
#include "yoga/YGNode.h"

#define WM_FLASH_CURSOR (WM_APP+4)

class WindowBase
{
public:
    WindowBase();
    virtual ~WindowBase();
    void show();
    void clearTimeout(const unsigned int& id);
    void setTimeout(const unsigned int& id, const unsigned int& ms);
    void close(const int& exitCode);
    HWND hwnd{nullptr};
    HWND hwndToolTip{nullptr};
    bool isMouseDown;
    int x{ 0 }, y{ 0 }, w{ 0 }, h{0};
    YGNode* layout;

protected:
    virtual LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) = 0;
    virtual void paint(SkCanvas* canvas) = 0;
    void initWindow();
    void paintWindow();

private:
    static LRESULT CALLBACK RouteWindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    SkAutoMalloc surfaceMemory;
    sk_sp<SkSurface> surface;
    int nctest(const int& x,const int& y);
};