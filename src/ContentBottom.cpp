#include "ContentBottom.h"

ContentBottom::ContentBottom(WindowMain *root) : ControlBase(root)
{
}

ContentBottom::~ContentBottom()
{
}

void ContentBottom::paint(SkCanvas *canvas)
{
	if (!needPaint(canvas))
		return;
}
