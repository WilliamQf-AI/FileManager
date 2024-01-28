#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <vector>
#include "include/core/SkCanvas.h"
#include "ControlBase.h"

class TitleBarBtns : public ControlBase
{
public:
    TitleBarBtns();
    ~TitleBarBtns();
    void paint(SkCanvas *canvas);
    void mousemove(const int& x, const int& y);
    int hoverIndex{ -1 };
private:
};