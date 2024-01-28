#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <vector>
#include <memory>
#include "include/core/SkCanvas.h"
#include "WindowBase.h"
#include "TitleBar.h"
#include "ToolBar.h"
#include "LeftPanel.h"
#include "ContentPanel.h"
#include "BottomBar.h"

class WindowMain : public WindowBase
{
public:
    WindowMain();
    ~WindowMain();
    void init();
    void mousemove(const int& x, const int& y);
    std::shared_ptr<TitleBar> titleBar;
    std::shared_ptr<ToolBar> toolBar;
    std::shared_ptr<LeftPanel> leftPanel;
    std::shared_ptr<ContentPanel> contentPanel;
    std::shared_ptr<BottomBar> bottomBar;
private:
    LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) override;
    void paint(SkCanvas* canvas) override;
    void initSize();
};