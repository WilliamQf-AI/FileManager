#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <vector>
#include "include/core/SkCanvas.h"
#include "ControlBase.h"

class WindowBase;
class ToolBar : public ControlBase
{
public:
    ToolBar(WindowBase* root);
    ~ToolBar();
    void paint(SkCanvas* canvas);
private:
};