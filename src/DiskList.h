#pragma once
#include "ControlBase.h"
#include "include/core/SkCanvas.h"

class WindowMain;
class DiskList : public ControlBase
{
public:
	DiskList(WindowMain* root);
	~DiskList();
	std::vector<std::tuple<char, double, double, bool>> driveInfo;
	float y;
private:
	void paint(SkCanvas* canvas) override;
	void resize(const int& w, const int& h) override;
	void mouseMove(const int& x, const int& y) override;
	void mouseDown(const int& x, const int& y) override;
	int hoverIndex{ -1 };
};

