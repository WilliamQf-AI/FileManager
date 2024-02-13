#pragma once
#include <include/core/SkRect.h>
#include <include/core/SkFont.h>
#include <include/core/SkCanvas.h>
#include <filesystem>
class WindowMain;

class ControlBase
{
public:
	ControlBase(WindowMain* root);
	~ControlBase();
	SkPoint getStartPosOfIconAtCenterOfRect(const char* text,SkRect& rect,SkFont* font);
	SkPoint getStartPosOfIconAtCenterOfRect(std::wstring& str,SkRect& rect, SkFont* font);
	float getTextVerticalVal(SkFont* font);
	std::wstring fileTimeToString(const std::filesystem::file_time_type& timePoint);
	virtual void paint(SkCanvas* canvas) = 0;
	SkRect rect;
	WindowMain* root;
private:

};
