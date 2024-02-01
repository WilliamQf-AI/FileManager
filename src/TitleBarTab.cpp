#include "TitleBarTab.h"

#include "yoga/Yoga.h"
#include "yoga/YGConfig.h"
#include "include/core/SkRRect.h"
#include "include/core/SkPixmap.h"
#include "include/core/SkBitmap.h"
#include "WindowBase.h"
#include "SystemIcon.h"

TitleBarTab::TitleBarTab(WindowBase* root) :Layout(root)
{
	YGNodeStyleSetFlexDirection(layout, YGFlexDirectionRow);
	YGNodeStyleSetWidthAuto(layout);
	YGNodeStyleSetMaxWidth(layout, 260.f);
	YGNodeStyleSetHeight(layout, 46.f);
	YGNodeStyleSetMargin(layout, YGEdgeTop, 10.f);
	YGNodeStyleSetAlignItems(layout, YGAlignCenter);
}

TitleBarTab::~TitleBarTab()
{
}

void TitleBarTab::paint(SkCanvas* canvas)
{	
	auto rect = getOffsetRect();
	SkPaint paint;
	paint.setAntiAlias(true);
	if (isSelected) {
		paint.setColor(0xFFFFFFFF);
	}
	paint.setStyle(SkPaint::kFill_Style);
	SkVector radii[4] = { {6, 6}, {6, 6}, {0, 0}, {0, 0} };
	auto rr = SkRRect::MakeEmpty();
	rr.setRectRadii(rect, radii);
	canvas->drawRRect(rr, paint);


	auto img = SystemIcon::getIcon(SIID_FOLDER);
	canvas->drawImage(img, 8, 22);
	//SystemIcon::reset();
	//PostMessage(root->hwnd, WM_DEBUG_MESSAGE, 0, 0);
}
