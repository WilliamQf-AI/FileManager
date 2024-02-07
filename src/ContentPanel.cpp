#include "TitleBar.h"
#include "WindowMain.h"
#include "App.h"
#include <filesystem>
#include <fileapi.h>
#include <thread>


ContentPanel::ContentPanel(WindowBase* root) :ControlBase(root)
{
	root->resizeHandlers.push_back(
		std::bind(&ContentPanel::resize, this, std::placeholders::_1, std::placeholders::_2)
	);
	std::jthread myThread(&ContentPanel::getRecentFiles, this);
	myThread.detach();
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
	std::wstring str = L"最近使用的文件";
	auto textLength = wcslen(str.data()) * 2;
	auto fontText = App::GetFontText();
	fontText->setSize(16.8);
	auto verticalVal = getTextVerticalVal(fontText.get());
	canvas->drawSimpleText(str.data(), textLength, SkTextEncoding::kUTF16,
		rect.fLeft + paddingLeft, rect.fTop + 24 + verticalVal, *fontText, paint);

	str = L"使用时间";
	textLength = wcslen(str.data()) * 2;
	canvas->drawSimpleText(str.data(), textLength, SkTextEncoding::kUTF16,
		rightRect.fLeft + paddingLeft, rect.fTop + 24 + verticalVal, *fontText, paint);

	auto font = App::GetFontIcon();
	font->setSize(23.f);
	paint.setAntiAlias(false);
	auto iconCode = (const char*)u8"\ue67d";
	canvas->drawString(iconCode, leftRect.fRight- paddingRight, rect.fTop+ 32.f, *font, paint);
	canvas->drawString(iconCode, rightRect.fRight - paddingRight, rect.fTop + 32.f, *font, paint);

	paint.setColor(0xFF555555);
	auto y = rect.fTop + 35 + 40 + verticalVal;
	for (auto& item:files) //192个要200多毫秒
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


	//std::filesystem::path path(L"C:\\Users\\liuxiaolun\\AppData\\Roaming\\Microsoft\\Windows\\Recent");
	//auto y = rect.fTop + 35+40+verticalVal;
	//for (const auto& entry : std::filesystem::directory_iterator(path)) {
	//	str = entry.path().stem().wstring();
	//	textLength = wcslen(str.data()) * 2;
	//	canvas->drawSimpleText(str.data(), textLength, SkTextEncoding::kUTF16,
	//		rect.fLeft + paddingLeft, y, *fontText, paint);
	//	str = fileTimeToString(entry.last_write_time());
	//	textLength = wcslen(str.data()) * 2;
	//	canvas->drawSimpleText(str.data(), textLength, SkTextEncoding::kUTF16,
	//		rightRect.fLeft + paddingLeft, y, *fontText, paint);
	//	y += 40;
	//}

	auto i = 1;
}

void ContentPanel::resize(const int& w, const int& h)
{
	auto topVal = root->ctrls[0]->rect.height() + root->ctrls[1]->rect.height();
	auto leftVal = root->ctrls[2]->rect.fRight;
	rect.setXYWH(leftVal, topVal, w-leftVal, h - topVal);


	//recent files 
	//C:\Users\liuxiaolun\AppData\Roaming\Microsoft\Windows\Recent
}

void ContentPanel::getRecentFiles()
{
	auto zone = std::chrono::current_zone();
	std::filesystem::path path(L"C:\\Users\\liuxiaolun\\AppData\\Roaming\\Microsoft\\Windows\\Recent");
	for (const auto& entry : std::filesystem::directory_iterator(path)) {
		auto fileName = entry.path().stem().wstring();
		auto sysClock = std::chrono::clock_cast<std::chrono::system_clock>(entry.last_write_time());
		auto zTime = std::chrono::zoned_time(zone, sysClock);
		files.push_back(std::make_tuple(fileName, zTime));
	}
	InvalidateRect(root->hwnd, nullptr, false);
}
