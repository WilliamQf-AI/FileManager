#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <vector>
#include "include/core/SkCanvas.h"
#include "Layout.h"

class WindowBase;
class TitleBarBtns :public Layout
{
public:
    TitleBarBtns(WindowBase* root);
    ~TitleBarBtns();
    void paint(SkCanvas *canvas);
    void mouseMove(const int& x, const int& y);
    void mouseDown(const int& x, const int& y);
    int hoverIndex{ -1 };
private:
};