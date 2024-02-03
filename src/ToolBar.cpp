#include "ToolBar.h"
#include "WindowMain.h"
#include "App.h"

ToolBar::ToolBar(WindowBase* root) :ControlBase(root)
{
	YGNodeStyleSetFlexDirection(layout, YGFlexDirectionRow);
	YGNodeStyleSetWidthAuto(layout);
	YGNodeStyleSetHeight(layout, 60.f);
	YGNodeStyleSetAlignItems(layout, YGAlignCenter);

	auto toolLayout = YGNodeNew();
	YGNodeStyleSetHeight(toolLayout, 50.f);
	YGNodeStyleSetWidth(toolLayout,200.f);
	YGNodeStyleSetHeightAuto(toolLayout);
	YGNodeInsertChild(layout, toolLayout, 0);

	auto addressLayout = YGNodeNew();
	YGNodeStyleSetHeight(addressLayout, 40.f);
	YGNodeStyleSetFlexGrow(addressLayout, 1.f);
	YGNodeStyleSetMargin(addressLayout, YGEdgeLeft, 8.f);
	YGNodeStyleSetMargin(addressLayout, YGEdgeRight, 6.f);
	YGNodeInsertChild(layout, addressLayout, 1);

	auto searchLayout = YGNodeNew();
	YGNodeStyleSetHeight(searchLayout, 40.f);
	YGNodeStyleSetFlexGrow(searchLayout, 0.5f);
	YGNodeStyleSetMargin(searchLayout, YGEdgeLeft, 6.f);
	YGNodeStyleSetMargin(searchLayout, YGEdgeRight, 12.f);
	YGNodeInsertChild(layout, searchLayout, 2);
}

ToolBar::~ToolBar()
{
}

void ToolBar::paint(SkCanvas* canvas)
{
	auto rect = getRect();
	rect.fRight = 50.f;

	auto font = App::GetFontIcon();
	font->setSize(26.f);
	auto iconCode = (const char*)u8"\ue80b";
	auto pos = getStartPosOfIconAtCenterOfRect(iconCode, rect, font.get());
	SkPaint paint;
	paint.setColor(0xFF666666);
	canvas->drawString(iconCode, pos.fX, pos.fY, *font, paint);

	iconCode = (const char*)u8"\ue80c";
	canvas->drawString(iconCode, pos.fX+50, pos.fY, *font, paint);

	iconCode = (const char*)u8"\ue80a";
	canvas->drawString(iconCode, pos.fX + 100, pos.fY, *font, paint);

	iconCode = (const char*)u8"\ue741";
	canvas->drawString(iconCode, pos.fX + 150, pos.fY, *font, paint);

	paint.setColor(0xFFECEFF7);
	float radio{ 8.f };
	auto addressRect = getRect(YGNodeGetChild(layout, 1));
	addressRect.offsetTo(addressRect.fLeft, addressRect.fTop + rect.fTop);
	canvas->drawRoundRect(addressRect, radio, radio, paint);

	auto searchRect = getRect(YGNodeGetChild(layout, 2));
	searchRect.offsetTo(searchRect.fLeft, searchRect.fTop + rect.fTop);
	canvas->drawRoundRect(searchRect, radio, radio, paint);

	paint.setColor(0xFF999999);
	iconCode = (const char*)u8"\ue6a6";
	canvas->drawString(iconCode, searchRect.fLeft+8, pos.fY, *font, paint);

	paint.setColor(0xFFBBBBBB);
	auto fontText = App::GetFontText();
	std::wstring str = L"Powered by Everything";
	auto textLength = wcslen(str.data()) * 2;
	canvas->drawSimpleText(str.data(), textLength, SkTextEncoding::kUTF16, searchRect.fLeft + 38, pos.fY-4, *fontText, paint);
}
