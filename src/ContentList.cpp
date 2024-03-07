#include "ContentList.h"

#include <Windows.h>
#include <shellapi.h>
#include <shlobj.h>
#include <chrono>


#include "App.h"
#include "WindowMain.h"
#include "ContentPanel.h"
#include "TitleBar.h"
#include "TitleBarTab.h"
#include "SystemIcon.h"
#include "ToolBar.h"
#include "ToolBarAddress.h"

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
	auto columns = parent->contentHeader->columns;
	auto fontText = App::GetFontText();
	fontText->setSize(18.f);
	canvas->save();
	canvas->clipRect(rect);	
	SkPaint paint;
	paint.setAntiAlias(true);
	if (hoverIndex > -1) {
		auto y = rect.fTop + hoverIndex*lineHieght - offsetTop;
		paint.setColor(0x101677ff);
		canvas->drawRect(SkRect::MakeLTRB(rect.fLeft, y, rect.fRight, y + lineHieght), paint);
	}
	for (size_t i = 0; i < columns.size(); i++)
	{
		auto y = rect.fTop + 32.f - offsetTop;
		auto x = root->contentPanel->contentHeader->scrollerLeft + columns[i].left + parent->contentHeader->padding;
		canvas->save();
		canvas->clipRect(SkRect::MakeLTRB(x, y - 20, 
			root->contentPanel->contentHeader->scrollerLeft + columns[i].right - parent->contentHeader->padding, 
			rect.fBottom));
		for (size_t j = 0; j < files.size(); j++)
		{
			auto text = files[j][i]->getText();
			auto len = wcslen(text.data()) * 2;
			if (i == 0) {
				auto filePath = std::filesystem::path(root->titleBar->getCurTab()->path).append(text);
				auto img = SystemIcon::getIcon(filePath); //24
				canvas->drawImage(img, x, y - 18);
				if (j == hoverIndex) {
					paint.setColor(0xFF000000);
				}
				else {
					paint.setColor(0xFF555555);
				}
				
				canvas->drawSimpleText(text.data(), len, SkTextEncoding::kUTF16, x+34, y, *fontText, paint);
			}
			else {
				if (j == hoverIndex) {
					paint.setColor(0xFF000000);
				}
				else {
					paint.setColor(0xFF999999);
				}
				canvas->drawSimpleText(text.data(), len, SkTextEncoding::kUTF16, x, y, *fontText, paint);
			}
			y += lineHieght;
		}
		canvas->restore();
	}
	if (totalHeight > rect.height()) {
		if (hoverScroller==0) {
			paint.setColor(0xFFD3E3FD);
		}
		else {
			paint.setColor(0x11333333);
		}
		canvas->drawRoundRect(scrollerRight, 3, 3, paint);
	}
	if (root->contentPanel->contentHeader->totalWidth > rect.width()) {
		if (hoverScroller == 1) {
			paint.setColor(0xFFD3E3FD);
		}
		else {
			paint.setColor(0x11333333);
		}
		canvas->drawRoundRect(scrollerBottom, 3, 3, paint);
	}
	canvas->restore();
	paint.setColor(0xFFE8E8E8);
	canvas->drawLine(rect.fLeft, rect.fBottom, rect.fRight, rect.fBottom, paint);
}

void ContentList::mouseMove(const int& x, const int& y)
{
	if (root->titleBar->getCurTab()->path.empty()) {
		return;
	}
	int flag{ -1 };
	if (scrollerRight.contains(x, y)) {
		flag = 0;
	}
	else if (scrollerBottom.contains(x, y)) {
		flag = 1;
	}
	if (flag != hoverScroller) {
		hoverScroller = flag;
		repaint();
	}
	if (hoverScroller>=0) {
		hoverIndex = -1;
		return;
	}
	int index{ -1 };
	if (rect.contains(x, y)) {
		index = (y - rect.fTop + offsetTop) / lineHieght;;
		if (index >= files.size()) {
			index = -1;
		}
	}
	if (index != hoverIndex) {
		hoverIndex = index;
		repaint();
	}
}

