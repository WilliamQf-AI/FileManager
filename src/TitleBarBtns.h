#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <vector>
#include "include/core/SkCanvas.h"
#include "ControlBase.h"

class WindowMain;
class TitleBarBtns : public ControlBase
{
public:
    TitleBarBtns(WindowMain* root);
    ~TitleBarBtns();
    void paint(SkCanvas *canvas) override;
    void mouseMove(const int& x, const int& y);
    void mouseDown(const int& x, const int& y);
    void resize(const int& w, const int& h);
    int hoverIndex{ -1 };
private:
};