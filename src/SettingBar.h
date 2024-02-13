#pragma once
#include "ControlBase.h"
#include "include/core/SkCanvas.h"

class WindowMain;
class SettingBar : public ControlBase
{
public:
	SettingBar(WindowMain* root);
	~SettingBar();
	void paint(SkCanvas* canvas) override;
private:

};