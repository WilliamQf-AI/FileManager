#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <vector>
#include "include/core/SkCanvas.h"
#include "Layout.h"

class WindowBase;
class ToolBar :public Layout
{
public:
    ToolBar(WindowBase* root);
    ~ToolBar();
private:
};