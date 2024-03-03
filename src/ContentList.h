#pragma once
#include "ControlBase.h"
#include "include/core/SkCanvas.h"
#include <filesystem>
#include <any>
#include "FileColumn.h"

class WindowMain;
class TitleBarTab;
class ContentList : public ControlBase
{
public:
	ContentList(WindowMain* root);
	~ContentList();
    void tabChange(TitleBarTab* tab, TitleBarTab* tabNew);
    void resize(const int& w, const int& h) override;
private:
    void paint(SkCanvas* canvas) override;
    void mouseMove(const int& x, const int& y) override;
    void mouseDown(const int& x, const int& y) override;
    void mouseUp(const int& x, const int& y) override;
    void mouseDrag(const int& x, const int& y) override;
    void mouseWheel(const int& x, const int& y, const int& delta) override;
    void getRecentFiles();
    std::vector<std::vector<FileColumn>> files;
    void setRightScroller();
    void setBottomScroller();
    float totalHeight{ 0 };
    int hoverScroller{ -1 };
    SkRect scrollerRight;
    SkRect scrollerBottom;
    float downX{ 0.f };
    float downY{ 0.f };
    int hoverIndex{ -1 };
};