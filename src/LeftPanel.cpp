#include "LeftPanel.h"
#include "WindowMain.h"
#include "SystemIcon.h"
#include "App.h"


LeftPanel::LeftPanel(WindowBase* root) :ControlBase(root)
{
	auto index = 1;
	DWORD drives = GetLogicalDrives();
	for (char drive = 'A'; drive <= 'Z'; ++drive) {
		if (drives & 1 << (drive - 'A')) {
			ULARGE_INTEGER total, avail;
			auto nameStr = std::format(L"{}:\\", drive);
			if (GetDiskFreeSpaceEx(nameStr.c_str(), &avail, &total, nullptr))
			{
				double total_space = static_cast<double>(total.QuadPart);
				double free_space = static_cast<double>(avail.QuadPart);
				bool isDisk = GetDriveType(nameStr.c_str()) == DRIVE_FIXED;
				driveInfo.push_back({ drive,total_space,free_space,isDisk });
			}
		}
	}
	root->resizeHandlers.push_back(
		std::bind(&LeftPanel::resize, this, std::placeholders::_1, std::placeholders::_2)
	);
	quickBtn = std::make_shared<QuickBtn>(root);
	favoritePath = std::make_shared<FavoritePath>(root);
	favoritePath->y = driveInfo.size() * (46 + 8)+60+16+28;
	settingBar = std::make_shared<SettingBar>(root);
}

LeftPanel::~LeftPanel()
{
}

void LeftPanel::paint(SkCanvas* canvas)
{
	SkPaint paint;
	paint.setColor(0xFFE8E8E8);
	canvas->drawLine(rect.fRight, rect.fTop, rect.fRight, rect.fBottom, paint);
	paint.setColor(0x081677ff);
	paint.setStyle(SkPaint::kFill_Style);
	canvas->drawRect(rect, paint);
	quickBtn->paint(canvas);
	SkRect itemRect = SkRect::MakeXYWH(12.f,quickBtn->rect.fBottom+12.f, rect.width() - 24.f, 46.f);
	for (size_t i = 0; i < driveInfo.size(); i++)
	{
		auto str1 = std::format(L"{}:\\", std::get<0>(driveInfo[i]));
		auto img = SystemIcon::getIcon(str1, 24);
		paint.setColor(0x101677ff);
		canvas->drawRoundRect(itemRect,6,6, paint);
		canvas->drawImage(img, itemRect.fLeft+12, itemRect.fTop+9.f);
		std::wstring str = std::format(L"本地磁盘({}:)", std::get<0>(driveInfo[i]));
		auto textLength = wcslen(str.data()) * 2;
		auto fontText = App::GetFontText();
		fontText->setSize(16.6f);
		paint.setColor(0xFF333333);
		canvas->drawSimpleText(str.data(), textLength, SkTextEncoding::kUTF16, 
			itemRect.fLeft + 48.f, itemRect.fTop + 28.f, *fontText, paint);
		itemRect.setXYWH(12.f, itemRect.fBottom + 8.f, rect.width() - 24.f, 46.f);
	}
	favoritePath->paint(canvas);
	settingBar->paint(canvas);
}

void LeftPanel::mousemove(const int& x, const int& y)
{
}

void LeftPanel::resize(const int& w, const int& h)
{
	auto topVal = root->ctrls[0]->rect.height() + root->ctrls[1]->rect.height();
	rect.setXYWH(0.f, topVal, 380.f, h - topVal);
}
