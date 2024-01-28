#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <vector>
#include "include/core/SkCanvas.h"
#include "ControlBase.h"
#include "TitleBarBtns.h"

class TitleBar:public ControlBase
{
public:
    TitleBar();
    ~TitleBar();
    void paint(SkCanvas* canvas);
    void mousemove(const int& x, const int& y);
    std::shared_ptr<TitleBarBtns> btns;
private:
};