#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <vector>
#include "include/core/SkCanvas.h"
#include "ControlBase.h"
#include "TitleBarBtns.h"
#include "TitleBarTab.h"
#include "filesystem"
#include "functional"

class WindowMain;
class TitleBar : public ControlBase
{
public:
    TitleBar(WindowMain* root);
    ~TitleBar();
    int selectedTabIndex{0};
    void addTab(std::filesystem::path&& path,bool needRefresh=true);
    std::shared_ptr<TitleBarBtns> btns;
    std::vector<std::shared_ptr<TitleBarTab>> tabs;
    std::vector<std::function<void(TitleBarTab* tab)>> tabChangeEvents;
    POINT startPos;
    bool draggingWindow{ false };
private:
    void paint(SkCanvas* canvas) override;
    void mouseMove(const int& x, const int& y) override;
    void mouseDown(const int& x, const int& y) override;
    void mouseUp(const int& x, const int& y) override;
    void mouseDrag(const int& x, const int& y) override;
    void resize(const int& w, const int& h) override;
    void closeTab(TitleBarTab* tab);
    void selectTab(const int& index);
};