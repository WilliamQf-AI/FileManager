#include "TitleBar.h"
#include "WindowMain.h"
#include "App.h"
#include "include/core/SkFontMetrics.h"


TitleBar::TitleBar()
{
	YGNodeStyleSetFlexDirection(layout, YGFlexDirectionRow);
	YGNodeStyleSetWidthAuto(layout);
	YGNodeStyleSetHeight(layout, 60.f);

	auto tabLayout = new Layout();
	YGNodeStyleSetFlexGrow(tabLayout->layout, 1.f);
	this->addLayoutChild(tabLayout);

	minimizeBtn = std::make_shared<Layout>();
	minimizeBtn->setSize(62.f, 60.f);
	this->addLayoutChild(minimizeBtn.get());
}

TitleBar::~TitleBar()
{
}

void TitleBar::paint(SkCanvas* canvas)
{	
	auto rect = getOffsetRect();
	SkPaint paint;
	paint.setColor(0xFFD3E3FD);
	paint.setStyle(SkPaint::kFill_Style);
	canvas->drawRect(rect, paint);

	paint.setColor(SK_ColorWHITE);
	auto rect2 = minimizeBtn->getOffsetRect();
	canvas->drawRect(rect2, paint);

	paint.setColor(SK_ColorBLACK);
	auto font = App::GetFontIcon();
	//font = App::GetFontText();
	font->setSize(22.f);

	SkFontMetrics metrics;
	font->getMetrics(&metrics);


	auto iconCode = (const char*)u8"\uf2d1";
	//iconCode = (const char*)u8"AB";
	iconCode = (const char*)u8"\ue3e0"; //还原


	SkRect textBounds;
	font->measureText(iconCode, 3, SkTextEncoding::kUTF8, &textBounds);

	// 计算居中文本的绘制坐标
	SkScalar x1 = rect2.centerX() - textBounds.width() / 2;
	SkScalar y1 = rect2.centerY() + (metrics.fDescent - metrics.fAscent) / 2 - metrics.fDescent;
	canvas->drawString(iconCode, x1, y1, *font, paint);
}
