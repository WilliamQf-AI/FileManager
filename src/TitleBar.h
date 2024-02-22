#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <vector>
#include "include/core/SkCanvas.h"
#include "ControlBase.h"
#include "TitleBarBtns.h"
#include "TitleBarTab.h"

class WindowMain;
class TitleBar : public ControlBase
{
public:
    TitleBar(WindowMain* root);
    ~TitleBar();
    void addTab(bool needRefresh=true);
    std::shared_ptr<TitleBarBtns> btns;
    std::vector<std::shared_ptr<TitleBarTab>> tabs;
    POINT startPos;
    bool draggingWindow{ false };
private:
    void paint(SkCanvas* canvas) override;
    void mouseMove(const int& x, const int& y) override;
    void mouseDown(const int& x, const int& y) override;
    void mouseUp(const int& x, const int& y) override;
    void mouseDrag(const int& x, const int& y) override;
    void resize(const int& w, const int& h) override;
};