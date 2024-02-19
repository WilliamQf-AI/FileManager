#include "ToolBar.h"
#include "WindowMain.h"
#include "App.h"
#include "TitleBar.h"

ToolBar::ToolBar(WindowMain* root) :ControlBase(root)
{

	root->resizeHandlers.push_back(
		std::bind(&ToolBar::resize, this, std::placeholders::_1, std::placeholders::_2)
	);

	

	//auto toolLayout = YGNodeNew();
	//YGNodeStyleSetHeight(toolLayout, 50.f);
	//YGNodeStyleSetWidth(toolLayout,200.f);
	//YGNodeStyleSetHeightAuto(toolLayout);
	//YGNodeInsertChild(layout, toolLayout, 0);

	//auto addressLayout = YGNodeNew();
	//YGNodeStyleSetHeight(addressLayout, 40.f);
	//YGNodeStyleSetFlexGrow(addressLayout, 1.f);
	//YGNodeStyleSetMargin(addressLayout, YGEdgeLeft, 8.f);
	//YGNodeStyleSetMargin(addressLayout, YGEdgeRight, 6.f);
	//YGNodeInsertChild(layout, addressLayout, 1);

	//auto searchLayout = YGNodeNew();
	//YGNodeStyleSetHeight(searchLayout, 40.f);
	//YGNodeStyleSetFlexGrow(searchLayout, 0.5f);
	//YGNodeStyleSetMargin(searchLayout, YGEdgeLeft, 6.f);
	//YGNodeStyleSetMargin(searchLayout, YGEdgeRight, 12.f);
	//YGNodeInsertChild(layout, searchLayout, 2);
}

ToolBar::~ToolBar()
{
}

void ToolBar::paint(SkCanvas* canvas)
{
	if (!needPaint(canvas)) return;
	auto iconRect = SkRect::MakeXYWH(0, rect.fTop, 50, rect.height());
	auto font = App::GetFontIcon();
	font->setSize(26.f);
	auto iconCode = (const char*)u8"\ue80b";
	auto pos = getStartPosOfIconAtCenterOfRect(iconCode, iconRect, font.get());
	SkPaint paint;
	paint.setColor(0xFF666666);
	canvas->drawString(iconCode, pos.fX, pos.fY, *font, paint);
	iconCode = (const char*)u8"\ue80c";
	canvas->drawString(iconCode, pos.fX+50, pos.fY, *font, paint);
	iconCode = (const char*)u8"\ue80a";
	canvas->drawString(iconCode, pos.fX + 100, pos.fY, *font, paint);
	iconCode = (const char*)u8"\ue741";
	canvas->drawString(iconCode, pos.fX + 150, pos.fY, *font, paint);

	auto w = (root->w - 232) / 3 * 2;
	auto addressRect = SkRect::MakeXYWH(208, rect.fTop+10, w, 40);
	paint.setColor(0xFFECEFF7);
	float radio{ 8.f };
	canvas->drawRoundRect(addressRect, radio, radio, paint);

	auto searchRect = SkRect::MakeXYWH(addressRect.fRight+12.f, rect.fTop + 10, w/2, 40);
	canvas->drawRoundRect(searchRect, radio, radio, paint);

	paint.setColor(0xFF999999);
	iconCode = (const char*)u8"\ue611";
	canvas->drawString(iconCode, addressRect.fRight - 68, pos.fY, *font, paint);
	iconCode = (const char*)u8"\ue764";
	canvas->drawString(iconCode, addressRect.fRight - 34, pos.fY, *font, paint);
	iconCode = (const char*)u8"\ue6a6";
	canvas->drawString(iconCode, searchRect.fLeft+8, pos.fY, *font, paint);
	paint.setColor(0xFFBBBBBB);
	auto fontText = App::GetFontText();
	std::wstring str = L"Powered by Everything";
	auto textLength = wcslen(str.data()) * 2;
	canvas->drawSimpleText(str.data(), textLength, SkTextEncoding::kUTF16, searchRect.fLeft + 38, pos.fY-4, *fontText, paint);
	paint.setColor(0xFFE8E8E8);
	canvas->drawLine(0.f, rect.fBottom-1, rect.fRight, rect.fBottom-1, paint);
}

void ToolBar::resize(const int& w, const int& h)
{
	auto top = root->titleBar->rect.height();
	rect.setXYWH(0.f, top, root->w, 60.f);
}
