#include "ToolBar.h"
#include "WindowMain.h"
#include "App.h"
#include "TitleBar.h"
#include "ToolBarBtn.h"
#include "ToolBarAddress.h"
#include "ToolBarSearch.h"
#include "TitleBar.h"
#include "TitleBarTab.h"

ToolBar::ToolBar(WindowMain* root) :ControlBase(root)
{
	toolBarBtn = std::make_shared<ToolBarBtn>(root);
	toolBarAddress = std::make_shared<ToolBarAddress>(root);
	toolBarSearch = std::make_shared<ToolBarSearch>(root);
	auto func = std::bind(&ToolBar::tabChange, this, std::placeholders::_1, std::placeholders::_2);
	root->titleBar->tabChangeEvents.push_back(std::move(func));
}

ToolBar::~ToolBar()
{
}

void ToolBar::tabChange(TitleBarTab* tab, TitleBarTab* tabNew)
{
	toolBarAddress->isDirty = true;
	toolBarBtn->isDirty = true;
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
		if (x > 8.f && toolBarBtn->rect.contains(x, y)) {
			index = (x - 8.f) / 50;
		}
		else if (toolBarAddress->rect.contains(x, y)) {
			if (x < toolBarAddress->rect.fRight - 72) {
				index = 4;
			}
			else if (x < toolBarAddress->rect.fRight - 38) {
				index = 5;
			}
			else {
				index = 6;
			}
			
		}
		else if (x > toolBarAddress->rect.fRight && x < toolBarSearch->rect.fLeft) {
			index = 7;
		}
		else if (toolBarSearch->rect.contains(x, y)) {
			index = 8;
		}
	}
	if (index != hoverIndex) {
		if (index == 4) {
			SetCursor(LoadCursor(nullptr, IDC_IBEAM));
			toolBarAddress->isDirty = true;
		}
		else if (index == 5 || index == 6) {
			SetCursor(LoadCursor(nullptr, IDC_ARROW));
			toolBarAddress->isDirty = true;
		}
		else if (index == 8) {
			SetCursor(LoadCursor(nullptr, IDC_IBEAM));
			toolBarSearch->isDirty = true;
		}
		else if (index == 7) {
			SetCursor(LoadCursor(nullptr, IDC_SIZEWE));
		}
		else {
			SetCursor(LoadCursor(nullptr, IDC_ARROW));
		}
		if (hoverIndex < 4) {
			toolBarBtn->isDirty = true;
		}
		else if (hoverIndex < 7) {
			toolBarAddress->isDirty = true;
		}
		else if (hoverIndex == 8) {
			toolBarSearch->isDirty = true;
		}
		hoverIndex = index;
		InvalidateRect(root->hwnd, nullptr, false);
	}
}

void ToolBar::mouseDown(const int& x, const int& y)
{
	if (hoverIndex == 7) {
		SetCapture(root->hwnd);
		mouseDownX = x;
	}
}

void ToolBar::mouseDrag(const int& x, const int& y)
{
	if (hoverIndex == 7) {
		auto span = x - mouseDownX;
		auto right = toolBarAddress->rect.fRight + span;
		auto left = toolBarSearch->rect.fLeft + span;
		if (right < toolBarAddress->rect.fLeft + 120) {
			mouseDownX = x;
			return;
		}
		if (left > toolBarSearch->rect.fRight - 120) {
			mouseDownX = x;
			return;
		}
		toolBarAddress->rect.setLTRB( toolBarAddress->rect.fLeft,toolBarAddress->rect.fTop, right, toolBarAddress->rect.fBottom );
		toolBarSearch->rect.setLTRB(left,toolBarSearch->rect.fTop,toolBarSearch->rect.fRight,toolBarSearch->rect.fBottom);
		toolBarAddress->isDirty = true;
		toolBarSearch->isDirty = true;
		InvalidateRect(root->hwnd, nullptr, false);
		mouseDownX = x;
	}
}

void ToolBar::mouseUp(const int& x, const int& y)
{
	ReleaseCapture();
}
