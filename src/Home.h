#pragma once
#include "ControlBase.h"
#include "include/core/SkCanvas.h"
class WindowMain;
class Home : public ControlBase
{
public:
	Home(WindowMain* root);
	~Home();
	void paint(SkCanvas* canvas) override;
private:
	void resize(const int& w, const int& h);
};
