#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <vector>
#include "include/core/SkCanvas.h"
#include "yoga/Yoga.h"

class WindowMain;
class ControlBase
{
public:
    ControlBase();
    ~ControlBase();
    void init(WindowMain* win);
    WindowMain* win{ nullptr };
    YGNode* layout;

private:
};