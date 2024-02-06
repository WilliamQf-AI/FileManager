#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <vector>
#include <tuple>
#include "include/core/SkCanvas.h"
#include "ControlBase.h"
#include "FavoritePath.h"
#include "SettingBar.h"

class WindowBase;
class LeftPanel : public ControlBase
{
public:
    LeftPanel(WindowBase* root);
    ~LeftPanel();
    void paint(SkCanvas* canvas);
    void mousemove(const int& x, const int& y);
private:
    std::vector<std::tuple<char, double, double,bool>> driveInfo;
    std::shared_ptr<FavoritePath> favoritePath;
    std::shared_ptr<SettingBar> settingBar;
};