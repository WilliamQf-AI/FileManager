#include "LeftPanel.h"
#include "WindowMain.h"

LeftPanel::LeftPanel(WindowBase* root) :ControlBase(root)
{
	YGNodeStyleSetHeightAuto(layout);
	YGNodeStyleSetWidth(layout, 450.f);
}

LeftPanel::~LeftPanel()
{
}

void LeftPanel::paint(SkCanvas* canvas)
{
	auto parent = YGNodeGetParent(layout);	
	auto rect = getRect();
	rect.offsetTo(rect.fLeft, YGNodeLayoutGetTop(parent));
	SkPaint paint;
	paint.setColor(0xFFECEFF7);
	paint.setStyle(SkPaint::kFill_Style);
	canvas->drawRect(rect, paint);
}

void LeftPanel::mousemove(const int& x, const int& y)
{
}
