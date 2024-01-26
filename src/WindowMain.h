#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <vector>
#include <memory>
#include "include/core/SkCanvas.h"
#include "WindowBase.h"
#include "TitleBar.h"

class WindowMain : public WindowBase
{
public:
    WindowMain();
    ~WindowMain();
    void init();
    std::shared_ptr<TitleBar> titleBar;
private:
    LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) override;
    void paint(SkCanvas* canvas) override;
    void initSize();
};