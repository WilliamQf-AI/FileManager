#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <vector>
#include "include/core/SkCanvas.h"
#include "ControlBase.h"

class WindowMain;
class PathTool;
class PathInput;
class SearchInput;
class TitleBarTab;
class ToolBar : public ControlBase
{
public:
    ToolBar(WindowMain* root);
    ~ToolBar();
    void tabChange(TitleBarTab* tab, TitleBarTab* tabNew);
    std::shared_ptr<PathTool> pathTool;
    std::shared_ptr<PathInput> pathInput;
    std::shared_ptr<SearchInput> searchInput;
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