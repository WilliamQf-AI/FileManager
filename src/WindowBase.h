#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <vector>
#include <functional>
#include "include/core/SkSurface.h"
#include "src/base/SkAutoMalloc.h"
#include "yoga/Yoga.h"
#include "Layout.h"

#define WM_FLASH_CURSOR (WM_APP+8)
#define WM_DEBUG_MESSAGE (WM_APP+9)
using EventHandlerType = void(*)(const int&, const int&);

class WindowBase:public Layout
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
    bool isMouseDown{false};
    bool isTrackMouseEvent{ false };
    int x{ 0 }, y{ 0 }, w{ 0 }, h{0};
    std::vector<std::function<void(const int&, const int&)>> mouseMoveHandlers;
    std::vector<std::function<void(const int&, const int&)>> mouseDragHandlers;
    std::vector<std::function<void(const int&, const int&)>> mouseDownHandlers;
    std::vector<std::function<void(const int&, const int&)>> mouseDBClickHandlers;

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
    void mouseMove(const int& x, const int& y);
    void mouseLeave();
    void mouseDown(const int& x, const int& y);
    void onClose();
};