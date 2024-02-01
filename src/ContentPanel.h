#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <vector>
#include "include/core/SkCanvas.h"
#include "Layout.h"

class WindowBase;
class ContentPanel:public Layout
{
public:
    ContentPanel(WindowBase* root);
    ~ContentPanel();
    void paint(SkCanvas* canvas);
private:
};