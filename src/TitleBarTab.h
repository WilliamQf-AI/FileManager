#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <vector>
#include "include/core/SkCanvas.h"
#include "ControlBase.h"
#include "filesystem"

class WindowMain;
class TitleBarTab : public ControlBase
{
public:
    TitleBarTab(WindowMain* root,std::filesystem::path& path);
    ~TitleBarTab();
    std::vector<std::wstring> history; //记录此tab对应路径的历史变化

    bool hoverChange(const int& x, const int& y);
    bool isSelected{ true };
    int hoverIndex{ -1 };
    std::wstring title;
    std::filesystem::path path;
    int historyNum;
    int orderNum;
private:
    void resize(const int& w, const int& h) override;
    void paint(SkCanvas* canvas) override;
};