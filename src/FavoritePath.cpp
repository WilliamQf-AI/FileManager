#include "FavoritePath.h"
#include <string>
#include <format>
#include <Windows.h>
#include <include/core/SkPaint.h>

#include "WindowBase.h"
#include "SystemIcon.h"
#include "App.h"

FavoritePath::FavoritePath(WindowBase* root) :ControlBase(root)
{
	totalHeight = 46 * 26;

	root->mouseMoveHandlers.push_back(
		std::bind(&FavoritePath::mouseMove, this, std::placeholders::_1, std::placeholders::_2)
	);
	root->mouseDownHandlers.push_back(
		std::bind(&FavoritePath::mouseDown, this, std::placeholders::_1, std::placeholders::_2)
	);
	root->mouseDragHandlers.push_back(
		std::bind(&FavoritePath::mouseDrag, this, std::placeholders::_1, std::placeholders::_2)
	);
	root->mouseUpHandlers.push_back(
		std::bind(&FavoritePath::mouseUp, this, std::placeholders::_1, std::placeholders::_2)
	);
	root->resizeHandlers.push_back(
		std::bind(&FavoritePath::resize, this, std::placeholders::_1, std::placeholders::_2)
	);
}

FavoritePath::~FavoritePath()
{
}

void FavoritePath::paint(SkCanvas* canvas)
{
	auto rectHeight = rect.height();
	SkPaint paint;
	canvas->save();
	canvas->clipRect(rect);
	auto top = 0 - (scrollerRect.fTop-rect.fTop) / rectHeight * totalHeight;
	for (size_t i = 0; i < 26; i++)
	{
		auto img = SystemIcon::getIcon(SIID_FOLDER, 26); //CSIDL_QUICKACCESS		
		canvas->drawImage(img, 12, rect.fTop + top+ i*46 + 8);
		std::wstring str = std::format(L"这是一条收藏的路径({}:)", i);
		auto textLength = wcslen(str.data()) * 2;
		auto fontText = App::GetFontText();
		fontText->setSize(16.6f);
		paint.setColor(0xFF333333);
		canvas->drawSimpleText(str.data(), textLength, SkTextEncoding::kUTF16, 42, rect.fTop + top+ i * 46 + 26, *fontText, paint);
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
	if (x<rect.fRight && x>rect.fRight - 8 && y > rect.fTop && y < rect.fBottom) {
		flag = true;
	}
	if (flag != hoverScroller) {
		hoverScroller = flag;
		InvalidateRect(root->hwnd, nullptr, false);
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
		}
		InvalidateRect(root->hwnd, nullptr, false);
	}
}

void FavoritePath::mouseDrag(const int& x, const int& y)
{
	if (hoverScroller) {
		auto span = y - downY;
		if (span > 0) {
			if (scrollerRect.fBottom + span < rect.fBottom) {
				scrollerRect.offsetTo(rect.fRight - 8, scrollerRect.fTop + span);
			}
		}
		else {
			if (scrollerRect.fTop + span > rect.fTop) {
				scrollerRect.offsetTo(rect.fRight - 8, scrollerRect.fTop + span);
			}
		}		
		downY = y;
		InvalidateRect(root->hwnd, nullptr, false);
	}
}

void FavoritePath::resize(const int& w, const int& h)
{
	auto yVal = root->ctrls[2]->rect.fTop + y;
	rect.setXYWH(0, yVal, root->ctrls[2]->rect.width(), h - yVal - 50);
	if (totalHeight > rect.height()) {
		auto h = rect.height() * (rect.height() / totalHeight);
		if (h < 40.f) h = 40.f;
		scrollerRect.setXYWH(rect.fRight - 8, rect.fTop, 8, h);
	}
}
