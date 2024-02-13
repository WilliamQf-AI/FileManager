#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <vector>
#include <include/core/SkCanvas.h>
#include "ControlBase.h"


class WindowMain;
class BottomBar : public ControlBase
{
public:
    BottomBar(WindowMain* root);
    ~BottomBar();
    void paint(SkCanvas* canvas) override;
private:
};