#include "TitleBar.h"
#include "WindowMain.h"
#include "App.h"
#include "include/core/SkFontMetrics.h"
#include "TitleBarBtns.h"
#include "ContentPanel.h"
#include "ToolBar.h"

class WindowBase;
TitleBar::TitleBar(WindowMain* root) :ControlBase(root)
{
	addTab(std::filesystem::path(""), false);
	btns = std::make_shared<TitleBarBtns>(root);
}

TitleBar::~TitleBar()
{
}

void TitleBar::paint(SkCanvas* canvas)
{	
	if (!needPaint(canvas)) return;
	SkPaint paint;
	paint.setColor(0xFFD3E3FD);
	paint.setStyle(SkPaint::kFill_Style);
	canvas->drawRect(rect, paint);
}

void TitleBar::mouseMove(const int& x, const int& y)
{
	bool flag{ false };
	for (auto& tab:tabs)
	{
		auto tempFlag = tab->hoverChange(x, y);
		if (tempFlag) {
			flag = true;
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
	auto it = std::find_if(tabs.begin(), tabs.end(), [](auto& item) {return item->hoverIndex != -1; });
	if (it == tabs.end()) {
		auto span = std::chrono::system_clock::now() - mouseDownTime;
		auto msCount = std::chrono::duration_cast<std::chrono::milliseconds>(span).count();
		if (msCount < 380) {
			auto isMaximized = IsZoomed(root->hwnd) != 0;
			if (isMaximized) {
				PostMessage(root->hwnd, WM_SYSCOMMAND, SC_RESTORE, 0);
				root->isMouseDown = false;
			}
			else {
				PostMessage(root->hwnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
			}
			return;
		}
		mouseDownTime = std::chrono::system_clock::now();
		GetCursorPos(&startPos);
		ScreenToClient(root->hwnd, &startPos);
		SetCapture(root->hwnd);
		draggingWindow = true;
		return;
	}
	auto index = it - tabs.begin();
	if (tabs[index]->hoverIndex == 1) { //删除Tab
		closeTab(tabs[index].get());
		return;
	}
	if (tabs[index]->isSelected) {
		return;
	}
	selectTab(index);
}

void TitleBar::mouseUp(const int& x, const int& y)
{
	draggingWindow = false;
	ReleaseCapture();//不然拖拽窗口之后，就无法改变窗口大小了。
	std::erase_if(tabs, [](auto& item) { return item->isDel; }); //删除tab
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
	isDirty = true;
	rect.setXYWH(0, 0, w, 56.f);
	for (size_t i = 0; i < tabs.size(); i++)
	{
		tabs[i]->rect.setXYWH(12.f+i*200.f+i*3.f, 10.f, 200.f, 46.f);
	}	
}

void TitleBar::closeTab(TitleBarTab* tab)
{
	if (tabs.size() == 1 && tabs[0]->path.empty()) {
		return;
	}
	int index{0}, maxIndex{ -1 }, maxHistory{ -1 };
	for (size_t i = 0; i < tabs.size(); i++)
	{
		if (tabs[i].get() == tab) {
			tab->isDel = true; //删除
			if (i + 1 < tabs.size()) {
				tabs[i + 1]->hoverIndex = 1;
			}
			continue;
		}
		tabs[i]->rect.setXYWH(12.f + index * 200.f + index * 3.f, 10.f, 200.f, 46.f);
		index += 1;
		tabs[i]->isDirty = true;
		if (tabs[i]->historyNum > tab->historyNum) {
			tabs[i]->historyNum -= 1;
		}
		if (tabs[i]->historyNum > maxHistory) {
			maxHistory = tabs[i]->historyNum;
			maxIndex = i;
		}
	}
	if (maxIndex > -1) {
		tabs[maxIndex]->isSelected = true;
		auto old = tabs[selectedTabIndex].get();
		selectedTabIndex = maxIndex;
		for (size_t i = 0; i < tabChangeEvents.size(); i++)
		{
			tabChangeEvents[i](old,tabs[maxIndex].get());
		}
	}
	btns->isDirty = true;
	if (tabs.size() == 1) {
		std::filesystem::path p("");
		auto tab = std::make_shared<TitleBarTab>(root, p);
		tab->rect.setXYWH(12.f, 10.f, 200.f, 46.f);
		tab->historyNum = 0;
		tab->hoverIndex = 1;
		tabs.push_back(std::move(tab));
		selectedTabIndex = 0;
	}
	repaint();
}

void TitleBar::selectTab(const int& index)
{
	tabs[selectedTabIndex]->isSelected = false;
	tabs[selectedTabIndex]->isDirty = true;
	tabs[index]->isSelected = true;
	tabs[index]->isDirty = true;
	for (auto& item : tabs)
	{
		if (item->historyNum > tabs[index]->historyNum) {
			item->historyNum -= 1;
		}
	}
	tabs[index]->historyNum = tabs.size() - 1;
	auto old = tabs[selectedTabIndex].get();
	selectedTabIndex = index;
	for (size_t i = 0; i < tabChangeEvents.size(); i++)
	{
		tabChangeEvents[i](old,tabs[selectedTabIndex].get());
	}
	InvalidateRect(root->hwnd, nullptr, false);
}

void TitleBar::addTab(std::filesystem::path&& path, bool needRefresh)
{
	for (auto& tab:tabs)
	{
		if (tab->isSelected) {
			tab->isDirty = true;
			tab->isSelected = false;
			tab->hoverIndex = -1;
			break;
		}
	}
	auto tab = std::make_shared<TitleBarTab>(root, path);
	auto size = tabs.size();
	tab->rect.setXYWH(12.f + size * 200.f + size * 3.f, 10.f, 200.f, 46.f);
	tab->historyNum = size;
	tab->orderNum = size;
	tabs.push_back(std::move(tab));
	auto old = tabs[selectedTabIndex].get();
	selectedTabIndex = size;
	if (needRefresh) {
		for (size_t i = 0; i < tabChangeEvents.size(); i++)
		{
			tabChangeEvents[i](old,tabs[selectedTabIndex].get());
		}
		InvalidateRect(root->hwnd, nullptr, false);
	}
}
