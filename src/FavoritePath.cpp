#include "FavoritePath.h"
#include <string>
#include <format>
#include <Windows.h>
#include <include/core/SkPaint.h>

#include "WindowMain.h"
#include "SystemIcon.h"
#include "App.h"
#include "LeftPanel.h"

FavoritePath::FavoritePath(WindowMain* root) :ControlBase(root)
{
	totalHeight = 46 * 26;
}

FavoritePath::~FavoritePath()
{
}

void FavoritePath::paint(SkCanvas* canvas)
{
	if (!needPaint(canvas, 0xFFF8FBFF)) return;
	SkPaint paint;
	auto rectHeight = rect.height();
	canvas->save();
	canvas->clipRect(rect);
	auto top = 0 - (scrollerRect.fTop-rect.fTop) / rectHeight * totalHeight;
	for (size_t i = 0; i < 26; i++)
	{
		auto y = rect.fTop + top + i * 46;
		if (i == hoverIndex) {
			paint.setColor(0xFFD3E3FD);
			canvas->drawRect(SkRect::MakeLTRB(rect.fLeft, y, rect.fRight, y + 46.f), paint);
		}
		auto img = SystemIcon::getIcon(SIID_FOLDER); //26
		canvas->drawImage(img, 12, y + 12);
		std::wstring str = std::format(L"这是一条收藏的路径({}:)", i);
		auto textLength = wcslen(str.data()) * 2;
		auto fontText = App::GetFontText();
		fontText->setSize(16.6f);
		paint.setColor(0xFF333333);
		canvas->drawSimpleText(str.data(), textLength, SkTextEncoding::kUTF16, 42, y + 29, *fontText, paint);
	}
	if (totalHeight > rectHeight) {
		if (hoverScroller) {
			paint.setColor(0xFFD3E3FD);
		}
		else {
			paint.setColor(0x11333333);
		}		
		canvas->drawRoundRect(scrollerRect,3,3, paint);
	}
	canvas->restore();
}

void FavoritePath::mouseMove(const int& x, const int& y)
{
	bool flag{ false };
	if (scrollerRect.contains(x, y)) {
		flag = true;
	}
	if (flag != hoverScroller) {
		hoverScroller = flag;
		repaint();
	}
	if (hoverScroller) {
		hoverIndex = -1;
		return;
	}
	int index{ -1 };
	if (rect.contains(x, y)) {
		auto top = (scrollerRect.fTop - rect.fTop) / rect.height() * totalHeight;
		index = (y - rect.fTop + top) / 46;
	}
	if (index != hoverIndex) {
		hoverIndex = index;
		repaint();
	}
}

void FavoritePath::mouseDown(const int& x, const int& y)
{
	downY = y;
}

void FavoritePath::mouseUp(const int& x, const int& y)
{
	if (!scrollerRect.contains(x,y)) {
		if (hoverScroller) {
			hoverScroller = false;
			repaint();
		}
	}
}

void FavoritePath::mouseDrag(const int& x, const int& y)
{
	if (totalHeight <= rect.height()) {
		return;
	}
	if (!hoverScroller) {
		return;
	}
	float span = y - downY;
	if (span > 0) {
		if (scrollerRect.fBottom < rect.fBottom) {
			auto v = std::min(scrollerRect.fBottom + span, rect.fBottom);
			scrollerRect.offsetTo(rect.fRight - 8, scrollerRect.fTop + v - scrollerRect.fBottom);
			repaint();
		}
	}
	else {
		if (scrollerRect.fTop > rect.fTop) {
			auto v = std::max(scrollerRect.fTop + span, rect.fTop);
			scrollerRect.offsetTo(rect.fRight - 8, v);
			repaint();
		}
	}
	downY = y;
}

void FavoritePath::mouseWheel(const int& x, const int& y,const int& delta)
{
	if (totalHeight <= rect.height()) {
		return;
	}
	if (!rect.contains(x, y)) {
		return;
	}
	auto span = 12.f;
	if (delta > 0) {
		if (scrollerRect.fTop > rect.fTop) {
			auto v = std::max(scrollerRect.fTop - span, rect.fTop);
			scrollerRect.offsetTo(rect.fRight - 8, v);
			auto top = (scrollerRect.fTop - rect.fTop) / rect.height() * totalHeight;
			hoverIndex = (y - rect.fTop + top) / 46;
			repaint();
		}
	}
	else {
		if (scrollerRect.fBottom < rect.fBottom) {
			auto v = std::min(scrollerRect.fBottom + span, rect.fBottom);
			scrollerRect.offsetTo(rect.fRight - 8, scrollerRect.fTop + v - scrollerRect.fBottom);
			auto top = (scrollerRect.fTop - rect.fTop) / rect.height() * totalHeight;
			hoverIndex = (y - rect.fTop + top) / 46;
			repaint();
		}
	}
}

void FavoritePath::resize(const int& w, const int& h)
{
	rect.setXYWH(0, y, root->leftPanel->rect.width(), h - y - 50);
	if (totalHeight > rect.height()) {
		auto h = rect.height() * (rect.height() / totalHeight);
		if (h < 40.f) h = 40.f;
		scrollerRect.setXYWH(rect.fRight - 8, rect.fTop, 8, h);
	}
}
