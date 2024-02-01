#include "TitleBarTab.h"
#include <Windows.h>
#include <shellapi.h>
#include <shlobj.h>
#include "yoga/Yoga.h"
#include "yoga/YGConfig.h"
#include "include/core/SkRRect.h"
#include "include/core/SkPixmap.h"
#include "include/core/SkBitmap.h"
#include "include/core/SkSurface.h"


TitleBarTab::TitleBarTab(WindowBase* root) :Layout(root)
{
	YGNodeStyleSetFlexDirection(layout, YGFlexDirectionRow);
	YGNodeStyleSetWidthAuto(layout);
	YGNodeStyleSetMaxWidth(layout, 260.f);
	YGNodeStyleSetHeight(layout, 46.f);
	YGNodeStyleSetMargin(layout, YGEdgeTop, 10.f);
}

TitleBarTab::~TitleBarTab()
{
}

void TitleBarTab::paint(SkCanvas* canvas)
{	
	auto left = YGNodeLayoutGetLeft(layout);
	auto rect = getOffsetRect();
	SkPaint paint;
	paint.setAntiAlias(true);
	if (isSelected) {
		paint.setColor(0xFFFFFFFF);
	}
	paint.setStyle(SkPaint::kFill_Style);
	SkVector radii[4] = { {6, 6}, {6, 6}, {0, 0}, {0, 0} };
	auto rr = SkRRect::MakeEmpty();
	rr.setRectRadii(rect, radii);
	canvas->drawRRect(rr, paint);

	SHSTOCKICONINFO sii = { sizeof(SHSTOCKICONINFO) };
	HRESULT hr = SHGetStockIconInfo(SIID_FOLDER, SHGSI_ICON | SHGSI_LARGEICON, &sii);
	if (SUCCEEDED(hr)) {
		HICON icon = sii.hIcon;

		BITMAP bmpInfo;
		GetObject(icon, sizeof(BITMAP), &bmpInfo);

		//auto width = GetSystemMetrics(SM_CXICON);
		//auto height = GetSystemMetrics(SM_CXICON);

		auto width = 36;
		auto height = 36;
		
		HDC hdcScreen = GetDC(NULL);
		HDC hdcMemory = CreateCompatibleDC(hdcScreen);
		auto hBmp = CreateCompatibleBitmap(hdcScreen, width, width);
		SelectObject(hdcMemory, hBmp);
		DrawIconEx(hdcMemory, 0, 0, icon, width, height, 0, NULL, DI_NORMAL);

		SkImageInfo imgInfo = SkImageInfo::MakeN32Premul(width, height);
		std::vector<int32_t> pixSrcData;
		pixSrcData.resize(width*height*4);
		SkPixmap pixmap(imgInfo, &pixSrcData.front(), width*4);

		


		BITMAPINFO info = { sizeof(BITMAPINFOHEADER), width, 0 - height, 1, 32, BI_RGB, width * 4 * height, 0, 0, 0, 0 };
		GetDIBits(hdcMemory, hBmp, 0, height, &pixSrcData.front(), &info, DIB_RGB_COLORS);


		SkBitmap bitmap;
		bitmap.installPixels(pixmap);
		canvas->drawImage(bitmap.asImage(), 0, 0);

		// 不要忘记清理资源
		DeleteObject(hBmp);
		DeleteDC(hdcMemory);
		ReleaseDC(NULL, hdcScreen);
		DestroyIcon(icon);  // 不要忘记释放图标资源
	}


	
}
