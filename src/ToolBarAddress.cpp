#include "ToolBarAddress.h"
#include "WindowMain.h"
#include "ToolBar.h"
#include "ToolBarBtn.h"
#include "App.h"
#include "TitleBar.h"
#include "TitleBar.h"
#include "TitleBarTab.h"

ToolBarAddress::ToolBarAddress(WindowMain* root) : ToolBarInputBase(root)
{
	auto func = std::bind(&ToolBarAddress::tabChange, this, std::placeholders::_1, std::placeholders::_2);
	root->titleBar->tabChangeEvents.push_back(std::move(func));

	paddingLeft = 14.f;
	paddingRight = 68.f;
	hoverIndexVal = 4;
	timerID = WM_APP + 2;
}

ToolBarAddress::~ToolBarAddress()
{
}

void ToolBarAddress::tabChange(TitleBarTab* tab, TitleBarTab* tabNew)
{
	address = tabNew->path.wstring();
}

void ToolBarAddress::resize(const int& w, const int& h)
{
	isDirty = true;
	auto top = root->toolBar->rect.fTop + 10.f;
	auto left = root->toolBar->toolBarBtn->rect.width() + 12.f;
	auto width = (root->w - left) / 3 * 2 - 12.f;
	rect.setXYWH(left, top, width, 40.f);
}
void ToolBarAddress::paint2(SkCanvas* canvas)
{
	SkPaint paint;
	auto font = App::GetFontIcon();
	font->setSize(26.f);
	if (root->toolBar->hoverIndex == 5) {
		paint.setColor(0xFFE0E3EA);
		auto r = SkRect::MakeLTRB(rect.fRight - 72, rect.fTop + 7, rect.fRight - 42, rect.fBottom - 7);
		canvas->drawRoundRect(r,3.f,3.f,paint);
		paint.setColor(0xFF333333);
	}
	else {
		paint.setColor(0xFF999999);
	}
	auto iconCode = (const char*)u8"\ue611";
	canvas->drawString(iconCode, rect.fRight - 70, rect.fTop + 29, *font, paint);
	if (root->toolBar->hoverIndex == 6) {
		paint.setColor(0xFFE0E3EA);
		auto r = SkRect::MakeLTRB(rect.fRight - 38, rect.fTop + 7, rect.fRight - 8, rect.fBottom - 7);
		canvas->drawRoundRect(r, 3.f, 3.f, paint);
		paint.setColor(0xFF333333);
	}
	else {
		paint.setColor(0xFF999999);
	}
	iconCode = (const char*)u8"\ue764";
	canvas->drawString(iconCode, rect.fRight - 36, rect.fTop + 29, *font, paint);
	if (address.empty()) {
		return;
	}
	auto color = root->toolBar->hoverIndex == 4 ? 0xFF333333 : 0xFF666666;
	paint.setColor(color);
	auto fontText = App::GetFontText();
	fontText->setSize(16.f);
	auto len = wcslen(address.data()) * 2;
	canvas->drawSimpleText(address.data(), len, SkTextEncoding::kUTF16,
		rect.fLeft + paddingLeft, rect.fTop + 27.f, *fontText, paint);
}
