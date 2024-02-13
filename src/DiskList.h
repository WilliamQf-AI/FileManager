#pragma once
#include "ControlBase.h"
#include "include/core/SkCanvas.h"

class WindowBase;
class DiskList : public ControlBase
{
public:
	DiskList(WindowBase* root);
	~DiskList();
	void paint(SkCanvas* canvas) override;
	std::vector<std::tuple<char, double, double, bool>> driveInfo;
	float y;
private:
	void resize(const int& w, const int& h);
	void mouseMove(const int& x, const int& y);
	void mouseDown(const int& x, const int& y);
	int hoverIndex{ -1 };
};

