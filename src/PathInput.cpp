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
	root->mouseMoveHandlers.push_back(
		std::bind(&PathInput::mouseMove, this, std::placeholders::_1, std::placeholders::_2)
	);
	root->mouseDownHandlers.push_back(
		std::bind(&PathInput::mouseDown, this, std::placeholders::_1, std::placeholders::_2)
	);
}

PathInput::~PathInput()
{
}

void PathInput::resize(const int& w, const int& h)
{
	isDirty = true;
	auto top = root->toolBar->rect.fTop + 10.f;
	auto left = root->toolBar->pathTool->rect.width() + 12.f;
	auto width = (root->w - left) / 3 * 2 - 12.f;
	rect.setXYWH(left, top, width, 40.f);
}

void PathInput::paint(SkCanvas* canvas)
{
	if (!needPaint(canvas)) return;
	auto font = App::GetFontIcon();
	font->setSize(26.f);
	SkPaint paint;
	auto color = hoverIndex == 0 ? 0xFFE0E3EA : 0xFFECEFF7;
	paint.setColor(color);
	canvas->drawRoundRect(rect, 8.f, 8.f, paint);

	paint.setColor(0xFF999999);
	auto iconCode = (const char*)u8"\ue611";
	canvas->drawString(iconCode, rect.fRight - 70, rect.fTop + 29, *font, paint);
	iconCode = (const char*)u8"\ue764";
	canvas->drawString(iconCode, rect.fRight - 36, rect.fTop + 29, *font, paint);
}

void PathInput::mouseMove(const int& x, const int& y)
{
	int index = -1;
	if (rect.contains(x, y)) {
		index = 0;
	}
	if (index != hoverIndex) {
		hoverIndex = index;
		repaint();
	}
}

void PathInput::mouseDown(const int& x, const int& y)
{
}
