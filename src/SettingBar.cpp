#include "SettingBar.h"
#include "WindowMain.h"

SettingBar::SettingBar(WindowMain* root) :ControlBase(root)
{
	root->resizeHandlers.push_back(
		std::bind(&SettingBar::resize, this, std::placeholders::_1, std::placeholders::_2)
	);
}

SettingBar::~SettingBar()
{
}

void SettingBar::paint(SkCanvas* canvas)
{
	//SkPaint paint;
	//paint.setColor(0x55654321);
	//canvas->drawRect(rect, paint);
	if (!needPaint(canvas, 0xFFF8FBFF)) return;
}

void SettingBar::resize(const int& w, const int& h)
{
}
