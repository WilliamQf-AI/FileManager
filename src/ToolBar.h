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
class ToolBar : public ControlBase
{
public:
    ToolBar(WindowMain* root);
    ~ToolBar();
    std::shared_ptr<PathTool> pathTool;
    std::shared_ptr<PathInput> pathInput;
    std::shared_ptr<SearchInput> searchInput;
private:
    void paint(SkCanvas* canvas) override;
    void resize(const int& w, const int& h) override;
};