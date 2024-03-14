#pragma once
#include "ControlBase.h"
#include "include/core/SkCanvas.h"
#include <filesystem>
#include "Column.h"

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
    void rightScrollerMove(const float& span);
    void bottomScrollerMove(const float& span);
    void getFiles(std::filesystem::path& path);
    std::vector<std::vector<std::shared_ptr<ColumnBase>>> files;
    void setRightScroller();
    void setBottomScroller();
    float totalHeight{ 0 };
    int hoverScroller{ -1 };
    SkRect scrollerRight;
    SkRect scrollerBottom;
    float downX{ 0.f };
    float downYRightScrollerSpan{ 0.f };
    int hoverIndex{ -1 };
    float lineHieght{ 48.f };
    float scrollerMiniSize{ 60.f };
    float offsetTop{ 0.f };
    std::chrono::system_clock::time_point mouseDownTime;
};