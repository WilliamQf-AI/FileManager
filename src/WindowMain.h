#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <vector>
#include "WindowBase.h"

class WindowMain : public WindowBase
{
public:
    WindowMain();
    ~WindowMain();
private:
    LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) override;
    void paintCanvas() override;
    void initSize();
};