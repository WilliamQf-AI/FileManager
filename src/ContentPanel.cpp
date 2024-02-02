#include "TitleBar.h"
#include "WindowMain.h"

ContentPanel::ContentPanel(WindowBase* root) :ControlBase(root)
{
	YGNodeStyleSetFlexGrow(layout, 1.f);
	YGNodeStyleSetHeightAuto(layout);
}

ContentPanel::~ContentPanel()
{
}

void ContentPanel::paint(SkCanvas* canvas)
{
}
