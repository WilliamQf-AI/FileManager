#pragma once
#include "ControlBase.h"
#include "include/core/SkCanvas.h"

class WindowMain;
class SettingBar : public ControlBase
{
public:
	SettingBar(WindowMain* root);
	~SettingBar();
private:
	void paint(SkCanvas* canvas) override;
	void resize(const int& w, const int& h) override;

};