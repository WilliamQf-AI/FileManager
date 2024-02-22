#include "Home.h"
#include "WindowMain.h"
#include "TitleBar.h"
#include "ToolBar.h"
#include "LeftPanel.h"
#include "App.h"

Home::Home(WindowMain* root) :ControlBase(root)
{
}

Home::~Home()
{
}

void Home::paint(SkCanvas* canvas)
{
	if (!needPaint(canvas)) return;
	SkPaint paint;
	paint.setColor(0xFFFFFFFF);
	canvas->drawRect(rect, paint);
	paint.setColor(0xFFE8E8E8);
	canvas->drawLine(rect.fLeft, rect.fTop, rect.fLeft, rect.fBottom, paint);

	paint.setColor(0xFFD3E3FD);
	auto y = rect.centerY() - 58.f;
	canvas->drawLine(rect.fLeft+110.f, y, rect.centerX()-140.f, y, paint);
	canvas->drawLine(rect.centerX() + 140.f, y, rect.fRight-110.f, y, paint);

	auto fontText = App::GetFontText();
	fontText->setSize(18.f);
	std::wstring str = L"FileManager 文件管理器";
	auto textLength = wcslen(str.data()) * 2;
	paint.setColor(0xFFC0D0EA);
	canvas->drawSimpleText(str.data(), textLength, SkTextEncoding::kUTF16, rect.centerX() - 102.f, y+8.f, *fontText, paint);
}

void Home::resize(const int& w, const int& h)
{
	isDirty = true;
	auto topVal = root->titleBar->rect.height() + root->toolBar->rect.height();
	auto leftVal = root->leftPanel->rect.fRight;
	rect.setLTRB(leftVal, topVal, w, h);
}
