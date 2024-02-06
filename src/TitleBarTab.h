#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <vector>
#include "include/core/SkCanvas.h"
#include "ControlBase.h"

class WindowBase;
class TitleBarTab : public ControlBase
{
public:
    TitleBarTab(WindowBase* root);
    ~TitleBarTab();
    void paint(SkCanvas* canvas) override;
    bool isSelected{ true };
    bool isHovered{ false };
    bool isHoverCloseBtn{ false };
};