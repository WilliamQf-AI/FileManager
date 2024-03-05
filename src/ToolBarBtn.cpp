#include "ToolBarBtn.h"
#include "WindowMain.h"
#include "ToolBar.h"
#include "App.h"
#include "TitleBar.h"

ToolBarBtn::ToolBarBtn(WindowMain* root) : ControlBase(root)
{
}

ToolBarBtn::~ToolBarBtn()
{
}

void ToolBarBtn::resize(const int& w, const int& h)
{
	isDirty = true;
	auto top = root->toolBar->rect.fTop;
	rect.setXYWH(0.f, top, 200.f, 59.f);
}

void ToolBarBtn::paint(SkCanvas* canvas)
{
	if (!needPaint(canvas)) return;
	SkPaint paint;
	float start{ 16.f };
	float top{ rect.fTop + 41.f };
	auto font = App::GetFontIcon();
	font->setSize(26.f);
	for (size_t i = 0; i < codes.size(); i++)
	{
		if (root->toolBar->hoverIndex == i && enableFlag[i]) {
			paint.setColor(0x18000000);  //0xFFA8C7FA
			auto r = SkRect::MakeXYWH(11.f + root->toolBar->hoverIndex * 50.f, rect.fTop + 16.f, 34.f, 30.f);
			canvas->drawRoundRect(r, 6.f, 6.f, paint);
			paint.setColor(0xFF222222);
		}
		else if(!enableFlag[i]) {
			paint.setColor(0xFFDDDDDD);
		}
		else {
			paint.setColor(0xFF888888);
		}
		canvas->drawString(codes[i], start+i*50.f, top, *font, paint);
	}
}

void ToolBarBtn::mouseDown(const int& x, const int& y)
{
	if (root->toolBar->hoverIndex >= 0) {
		auto tab = root->titleBar->tabs[root->titleBar->selectedTabIndex].get();
		switch (root->toolBar->hoverIndex)
		{
		case 0: {

		}
		case 1:{

			  }
		case 2: {

		}
		case 3: {

		}
		default:
			break;
		}
	}
}
