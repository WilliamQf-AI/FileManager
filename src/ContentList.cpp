#include "ContentList.h"

#include <Windows.h>
#include <shellapi.h>
#include <shlobj.h>
#include <chrono>

#include "App.h"
#include "WindowMain.h"
#include "ContentPanel.h"
#include "FileColumnTime.h"
#include "FileColumnSize.h"
#include "FileColumnPath.h"
#include "TitleBar.h"
#include "TitleBarTab.h"
#include "SystemIcon.h"

ContentList::ContentList(WindowMain* root) :ControlBase(root)
{
	auto func = std::bind(&ContentList::tabChange, this, std::placeholders::_1, std::placeholders::_2);
	root->titleBar->tabChangeEvents.push_back(std::move(func));
}

ContentList::~ContentList()
{
}

void ContentList::paint(SkCanvas* canvas)
{
	if (!needPaint(canvas)) return;
	auto parent = (ContentPanel*)root->contentPanel.get();
	auto paddingLeft = parent->contentHeader->paddingLeft;
	auto paddingRight = parent->contentHeader->paddingRight;
	auto columns = parent->contentHeader->columns;
	auto fontText = App::GetFontText();
	fontText->setSize(18.f);
	canvas->save();
	canvas->clipRect(rect);
	auto top = 0 - (scrollerRect.fTop - rect.fTop) / rect.height() * totalHeight;
	auto y = top + rect.fTop + 32.f;
	SkPaint paint;
	paint.setAntiAlias(true);
	auto rootPath = root->titleBar->tabs[root->titleBar->selectedTabIndex]->path.wstring();
	for (auto& file : files)
	{
		for (size_t i = 0; i < columns.size(); i++)
		{
			canvas->save();
			auto left = columns[i].left + paddingLeft;
			canvas->clipRect(SkRect::MakeLTRB(left, y - 20, columns[i].right - paddingRight, y + 20));
			if (i == 0) {
				auto str = std::format(L"{}\\{}",rootPath, file[i].text);
				auto img = SystemIcon::getIcon(str); //24
				canvas->drawImage(img, left, y - 18);
				left += 34;
				paint.setColor(0xFF555555);
			}
			else {
				paint.setColor(0xFF999999);
			}
			auto len = wcslen(file[i].text.data()) * 2;
			canvas->drawSimpleText(file[i].text.data(), len, SkTextEncoding::kUTF16, left, y, *fontText, paint);
			canvas->restore();
		}
		y += 48;
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
	paint.setColor(0xFFE8E8E8);
	canvas->drawLine(rect.fLeft, rect.fBottom, rect.fRight, rect.fBottom, paint);
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
	auto parent = (ContentPanel*)root->contentPanel.get();
	rect.setLTRB(parent->rect.fLeft+1,
		parent->contentHeader->rect.fBottom+1,
		parent->rect.fRight,
		parent->contentBottom->rect.fTop
	);
	if (totalHeight > rect.height()) {
		auto h = rect.height() * (rect.height() / totalHeight);
		if (h < 40.f) h = 40.f;
		scrollerRect.setXYWH(rect.fRight - 16, rect.fTop, 16, h);
	}
	else {
		scrollerRect.setXYWH(0, rect.fTop, 0, 0);
	}
}

void ContentList::mouseWheel(const int& x, const int& y, const int& delta)
{
	if (totalHeight <= rect.height()) {
		return;
	}
	if (!rect.contains(x, y)) {
		return;
	}
	auto span = 16.f;
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

void ContentList::tabChange(TitleBarTab* tab, TitleBarTab* tabNew)
{
	if (tab->path == tabNew->path) {
		if (scrollerRect.fTop != rect.fTop) {
			isDirty = true;
			setScrollerRect();
		}
		return;
	}
	root->contentPanel->isDirty = true;
	files.clear();
	if (tabNew->path.empty()) {
		return;
	}
	if (tab->path.empty()) {
		root->contentPanel->contentHeader->isDirty = true;
	}	
	isDirty = true;
	auto zone = std::chrono::current_zone();
	SHFILEINFO fileInfo = { 0 };
	for (const auto& entry : std::filesystem::directory_iterator(tabNew->path)) {
		auto fileName = entry.path().filename().wstring();
		if (fileName == L"desktop.ini") {
			continue;
		}
		auto fileTime = entry.last_write_time();
		auto sysClock = std::chrono::clock_cast<std::chrono::system_clock>(fileTime);
		auto zTime = std::chrono::zoned_time(zone, sysClock);
		auto fileTimeStr = std::format(L"{:%Y-%m-%d %H:%M:%S}", zTime);
		fileTimeStr = fileTimeStr.substr(0, fileTimeStr.find_last_of(L"."));
		std::wstring  typeStr;
		unsigned long long fileSize{ 0 };
		auto hr = SHGetFileInfo(entry.path().wstring().c_str(), 0, &fileInfo, sizeof(fileInfo),
			SHGFI_USEFILEATTRIBUTES | SHGFI_TYPENAME | SHGFI_SYSICONINDEX);
		if (std::filesystem::is_directory(entry.path())) {
			typeStr = L"文件夹";
		}
		else {
			if (hr)
			{
				//todo
				//if ((fileInfo.dwAttributes & FILE_ATTRIBUTE_HIDDEN) == FILE_ATTRIBUTE_HIDDEN) {  //
				//	continue;
				//}
				typeStr = fileInfo.szTypeName;
			}
			fileSize = std::filesystem::file_size(entry.path()) / 1024;
		}		
		//auto p = entry.path().wstring();
		//FileColumnPath fcp(fileName, p);
		files.push_back({ FileColumn(fileName),
			FileColumnTime(fileTimeStr,fileTime),
			FileColumnSize(fileSize),FileColumn(typeStr)});
	}
	totalHeight = 40 * files.size();
	std::sort(files.begin(), files.end(), [](const auto& a, const auto& b) {
		return a[1] > b[1];
		});
	setScrollerRect();
}

void ContentList::getRecentFiles()
{
	PWSTR pszPath = nullptr;
	HRESULT hr = SHGetKnownFolderPath(FOLDERID_Recent, 0, NULL, &pszPath);
	std::wstring pathStr(pszPath);
	CoTaskMemFree(pszPath);

	auto zone = std::chrono::current_zone();
	std::filesystem::path path(pathStr);
	SHFILEINFO fileInfo = { 0 };
	for (const auto& entry : std::filesystem::directory_iterator(path)) {
		auto fileName = entry.path().stem().wstring();
		auto fileTime = entry.last_write_time();
		auto sysClock = std::chrono::clock_cast<std::chrono::system_clock>(entry.last_write_time());
		auto zTime = std::chrono::zoned_time(zone, sysClock);
		auto str = std::format(L"{:%Y-%m-%d %H:%M:%S}", zTime);
		str = str.substr(0, str.find_last_of(L"."));


		files.push_back({ FileColumn(fileName), FileColumnTime(str,fileTime)});
	}
	totalHeight = 40 * files.size();
	std::sort(files.begin(), files.end(), [](const auto& a, const auto& b) {
		return a[1] > b[1];
		});
}

void ContentList::setScrollerRect()
{
	if (totalHeight > rect.height()) {
		auto h = rect.height() * (rect.height() / totalHeight);
		if (h < 40.f) h = 40.f;
		scrollerRect.setXYWH(rect.fRight - 16, rect.fTop, 16, h);
	}
	else {
		scrollerRect.setXYWH(0, rect.fTop, 0, 0);
	}
}
