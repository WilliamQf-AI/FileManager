#include "TitleBar.h"
#include "WindowMain.h"

TitleBar::TitleBar()
{
	YGNodeStyleSetWidthAuto(layout);
	YGNodeStyleSetHeight(layout, 50.f);
}

TitleBar::~TitleBar()
{
}

void TitleBar::paint(SkCanvas* canvas)
{	
	auto w = YGNodeLayoutGetWidth(layout);
	auto h = YGNodeLayoutGetHeight(layout);
	auto x = YGNodeLayoutGetLeft(layout);
	auto y = YGNodeLayoutGetTop(layout);
	SkPaint paint;
	paint.setColor(0xFFD3E3FD);
	paint.setStyle(SkPaint::kFill_Style);
	canvas->drawRect(SkRect::MakeXYWH(x, y, w, h), paint);
}
