#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <vector>
#include "include/core/SkCanvas.h"
#include "ControlBase.h"

class WindowMain;
class ToolBarBtn;
class ToolBarAddress;
class ToolBarSearch;
class TitleBarTab;
class ToolBar : public ControlBase
{
public:
    ToolBar(WindowMain* root);
    ~ToolBar();
    void tabChange(TitleBarTab* tab, TitleBarTab* tabNew);
    std::shared_ptr<ToolBarBtn> toolBarBtn;
    std::shared_ptr<ToolBarAddress> toolBarAddress;
    std::shared_ptr<ToolBarSearch> toolBarSearch;
    int hoverIndex{ -1 };
    int mouseDownX{ -1 };
private:
    void paint(SkCanvas* canvas) override;
    void resize(const int& w, const int& h) override;
    void mouseMove(const int& x, const int& y) override;
    void mouseDown(const int& x, const int& y) override;
    void mouseDrag(const int& x, const int& y) override;
    void mouseUp(const int& x, const int& y) override;
};