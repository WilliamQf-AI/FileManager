#pragma once
#include "ControlBase.h"
#include "include/core/SkCanvas.h"
#include <filesystem>
#include <any>
#include "FileColumn.h"

class WindowMain;
class ContentList : public ControlBase
{
public:
	ContentList(WindowMain* root);
	~ContentList();
    void paint(SkCanvas* canvas) override;
    void mouseMove(const int& x, const int& y);
    void mouseDown(const int& x, const int& y);
    void mouseUp(const int& x, const int& y);
    void mouseDrag(const int& x, const int& y);
    void resize(const int& w, const int& h);
    void mouseWheel(const int& x, const int& y, const int& delta);
private:
    void getRecentFiles();
    std::vector<std::vector<FileColumn>> columns;

    float totalHeight{ 0 };
    bool hoverScroller{ false };
    SkRect scrollerRect;
    double downY{ 0.f };
};