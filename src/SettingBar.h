#pragma once
#include "ControlBase.h"
#include "include/core/SkCanvas.h"

class WindowBase;
class SettingBar : public ControlBase
{
public:
	SettingBar(WindowBase* root);
	~SettingBar();
	void paint(SkCanvas* canvas) override;
private:

};