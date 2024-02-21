#include "PathTool.h"
#include "WindowMain.h"
#include "ToolBar.h"
#include "App.h"

PathTool::PathTool(WindowMain* root) : ControlBase(root)
{
	root->resizeHandlers.push_back(
		std::bind(&PathTool::resize, this, std::placeholders::_1, std::placeholders::_2)
	);
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
	auto font = App::GetFontIcon();
	font->setSize(26.f);
	auto iconCode = (const char*)u8"\ue80b";
	SkPaint paint;
	paint.setColor(0xFF666666);
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
