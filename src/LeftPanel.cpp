#include "LeftPanel.h"
#include "WindowMain.h"

LeftPanel::LeftPanel()
{
	
	YGNodeStyleSetHeightAuto(layout);
	YGNodeStyleSetWidth(layout, 450.f);

}

LeftPanel::~LeftPanel()
{
}

void LeftPanel::paint(SkCanvas* canvas)
{
	auto p = YGNodeGetParent(layout);
	auto h1 = YGNodeLayoutGetHeight(p);


	auto w = YGNodeLayoutGetWidth(layout);
	auto h = YGNodeLayoutGetHeight(layout);
	auto pos = getPos();
	SkPaint paint;
	paint.setColor(0xFFECEFF7);
	paint.setStyle(SkPaint::kFill_Style);
	canvas->drawRect(SkRect::MakeXYWH(pos.fX, pos.fY, w, h), paint);
}
