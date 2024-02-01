#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <vector>
#include "include/core/SkCanvas.h"
#include "Layout.h"
#include "TitleBarBtns.h"

class WindowBase;
class TitleBar:public Layout
{
public:
    TitleBar(WindowBase* root);
    ~TitleBar();
    void paint(SkCanvas* canvas);
    std::shared_ptr<TitleBarBtns> btns;
private:
};