void ContentList::mouseDown(const int& x, const int& y)
{
	downX = x;
	downY = y;
	if (hoverScroller>=0) {
		SetCapture(root->hwnd);
	}
	if (hoverIndex >= 0) {
		auto span = std::chrono::system_clock::now() - mouseDownTime;
		auto msCount = std::chrono::duration_cast<std::chrono::milliseconds>(span).count();
		if (msCount < 380) {
			auto tab = root->titleBar->getCurTab();
			auto filePath = std::filesystem::path(tab->path).append(files[hoverIndex][0]->getText());
			if (std::filesystem::is_directory(filePath)) {
				tab->path = filePath;
				getFiles(filePath);
				tab->isDirty = true;
				root->toolBar->toolBarAddress->isDirty = true;
				isDirty = true;
				InvalidateRect(root->hwnd, nullptr, false);
			}
			else {
				if (!std::filesystem::exists(filePath)) {
					return;
				}
				HINSTANCE result = ShellExecute(NULL, L"open", filePath.wstring().data(), NULL, NULL, SW_SHOW);
				if ((INT_PTR)result > 32)
				{
					// 成功打开了文件
				}
				else
				{
					//todo
					DWORD error = GetLastError();
				}
			}
		}
		mouseDownTime = std::chrono::system_clock::now();
	}
}

void ContentList::mouseUp(const int& x, const int& y)
{
	if (!scrollerRight.contains(x, y)) {
		if (hoverScroller>=0) {
			hoverScroller = -1;
			ReleaseCapture();
			repaint();
		}
	}
}

void ContentList::mouseDrag(const int& x, const int& y)
{
	if (hoverScroller == 0) { //右侧滚动条
		float span = y - downY;
		rightScrollerMove(span);
		hoverIndex = (y - rect.fTop + offsetTop) / lineHieght;
		repaint();
		downY = y;
	}
	else if (hoverScroller == 1) { //下方滚动条
		float span = x - downX;
		bottomScrollerMove(span);
		downX = x;
	}
}

void ContentList::resize(const int& w, const int& h)
{
	auto parent = (ContentPanel*)root->contentPanel.get();
	bool flag = rect.isEmpty();
	rect.setLTRB(parent->rect.fLeft+1,
		parent->contentHeader->rect.fBottom+1,
		parent->rect.fRight,
		parent->contentBottom->rect.fTop
	);
	if (offsetTop>0) {
		if (totalHeight <= rect.height()) {
			offsetTop = 0;
		}
		else if(offsetTop + rect.height() > totalHeight) {
			offsetTop = totalHeight - rect.height();
		}		
	}
	if (!flag) {
		setRightScroller();
		setBottomScroller();
	}
}

void ContentList::mouseWheel(const int& x, const int& y, const int& delta)
{
	if (totalHeight <= rect.height() || !rect.contains(x, y) || root->titleBar->getCurTab()->path.empty()) {
		return;
	}
	rightScrollerMove(delta > 0 ? -16.f : 16.f);
	hoverIndex = (y - rect.fTop + offsetTop) / lineHieght;
	repaint();
}


void ContentList::setRightScroller()
{
	if (totalHeight > rect.height()) {
		auto h = rect.height() * (rect.height() / totalHeight);
		if (h < scrollerMiniSize) {
			h = scrollerMiniSize;
		}
		scrollerRight.setXYWH(rect.fRight - 16, rect.fTop, 16, h);
	}
	else {
		scrollerRight.setXYWH(0, rect.fTop, 0, 0);
	}
}

void ContentList::setBottomScroller()
{
	auto totalWidth = root->contentPanel->contentHeader->totalWidth;
	if (totalWidth > rect.width()) {
		auto w = rect.width() * (rect.width() / totalWidth);
		if (w < 80.f) w = 80.f;
		scrollerBottom.setXYWH(rect.fLeft, rect.fBottom - 16.f, w, 16);
	}
	else {
		scrollerBottom.setXYWH(rect.fLeft, 0, 0, 0);
	}
}

void ContentList::tabChange(TitleBarTab* tab, TitleBarTab* tabNew)
{
	if (tab->path == tabNew->path) {
		if (offsetTop != 0) {
			offsetTop = 0;
			isDirty = true;
			setRightScroller();
		}
		return;
	}
	if (tabNew->path.empty()) {
		totalHeight = 0;
		root->contentPanel->isDirty = true;
		return;
	}
	if (tab->path.empty()) {
		root->contentPanel->contentHeader->isDirty = true;
	}
	offsetTop = 0;
	getFiles(tabNew->path);
}

