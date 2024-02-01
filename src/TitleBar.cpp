#include "TitleBar.h"
#include "WindowMain.h"
#include "App.h"
#include "include/core/SkFontMetrics.h"
#include "TitleBarBtns.h"

class WindowBase;
TitleBar::TitleBar(WindowBase* root):Layout(root)
{
	YGNodeStyleSetFlexDirection(layout, YGFlexDirectionRow);
	YGNodeStyleSetWidthAuto(layout);
	YGNodeStyleSetHeight(layout, 56.f);
	YGNodeStyleSetPadding(layout, YGEdgeLeft, 12.f);
	

	auto tabLayout = new Layout();
	YGNodeStyleSetFlexGrow(tabLayout->layout, 1.f);
	auto tab1 = std::make_shared<TitleBarTab>(root);
	tabLayout->addChild(tab1.get());
	tabs.push_back(std::move(tab1));
	this->addChild(tabLayout);

	btns = std::make_shared<TitleBarBtns>(root);
	this->addChild(btns.get());
}

TitleBar::~TitleBar()
{
}

void TitleBar::paint(SkCanvas* canvas)
{	
	auto left = YGNodeLayoutGetPadding(layout, YGEdgeLeft);
	auto rect = getOffsetRect();
	SkPaint paint;
	paint.setColor(0xFFD3E3FD);
	paint.setStyle(SkPaint::kFill_Style);
	canvas->drawRect(rect, paint);
	canvas->save();
	canvas->translate(left, 0);
	for (auto& tab:tabs)
	{
		tab->paint(canvas);
	}
	canvas->restore();
	btns->paint(canvas);
}
