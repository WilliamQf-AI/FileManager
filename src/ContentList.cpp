#include "ContentList.h"

#include <Windows.h>
#include <shellapi.h>
#include <shlobj.h>

#include "App.h"
#include "WindowMain.h"
#include "ContentPanel.h"

ContentList::ContentList(WindowMain* root) :ControlBase(root)
{
	getRecentFiles();
	root->mouseMoveHandlers.push_back(
		std::bind(&ContentList::mouseMove, this, std::placeholders::_1, std::placeholders::_2)
	);
	root->mouseDownHandlers.push_back(
		std::bind(&ContentList::mouseDown, this, std::placeholders::_1, std::placeholders::_2)
	);
	root->mouseDragHandlers.push_back(
		std::bind(&ContentList::mouseDrag, this, std::placeholders::_1, std::placeholders::_2)
	);
	root->mouseUpHandlers.push_back(
		std::bind(&ContentList::mouseUp, this, std::placeholders::_1, std::placeholders::_2)
	);
	root->resizeHandlers.push_back(
		std::bind(&ContentList::resize, this, std::placeholders::_1, std::placeholders::_2)
	);
}

ContentList::~ContentList()
{
}

void ContentList::paint(SkCanvas* canvas)
{
	auto leftRect = SkRect::MakeXYWH(rect.fLeft, rect.fTop, 460.f, 46.f);
	auto rightRect = SkRect::MakeLTRB(rect.fLeft + 460.f, rect.fTop, root->w, rect.fTop + 46.f);
	SkPaint paint;
	auto paddingLeft{ 18.f };
	auto fontText = App::GetFontText();
	fontText->setSize(16.8);
	auto verticalVal = getTextVerticalVal(fontText.get());
	canvas->save();
	canvas->clipRect(rect);
	paint.setColor(0xFF555555);
	auto top = 0 - (scrollerRect.fTop - rect.fTop) / rect.height() * totalHeight;
	auto y = top + rect.fTop + verticalVal + 28.f;
	if (y > 195.f)y = 195.f; // magic num

	for (auto& item : files) //192个要200多毫秒
	{
		auto [fileName, lastTime] = item;
		auto textLength = wcslen(fileName.data()) * 2;
		canvas->save();
		canvas->clipRect(SkRect::MakeLTRB(rect.fLeft, y - 20, leftRect.fRight, y + 20));
		canvas->drawSimpleText(fileName.data(), textLength, SkTextEncoding::kUTF16,
			rect.fLeft + paddingLeft, y, *fontText, paint);
		canvas->restore();
		auto str = std::format(L"{:%Y-%m-%d %H:%M:%S}", lastTime);
		str = str.substr(0, str.find_last_of(L"."));
		textLength = wcslen(str.data()) * 2;
		canvas->drawSimpleText(str.data(), textLength, SkTextEncoding::kUTF16,
			rightRect.fLeft + paddingLeft, y, *fontText, paint);
		y += 40;
	}
	if (totalHeight > rect.height()) {
		if (hoverScroller) {
			paint.setColor(0xFFD3E3FD);
		}
		else {
			paint.setColor(0x11333333);
		}
		canvas->drawRoundRect(scrollerRect, 3, 3, paint);
	}
	canvas->restore();
}

void ContentList::mouseMove(const int& x, const int& y)
{
	bool flag{ false };
	if (scrollerRect.contains(x, y)) {
		flag = true;
	}
	if (flag != hoverScroller) {
		hoverScroller = flag;
		repaint();
	}
}

void ContentList::mouseDown(const int& x, const int& y)
{
	downY = y;
}

void ContentList::mouseUp(const int& x, const int& y)
{
	if (!scrollerRect.contains(x, y)) {
		if (hoverScroller) {
			hoverScroller = false;
			repaint();
		}
	}
}

void ContentList::mouseDrag(const int& x, const int& y)
{
	if (hoverScroller) {
		float span = y - downY;
		if (span > 0) {
			if (scrollerRect.fBottom < rect.fBottom) {
				auto v = std::min(scrollerRect.fBottom + span, rect.fBottom);
				scrollerRect.offsetTo(rect.fRight - 16, scrollerRect.fTop + v - scrollerRect.fBottom);
				repaint();
			}
		}
		else {
			if (scrollerRect.fTop > rect.fTop) {
				auto v = std::max(scrollerRect.fTop + span, rect.fTop);
				scrollerRect.offsetTo(rect.fRight - 16, v);
				repaint();
			}
		}
		downY = y;
	}
}

void ContentList::resize(const int& w, const int& h)
{
	rect.setLTRB(root->contentPanel->rect.fLeft,
		root->contentPanel->contentHeader->rect.fBottom,
		root->contentPanel->rect.fRight,
		root->contentPanel->contentBottom->rect.fTop
	);
	if (totalHeight > rect.height()) {
		auto h = rect.height() * (rect.height() / totalHeight);
		if (h < 40.f) h = 40.f;
		scrollerRect.setXYWH(rect.fRight - 16, rect.fTop, 16, h);
	}
}

void ContentList::mouseWheel(const int& x, const int& y, const int& delta)
{
	if (rect.contains(x, y)) {
		auto span = 12.f;
		if (delta > 0) {
			if (scrollerRect.fTop > rect.fTop) {
				auto v = std::max(scrollerRect.fTop - span, rect.fTop);
				scrollerRect.offsetTo(rect.fRight - 16, v);
				repaint();
			}
		}
		else {
			if (scrollerRect.fBottom < rect.fBottom) {
				auto v = std::min(scrollerRect.fBottom + span, rect.fBottom);
				scrollerRect.offsetTo(rect.fRight - 16, scrollerRect.fTop + v - scrollerRect.fBottom);
				repaint();
			}
		}
	}
}

void ContentList::getRecentFiles()
{
	PWSTR pszPath = nullptr;
	HRESULT hr = SHGetKnownFolderPath(FOLDERID_Recent, 0, NULL, &pszPath);
	std::wstring pathStr(pszPath);
	CoTaskMemFree(pszPath);

	auto zone = std::chrono::current_zone();
	std::filesystem::path path(pathStr);
	for (const auto& entry : std::filesystem::directory_iterator(path)) {
		auto fileName = entry.path().stem().wstring();
		auto sysClock = std::chrono::clock_cast<std::chrono::system_clock>(entry.last_write_time());
		auto zTime = std::chrono::zoned_time(zone, sysClock);
		files.push_back(std::make_tuple(fileName, zTime));
	}
	totalHeight = 40 * files.size();
}