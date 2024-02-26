#include "ContentPanel.h"

#include "WindowMain.h"
#include "App.h"
#include "TitleBar.h"
#include "ToolBar.h"
#include "LeftPanel.h"



ContentPanel::ContentPanel(WindowMain* root) :ControlBase(root)
{
	contentHeader = std::make_shared<ContentHeader>(root);
	contentBottom = std::make_shared<ContentBottom>(root);
	contentList = std::make_shared<ContentList>(root);
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
}

void ContentPanel::initResize(const int& w, const int& h)
{
	isDirty = true;
	resize(w, h);
	contentHeader->resize(w, h);
	contentBottom->resize(w, h);
	contentList->resize(w, h);
}

void ContentPanel::resize(const int& w, const int& h)
{
	isDirty = true;
	contentHeader->isDirty = true;
	contentList->isDirty = true;
	contentBottom->isDirty = true;
	rect.setLTRB(root->leftPanel->rect.fRight, root->toolBar->rect.fBottom, w, h);

	//recent files 
	//C:\Users\liuxiaolun\AppData\Roaming\Microsoft\Windows\Recent
}
