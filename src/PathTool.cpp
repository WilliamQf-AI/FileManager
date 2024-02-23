#include "PathTool.h"
#include "WindowMain.h"
#include "ToolBar.h"
#include "App.h"

PathTool::PathTool(WindowMain* root) : ControlBase(root)
{
}

PathTool::~PathTool()
{
}

void PathTool::resize(const int& w, const int& h)
{
	isDirty = true;
	auto top = root->toolBar->rect.fTop;
	rect.setXYWH(0.f, top, 200.f, 59.f);
}

void PathTool::paint(SkCanvas* canvas)
{
	if (!needPaint(canvas)) return;
	SkPaint paint;
	if (hoverIndex >= 0) {
		paint.setColor(0x18000000);  //0xFFA8C7FA
		auto r = SkRect::MakeXYWH(10.f + hoverIndex * 50.f, rect.fTop + 11.f, 36.f, 36.f);
		canvas->drawRoundRect(r,6.f,6.f, paint);
		paint.setColor(0xFF222222);
	}
	else {
		paint.setColor(0xFF666666);
	}
	auto font = App::GetFontIcon();
	font->setSize(26.f);
	auto iconCode = (const char*)u8"\ue80b";
	float start{ 16.f };
	float top{ rect.fTop + 39.f };
	canvas->drawString(iconCode, start, top, *font, paint);
	iconCode = (const char*)u8"\ue80c";
	canvas->drawString(iconCode, start + 50, top, *font, paint);
	iconCode = (const char*)u8"\ue80a";
	canvas->drawString(iconCode, start + 100, top, *font, paint);
	iconCode = (const char*)u8"\ue741";
	canvas->drawString(iconCode, start + 150, top, *font, paint);
}

void PathTool::mouseMove(const int& x, const int& y)
{
	int index = -1;
	if (rect.contains(x, y) && x > 8.f) {
		index = (x-8.f) / 50;
	}
	if (index != hoverIndex) {
		hoverIndex = index;
		repaint();
	}
}

void PathTool::mouseDown(const int& x, const int& y)
{
}
