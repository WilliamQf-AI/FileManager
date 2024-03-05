#include "ToolBarInputBase.h"
#include "WindowMain.h"
#include "App.h"
#include "ToolBar.h"
#include "TitleBar.h"

ToolBarInputBase::ToolBarInputBase(WindowMain* root) : ControlBase(root)
{
}

ToolBarInputBase::~ToolBarInputBase()
{
}


void ToolBarInputBase::paint(SkCanvas* canvas)
{
	if (!needPaint(canvas)) return;
	SkPaint paint;
	if (isFocus) {
		paint.setAntiAlias(true);
		paint.setStroke(true);
		paint.setStrokeWidth(1.5f);
		paint.setColor(0xFF0B57D0);
		canvas->drawRoundRect(rect.makeInset(1.5f, 1.5f), 6.f, 6.f, paint);
	}
	else {
		if (root->toolBar->hoverIndex == 4 || root->toolBar->hoverIndex == 5) {
			paint.setColor(0xFFE0E3EA);
		}
		else {
			paint.setColor(0xFFECEFF7);
		}		
		canvas->drawRoundRect(rect, 6.f, 6.f, paint);
	}
	paint2(canvas);
}

void ToolBarInputBase::mouseDown(const int& x, const int& y)
{
	bool flag{ false };
	if (rect.contains(x, y)) {
		flag = true;
	}
	else {
		flag = false;
	}
	if (flag != isFocus) {
		isFocus = flag;
		repaint();
	}
}
