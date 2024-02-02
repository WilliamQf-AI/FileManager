#pragma once
#include <yoga/Yoga.h>
#include <include/core/SkRect.h>

class WindowBase;

class ControlBase
{
public:
	ControlBase(WindowBase* root);
	~ControlBase();
	SkRect getRect();
	YGNodeRef layout;
	WindowBase* root;
private:

};
