#include "TitleBar.h"
#include "WindowMain.h"
#include "App.h"
#include "include/core/SkFontMetrics.h"
#include "TitleBarBtns.h"

class WindowBase;
TitleBar::TitleBar(WindowBase* root) :ControlBase(root)
{
	auto tab1 = std::make_shared<TitleBarTab>(root);
	tab1->isSelected = false;
	tabs.push_back(tab1);
	auto tab2 = std::make_shared<TitleBarTab>(root);
	tabs.push_back(tab2);
	btns = std::make_shared<TitleBarBtns>(root);
	root->mouseMoveHandlers.push_back(
		std::bind(&TitleBar::mouseMove, this, std::placeholders::_1, std::placeholders::_2)
	);
	root->mouseDownHandlers.push_back(
		std::bind(&TitleBar::mouseDown, this, std::placeholders::_1, std::placeholders::_2)
	);
	root->mouseDragHandlers.push_back(
		std::bind(&TitleBar::mouseDrag, this, std::placeholders::_1, std::placeholders::_2)
	);
	root->mouseUpHandlers.push_back(
		std::bind(&TitleBar::mouseUp, this, std::placeholders::_1, std::placeholders::_2)
	);
	root->resizeHandlers.push_back(
		std::bind(&TitleBar::resize, this, std::placeholders::_1, std::placeholders::_2)
	);
}

TitleBar::~TitleBar()
{
}

void TitleBar::paint(SkCanvas* canvas)
{	
	SkPaint paint;
	paint.setColor(0xFFD3E3FD);
	paint.setStyle(SkPaint::kFill_Style);
	canvas->drawRect(rect, paint);
	for (auto& tab:tabs)
	{
		tab->paint(canvas);
	}
	btns->paint(canvas);
}

void TitleBar::mouseMove(const int& x, const int& y)
{
	bool flag{ false };
	for (auto& tab:tabs)
	{
		auto hovered = tab->rect.contains(x, y);
		auto hoverClose{ false };
		if (hovered) {
			SkRect r = SkRect::MakeXYWH(tab->rect.fRight - 8.f - 26.f, tab->rect.fTop + 10, 26.f, 26.f);
			hoverClose = r.contains(x, y);
		}
		if (tab->isHovered != hovered) {
			flag = true;
			tab->isHovered = hovered;
		}
		if (tab->isHoverCloseBtn != hoverClose) {
			flag = true;
			tab->isHoverCloseBtn = hoverClose;
		}
	}
	if (flag) {
		InvalidateRect(root->hwnd, nullptr, false);
	}	
}

void TitleBar::mouseDown(const int& x, const int& y)
{
	if (!rect.contains(x, y)) {
		return;
	}
	auto it = std::find_if(tabs.begin(), tabs.end(), [](auto& item) {return item->isHovered; });
	if (it == tabs.end()) {
		GetCursorPos(&startPos);
		ScreenToClient(root->hwnd, &startPos);
		SetCapture(root->hwnd);
		draggingWindow = true;
		return;
	}
	auto tab = *it;
	if (tab->isSelected) {
		return;
	}
	auto it2 = std::find_if(tabs.begin(), tabs.end(), [](auto& item) {return item->isSelected; });
	(*it2)->isSelected = false;
	tab->isSelected = true;
	InvalidateRect(root->hwnd, nullptr, false);
}

void TitleBar::mouseUp(const int& x, const int& y)
{
	draggingWindow = false;
	ReleaseCapture();
}

void TitleBar::mouseDrag(const int& x, const int& y)
{
	if (draggingWindow) {
		POINT point;
		GetCursorPos(&point);
		ScreenToClient(root->hwnd, &point);
		RECT windowRect;
		GetWindowRect(root->hwnd, &windowRect);
		int dx = windowRect.left + point.x - startPos.x;
		int dy = windowRect.top + point.y - startPos.y;
		SetWindowPos(root->hwnd, nullptr, dx, dy, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}
}

void TitleBar::resize(const int& w, const int& h)
{
	rect.setXYWH(0, 0, w, 56.f);
	for (size_t i = 0; i < tabs.size(); i++)
	{
		tabs[i]->rect.setXYWH(12.f+i*200.f+i*3.f, 10.f, 200.f, 46.f);
	}	
}
