#include "TitleBarTab.h"

#include "include/core/SkRRect.h"
#include "include/core/SkPixmap.h"
#include "include/core/SkBitmap.h"
#include "WindowMain.h"
#include "SystemIcon.h"
#include "App.h"

TitleBarTab::TitleBarTab(WindowMain* root, std::wstring&& title) :ControlBase(root),title{title}
{
}

TitleBarTab::~TitleBarTab()
{
	//todo 移除元素时，释放layout
}

void TitleBarTab::paint(SkCanvas* canvas)
{
	SkPaint paint;
	paint.setAntiAlias(true);
	if (isSelected) {
		paint.setColor(0xFFFFFFFF);
		paint.setStyle(SkPaint::kFill_Style);
		SkVector radii[4] = { {6, 6}, {6, 6}, {0, 0}, {0, 0} };
		auto rr = SkRRect::MakeEmpty();
		rr.setRectRadii(rect, radii);
		canvas->drawRRect(rr, paint);
	}
	else if (isHovered) {
		paint.setColor(0x88FFFFFF);  //0xFFA8C7FA
		auto r = rect;
		r.inset(4, 6);
		canvas->drawRoundRect(r, 6, 6, paint);
	}
	auto img = SystemIcon::getIcon(SIID_FOLDER,26); //CSIDL_QUICKACCESS
	canvas->drawImage(img, rect.fLeft + 8.f, rect.centerY() - img->height() / 2);

	paint.setColor(0xFF333333);
	auto textLength = wcslen(title.data()) * 2;
	auto fontText = App::GetFontText();
	fontText->setSize(16.f);
	canvas->drawSimpleText(title.data(), textLength, SkTextEncoding::kUTF16, 
		rect.fLeft+34.f, rect.centerY()+4.5, *fontText, paint);
	if (isHoverCloseBtn) {
		paint.setColor(0x18000000);
		SkRect closeRect = SkRect::MakeXYWH(rect.fRight - 8.f - 26.f, rect.fTop + 10.f, 26.f, 26.f);
		canvas->drawRoundRect(closeRect, 6, 6, paint);
		paint.setColor(0xFF333333);
	}
	else {
		paint.setColor(0xFF888888);
	}
	
	auto font = App::GetFontIcon();
	font->setSize(20.f);
	paint.setAntiAlias(false);	
	auto iconCode = (const char*)u8"\ue6e7"; 
	canvas->drawString(iconCode, 
		rect.fRight - 8.f - 13.f-10.f,
		rect.fTop + 10.f + 20.f,
		*font, paint);

	//canvas->drawSimpleText(iconCode, 3, SkTextEncoding::kUTF8,0, 0, *font,paint);
	//SystemIcon::reset();
	//PostMessage(root->hwnd, WM_DEBUG_MESSAGE, 0, 0);
}
