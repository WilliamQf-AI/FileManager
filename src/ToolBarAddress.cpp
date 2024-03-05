#include "ToolBarAddress.h"
#include "WindowMain.h"
#include "ToolBar.h"
#include "ToolBarBtn.h"
#include "App.h"
#include "TitleBar.h"

ToolBarAddress::ToolBarAddress(WindowMain* root) : ToolBarInputBase(root)
{
	paddingLeft = 14.f;
	paddingRight = 38.f;
	hoverIndexVal = 4;
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
void ToolBarAddress::paint2(SkCanvas* canvas)
{
	SkPaint paint;
	auto font = App::GetFontIcon();
	font->setSize(26.f);
	paint.setColor(0xFF999999);
	auto iconCode = (const char*)u8"\ue611";
	canvas->drawString(iconCode, rect.fRight - 70, rect.fTop + 29, *font, paint);
	iconCode = (const char*)u8"\ue764";
	canvas->drawString(iconCode, rect.fRight - 36, rect.fTop + 29, *font, paint);
	auto tab = root->titleBar->getCurTab();
	if (!tab->path.empty()) {
		auto color = root->toolBar->hoverIndex == 4 ? 0xFF333333 : 0xFF666666;
		paint.setColor(color);
		auto fontText = App::GetFontText();
		fontText->setSize(16.f);
		auto pathStr = tab->path.wstring();
		auto textLength = wcslen(pathStr.data()) * 2;
		canvas->drawSimpleText(pathStr.data(), textLength, SkTextEncoding::kUTF16,
			rect.fLeft + 12.f, rect.fTop + 27.f, *fontText, paint);
	}
}