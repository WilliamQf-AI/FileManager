#include "ToolBar.h"
#include "WindowMain.h"
#include "App.h"
#include "TitleBar.h"
#include "PathTool.h"
#include "PathInput.h"
#include "SearchInput.h"
#include "TitleBar.h"
#include "TitleBarTab.h"

ToolBar::ToolBar(WindowMain* root) :ControlBase(root)
{
	pathTool = std::make_shared<PathTool>(root);
	pathInput = std::make_shared<PathInput>(root);
	searchInput = std::make_shared<SearchInput>(root);
	auto func = std::bind(&ToolBar::tabChange, this, std::placeholders::_1, std::placeholders::_2);
	root->titleBar->tabChangeEvents.push_back(std::move(func));
}

ToolBar::~ToolBar()
{
}

void ToolBar::tabChange(TitleBarTab* tab, TitleBarTab* tabNew)
{
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

void ToolBar::mouseMove(const int& x, const int& y)
{
	int index{ -1 };
	if (rect.contains(x, y)) {
		if (x > 8.f && pathTool->rect.contains(x, y)) {
			index = (x - 8.f) / 50;
		}
		else if (pathInput->rect.contains(x, y)) {
			index = 4;
		}
		else if (searchInput->rect.contains(x, y)) {
			index = 5;
		}
		else if (x > pathInput->rect.fRight && x < searchInput->rect.fLeft) {
			index = 6;
		}
	}
	if (index != hoverIndex) {
		if (index == 4) {
			SetCursor(LoadCursor(nullptr, IDC_IBEAM));
			pathInput->repaint();
		}
		else if (index == 5) {
			SetCursor(LoadCursor(nullptr, IDC_IBEAM));
			searchInput->repaint();
		}
		else if (index == 6) {
			SetCursor(LoadCursor(nullptr, IDC_SIZEWE));
		}
		else {
			SetCursor(LoadCursor(nullptr, IDC_ARROW));
		}
		if (hoverIndex < 4) {
			pathTool->repaint();
		}
		else if (hoverIndex == 4) {
			pathInput->repaint();
		}
		else if (hoverIndex == 5) {
			searchInput->repaint();
		}
		hoverIndex = index;
	}
}

void ToolBar::mouseDown(const int& x, const int& y)
{
}

void ToolBar::mouseDrag(const int& x, const int& y)
{
}
