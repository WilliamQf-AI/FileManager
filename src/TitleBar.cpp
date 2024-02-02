#include "TitleBar.h"
#include "WindowMain.h"
#include "App.h"
#include "include/core/SkFontMetrics.h"
#include "TitleBarBtns.h"

class WindowBase;
TitleBar::TitleBar(WindowBase* root) :ControlBase(root)
{
	auto tab1 = std::make_shared<TitleBarTab>(root);
	tab1->isSelected = false;
	tabs.push_back(tab1);
	auto tab2 = std::make_shared<TitleBarTab>(root);
	tabs.push_back(tab2);
	btns = std::make_shared<TitleBarBtns>(root);


	YGNodeStyleSetFlexDirection(layout, YGFlexDirectionRow);
	YGNodeStyleSetWidthAuto(layout);
	YGNodeStyleSetFlexGrow(layout, 1.f);
	YGNodeStyleSetMaxHeight(layout, 56.f);
	YGNodeStyleSetPadding(layout, YGEdgeLeft, 12.f);
	
	auto tabLayout = YGNodeNew();
	YGNodeStyleSetMaxHeight(layout, 56.f);
	YGNodeStyleSetFlexDirection(tabLayout, YGFlexDirectionRow);
	YGNodeStyleSetFlexGrow(tabLayout, 1.f);
	YGNodeStyleSetWidthAuto(tabLayout);
	YGNodeInsertChild(tabLayout, tab1->layout, 0);
	YGNodeInsertChild(tabLayout, tab2->layout, 1);

	YGNodeInsertChild(layout, tabLayout, 0);
	YGNodeInsertChild(layout, btns->layout, 1);
}

TitleBar::~TitleBar()
{
}

void TitleBar::paint(SkCanvas* canvas)
{	
	auto left = YGNodeLayoutGetPadding(layout, YGEdgeLeft);
	auto rect = getRect();
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
