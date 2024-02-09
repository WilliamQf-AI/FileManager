#pragma once
#include "ControlBase.h"
#include "include/core/SkCanvas.h"
class WindowBase;
class QuickBtn : public ControlBase
{
public:
	QuickBtn(WindowBase* root);
	~QuickBtn();
	void paint(SkCanvas* canvas) override;
private:
	void resize(const int& w, const int& h);
};