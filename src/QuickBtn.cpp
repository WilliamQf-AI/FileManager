#include "QuickBtn.h"
#include <Windows.h>
#include "SystemIcon.h"
#include "App.h"
#include <include/core/SkPaint.h>
#include "WindowBase.h"

QuickBtn::QuickBtn(WindowBase* root) :ControlBase(root)
{
	root->resizeHandlers.push_back(
		std::bind(&QuickBtn::resize, this, std::placeholders::_1, std::placeholders::_2)
	);
}

QuickBtn::~QuickBtn()
{
}

void QuickBtn::paint(SkCanvas* canvas)
{
	std::vector<std::wstring> names{ L"◊¿√Ê",L"“Ù¿÷",L" ”∆µ",L"œ¬‘ÿ",L"Õº∆¨",L"Œƒµµ" };
	std::vector<GUID> ids{ FOLDERID_Desktop,FOLDERID_Music,FOLDERID_Videos,
						  FOLDERID_Downloads,FOLDERID_Pictures,FOLDERID_Documents };
	SkPaint paint;
	for (size_t i = 0; i < 6; i++)
	{
		auto img = SystemIcon::getIcon(ids[i], 24);
		canvas->drawImage(img, 10.f + 60 * i + 16.f, rect.fTop+16.f+12.f);
		auto textLength = wcslen(names[i].data()) * 2;
		auto fontText = App::GetFontText();
		fontText->setSize(16.f);
		paint.setColor(0xFF666666);
		canvas->drawSimpleText(names[i].data(), textLength, 
			SkTextEncoding::kUTF16, 
			10.f + 60 * i + 12.f, rect.fTop + 16.f + 62.f, *fontText, paint);
	}
}

void QuickBtn::resize(const int& w, const int& h)
{
	auto yVal = root->ctrls[2]->rect.fTop;
	rect.setXYWH(0.f, yVal, 380.f, 92.f);
}
