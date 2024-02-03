#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <vector>
#include "include/core/SkCanvas.h"
#include "ControlBase.h"
#include "TitleBarBtns.h"
#include "TitleBarTab.h"

class WindowBase;
class TitleBar : public ControlBase
{
public:
    TitleBar(WindowBase* root);
    ~TitleBar();
    void paint(SkCanvas* canvas);
    void mouseMove(const int& x, const int& y);
    void mouseDown(const int& x, const int& y);
    void mouseUp(const int& x, const int& y);
    void mouseDrag(const int& x, const int& y);
    std::shared_ptr<TitleBarBtns> btns;
    std::vector<std::shared_ptr<TitleBarTab>> tabs;
    POINT startPos;
    bool draggingWindow{ false };
private:
};