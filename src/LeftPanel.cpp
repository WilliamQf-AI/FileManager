#include "LeftPanel.h"
#include "WindowMain.h"
#include "SystemIcon.h"
#include "App.h"

LeftPanel::LeftPanel(WindowBase* root) :ControlBase(root)
{
	root->resizeHandlers.push_back(
		std::bind(&LeftPanel::resize, this, std::placeholders::_1, std::placeholders::_2)
	);
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
	

	std::vector<std::wstring> names{ L"桌面",L"音乐",L"视频",L"下载",L"图片",L"文档" };
	std::vector<GUID> ids{ FOLDERID_Desktop,FOLDERID_Music,FOLDERID_Videos,
						  FOLDERID_Downloads,FOLDERID_Pictures,FOLDERID_Documents };
	auto itemRect = SkRect::MakeXYWH(10.f, rect.fTop + 16.f, 60.f, 60.f);
	for (size_t i = 0; i < 6; i++)
	{
		itemRect.offsetTo(10.f + 60 * i, rect.fTop + 16.f);
		auto img = SystemIcon::getIcon(ids[i], 24);
		canvas->drawImage(img, itemRect.centerX() - 12, itemRect.centerY() - 24);
		auto textLength = wcslen(names[i].data()) * 2;
		auto fontText = App::GetFontText();
		fontText->setSize(16.f);
		auto posText = getStartPosOfIconAtCenterOfRect(names[i], itemRect, fontText.get());
		paint.setColor(0xFF666666);
		canvas->drawSimpleText(names[i].data(), textLength, SkTextEncoding::kUTF16, posText.fX, itemRect.fBottom-8, *fontText, paint);
	}
	itemRect.fBottom = itemRect.fBottom + 12.f;
	for (size_t i = 0; i < driveInfo.size(); i++)
	{
		itemRect.setXYWH(12.f, itemRect.fBottom + 8.f, rect.width() - 24.f, 46.f);
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
