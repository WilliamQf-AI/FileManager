#include "TitleBarBtns.h"
#include <Windows.h>
#include <functional>
#include "include/core/SkFontMetrics.h"
#include "App.h"
#include "WindowMain.h"


TitleBarBtns::TitleBarBtns(WindowMain* root) :ControlBase(root)
{
	
	root->mouseMoveHandlers.push_back(
		std::bind(&TitleBarBtns::mouseMove, this, std::placeholders::_1, std::placeholders::_2)
	);
	root->mouseDownHandlers.push_back(
		std::bind(&TitleBarBtns::mouseDown, this, std::placeholders::_1, std::placeholders::_2)
	);
	root->resizeHandlers.push_back(
		std::bind(&TitleBarBtns::resize, this, std::placeholders::_1, std::placeholders::_2)
	);
}

TitleBarBtns::~TitleBarBtns()
{
}

void TitleBarBtns::paint(SkCanvas *canvas)
{
	auto isMaximized = IsZoomed(root->hwnd) != 0;
	SkPaint paint;
	if (hoverIndex == 0) {
		paint.setColor(0xAAFFFFFF);
		canvas->drawRect(SkRect::MakeXYWH(rect.fLeft, rect.fTop, 66, 56),paint);
	}
	else if (hoverIndex == 1) {
		paint.setColor(0xAAFFFFFF);
		canvas->drawRect(SkRect::MakeXYWH(rect.fLeft+66, rect.fTop, 66, 56), paint);
	}
	else if (hoverIndex == 2) {
		paint.setColor(SK_ColorRED);
		canvas->drawRect(SkRect::MakeXYWH(rect.fLeft + 132, rect.fTop, 66, 56), paint);
	}
	auto r = SkRect::MakeXYWH(rect.fLeft, 0, 66, 56);
	auto font = App::GetFontIcon();
	font->setSize(24.f);
	auto iconCode = (const char *)u8"\ue6e8"; //最小化
	auto pos = getStartPosOfIconAtCenterOfRect(iconCode, r, font.get());	
	paint.setColor(0xFF888888);
	canvas->drawString(iconCode, pos.fX, pos.fY, *font, paint);
	iconCode = isMaximized? (const char*)u8"\ue6e9" : (const char*)u8"\ue6e5"; //最大化
	canvas->drawString(iconCode, pos.fX +66, pos.fY, *font, paint);
	iconCode = (const char*)u8"\ue6e7"; // 关闭
	if (hoverIndex == 2) {
		paint.setColor(SK_ColorWHITE);
	}
	canvas->drawString(iconCode, pos.fX + 132, pos.fY, *font, paint);
}

void TitleBarBtns::mouseDown(const int& x, const int& y)
{
	if (hoverIndex == 0) {
		//PostMessage(root->hwnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
		SendMessage(root->hwnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
		root->isMouseDown = false;
	}
	else if (hoverIndex == 1) {
		auto isMaximized = IsZoomed(root->hwnd) != 0;
		if (isMaximized) {
			//PostMessage(root->hwnd, WM_SYSCOMMAND, SC_RESTORE, 0);
			SendMessage(root->hwnd, WM_SYSCOMMAND, SC_RESTORE, 0);
		}
		else {
			//ShowWindow(root->hwnd, SW_MAXIMIZE);
			//PostMessage(root->hwnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
			SendMessage(root->hwnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
		}
		root->isMouseDown = false;
	}
	else if (hoverIndex == 2) {
		PostMessage(root->hwnd, WM_CLOSE, 0, 0); //PostMessage异步，SendMessage同步
		root->isMouseDown = false;
	}
	hoverIndex = -1;
}

void TitleBarBtns::resize(const int& w, const int& h)
{
	rect.setXYWH(w - 198.f, 0.f, 198.f, 56.f);
}

void TitleBarBtns::mouseMove(const int& x, const int& y)
{
	if (!rect.contains(x, y)) {
		if (hoverIndex >= 0) {
			hoverIndex = -1;
			InvalidateRect(root->hwnd, nullptr, false);
		}
		return;
	}
	if (x < rect.fLeft + 66) {
		hoverIndex = 0;
	}
	else if (x < rect.fLeft + 132) {
		hoverIndex = 1;
	}
	else {
		hoverIndex = 2;
	}
	InvalidateRect(root->hwnd, nullptr, false);
}