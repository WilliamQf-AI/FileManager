#include "ContentBottom.h"
#include "WindowMain.h"
#include "ContentPanel.h"

ContentBottom::ContentBottom(WindowMain *root) : ControlBase(root)
{
	root->resizeHandlers.push_back(
		std::bind(&ContentBottom::resize, this, std::placeholders::_1, std::placeholders::_2)
	);
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
