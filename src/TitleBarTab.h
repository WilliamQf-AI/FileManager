#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <vector>
#include "include/core/SkCanvas.h"
#include "Layout.h"

class WindowBase;
class TitleBarTab : public Layout
{
public:
    TitleBarTab(WindowBase* root);
    ~TitleBarTab();
};