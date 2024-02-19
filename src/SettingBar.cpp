#include "SettingBar.h"

SettingBar::SettingBar(WindowMain* root) :ControlBase(root)
{
}

SettingBar::~SettingBar()
{
}

void SettingBar::paint(SkCanvas* canvas)
{
	//SkPaint paint;
	//paint.setColor(0x55654321);
	//canvas->drawRect(rect, paint);
	if (!needPaint(canvas)) return;
}