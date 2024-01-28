#include "TitleBar.h"
#include "WindowMain.h"
#include "App.h"
#include "include/core/SkFontMetrics.h"
#include "TitleBarBtns.h"


TitleBar::TitleBar()
{
	YGNodeStyleSetFlexDirection(layout, YGFlexDirectionRow);
	YGNodeStyleSetWidthAuto(layout);
	YGNodeStyleSetHeight(layout, 60.f);

	auto tabLayout = new Layout();
	YGNodeStyleSetFlexGrow(tabLayout->layout, 1.f);
	this->addLayoutChild(tabLayout);

	btns = std::make_shared<TitleBarBtns>();
	this->addLayoutChild(btns.get());
}

TitleBar::~TitleBar()
{
}

void TitleBar::paint(SkCanvas* canvas)
{	
	auto rect = getOffsetRect();
	SkPaint paint;
	paint.setColor(0xFFD3E3FD);
	paint.setStyle(SkPaint::kFill_Style);
	canvas->drawRect(rect, paint);
	btns->paint(canvas);
}

void TitleBar::mousemove(const int& x, const int& y)
{
	btns->mousemove(x, y);
}
