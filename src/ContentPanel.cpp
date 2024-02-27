#include "ContentPanel.h"
#include "WindowMain.h"
#include "App.h"
#include "TitleBar.h"
#include "TitleBarTab.h"
#include "ToolBar.h"
#include "LeftPanel.h"




ContentPanel::ContentPanel(WindowMain* root) :ControlBase(root)
{
	auto func = std::bind(&ContentPanel::tabChange, this, std::placeholders::_1);
	root->titleBar->tabChangeEvents.push_back(std::move(func));
}

ContentPanel::~ContentPanel()
{
}

void ContentPanel::paint(SkCanvas* canvas)
{
	if (!needPaint(canvas)) return;
	SkPaint paint;
	paint.setColor(0xFFE8E8E8);
	canvas->drawLine(rect.fLeft, rect.fTop, rect.fLeft, rect.fBottom, paint);
	auto it = std::find_if(root->titleBar->tabs.begin(), root->titleBar->tabs.end(), [](auto& item) {return item->isSelected; });
	auto tab = *it;
	if (!tab->path.empty()) {
		contentHeader->isDirty = true;
		contentList->isDirty = true;
		contentBottom->isDirty = true;
		return;
	}
	paint.setColor(0xFFFFFFFF);
	canvas->drawRect(rect, paint);
	paint.setColor(0xFFE8E8E8);
	canvas->drawLine(rect.fLeft, rect.fTop, rect.fLeft, rect.fBottom, paint);
	paint.setColor(0xFFD3E3FD);
	auto y = rect.centerY() - 58.f;
	canvas->drawLine(rect.fLeft + 110.f, y, rect.centerX() - 140.f, y, paint);
	canvas->drawLine(rect.centerX() + 140.f, y, rect.fRight - 110.f, y, paint);
	auto fontText = App::GetFontText();
	fontText->setSize(18.f);
	std::wstring str = L"FileManager 文件管理器";
	auto textLength = wcslen(str.data()) * 2;
	paint.setColor(0xFFC0D0EA);
	canvas->drawSimpleText(str.data(), textLength, SkTextEncoding::kUTF16, rect.centerX() - 102.f, y + 8.f, *fontText, paint);

}

void ContentPanel::resize(const int& w, const int& h)
{
	if (!isDirty) {
		isDirty = true;
		auto it = std::find_if(root->titleBar->tabs.begin(), root->titleBar->tabs.end(), [](auto& item) {return item->isSelected; });
		auto tab = *it;
		if (contentHeader && !tab->path.empty()) {
			contentHeader->isDirty = true;
			contentList->isDirty = true;
			contentBottom->isDirty = true;
		}
	}
	rect.setLTRB(380.f, 116.f, w, h);

	//recent files 
	//C:\Users\liuxiaolun\AppData\Roaming\Microsoft\Windows\Recent
}

void ContentPanel::tabChange(TitleBarTab* tab)
{
	isDirty = true;
	if (contentHeader) {
		contentHeader->isDirty = true;
		contentBottom->isDirty = true;
		contentList->isDirty = true;
	}
	else
	{
		contentHeader = std::make_shared<ContentHeader>(root);
		contentBottom = std::make_shared<ContentBottom>(root);
		contentList = std::make_shared<ContentList>(root);
	}
	contentHeader->resize(root->w, root->h);
	contentBottom->resize(root->w, root->h);
	contentList->resize(root->w, root->h);
}
