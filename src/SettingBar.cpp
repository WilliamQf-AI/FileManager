#include "SettingBar.h"

SettingBar::SettingBar(WindowBase* root) :ControlBase(root)
{
	YGNodeStyleSetFlexDirection(layout, YGFlexDirectionRow);
	YGNodeStyleSetHeight(layout, 0);
}

SettingBar::~SettingBar()
{
}

void SettingBar::paint(SkCanvas* canvas)
{
	auto rect = getRect();
	SkPaint paint;
	paint.setColor(0x55654321);
	canvas->drawRect(rect, paint);
	canvas->save();
	canvas->translate(rect.fLeft, rect.fTop);
	canvas->restore();
}