#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <vector>
#include <chrono>
#include "include/core/SkCanvas.h"
#include "ControlBase.h"

class WindowMain;
class ContentPanel : public ControlBase
{
public:
    ContentPanel(WindowMain* root);
    ~ContentPanel();
    void paint(SkCanvas* canvas) override;
    void resize(const int& w, const int& h);
    void getRecentFiles();
private:
    void mouseMove(const int& x, const int& y);
    void mouseDown(const int& x, const int& y);
    void mouseUp(const int& x, const int& y);
    void mouseDrag(const int& x, const int& y);
    void mouseWheel(const int& x, const int& y, const int& delta);
    std::vector<std::tuple<std::wstring, 
        std::chrono::zoned_time<std::chrono::system_clock::duration,const std::chrono::time_zone*>>> files;
    float totalHeight{ 0 };
    bool hoverScroller{ false };
    SkRect scrollerRect;
    SkRect clipRect;
    double downY{ 0.f };
};