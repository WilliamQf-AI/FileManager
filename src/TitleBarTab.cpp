#include "TitleBarTab.h"

#include "yoga/Yoga.h"
#include "yoga/YGConfig.h"
#include "include/core/SkRRect.h"
#include "include/core/SkPixmap.h"
#include "include/core/SkBitmap.h"
#include "WindowBase.h"
#include "SystemIcon.h"
#include "App.h"

TitleBarTab::TitleBarTab(WindowBase* root) :ControlBase(root)
{
	YGNodeStyleSetFlexDirection(layout, YGFlexDirectionRow);
	YGNodeStyleSetWidthAuto(layout);
	YGNodeStyleSetHeightAuto(layout);
	YGNodeStyleSetMargin(layout, YGEdgeTop, 10.f);
	YGNodeStyleSetMargin(layout, YGEdgeLeft, 3.f);
	YGNodeStyleSetMargin(layout, YGEdgeRight, 3.f);
	YGNodeStyleSetFlexGrow(layout, 1.f);
	YGNodeStyleSetMaxWidth(layout, 200.f);
	YGNodeStyleSetAlignItems(layout, YGAlignCenter);

	auto iconLayout = YGNodeNew();
	YGNodeStyleSetMargin(iconLayout, YGEdgeLeft, 8.f);
	YGNodeStyleSetHeight(iconLayout, 26.f);
	YGNodeStyleSetWidth(iconLayout, 26.f);
	YGNodeInsertChild(layout, iconLayout, 0);


	auto titleLayout = YGNodeNew();
	YGNodeStyleSetWidthAuto(titleLayout);
	YGNodeStyleSetHeight(titleLayout, 26.f);
	YGNodeStyleSetFlexGrow(titleLayout, 1.f);
	YGNodeInsertChild(layout, titleLayout, 1);

	auto closeLayout = YGNodeNew();
	YGNodeStyleSetMargin(closeLayout, YGEdgeRight, 8.f);
	YGNodeStyleSetHeight(closeLayout, 26.f);
	YGNodeStyleSetWidth(closeLayout, 26.f);
	YGNodeInsertChild(layout, closeLayout, 2);
}

TitleBarTab::~TitleBarTab()
{
	//todo 移除元素时，释放layout
}

void TitleBarTab::paint(SkCanvas* canvas)
{	
	auto rect = getRect();
	SkPaint paint;
	paint.setAntiAlias(true);
	if (isSelected) {
		paint.setColor(0xFFFFFFFF);
		paint.setStyle(SkPaint::kFill_Style);
		SkVector radii[4] = { {6, 6}, {6, 6}, {0, 0}, {0, 0} };
		auto rr = SkRRect::MakeEmpty();
		rr.setRectRadii(rect, radii);
		canvas->drawRRect(rr, paint);
	}
	else if (isHovered) {
		paint.setColor(0x88FFFFFF);  //0xFFA8C7FA
		auto r = getRect();
		r.inset(4, 6);
		canvas->drawRoundRect(r, 6, 6, paint);
	}
	auto iconLayout = YGNodeGetChild(layout, 0);
	auto iconRect = getRect(iconLayout);
	iconRect.offsetTo(rect.fLeft+iconRect.fLeft,rect.fTop+iconRect.fTop);

	auto img = SystemIcon::getIcon(SIID_FOLDER,26); //CSIDL_QUICKACCESS
	canvas->drawImage(img, iconRect.centerX() - img->width()/2, iconRect.centerY() - img->height() / 2);

	paint.setColor(0xFF333333);
	auto titleLayout = YGNodeGetChild(layout, 1);
	auto titleRect = getRect(titleLayout);
	titleRect.offsetTo(rect.fLeft + titleRect.fLeft, rect.fTop + titleRect.fTop);
	std::wstring str = L"文件夹名称";
	auto textLength = wcslen(str.data()) * 2;
	auto fontText = App::GetFontText();
	fontText->setSize(16.f);
	auto posText = getStartPosOfIconAtCenterOfRect(str, titleRect, fontText.get());
	canvas->drawSimpleText(str.data(), textLength, SkTextEncoding::kUTF16, titleRect.fLeft, posText.fY, *fontText, paint);


	auto closeLayout = YGNodeGetChild(layout, 2);
	auto closeRect = getRect(closeLayout);
	closeRect.offsetTo(rect.fLeft + closeRect.fLeft, rect.fTop + closeRect.fTop);
	if (isHoverCloseBtn) {
		paint.setColor(0x18000000);
		canvas->drawRoundRect(closeRect, 6, 6, paint);
		paint.setColor(0xFF333333);
	}
	else {
		paint.setColor(0xFF888888);
	}
	
	auto font = App::GetFontIcon();
	font->setSize(20.f);
	paint.setAntiAlias(false);	
	auto iconCode = (const char*)u8"\ue6e7"; 
	auto pos = getStartPosOfIconAtCenterOfRect(iconCode, closeRect, font.get());
	canvas->drawString(iconCode, pos.fX, pos.fY, *font, paint);

	//canvas->drawSimpleText(iconCode, 3, SkTextEncoding::kUTF8,0, 0, *font,paint);
	//SystemIcon::reset();
	//PostMessage(root->hwnd, WM_DEBUG_MESSAGE, 0, 0);
}
