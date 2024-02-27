#include "ToolBar.h"
#include "WindowMain.h"
#include "App.h"
#include "TitleBar.h"
#include "PathTool.h"
#include "PathInput.h"
#include "SearchInput.h"
#include "TitleBar.h"

ToolBar::ToolBar(WindowMain* root) :ControlBase(root)
{
	pathTool = std::make_shared<PathTool>(root);
	pathInput = std::make_shared<PathInput>(root);
	searchInput = std::make_shared<SearchInput>(root);
}

ToolBar::~ToolBar()
{
}

void ToolBar::changeAddress()
{
	//auto tab = root->titleBar->tabs[root->titleBar->selectedTabIndex].get();
	//bool is_root_directory = (tab->path.root_path() == tab->path);
	//if()
	pathInput->isDirty = true;
	pathTool->isDirty = true;
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
