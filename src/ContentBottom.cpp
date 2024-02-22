#include "ContentBottom.h"
#include "WindowMain.h"
#include "ContentPanel.h"

ContentBottom::ContentBottom(WindowMain *root) : ControlBase(root)
{
}

ContentBottom::~ContentBottom()
{
}

void ContentBottom::paint(SkCanvas *canvas)
{
	if (!needPaint(canvas)) return;
}

void ContentBottom::resize(const int& w, const int& h)
{
	rect.setLTRB(root->contentPanel->rect.fLeft+1,
		root->contentPanel->rect.fBottom - 42.f,
		root->contentPanel->rect.fRight,
		root->contentPanel->rect.fBottom
	);
}
