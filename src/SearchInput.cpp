#include "SearchInput.h"
#include "WindowMain.h"
#include "ToolBar.h"
#include "PathInput.h"
#include "App.h"

SearchInput::SearchInput(WindowMain* root) : ControlBase(root)
{
	root->resizeHandlers.push_back(
		std::bind(&SearchInput::resize, this, std::placeholders::_1, std::placeholders::_2)
	);
}

SearchInput::~SearchInput()
{
}

void SearchInput::resize(const int& w, const int& h)
{
	isDirty = true;
	auto top = root->toolBar->rect.fTop;
	auto left = root->toolBar->pathInput->rect.fRight;
	auto width = root->toolBar->pathInput->rect.width() / 2;
	rect.setXYWH(left, top, width, 59.f);
}

void SearchInput::paint(SkCanvas* canvas)
{
	if (!needPaint(canvas)) return;
	SkPaint paint;
	auto font = App::GetFontIcon();
	font->setSize(26.f); 
	paint.setColor(0xFFECEFF7);
	auto searchRect = SkRect::MakeLTRB(rect.fLeft+12.f, rect.fTop + 10, rect.fRight-12.f, rect.fBottom-10);
	canvas->drawRoundRect(searchRect, 8.f, 8.f, paint);

	paint.setColor(0xFF999999);
	auto iconCode = (const char*)u8"\ue6a6";
	canvas->drawString(iconCode, searchRect.fLeft+8, rect.fTop + 39, *font, paint);

	paint.setColor(0xFFBBBBBB);
	auto fontText = App::GetFontText();
	std::wstring str = L"Powered by Everything";
	auto textLength = wcslen(str.data()) * 2;
	canvas->drawSimpleText(str.data(), textLength, SkTextEncoding::kUTF16, searchRect.fLeft + 38, rect.fTop + 35, *fontText, paint);
}
