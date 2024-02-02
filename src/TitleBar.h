#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <vector>
#include "include/core/SkCanvas.h"
#include "ControlBase.h"
#include "TitleBarBtns.h"
#include "TitleBarTab.h"

class WindowBase;
class TitleBar : public ControlBase
{
public:
    TitleBar(WindowBase* root);
    ~TitleBar();
    void paint(SkCanvas* canvas);
    std::shared_ptr<TitleBarBtns> btns;
    std::vector<std::shared_ptr<TitleBarTab>> tabs;
    
private:
};