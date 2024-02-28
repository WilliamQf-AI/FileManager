#include "SystemIcon.h"
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

sk_sp<SkImage> SystemIcon::getIcon(SHSTOCKICONID id, const int& size)
{
	SHSTOCKICONINFO sii = { sizeof(SHSTOCKICONINFO) };
	HRESULT hr = SHGetStockIconInfo(SIID_FOLDER, SHGSI_ICON | SHGSI_LARGEICON, &sii);
	if (FAILED(hr)) {
		return nullptr;
	}
	return getIcon(sii.iIcon,sii.hIcon,size);
}

sk_sp<SkImage> SystemIcon::getIcon(std::wstring path, const int& size)
{
	SHFILEINFO fileInfo = { 0 };
	auto hr = SHGetFileInfo(path.data(), 0, &fileInfo, sizeof(fileInfo), SHGFI_ICON | SHGFI_SMALLICON);
	if (!hr) {
		return nullptr;
	}
	return getIcon(fileInfo.iIcon,fileInfo.hIcon, size);
}

sk_sp<SkImage> SystemIcon::getIcon(const int& index, const HICON icon, const int& size)
{
	if (iconCache.contains(index)) {
		return iconCache[index];
	}
	auto img = iconToImg(icon, size);
	iconCache.insert({ index, img });
	return img;
}



void SystemIcon::reset()
{
	std::map<int, sk_sp<SkImage>>().swap(iconCache);
}

sk_sp<SkImage> SystemIcon::iconToImg(HICON icon, const int& size)
{
	HDC hdcScreen = GetDC(NULL);
	HDC hdcMemory = CreateCompatibleDC(hdcScreen);
	auto hBmp = CreateCompatibleBitmap(hdcScreen, size, size);
	SelectObject(hdcMemory, hBmp);
	DrawIconEx(hdcMemory, 0, 0, icon, size, size, 0, NULL, DI_NORMAL);
	SkImageInfo imgInfo = SkImageInfo::MakeN32Premul(size, size);
	std::vector<int32_t> pixSrcData;
	unsigned long dataSize = size * 4 * size;
	pixSrcData.resize(dataSize);
	SkPixmap pixmap(imgInfo, &pixSrcData.front(), size * 4);
	BITMAPINFO info = { sizeof(BITMAPINFOHEADER), size, 0 - size, 1, 32, BI_RGB, dataSize, 0, 0, 0, 0 };
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
	return img;
}
