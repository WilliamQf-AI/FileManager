#include "SystemIcon.h"
#include "include/core/SkPixmap.h"
#include "include/core/SkBitmap.h"
#include <map>
#include <vector>
#include <format>
#include <functional>

std::map<int, sk_sp<SkImage>> iconCache;
std::map<int, sk_sp<SkImage>> iconCache2;
std::map<std::wstring, sk_sp<SkImage>> iconCache3;
std::map<size_t, int> pathMap;

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
	HRESULT hr = SHGetStockIconInfo(id, SHGSI_ICON | SHGSI_LARGEICON, &sii);
	if (FAILED(hr)) {
		return nullptr;
	}
	auto img = iconToImg(sii.hIcon, size);
	iconCache.insert({ id, img });
	return img;
}

sk_sp<SkImage> SystemIcon::getIcon(GUID& id, const std::wstring& key, const int& size)
{
	if (iconCache3.contains(key)) {
		return iconCache3[key];
	}
	PWSTR pszPath;
	HRESULT hr = SHGetKnownFolderPath(id, 0, NULL, &pszPath);
	if (FAILED(hr)) {
		CoTaskMemFree(pszPath);
		return nullptr;
	}
	std::wstring pathStr(pszPath);
	CoTaskMemFree(pszPath);
	SHFILEINFO fileInfo = { 0 };
	auto gr = SHGetFileInfo(pathStr.data(), 0, &fileInfo, sizeof(fileInfo), SHGFI_ICON | SHGFI_SMALLICON);
	if (!gr) {
		return nullptr;
	}
	auto img = iconToImg(fileInfo.hIcon, size);
	iconCache3.insert({ key, img });
	return img;
}

sk_sp<SkImage> SystemIcon::getIcon(std::filesystem::path path, const int& size)
{
	if (std::filesystem::is_directory(path)) {
		return getIcon(SIID_FOLDER, size);
	}

	std::hash<std::wstring> wstr_hash;
	size_t id = wstr_hash(path.wstring());
	if (pathMap.contains(id)) {
		return iconCache2[pathMap[id]];
	}
	SHFILEINFO fileInfo = { 0 };
	//auto hr = SHGetFileInfo(path.wstring().data(), 0, &fileInfo, sizeof(fileInfo), SHGFI_SYSICONINDEX);
	//if (!hr) {
	//	return nullptr;
	//}
	//if (iconCache2.contains(fileInfo.iIcon)) {
	//	return iconCache2[fileInfo.iIcon];
	//}
	auto hr = SHGetFileInfo(path.wstring().data(), 0, &fileInfo, sizeof(fileInfo), SHGFI_ICON | SHGFI_SMALLICON);
	if (!hr) {
		return nullptr;
	}
	auto img = iconToImg(fileInfo.hIcon, size);
	iconCache2.insert({ fileInfo.iIcon, img });
	pathMap.insert({ id,fileInfo.iIcon });
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
