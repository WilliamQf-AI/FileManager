#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <vector>
#include "include/core/SkCanvas.h"
#include "Layout.h"

class WindowBase;
class LeftPanel :public Layout
{
public:
    LeftPanel(WindowBase* root);
    ~LeftPanel();
    void paint(SkCanvas* canvas);
    void mousemove(const int& x, const int& y);
private:
};