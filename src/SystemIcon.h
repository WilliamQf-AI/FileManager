#include <include/core/SkImage.h>
#include <Windows.h>

class SystemIcon
{
public:
	SystemIcon();
	~SystemIcon();
	static sk_sp<SkImage> getIcon(SHSTOCKICONID id);
	static void reset();
private:
	
};