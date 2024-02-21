#include "PathInput.h"
#include "WindowMain.h"
#include "ToolBar.h"
#include "PathTool.h"
#include "App.h"

PathInput::PathInput(WindowMain* root) : ControlBase(root)
{
	root->resizeHandlers.push_back(
		std::bind(&PathInput::resize, this, std::placeholders::_1, std::placeholders::_2)
	);
}

PathInput::~PathInput()
{
}

void PathInput::resize(const int& w, const int& h)
{
	isDirty = true;
	auto top = root->toolBar->rect.fTop;
	auto left = root->toolBar->pathTool->rect.width();
	auto width = (root->w - left) / 3 * 2;
	rect.setXYWH(left, top, width, 59.f);
}

void PathInput::paint(SkCanvas* canvas)
{
	if (!needPaint(canvas)) return;
	auto font = App::GetFontIcon();
	font->setSize(26.f);
	SkPaint paint;
	auto addressRect = SkRect::MakeXYWH(rect.fLeft+12.f, rect.fTop + 10, rect.width()-12.f, 40);
	paint.setColor(0xFFECEFF7);
	canvas->drawRoundRect(addressRect, 8.f, 8.f, paint);

	paint.setColor(0xFF999999);
	auto iconCode = (const char*)u8"\ue611";
	canvas->drawString(iconCode, addressRect.fRight - 70, rect.fTop + 40, *font, paint);
	iconCode = (const char*)u8"\ue764";
	canvas->drawString(iconCode, addressRect.fRight - 36, rect.fTop + 40, *font, paint);
}
