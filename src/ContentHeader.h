#pragma once
#include "ControlBase.h"
#include "include/core/SkCanvas.h"

class WindowMain;
class ContentHeader : public ControlBase
{
public:
	ContentHeader(WindowMain* root);
	~ContentHeader();
    void paint(SkCanvas* canvas) override;
    void mouseMove(const int& x, const int& y);
    void mouseDown(const int& x, const int& y);
    void mouseUp(const int& x, const int& y);
    void mouseDrag(const int& x, const int& y);
    void resize(const int& w, const int& h);
    std::vector<std::tuple<std::wstring, float, const char*>> columns;
private:

};