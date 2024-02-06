#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <vector>
#include "include/core/SkCanvas.h"
#include "ControlBase.h"

class WindowBase;
class ContentPanel : public ControlBase
{
public:
    ContentPanel(WindowBase* root);
    ~ContentPanel();
    void paint(SkCanvas* canvas) override;
    void resize(const int& w, const int& h);
private:
};