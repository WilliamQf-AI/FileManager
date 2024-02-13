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
#include "QuickBtn.h"
#include "DiskList.h"

class WindowBase;
class LeftPanel : public ControlBase
{
public:
    LeftPanel(WindowBase* root);
    ~LeftPanel();
    void paint(SkCanvas* canvas) override;

    void resize(const int& w, const int& h);
private:
    std::shared_ptr<FavoritePath> favoritePath;
    std::shared_ptr<SettingBar> settingBar;
    std::shared_ptr<QuickBtn> quickBtn;
    std::shared_ptr<DiskList> diskList;
};