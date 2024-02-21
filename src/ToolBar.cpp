#include "ToolBar.h"
#include "WindowMain.h"
#include "App.h"
#include "TitleBar.h"
#include "PathTool.h"
#include "PathInput.h"
#include "SearchInput.h"

ToolBar::ToolBar(WindowMain* root) :ControlBase(root)
{
	root->resizeHandlers.push_back(
		std::bind(&ToolBar::resize, this, std::placeholders::_1, std::placeholders::_2)
	);
	pathTool = std::make_shared<PathTool>(root);
	pathInput = std::make_shared<PathInput>(root);
	searchInput = std::make_shared<SearchInput>(root);
}

ToolBar::~ToolBar()
{
}

void ToolBar::paint(SkCanvas* canvas)
{
	if (!needPaint(canvas)) return;
	//auto font = App::GetFontIcon();
	//font->setSize(26.f);
	//paint.setColor(0xFF666666);

	//auto w = (root->w - 232) / 3 * 2;
	//auto searchRect = SkRect::MakeXYWH(addressRect.fRight+12.f, rect.fTop + 10, w/2, 40);
	//canvas->drawRoundRect(searchRect, radio, radio, paint);	
	//auto iconCode = (const char*)u8"\ue6a6";
	//canvas->drawString(iconCode, searchRect.fLeft+8, 25, *font, paint);
	//paint.setColor(0xFFBBBBBB);
	//auto fontText = App::GetFontText();
	//std::wstring str = L"Powered by Everything";
	//auto textLength = wcslen(str.data()) * 2;
	//canvas->drawSimpleText(str.data(), textLength, SkTextEncoding::kUTF16, searchRect.fLeft + 38, 25, *fontText, paint);
	SkPaint paint;
	paint.setColor(0xFFE8E8E8);
	canvas->drawLine(0.f, rect.fBottom-1, rect.fRight, rect.fBottom-1, paint);
}

void ToolBar::resize(const int& w, const int& h)
{
	isDirty = true;
	auto top = root->titleBar->rect.height();
	rect.setXYWH(0.f, top, root->w, 60.f);
}
