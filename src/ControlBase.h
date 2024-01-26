#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <vector>
#include "include/core/SkCanvas.h"
#include "yoga/YGNode.h"

class WindowMain;
class ControlBase
{
public:
    ControlBase();
    ~ControlBase();
    void init(WindowMain* win);

private:
    WindowMain* win{nullptr};
    YGNode* layout;
};