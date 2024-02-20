#include "TitleBarTab.h"

#include "include/core/SkRRect.h"
#include "include/core/SkPixmap.h"
#include "include/core/SkBitmap.h"
#include "WindowMain.h"
#include "SystemIcon.h"
#include "App.h"

TitleBarTab::TitleBarTab(WindowMain* root, std::wstring&& title) :ControlBase(root),title{title}
{
	root->resizeHandlers.push_back(
		std::bind(&TitleBarTab::resize, this, std::placeholders::_1, std::placeholders::_2)
	);
}

TitleBarTab::~TitleBarTab()
{
}

void TitleBarTab::resize(const int& w, const int& h)
{
	isDirty = true;
}

void TitleBarTab::paint(SkCanvas* canvas)
{
	if (!needPaint(canvas, 0xFFD3E3FD)) return;
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
		paint.setColor(0xFF999999);
	}
	
	auto font = App::GetFontIcon();
	font->setSize(18.f);
	paint.setAntiAlias(false);	
	auto iconCode = (const char*)u8"\ue6e7"; 
	canvas->drawString(iconCode, 
		rect.fRight - 8.f - 22.f,
		rect.fTop + 10.f + 20.f,
		*font, paint);
}
