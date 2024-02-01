#include "App.h"
#include "../res/res.h"
#include "include/core/SkFont.h"
#include "include/core//SkFontMgr.h"
#include "include/core/SkFontStyle.h"
#include "include/core/SkData.h"
#include "include/core/SkGraphics.h"
#include "include/ports/SkTypeface_win.h"
#include "WindowBase.h"
#include "WindowMain.h"


HINSTANCE hinstance;
std::shared_ptr<SkFont> fontIcon{ nullptr };
std::shared_ptr<SkFont> fontText{ nullptr };
std::vector<std::shared_ptr<WindowBase>> windows;
sk_sp<SkFontMgr> fontMgr;

App::~App()
{
}

bool App::Init(HINSTANCE hins)
{
    hinstance = hins;
    SkGraphics::Init();
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (FAILED(hr))
    {
        MessageBox(NULL, L"Failed to initialize COM library.", L"Error", MB_OK | MB_ICONERROR);
        return false;
    }
    fontMgr = SkFontMgr_New_GDI();
    initFontText();
    initFontIcon();
    auto win = std::make_shared<WindowMain>();
    win->show();
    windows.push_back(std::move(win));
    return true;
}

void App::Dispose()
{
    CoUninitialize();
}

std::shared_ptr<SkFont> App::GetFontIcon()
{
	return fontIcon;
}

std::shared_ptr<SkFont> App::GetFontText()
{
	return fontText;
}



void App::Quit(const int& code) {
    PostQuitMessage(0);
}

void App::initFontIcon()
{
    HMODULE instance = GetModuleHandle(NULL);
    HRSRC resID = FindResource(instance, MAKEINTRESOURCE(IDR_ICON_FONT), L"ICON_FONT");
    if (resID == 0)
    {
        MessageBox(NULL, L"查找字体图标资源失败", L"系统提示", NULL);
        return;
    }
    size_t resSize = SizeofResource(instance, resID);
    HGLOBAL res = LoadResource(instance, resID);
    if (res == 0)
    {
        MessageBox(NULL, L"加载字体图标资源失败", L"系统提示", NULL);
        return;
    }
    LPVOID resData = LockResource(res);
    auto fontData = SkData::MakeWithoutCopy(resData, resSize);
    fontIcon = std::make_shared<SkFont>(fontMgr->makeFromData(fontData));
}

void App::initFontText()
{
    fontText = std::make_shared<SkFont>(fontMgr->matchFamilyStyle("Microsoft YaHei", {}));
}

void App::Log(std::string&& info) {
    SkDebugf(info.data());
}