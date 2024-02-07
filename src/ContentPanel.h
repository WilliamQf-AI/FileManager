#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <vector>
#include <chrono>
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
    void getRecentFiles();
private:
    std::vector<std::tuple<std::wstring, 
        std::chrono::zoned_time<std::chrono::system_clock::duration,const std::chrono::time_zone*>>> files;
};