#pragma once
#include <yoga/Yoga.h>
#include <include/core/SkRect.h>
#include <include/core/SkFont.h>
class WindowBase;

class ControlBase
{
public:
	ControlBase(WindowBase* root);
	~ControlBase();
	SkRect getRect();
	SkRect getRect(YGNodeRef target);
	SkPoint getStartPosOfIconAtCenterOfRect(const char* text,SkRect& rect,SkFont* font);
	SkPoint getStartPosOfIconAtCenterOfRect(std::wstring& str,SkRect& rect, SkFont* font);
	YGNodeRef layout;
	WindowBase* root;
private:

};
