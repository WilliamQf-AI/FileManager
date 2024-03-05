#include "ToolBarSearch.h"
#include "WindowMain.h"
#include "ToolBar.h"
#include "ToolBarAddress.h"
#include "App.h"

ToolBarSearch::ToolBarSearch(WindowMain* root) : ToolBarInputBase(root)
{
	paddingLeft = 39.f;
	paddingRight = 18.f;
	hoverIndexVal = 5;
}

ToolBarSearch::~ToolBarSearch()
{
}

void ToolBarSearch::resize(const int& w, const int& h)
{
	isDirty = true;
	auto top = root->toolBar->rect.fTop+10.f;
	auto left = root->toolBar->pathInput->rect.fRight+12.f;
	auto bottom = root->toolBar->pathInput->rect.fBottom;
	rect.setLTRB(left, top, root->w-16.f, bottom);
}

void ToolBarSearch::paint2(SkCanvas* canvas)
{
	SkPaint paint;
	paint.setColor(0xFFFFFFFF);
	//拖拽改变两个输入框大小的时候，要重绘一下输入框中间的部分
	canvas->drawRect(SkRect::MakeLTRB(root->toolBar->pathInput->rect.fRight, rect.fTop, rect.fLeft, rect.fBottom), paint);

	auto font = App::GetFontIcon();
	font->setSize(26.f);
	paint.setColor(0xFF999999);
	auto iconCode = (const char*)u8"\ue6a6";
	canvas->drawString(iconCode, rect.fLeft+8.f, rect.fTop + 29, *font, paint);

	if (!isFocus && rect.width() > 226.f) {
		paint.setColor(0xFFBBBBBB);
		auto fontText = App::GetFontText();
		fontText->setSize(16.f);
		std::wstring str = L"Powered by Everything";
		auto textLength = wcslen(str.data()) * 2;
		canvas->drawSimpleText(str.data(), textLength, SkTextEncoding::kUTF16, rect.fLeft + 38, rect.fTop + 26, *fontText, paint);
	}
}
