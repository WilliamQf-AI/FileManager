#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <vector>
#include "include/core/SkCanvas.h"
#include "ControlBase.h"

class WindowMain;
class TitleBarTab : public ControlBase
{
public:
    TitleBarTab(WindowMain* root,std::wstring&& title);
    ~TitleBarTab();
    bool hoverChange(const int& x, const int& y);
    void resize(const int& w, const int& h);
    void paint(SkCanvas* canvas) override;
    bool isSelected{ true };
    int hoverIndex{ -1 };
    std::wstring title;
    unsigned historyNum;
};