void ContentList::getRecentFiles()
{
	//PWSTR pszPath = nullptr;
	//HRESULT hr = SHGetKnownFolderPath(FOLDERID_Recent, 0, NULL, &pszPath);
	//std::wstring pathStr(pszPath);
	//CoTaskMemFree(pszPath);
	//auto zone = std::chrono::current_zone();
	//std::filesystem::path path(pathStr);
	//SHFILEINFO fileInfo = { 0 };
	//for (const auto& entry : std::filesystem::directory_iterator(path)) {
	//	auto fileName = entry.path().stem().wstring();
	//	auto fileTime = entry.last_write_time();
	//	auto sysClock = std::chrono::clock_cast<std::chrono::system_clock>(entry.last_write_time());
	//	auto zTime = std::chrono::zoned_time(zone, sysClock);
	//	auto str = std::format(L"{:%Y-%m-%d %H:%M:%S}", zTime);
	//	str = str.substr(0, str.find_last_of(L"."));
	//	files.push_back({ FileColumn(fileName), FileColumnTime(str,fileTime)});
	//}
	//totalHeight = 40 * files.size();
	//std::sort(files.begin(), files.end(), [](const auto& a, const auto& b) {
	//	return a[1] > b[1];
	//	});
}

void ContentList::rightScrollerMove(const float& span)
{
	if (span < 0) {
		if (offsetTop == 0) {
			return;
		}
		offsetTop += span;
		if (offsetTop < 0) {
			offsetTop = 0;
		}
	}
	else {
		if (offsetTop + rect.height() == totalHeight) {
			return;
		}
		offsetTop += span;
		if (offsetTop + rect.height() > totalHeight) {
			offsetTop = totalHeight - rect.height();
		}
	}
	auto scroolerRightTop = offsetTop / (totalHeight - rect.height()) * (rect.height() - scrollerRight.height());
	scrollerRight.offsetTo(rect.fRight - 16, rect.fTop + scroolerRightTop);
}

void ContentList::bottomScrollerMove(const float& span)
{
	if (span > 0) {
		if (scrollerBottom.fRight < rect.fRight) {
			auto v = std::min(scrollerBottom.fRight + span, rect.fRight);
			scrollerBottom.offsetTo(scrollerBottom.fLeft + v - scrollerBottom.fRight, rect.fBottom - 16);
			root->contentPanel->contentHeader->scrollerLeft =
				0 - (scrollerBottom.fLeft - rect.fLeft) / rect.width() * root->contentPanel->contentHeader->totalWidth;
			isDirty = true;
			root->contentPanel->contentHeader->isDirty = true;
			InvalidateRect(root->hwnd, nullptr, false);
		}
	}
	else {
		if (scrollerBottom.fLeft > rect.fLeft) {
			auto v = std::max(scrollerBottom.fLeft + span, rect.fLeft);
			scrollerBottom.offsetTo(v, rect.fBottom - 16);
			root->contentPanel->contentHeader->scrollerLeft =
				0 - (scrollerBottom.fLeft - rect.fLeft) / rect.width() * root->contentPanel->contentHeader->totalWidth;
			isDirty = true;
			root->contentPanel->contentHeader->isDirty = true;
			InvalidateRect(root->hwnd, nullptr, false);
		}
	}
}

void ContentList::getFiles(std::filesystem::path& path)
{
	files.clear();
	isDirty = true;
	auto zone = std::chrono::current_zone();

	SHFILEINFO fileInfo{ 0 };
	WIN32_FIND_DATA data;
	HANDLE hFind = FindFirstFile((path.wstring() + L"\\*").data(), &data);// FindFirstFile(L"C:\\Windows\\System32\\*", &data);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (wcscmp(data.cFileName, L".") == 0 || wcscmp(data.cFileName, L"..") == 0) {
				continue;
			}
			if ((data.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM))
			{
				//(data.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) || 
				continue;
			}
			std::wstring fileName(data.cFileName);
			FILETIME fTime;
			FileTimeToLocalFileTime(&data.ftLastWriteTime, &fTime);
			SYSTEMTIME fileTime;
			FileTimeToSystemTime(&fTime, &fileTime);
			std::wstring  typeStr;
			size_t dotPos = fileName.rfind(L'.');
			if (dotPos != std::wstring::npos) {
				typeStr = fileName.substr(dotPos + 1); //TXT
				std::transform(typeStr.begin(), typeStr.end(), typeStr.begin(),toupper);
			}
			ULARGE_INTEGER fileSize;
			fileSize.HighPart = data.nFileSizeHigh;
			fileSize.LowPart = data.nFileSizeLow;
			files.push_back({ std::make_shared<Column<std::wstring>>(fileName),
				std::make_shared<Column<SYSTEMTIME>>(fileTime),
				std::make_shared<Column<unsigned long long>>(fileSize.QuadPart),
				std::make_shared<Column<std::wstring>>(typeStr)
				});
			
		} while (FindNextFile(hFind, &data));
	}
	FindClose(hFind);
	totalHeight = lineHieght * files.size();
	setRightScroller();
	setBottomScroller();
}

