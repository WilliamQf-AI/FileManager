#include "Home.h"
#include "WindowMain.h"

Home::Home(WindowMain* root) :ControlBase(root)
{
	root->resizeHandlers.push_back(
		std::bind(&Home::resize, this, std::placeholders::_1, std::placeholders::_2)
	);
}

Home::~Home()
{
}

void Home::paint(SkCanvas* canvas)
{
}

void Home::resize(const int& w, const int& h)
{
}
