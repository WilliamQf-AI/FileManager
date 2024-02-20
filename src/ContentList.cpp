#include "ContentList.h"
#include "App.h"
#include "WindowMain.h"

ContentList::ContentList(WindowMain* root) :ControlBase(root)
{
	root->mouseMoveHandlers.push_back(
		std::bind(&ContentList::mouseMove, this, std::placeholders::_1, std::placeholders::_2)
	);
	root->mouseDownHandlers.push_back(
		std::bind(&ContentList::mouseDown, this, std::placeholders::_1, std::placeholders::_2)
	);
	root->mouseDragHandlers.push_back(
		std::bind(&ContentList::mouseDrag, this, std::placeholders::_1, std::placeholders::_2)
	);
	root->mouseUpHandlers.push_back(
		std::bind(&ContentList::mouseUp, this, std::placeholders::_1, std::placeholders::_2)
	);
	root->resizeHandlers.push_back(
		std::bind(&ContentList::resize, this, std::placeholders::_1, std::placeholders::_2)
	);
}

ContentList::~ContentList()
{
}

void ContentList::paint(SkCanvas* canvas)
{
}

void ContentList::mouseMove(const int& x, const int& y)
{
}

void ContentList::mouseDown(const int& x, const int& y)
{
}

void ContentList::mouseUp(const int& x, const int& y)
{
}

void ContentList::mouseDrag(const int& x, const int& y)
{
}

void ContentList::resize(const int& w, const int& h)
{
}
