#include "TitleBar.h"
#include "WindowMain.h"
#include "App.h"

ContentPanel::ContentPanel(WindowBase* root) :ControlBase(root)
{
	root->resizeHandlers.push_back(
		std::bind(&ContentPanel::resize, this, std::placeholders::_1, std::placeholders::_2)
	);
}

ContentPanel::~ContentPanel()
{
}

void ContentPanel::paint(SkCanvas* canvas)
{
	auto leftRect = SkRect::MakeXYWH(rect.fLeft, rect.fTop, 300.f, 50.f);
	auto rightRect = SkRect::MakeLTRB(rect.fLeft+300.f, rect.fTop, root->w, rect.fTop+50.f);
	SkPaint paint;
	paint.setColor(0xFFE8E8E8);
	canvas->drawLine(rect.fLeft, rect.fTop + 50.f, rect.fRight, rect.fTop + 50.f,paint);
	canvas->drawLine(rightRect.fLeft, rightRect.fTop, rightRect.fLeft, rightRect.fBottom, paint);


	paint.setColor(0xFF888888);
	std::wstring str = L"最近使用的文件";
	auto textLength = wcslen(str.data()) * 2;
	auto fontText = App::GetFontText();
	fontText->setSize(16.8);
	auto verticalVal = getTextVerticalVal(fontText.get());
	canvas->drawSimpleText(str.data(), textLength, SkTextEncoding::kUTF16,
		rect.fLeft + 12.f, rect.fTop + 25 + verticalVal, *fontText, paint);

	str = L"使用时间";
	textLength = wcslen(str.data()) * 2;
	canvas->drawSimpleText(str.data(), textLength, SkTextEncoding::kUTF16,
		rect.fLeft + 312.f, rect.fTop + 25 + verticalVal, *fontText, paint);

	auto font = App::GetFontIcon();
	font->setSize(24.f);
	paint.setAntiAlias(false);
	auto iconCode = (const char*)u8"\ue67d";
	canvas->drawString(iconCode, leftRect.fRight-30, rect.fTop+ 34.f, *font, paint);

	canvas->drawString(iconCode, rightRect.fRight - 30, rect.fTop + 34.f, *font, paint);
}

void ContentPanel::resize(const int& w, const int& h)
{
	auto topVal = root->ctrls[0]->rect.height() + root->ctrls[1]->rect.height();
	auto leftVal = root->ctrls[2]->rect.fRight;
	rect.setXYWH(leftVal, topVal, w-leftVal, h - topVal);


	//recent files 
	//C:\Users\liuxiaolun\AppData\Roaming\Microsoft\Windows\Recent
}
