#include <include/core/SkImage.h>
#include <Windows.h>
#include <shellapi.h>
#include <shlobj.h>
#include <string>
#include <filesystem>

class SystemIcon
{
public:
	SystemIcon();
	~SystemIcon();
	static sk_sp<SkImage> getIcon(SHSTOCKICONID id);
	static sk_sp<SkImage> getIcon(std::filesystem::path path);
	static void reset();
private:
	static sk_sp<SkImage> iconToImg(HICON icon);
	static void initKnownPath();
};