#include "TitleBarTab.h"
#include "include/core/SkRRect.h"
#include "include/core/SkPixmap.h"
#include "include/core/SkBitmap.h"
#include "WindowMain.h"
#include "SystemIcon.h"
#include "App.h"
#include "ContentPanel.h"

TitleBarTab::TitleBarTab(WindowMain* root, std::filesystem::path& path) :ControlBase(root),path{path}
{
	if (path.empty()) {
		title = L"主页";
	}
	else {
		title = path.filename().wstring();		
	}
}

TitleBarTab::~TitleBarTab()
{
}

bool TitleBarTab::hoverChange(const int& x, const int& y)
{
	int index = -1;
	if (rect.contains(x, y)) {
		index = 0;
		SkRect r = SkRect::MakeXYWH(rect.fRight - 8.f - 26.f, rect.fTop + 10, 26.f, 26.f);
		if (r.contains(x, y)) {
			index = 1;
		}
	}
	if (index != hoverIndex) {
		hoverIndex = index;
		isDirty = true;
		return true;
	}
	return false;
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
	else if (hoverIndex >= 0) {
		paint.setColor(0x88FFFFFF);  //0xFFA8C7FA
		auto r = rect;
		r.inset(4, 6);
		canvas->drawRoundRect(r, 6, 6, paint);
	}
	auto img = SystemIcon::getIcon(path.wstring()); //22
	auto r = SkRect::MakeXYWH(rect.fLeft + 8.f, rect.fTop + 11.f, 22.f, 22.f);
	canvas->drawImageRect(img, r, { SkFilterMode::kLinear, SkMipmapMode::kLinear });

	paint.setColor(0xFF666666);
	auto textLength = wcslen(title.data()) * 2;
	auto fontText = App::GetFontText();
	fontText->setSize(16.f);
	canvas->drawSimpleText(title.data(), textLength, SkTextEncoding::kUTF16, 
		rect.fLeft+34.f, rect.centerY()+4.5, *fontText, paint);
	if (hoverIndex == 1) { //close
		paint.setColor(0x18000000);
		SkRect closeRect = SkRect::MakeXYWH(rect.fRight - 8.f - 26.f, rect.fTop + 10.f, 26.f, 26.f);
		canvas->drawRoundRect(closeRect, 6, 6, paint);
		paint.setColor(0xFF666666);
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
