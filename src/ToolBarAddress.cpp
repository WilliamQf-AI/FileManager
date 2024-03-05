#include "ToolBarAddress.h"

#include "WindowMain.h"
#include "ToolBar.h"
#include "ToolBarBtn.h"
#include "App.h"
#include "TitleBar.h"

ToolBarAddress::ToolBarAddress(WindowMain* root) : ControlBase(root)
{
}

ToolBarAddress::~ToolBarAddress()
{
}

void ToolBarAddress::resize(const int& w, const int& h)
{
	isDirty = true;
	auto top = root->toolBar->rect.fTop + 10.f;
	auto left = root->toolBar->pathTool->rect.width() + 12.f;
	auto width = (root->w - left) / 3 * 2 - 12.f;
	rect.setXYWH(left, top, width, 40.f);
}

void ToolBarAddress::paint(SkCanvas* canvas)
{
	if (!needPaint(canvas)) return;
	SkPaint paint;
	auto font = App::GetFontIcon();
	font->setSize(26.f);
	if (isFocus) {
		paint.setAntiAlias(true);
		paint.setStroke(true);
		paint.setStrokeWidth(1.5f);
		paint.setColor(0xFF0B57D0);
		canvas->drawRoundRect(rect.makeInset(1.5f,1.5f), 6.f, 6.f, paint);
	}
	else {
		auto color = root->toolBar->hoverIndex == 4 ? 0xFFE0E3EA : 0xFFECEFF7;
		paint.setColor(color);
		canvas->drawRoundRect(rect, 6.f, 6.f, paint);
	}
	paint.setColor(0xFF999999);
	auto iconCode = (const char*)u8"\ue611";
	canvas->drawString(iconCode, rect.fRight - 70, rect.fTop + 29, *font, paint);
	iconCode = (const char*)u8"\ue764";
	canvas->drawString(iconCode, rect.fRight - 36, rect.fTop + 29, *font, paint);
	auto tab = root->titleBar->tabs[root->titleBar->selectedTabIndex].get();
	if (!tab->path.empty()) {
		auto color = root->toolBar->hoverIndex == 4 ? 0xFF333333 : 0xFF666666;
		paint.setColor(color);
		auto fontText = App::GetFontText();
		fontText->setSize(16.f);
		auto pathStr = tab->path.wstring();
		auto textLength = wcslen(pathStr.data()) * 2;
		canvas->drawSimpleText(pathStr.data(), textLength, SkTextEncoding::kUTF16,
			rect.fLeft + 12.f, rect.fTop+27.f, *fontText, paint);
	}
}

void ToolBarAddress::mouseDown(const int& x, const int& y)
{
	bool flag{ false };
	if (rect.contains(x, y)) {
		flag = true;
	}
	else {
		flag = false;
	}
	if (flag != isFocus) {
		isFocus = flag;
		repaint();
	}
	
}
