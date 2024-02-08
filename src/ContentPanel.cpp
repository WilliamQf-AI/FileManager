#include "ContentPanel.h"
#include <filesystem>
#include <fileapi.h>
#include <thread>
#include <Windows.h>
#include <shellapi.h>
#include <shlobj.h>
#include "WindowMain.h"
#include "App.h"



ContentPanel::ContentPanel(WindowBase* root) :ControlBase(root)
{
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
	
	auto leftRect = SkRect::MakeXYWH(rect.fLeft, rect.fTop, 460.f, 46.f);
	auto rightRect = SkRect::MakeLTRB(rect.fLeft+460.f, rect.fTop, root->w, rect.fTop+46.f);
	
	SkPaint paint;
	paint.setColor(0xFFE8E8E8);
	canvas->drawLine(rect.fLeft, rect.fTop + 46.f, rect.fRight, rect.fTop + 46.f,paint);
	canvas->drawLine(rightRect.fLeft, rightRect.fTop, rightRect.fLeft, rightRect.fBottom, paint);

	auto paddingLeft{ 18.f };
	auto paddingRight{ 38.f };
	paint.setColor(0xFF888888);
	std::wstring str = L"���ʹ�õ��ļ�";
	auto textLength = wcslen(str.data()) * 2;
	auto fontText = App::GetFontText();
	fontText->setSize(16.8);
	auto verticalVal = getTextVerticalVal(fontText.get());
	canvas->drawSimpleText(str.data(), textLength, SkTextEncoding::kUTF16,
		rect.fLeft + paddingLeft, rect.fTop + 24 + verticalVal, *fontText, paint);

	str = L"ʹ��ʱ��";
	textLength = wcslen(str.data()) * 2;
	canvas->drawSimpleText(str.data(), textLength, SkTextEncoding::kUTF16,
		rightRect.fLeft + paddingLeft, rect.fTop + 24 + verticalVal, *fontText, paint);

	auto font = App::GetFontIcon();
	font->setSize(23.f);
	paint.setAntiAlias(false);
	auto iconCode = (const char*)u8"\ue67d";
	canvas->drawString(iconCode, leftRect.fRight- paddingRight, rect.fTop+ 32.f, *font, paint);
	canvas->drawString(iconCode, rightRect.fRight - paddingRight, rect.fTop + 32.f, *font, paint);

	
	canvas->save();
	canvas->clipRect(clipRect);
	paint.setColor(0xFF555555);
	auto top = 0 - (scrollerRect.fTop - clipRect.fTop) / clipRect.height() * totalHeight;
	auto y = top + clipRect.fTop + verticalVal +28.f;
	for (auto& item:files) //192��Ҫ200�����
	{
		auto [fileName, lastTime] = item;
		textLength = wcslen(fileName.data()) * 2;
		canvas->drawSimpleText(fileName.data(), textLength, SkTextEncoding::kUTF16,
					rect.fLeft + paddingLeft, y, *fontText, paint);
		auto str = std::format(L"{:%Y-%m-%d %H:%M:%S}", lastTime);
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
	auto topVal = root->ctrls[0]->rect.height() + root->ctrls[1]->rect.height();
	auto leftVal = root->ctrls[2]->rect.fRight;
	rect.setXYWH(leftVal, topVal, w-leftVal, h - topVal);
	clipRect = SkRect::MakeLTRB(rect.fLeft, rect.fTop + 46.f, rect.fRight, rect.fBottom);
	auto yVal = topVal+46.f;
	if (totalHeight > clipRect.height()) {
		auto h = clipRect.height() * (clipRect.height() / totalHeight);
		if (h < 40.f) h = 40.f;
		scrollerRect.setXYWH(clipRect.fRight - 8, yVal, 8, h);
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
	InvalidateRect(root->hwnd, nullptr, false);
}

void ContentPanel::mouseMove(const int& x, const int& y)
{
	bool flag{ false };
	if (scrollerRect.contains(x,y)) {
		flag = true;
	}
	if (flag != hoverScroller) {
		hoverScroller = flag;
		InvalidateRect(root->hwnd, nullptr, false);
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
		}
		InvalidateRect(root->hwnd, nullptr, false);
	}
}

void ContentPanel::mouseDrag(const int& x, const int& y)
{
	if (hoverScroller) {
		float span = y - downY;
		if (span > 0) {
			if (scrollerRect.fBottom < rect.fBottom) {
				auto v = std::min(scrollerRect.fBottom + span, rect.fBottom);
				scrollerRect.offsetTo(rect.fRight - 8, scrollerRect.fTop + v - scrollerRect.fBottom);
				InvalidateRect(root->hwnd, nullptr, false);
			}
		}
		else {
			if (scrollerRect.fTop > rect.fTop) {
				auto v = std::max(scrollerRect.fTop + span, rect.fTop);
				scrollerRect.offsetTo(rect.fRight - 8, v);
				InvalidateRect(root->hwnd, nullptr, false);
			}
		}
		downY = y;
	}
}

void ContentPanel::mouseWheel(const int& x, const int& y, const int& delta)
{
	if (rect.contains(x, y)) {
		auto span = 8.f;
		if (delta > 0) {
			if (scrollerRect.fTop > clipRect.fTop) {
				auto v = std::max(scrollerRect.fTop - span, clipRect.fTop);
				scrollerRect.offsetTo(clipRect.fRight - 8, v);
				InvalidateRect(root->hwnd, nullptr, false);
			}
		}
		else {
			if (scrollerRect.fBottom < clipRect.fBottom) {
				auto v = std::min(scrollerRect.fBottom + span, clipRect.fBottom);
				scrollerRect.offsetTo(clipRect.fRight - 8, scrollerRect.fTop + v - scrollerRect.fBottom);
				InvalidateRect(root->hwnd, nullptr, false);
			}
		}
	}
}
