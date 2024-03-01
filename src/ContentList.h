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
    void paint(SkCanvas* canvas) override;
    void mouseMove(const int& x, const int& y) override;
    void mouseDown(const int& x, const int& y) override;
    void mouseUp(const int& x, const int& y) override;
    void mouseDrag(const int& x, const int& y) override;
    void resize(const int& w, const int& h) override;
    void mouseWheel(const int& x, const int& y, const int& delta) override;
    void tabChange(TitleBarTab* tab, TitleBarTab* tabNew);
private:
    void getRecentFiles();
    std::vector<std::vector<FileColumn>> files;
    void setScrollerRect();
    float totalHeight{ 0 };
    bool hoverScroller{ false };
    SkRect scrollerRect;
    double downY{ 0.f };
};