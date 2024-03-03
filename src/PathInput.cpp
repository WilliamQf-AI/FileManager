#include "PathInput.h"
#include "WindowMain.h"
#include "ToolBar.h"
#include "PathTool.h"
#include "App.h"
#include "TitleBar.h"

PathInput::PathInput(WindowMain* root) : ControlBase(root)
{
}

PathInput::~PathInput()
{
}

void PathInput::resize(const int& w, const int& h)
{
	isDirty = true;
	auto top = root->toolBar->rect.fTop + 10.f;
	auto left = root->toolBar->pathTool->rect.width() + 12.f;
	auto width = (root->w - left) / 3 * 2 - 12.f;
	rect.setXYWH(left, top, width, 40.f);
}

void PathInput::paint(SkCanvas* canvas)
{
	if (!needPaint(canvas)) return;
	auto font = App::GetFontIcon();
	font->setSize(26.f);
	SkPaint paint;
	auto color = root->toolBar->hoverIndex == 4 ? 0xFFE0E3EA : 0xFFECEFF7;
	paint.setColor(color);
	canvas->drawRoundRect(rect, 6.f, 6.f, paint);
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

void PathInput::mouseDown(const int& x, const int& y)
{
}
