#pragma once
#include <Windows.h>
#include "include/core/SkFont.h"
class App
{
public:
    ~App();
    static bool init(HINSTANCE hins);
    static HINSTANCE getInstance();
    static void removeWindow(HWND hwnd);
    static void Dispose();
    static void Quit(const int& code);
    static std::shared_ptr<SkFont> GetFontIcon();
    static std::shared_ptr<SkFont> GetFontText();
    static void Log(std::string&& info);
private:
    App() {};
    static void initFontIcon();
};