#include "DiskList.h"
#include "WindowMain.h"
#include "SystemIcon.h"
#include "App.h"
#include "TitleBar.h"

DiskList::DiskList(WindowMain* root) :ControlBase(root)
{
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
}

DiskList::~DiskList()
{
}

void DiskList::paint(SkCanvas* canvas)
{
	if (!needPaint(canvas, 0xFFF8FBFF)) return;
	SkPaint paint;
	SkRect itemRect = SkRect::MakeXYWH(12.f, y, rect.width() - 24.f, 46.f);
	for (size_t i = 0; i < driveInfo.size(); i++)
	{
		auto img = SystemIcon::getIcon(std::format(L"{}:\\", std::get<0>(driveInfo[i]))); //28
		if (hoverIndex == i) {
			paint.setColor(0x221677ff);
		}
		else {
			paint.setColor(0x101677ff);
		}
		canvas->drawRoundRect(itemRect, 6, 6, paint);
		canvas->drawImage(img, itemRect.fLeft + 12, itemRect.fTop + 3.f);
		std::wstring str = std::format(L"本地磁盘({}:)", std::get<0>(driveInfo[i]));
		auto textLength = wcslen(str.data()) * 2;
		auto fontText = App::GetFontText();
		fontText->setSize(16.6f);
		if (hoverIndex == i) {
			paint.setColor(0xFF000000);
		}
		else {
			paint.setColor(0xFF666666);
		}
		canvas->drawSimpleText(str.data(), textLength, SkTextEncoding::kUTF16,
			itemRect.fLeft + 50.f, itemRect.fTop + 28.f, *fontText, paint);
		itemRect.setXYWH(12.f, itemRect.fBottom + 8.f, rect.width() - 24.f, 46.f);
	}
}

void DiskList::resize(const int& w, const int& h)
{
	auto h1 = driveInfo.size() * (46 + 8);
	rect.setXYWH(0.f, y, 380.f, h1);
}

void DiskList::mouseMove(const int& x, const int& y)
{
	auto index = -1;
	if (rect.contains(x, y)&& x>12 && x<rect.fRight-12) {
		for (size_t i = 0; i < driveInfo.size(); i++)
		{
			auto val = rect.fTop + i * (46.f + 8.f);
			if (y > val && y < val + 46.f) {
				index = i;
				break;
			}
		}
	}
	if (index != hoverIndex) {
		hoverIndex = index;
		repaint();
	}
}

void DiskList::mouseDown(const int& x, const int& y)
{
	if (hoverIndex >= 0) {
		auto pathStr = std::format(L"{}:\\", std::get<0>(driveInfo[hoverIndex]));
		root->titleBar->addTab(pathStr);
	}
}
