#include "ToolBar.h"
#include "WindowMain.h"
#include "App.h"
#include "TitleBar.h"
#include "PathTool.h"
#include "PathInput.h"
#include "SearchInput.h"

ToolBar::ToolBar(WindowMain* root) :ControlBase(root)
{
	root->resizeHandlers.push_back(
		std::bind(&ToolBar::resize, this, std::placeholders::_1, std::placeholders::_2)
	);
	pathTool = std::make_shared<PathTool>(root);
	pathInput = std::make_shared<PathInput>(root);
	searchInput = std::make_shared<SearchInput>(root);
}

ToolBar::~ToolBar()
{
}

void ToolBar::paint(SkCanvas* canvas)
{
	if (!needPaint(canvas)) return;
	SkPaint paint;
	paint.setColor(0xFFE8E8E8);
	canvas->drawLine(0.f, rect.fBottom-1, rect.fRight, rect.fBottom-1, paint);
}

void ToolBar::resize(const int& w, const int& h)
{
	isDirty = true;
	auto top = root->titleBar->rect.height();
	rect.setXYWH(0.f, top, root->w, 60.f);
}
