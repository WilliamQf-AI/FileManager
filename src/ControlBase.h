#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <vector>
#include "include/core/SkCanvas.h"
#include "yoga/Yoga.h"
#include "Layout.h"

class WindowMain;
class ControlBase:public Layout
{
public:
    ControlBase();
    ~ControlBase();

private:
};