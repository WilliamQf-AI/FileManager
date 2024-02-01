#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <vector>
#include "include/core/SkCanvas.h"
#include "Layout.h"


class WindowBase;
class BottomBar:public Layout
{
public:
    BottomBar(WindowBase* root);
    ~BottomBar();

private:
};