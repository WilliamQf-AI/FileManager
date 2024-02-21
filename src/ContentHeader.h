#pragma once
#include "ControlBase.h"
#include "include/core/SkCanvas.h"
#include "FileColumnHeader.h"

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
    std::vector<FileColumnHeader> columns;
    float paddingLeft{ 18.f };
    float paddingRight{ 38.f };
private:

};