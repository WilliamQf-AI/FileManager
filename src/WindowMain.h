#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <vector>
#include <functional>
#include "include/core/SkSurface.h"
#include "src/base/SkAutoMalloc.h"

#define WM_FLASH_CURSOR (WM_APP+8)
#define WM_DEBUG_MESSAGE (WM_APP+9)
using EventHandlerType = void(*)(const int&, const int&);

class TitleBar;
class ToolBar;
class LeftPanel;
class ContentPanel;
class WindowMain
{
public:
    WindowMain();
    virtual ~WindowMain();
    void show();
    void clearTimeout(const unsigned int& id);
    void setTimeout(const unsigned int& id, const unsigned int& ms);
    HWND hwnd{nullptr};
    HWND hwndToolTip{nullptr};
    bool isMouseDown{false};
    bool isTrackMouseEvent{ false };
    int w{ 1200 }, h{800};
    std::vector<std::function<void(const int&, const int&)>> mouseMoveHandlers;
    std::vector<std::function<void(const int&, const int&)>> mouseDragHandlers;
    std::vector<std::function<void(const int&, const int&)>> mouseDownHandlers;
    std::vector<std::function<void(const int&, const int&)>> mouseUpHandlers;
    std::vector<std::function<void(const int&, const int&)>> mouseDBClickHandlers;
    std::vector<std::function<void(const int&, const int&)>> resizeHandlers;
    std::vector<std::function<void(const int&, const int& ,const int&)>> mouseWheelHandlers;
    std::shared_ptr<TitleBar> titleBar;
    std::shared_ptr<ToolBar> toolBar;
    std::shared_ptr<LeftPanel> leftPanel;
    std::shared_ptr<ContentPanel> contentPanel;

protected:
    void initWindow();
    void paintWindow();
    virtual void onSize(const int& w, const int& h);
private:
    static LRESULT CALLBACK RouteWindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    SkAutoMalloc surfaceMemory;
    sk_sp<SkSurface> surface;
    int nctest(const int& x,const int& y);
    void mouseMove(const int& x, const int& y);
    void mouseLeave();
    void mouseDown(const int& x, const int& y);
    void mouseUp(const int& x, const int& y);
    void mouseWheel(const int& x, const int& y,const int& delta);
    void onClose();
    void onGetMaxMinMizeInfo(MINMAXINFO* mminfo);
};