#include "SearchInput.h"
#include "WindowMain.h"
#include "ToolBar.h"
#include "PathInput.h"
#include "App.h"

SearchInput::SearchInput(WindowMain* root) : ControlBase(root)
{
}

SearchInput::~SearchInput()
{
}

void SearchInput::resize(const int& w, const int& h)
{
	isDirty = true;
	auto top = root->toolBar->rect.fTop+10.f;
	auto left = root->toolBar->pathInput->rect.fRight+12.f;
	auto bottom = root->toolBar->pathInput->rect.fBottom;
	rect.setLTRB(left, top, root->w-16.f, bottom);
}

void SearchInput::paint(SkCanvas* canvas)
{
	if (!needPaint(canvas)) return;
	SkPaint paint;
	auto font = App::GetFontIcon();
	font->setSize(26.f); 
	auto color = root->toolBar->hoverIndex == 5 ? 0xFFE0E3EA : 0xFFECEFF7;
	paint.setColor(color);
	canvas->drawRoundRect(rect, 6.f, 6.f, paint);

	paint.setColor(0xFF999999);
	auto iconCode = (const char*)u8"\ue6a6";
	canvas->drawString(iconCode, rect.fLeft+8.f, rect.fTop + 29, *font, paint);

	paint.setColor(0xFFBBBBBB);
	auto fontText = App::GetFontText();
	fontText->setSize(16.f);
	std::wstring str = L"Powered by Everything";
	auto textLength = wcslen(str.data()) * 2;
	canvas->drawSimpleText(str.data(), textLength, SkTextEncoding::kUTF16, rect.fLeft + 38, rect.fTop + 26, *fontText, paint);
}

void SearchInput::mouseDown(const int& x, const int& y)
{
}
