#include "SearchInput.h"
#include "WindowMain.h"

SearchInput::SearchInput(WindowMain* root) : ControlBase(root)
{
	root->resizeHandlers.push_back(
		std::bind(&SearchInput::resize, this, std::placeholders::_1, std::placeholders::_2)
	);
}

SearchInput::~SearchInput()
{
}

void SearchInput::resize(const int& w, const int& h)
{
}
