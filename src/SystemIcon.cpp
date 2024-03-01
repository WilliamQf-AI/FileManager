#include "SystemIcon.h"
#include "include/core/SkPixmap.h"
#include "include/core/SkBitmap.h"
#include <map>
#include <vector>
#include <format>
#include <functional>

std::map<int, sk_sp<SkImage>> iconCache;
std::map<int, sk_sp<SkImage>> iconCache2;
std::map<size_t, int> pathMap;
std::map<std::wstring, std::wstring> knownPath;

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
	HRESULT hr = SHGetStockIconInfo(id, SHGSI_ICON | SHGSI_SMALLICON, &sii);
	if (FAILED(hr)) {
		return nullptr;
	}
	auto img = iconToImg(sii.hIcon);
	iconCache.insert({ id, img });
	return img;
}

sk_sp<SkImage> SystemIcon::getIcon(std::filesystem::path path)
{
	std::hash<std::wstring> wstr_hash;
	size_t id = wstr_hash(path.wstring());
	if (pathMap.contains(id)) {
		return iconCache2[pathMap[id]];
	}
	SHFILEINFO fileInfo = { 0 };
	auto hr = SHGetFileInfo(path.wstring().data(), 0, &fileInfo, sizeof(fileInfo), SHGFI_ICON | SHGSI_SMALLICON);	
	if (!hr) {
		return nullptr;
	}
	auto img = iconToImg(fileInfo.hIcon);
	iconCache2.insert({ fileInfo.iIcon, img });
	pathMap.insert({ id,fileInfo.iIcon });
	return img;
}
void SystemIcon::reset()
{
	std::map<int, sk_sp<SkImage>>().swap(iconCache);
}

sk_sp<SkImage> SystemIcon::iconToImg(HICON icon)
{
	auto size{ 24 };
	HDC hdcScreen = GetDC(NULL);
	HDC hdcMemory = CreateCompatibleDC(hdcScreen);
	auto hBmp = CreateCompatibleBitmap(hdcScreen, size, size);
	DeleteObject(SelectObject(hdcMemory, hBmp));
	DrawIconEx(hdcMemory, 0, 0, icon, size, size, 0, NULL, DI_NORMAL);
	std::vector<int32_t> pixSrcData;
	unsigned long dataSize = size * 4 * size;
	pixSrcData.resize(dataSize);
	BITMAPINFO info = { sizeof(BITMAPINFOHEADER), size, 0 - size, 1, 32, BI_RGB, dataSize, 0, 0, 0, 0 };
	GetDIBits(hdcMemory, hBmp, 0, size, &pixSrcData.front(), &info, DIB_RGB_COLORS);	
	DeleteDC(hdcScreen);
	DeleteDC(hdcMemory);
	ReleaseDC(NULL, hdcScreen);
	ReleaseDC(NULL, hdcMemory);
	DestroyIcon(icon);
	DeleteObject(hBmp);
	SkImageInfo imgInfo = SkImageInfo::MakeN32Premul(size, size);
	SkPixmap pixmap(imgInfo, &pixSrcData.front(), size * 4);
	SkBitmap bitmap;
	bitmap.installPixels(pixmap);
	auto img = bitmap.asImage();
	return img;
}

void SystemIcon::initKnownPath()
{
	if (knownPath.empty()) {
		return;
	}	
	std::vector<std::wstring> names{ L"桌面",L"音乐",L"视频",L"下载",L"图片",L"文档" };
	std::vector<GUID> ids{ FOLDERID_Desktop,FOLDERID_Music,FOLDERID_Videos,
						  FOLDERID_Downloads,FOLDERID_Pictures,FOLDERID_Documents };
	for (size_t i = 0; i < names.size(); i++)
	{
		PWSTR pszPath;
		HRESULT hr = SHGetKnownFolderPath(ids[i], 0, NULL, &pszPath);
		if (FAILED(hr)) {
			CoTaskMemFree(pszPath);
		}
		std::wstring pathStr(pszPath);
		CoTaskMemFree(pszPath);
		knownPath.insert({ names[i],pathStr });
	}
}
