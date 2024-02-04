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
	if (iconCache.contains(id)) {
		return iconCache[id];
	}
	SHSTOCKICONINFO sii = { sizeof(SHSTOCKICONINFO) };
	HRESULT hr = SHGetStockIconInfo(SIID_FOLDER, SHGSI_ICON | SHGSI_LARGEICON, &sii);
	if (FAILED(hr) || !sii.hIcon) {
		return nullptr;
	}
	auto img = iconToImg(sii.hIcon,size);
	iconCache.insert({id, img});
	return img;
}

sk_sp<SkImage> SystemIcon::getIcon(KNOWNFOLDERID id, const int& size)
{
	PWSTR pszPath;
	HRESULT hr = SHGetKnownFolderPath(id, 0, NULL, &pszPath);
	if (FAILED(hr)) {
		return nullptr;
	}
	SHFILEINFO sfi{ 0 };
	SHGetFileInfo(pszPath, 0, &sfi, sizeof(SHFILEINFO),  SHGFI_ICON | SHGFI_SMALLICON);
	if (!sfi.hIcon) {
		return nullptr;
	}
	auto img = iconToImg(sfi.hIcon, size);
	return img;
}

sk_sp<SkImage> SystemIcon::getIcon(std::wstring path, const int& size)
{
	SHFILEINFO sfi;
	ZeroMemory(&sfi, sizeof(SHFILEINFO));
	HICON hIcon = NULL;
	if (SHGetFileInfo(path.data(), 0, &sfi, sizeof(SHFILEINFO), SHGFI_ICON | SHGFI_SMALLICON))
	{
		hIcon = sfi.hIcon;
	}
	auto img = iconToImg(sfi.hIcon, size);
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
	return img;
}
