#include "LeftPanel.h"
#include "WindowMain.h"
#include "SystemIcon.h"
#include "App.h"

LeftPanel::LeftPanel(WindowBase* root) :ControlBase(root)
{
	YGNodeStyleSetHeightAuto(layout);
	YGNodeStyleSetWidth(layout, 380.f);

	auto quickLayout = YGNodeNew();
	YGNodeStyleSetHeightAuto(quickLayout);
	YGNodeStyleSetFlexDirection(quickLayout, YGFlexDirectionRow);
	YGNodeStyleSetFlexWrap(quickLayout, YGWrap::YGWrapWrap);
	YGNodeStyleSetPadding(quickLayout, YGEdgeLeft, 10.f);
	YGNodeStyleSetPadding(quickLayout, YGEdgeRight, 10.f);
	YGNodeStyleSetPadding(quickLayout, YGEdgeTop, 16.f);
	YGNodeStyleSetPadding(quickLayout, YGEdgeBottom, 20.f);
	YGNodeInsertChild(layout, quickLayout, 0);

	for (size_t i = 0; i < 6; i++)
	{
		auto quickItemLayout = YGNodeNew();
		YGNodeStyleSetHeight(quickItemLayout,60);
		YGNodeStyleSetWidth(quickItemLayout, 60);
		YGNodeInsertChild(quickLayout,quickItemLayout, i);
	}
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


				auto driveLayout = YGNodeNew();
				YGNodeStyleSetMargin(driveLayout, YGEdgeTop, 8.f);
				YGNodeStyleSetMargin(driveLayout, YGEdgeRight, 12.f);
				YGNodeStyleSetMargin(driveLayout, YGEdgeLeft, 12.f);
				YGNodeStyleSetHeight(driveLayout, 40);
				YGNodeInsertChild(layout, driveLayout, index);
				index += 1;
			}
		}
	}

	for (size_t i = 0; i < 26; i++)
	{
		auto driveLayout = YGNodeNew();
		if (i == 0) {
			YGNodeStyleSetMargin(driveLayout, YGEdgeTop, 20.f);
		}
		YGNodeStyleSetMargin(driveLayout, YGEdgeRight, 12.f);
		YGNodeStyleSetMargin(driveLayout, YGEdgeLeft, 12.f);
		YGNodeStyleSetHeight(driveLayout, 46);
		YGNodeInsertChild(layout, driveLayout, index);
		index += 1;
	}
	int a = 11;
}

LeftPanel::~LeftPanel()
{
}

void LeftPanel::paint(SkCanvas* canvas)
{
	canvas->save();
	canvas->translate(0, YGNodeLayoutGetTop(YGNodeGetParent(layout)));
	auto rect = getRect();
	SkPaint paint;
	paint.setColor(0xFFE8E8E8);
	canvas->drawLine(rect.fRight, rect.fTop, rect.fRight, rect.fBottom, paint);
	paint.setColor(0x081677ff);
	paint.setStyle(SkPaint::kFill_Style);
	canvas->drawRect(rect, paint);

	YGNodeRef quickLayout = YGNodeGetChild(layout, 0);
	

	std::vector<std::wstring> names{ L"桌面",L"音乐",L"视频",L"下载",L"图片",L"文档" };
	std::vector<GUID> ids{ FOLDERID_Desktop,FOLDERID_Music,FOLDERID_Videos,
						  FOLDERID_Downloads,FOLDERID_Pictures,FOLDERID_Documents };
	for (size_t i = 0; i < 6; i++)
	{
		auto img = SystemIcon::getIcon(ids[i], 24);
		auto itemLayout = YGNodeGetChild(quickLayout, i);
		auto itemRect = getRect(itemLayout);
		itemRect.offsetTo(itemRect.fLeft, itemRect.fTop);
		canvas->drawImage(img, itemRect.centerX()-12, itemRect.centerY()-24);

		auto textLength = wcslen(names[i].data()) * 2;
		auto fontText = App::GetFontText();
		fontText->setSize(16.f);
		auto posText = getStartPosOfIconAtCenterOfRect(names[i], itemRect, fontText.get());
		paint.setColor(0xFF666666);
		canvas->drawSimpleText(names[i].data(), textLength, SkTextEncoding::kUTF16, posText.fX, itemRect.fBottom-8, *fontText, paint);

		//paint.setColor(0x08681234);
		//canvas->drawRect(itemRect, paint);
	}

	auto index = 1;
	for (auto& drive:driveInfo)
	{
		auto itemLayout = YGNodeGetChild(layout, index);
		auto itemRect = getRect(itemLayout);
		itemRect.offsetTo(itemRect.fLeft, itemRect.fTop);
		auto str1 = std::format(L"{}:\\", std::get<0>(drive));
		auto img = SystemIcon::getIcon(str1, 24);
		paint.setColor(0x101677ff);
		canvas->drawRoundRect(itemRect,6,6, paint);
		canvas->drawImage(img, itemRect.fLeft+12, itemRect.fTop+6);

		std::wstring str = std::format(L"本地磁盘({}:)", std::get<0>(drive));
		auto textLength = wcslen(str.data()) * 2;
		auto fontText = App::GetFontText();
		fontText->setSize(16.6f);
		paint.setColor(0xFF333333);
		canvas->drawSimpleText(str.data(), textLength, SkTextEncoding::kUTF16, itemRect.fLeft + 48, itemRect.fTop + 26, *fontText, paint);

		index += 1;
	}

	for (size_t i = 0; i < 26; i++)
	{
		auto itemLayout = YGNodeGetChild(layout, index+i);
		auto itemRect = getRect(itemLayout);
		itemRect.offsetTo(itemRect.fLeft, itemRect.fTop);

		auto img = SystemIcon::getIcon(SIID_FOLDER, 26); //CSIDL_QUICKACCESS
		canvas->drawImage(img, itemRect.fLeft, itemRect.fTop + 8);


		std::wstring str = std::format(L"这是一条收藏的路径({}:)", i);
		auto textLength = wcslen(str.data()) * 2;
		auto fontText = App::GetFontText();
		fontText->setSize(16.6f);
		paint.setColor(0xFF333333);
		canvas->drawSimpleText(str.data(), textLength, SkTextEncoding::kUTF16, 42, itemRect.fTop + 26, *fontText, paint);
	}
	canvas->restore();
}

void LeftPanel::mousemove(const int& x, const int& y)
{
}
