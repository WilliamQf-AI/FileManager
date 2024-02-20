#include "ContentPanel.h"
#include <filesystem>
#include <fileapi.h>
#include <thread>
#include <Windows.h>
#include <shellapi.h>
#include <shlobj.h>
#include "WindowMain.h"
#include "App.h"
#include "TitleBar.h"
#include "ToolBar.h"
#include "LeftPanel.h"



ContentPanel::ContentPanel(WindowMain* root) :ControlBase(root)
{
	contentHeader = std::make_shared<ContentHeader>(root);
	contentList = std::make_shared<ContentList>(root);

	root->mouseMoveHandlers.push_back(
		std::bind(&ContentPanel::mouseMove, this, std::placeholders::_1, std::placeholders::_2)
	);
	root->mouseDownHandlers.push_back(
		std::bind(&ContentPanel::mouseDown, this, std::placeholders::_1, std::placeholders::_2)
	);
	root->mouseDragHandlers.push_back(
		std::bind(&ContentPanel::mouseDrag, this, std::placeholders::_1, std::placeholders::_2)
	);
	root->mouseUpHandlers.push_back(
		std::bind(&ContentPanel::mouseUp, this, std::placeholders::_1, std::placeholders::_2)
	);
	root->resizeHandlers.push_back(
		std::bind(&ContentPanel::resize, this, std::placeholders::_1, std::placeholders::_2)
	);
	root->mouseWheelHandlers.push_back(
		std::bind(&ContentPanel::mouseWheel, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
	);
	getRecentFiles();
}

ContentPanel::~ContentPanel()
{
}

void ContentPanel::paint(SkCanvas* canvas)
{
	if (!needPaint(canvas)) return;
	auto leftRect = SkRect::MakeXYWH(rect.fLeft, rect.fTop, 460.f, 46.f);
	auto rightRect = SkRect::MakeLTRB(rect.fLeft+460.f, rect.fTop, root->w, rect.fTop+46.f);	
	SkPaint paint;
	auto paddingLeft{ 18.f };
	auto fontText = App::GetFontText();
	fontText->setSize(16.8);
	auto verticalVal = getTextVerticalVal(fontText.get());	
	canvas->save();
	canvas->clipRect(clipRect);
	paint.setColor(0xFF555555);
	auto top = 0 - (scrollerRect.fTop - clipRect.fTop) / clipRect.height() * totalHeight;
	auto y = top + clipRect.fTop + verticalVal +28.f;
	if (y > 195.f)y = 195.f; // magic num
	
	for (auto& item:files) //192个要200多毫秒
	{
		auto [fileName, lastTime] = item;
		auto textLength = wcslen(fileName.data()) * 2;
		canvas->save();
		canvas->clipRect(SkRect::MakeLTRB(rect.fLeft,y-20, leftRect.fRight,y+20));
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
	if (totalHeight > clipRect.height()) {
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

void ContentPanel::resize(const int& w, const int& h)
{
	isDirty = true;
	contentHeader->isDirty = true;
	contentList->isDirty = true;

	auto topVal = root->titleBar->rect.height() + root->toolBar->rect.height();
	auto leftVal = root->leftPanel->rect.fRight;
	rect.setXYWH(leftVal, topVal, w-leftVal, h - topVal);



	clipRect = SkRect::MakeLTRB(rect.fLeft, rect.fTop + 46.f, rect.fRight, rect.fBottom);
	auto yVal = topVal+46.f;
	if (totalHeight > clipRect.height()) {
		auto h = clipRect.height() * (clipRect.height() / totalHeight);
		if (h < 40.f) h = 40.f;
		scrollerRect.setXYWH(clipRect.fRight - 16, yVal, 16, h);
	}


	//recent files 
	//C:\Users\liuxiaolun\AppData\Roaming\Microsoft\Windows\Recent
}

void ContentPanel::getRecentFiles()
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

void ContentPanel::mouseMove(const int& x, const int& y)
{
	bool flag{ false };
	if (scrollerRect.contains(x,y)) {
		flag = true;
	}
	if (flag != hoverScroller) {
		hoverScroller = flag;
		repaint();
	}
}

void ContentPanel::mouseDown(const int& x, const int& y)
{
	downY = y;
}

void ContentPanel::mouseUp(const int& x, const int& y)
{
	if (!scrollerRect.contains(x, y)) {
		if (hoverScroller) {
			hoverScroller = false;
			repaint();
		}
	}
}

void ContentPanel::mouseDrag(const int& x, const int& y)
{
	if (hoverScroller) {
		float span = y - downY;
		if (span > 0) {
			if (scrollerRect.fBottom < clipRect.fBottom) {
				auto v = std::min(scrollerRect.fBottom + span, rect.fBottom);
				scrollerRect.offsetTo(rect.fRight - 16, scrollerRect.fTop + v - scrollerRect.fBottom);
				repaint();
			}
		}
		else {
			if (scrollerRect.fTop > clipRect.fTop) {
				auto v = std::max(scrollerRect.fTop + span, rect.fTop);
				scrollerRect.offsetTo(rect.fRight - 16, v);
				repaint();
			}
		}
		downY = y;
	}
}

void ContentPanel::mouseWheel(const int& x, const int& y, const int& delta)
{
	if (rect.contains(x, y)) {
		auto span = 12.f;
		if (delta > 0) {
			if (scrollerRect.fTop > clipRect.fTop) {
				auto v = std::max(scrollerRect.fTop - span, clipRect.fTop);
				scrollerRect.offsetTo(clipRect.fRight - 16, v);
				repaint();
			}
		}
		else {
			if (scrollerRect.fBottom < clipRect.fBottom) {
				auto v = std::min(scrollerRect.fBottom + span, clipRect.fBottom);
				scrollerRect.offsetTo(clipRect.fRight - 16, scrollerRect.fTop + v - scrollerRect.fBottom);
				repaint();
			}
		}
	}
}
