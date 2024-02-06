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
	YGNodeStyleSetFlexGrow(layout, 1.f);
	YGNodeStyleSetWidthAuto(layout);
	YGNodeStyleSetMargin(layout, YGEdgeTop, 18.f);
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
}

FavoritePath::~FavoritePath()
{
}

void FavoritePath::paint(SkCanvas* canvas)
{
	
	rect = getRect();
	auto rectHeight = rect.height();
	SkPaint paint;
	canvas->clipRect(rect);
	canvas->save();
	canvas->translate(rect.fLeft, rect.fTop);
	auto top = 0 - scrollerRect.fTop / rectHeight * totalHeight;
	for (size_t i = 0; i < 26; i++)
	{
		auto img = SystemIcon::getIcon(SIID_FOLDER, 26); //CSIDL_QUICKACCESS		
		canvas->drawImage(img, 12, top+ i*46 + 8);
		std::wstring str = std::format(L"这是一条收藏的路径({}:)", i);
		auto textLength = wcslen(str.data()) * 2;
		auto fontText = App::GetFontText();
		fontText->setSize(16.6f);
		paint.setColor(0xFF333333);
		canvas->drawSimpleText(str.data(), textLength, SkTextEncoding::kUTF16, 42, top+ i * 46 + 26, *fontText, paint);
	}

	if (totalHeight > rectHeight) {
		auto h = rectHeight * (rectHeight/totalHeight);
		if (h < 40.f) h = 40.f;
		scrollerRect.setXYWH(rect.fRight - 8, scrollerRect.fTop,8,h);
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
	auto parent = YGNodeGetParent(YGNodeGetParent(layout));
	auto t = YGNodeLayoutGetTop(parent);
	auto p = YGNodeStyleGetPosition(layout, YGEdgeTop);
	if (x<rect.fRight && x>rect.fRight - 8 && y > rect.fTop+t && y < rect.fBottom+t) {
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
		hoverScroller = false;
	}
}

void FavoritePath::mouseDrag(const int& x, const int& y)
{
	if (hoverScroller) {
		auto span = y - downY;
		if (span > 0) {
			if (scrollerRect.fBottom + span < rect.height()) {
				scrollerRect.offsetTo(rect.fRight - 8, scrollerRect.fTop + span);
			}
		}
		else {
			if (scrollerRect.fTop + span > 0) {
				scrollerRect.offsetTo(rect.fRight - 8, scrollerRect.fTop + span);
			}
		}		
		downY = y;
		InvalidateRect(root->hwnd, nullptr, false);
	}
}
