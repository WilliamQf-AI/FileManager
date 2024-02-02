#include "SystemIcon.h"
#include <Windows.h>
#include <shellapi.h>
#include <shlobj.h>
#include "include/core/SkPixmap.h"
#include "include/core/SkBitmap.h"
#include <map>
#include <vector>

std::map<int, sk_sp<SkImage>> iconCache;

SystemIcon::SystemIcon()
{
}

SystemIcon::~SystemIcon()
{
}

sk_sp<SkImage> SystemIcon::getIcon(SHSTOCKICONID id)
{
	if (iconCache.contains(id)) {
		return iconCache[id];
	}
	SHSTOCKICONINFO sii = { sizeof(SHSTOCKICONINFO) };
	HRESULT hr = SHGetStockIconInfo(SIID_FOLDER, SHGSI_ICON | SHGSI_LARGEICON, &sii);
	if (FAILED(hr) || !sii.hIcon) {
		return nullptr;
	}
	HICON icon = sii.hIcon;
	auto size = 26;
	HDC hdcScreen = GetDC(NULL);
	HDC hdcMemory = CreateCompatibleDC(hdcScreen);
	auto hBmp = CreateCompatibleBitmap(hdcScreen, size, size);
	SelectObject(hdcMemory, hBmp);
	DrawIconEx(hdcMemory, 0, 0, icon, size, size, 0, NULL, DI_NORMAL);
	SkImageInfo imgInfo = SkImageInfo::MakeN32Premul(size, size);
	std::vector<int32_t> pixSrcData;
	pixSrcData.resize(size * size * 4);
	SkPixmap pixmap(imgInfo, &pixSrcData.front(), size * 4);
	BITMAPINFO info = { sizeof(BITMAPINFOHEADER), size, 0 - size, 1, 32, BI_RGB, size * 4 * size, 0, 0, 0, 0 };
	GetDIBits(hdcMemory, hBmp, 0, size, &pixSrcData.front(), &info, DIB_RGB_COLORS);
	DeleteObject(hBmp);
	DeleteDC(hdcScreen);
	DeleteDC(hdcMemory);
	ReleaseDC(NULL, hdcScreen);
	ReleaseDC(NULL, hdcMemory);
	DestroyIcon(icon);  // 不要忘记释放图标资源
	SkBitmap bitmap;
	bitmap.installPixels(pixmap);
	auto img = bitmap.asImage();
	iconCache.insert({id, img});
	return img;
}

void SystemIcon::reset()
{
	std::map<int, sk_sp<SkImage>>().swap(iconCache);
}
