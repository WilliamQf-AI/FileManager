#include "ContentPanel.h"

#include "WindowMain.h"
#include "App.h"
#include "TitleBar.h"
#include "ToolBar.h"
#include "LeftPanel.h"



ContentPanel::ContentPanel(WindowMain* root) :ControlBase(root)
{
	root->resizeHandlers.push_back(
		std::bind(&ContentPanel::resize, this, std::placeholders::_1, std::placeholders::_2)
	);
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

void ContentPanel::resize(const int& w, const int& h)
{
	isDirty = true;
	contentHeader->isDirty = true;
	contentList->isDirty = true;
	contentBottom->isDirty = true;

	auto topVal = root->titleBar->rect.height() + root->toolBar->rect.height();
	auto leftVal = root->leftPanel->rect.fRight;
	rect.setLTRB(leftVal, topVal, w, h);

	//recent files 
	//C:\Users\liuxiaolun\AppData\Roaming\Microsoft\Windows\Recent
}
