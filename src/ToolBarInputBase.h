#pragma once
#include "ControlBase.h"
#include "Windows.h"

class WindowMain;
class ToolBarInputBase :public ControlBase
{
public:
	ToolBarInputBase(WindowMain* root);
	~ToolBarInputBase();
	void paint(SkCanvas* canvas) override;
	virtual void paint2(SkCanvas* canvas) = 0;
	void mouseDown(const int& x, const int& y) override;
	bool isFocus{ false };
protected:
	float paddingLeft{ 0.f };
	float paddingRight{ 0.f };
	int hoverIndexVal{ -1 };
	int timerID{ 0 };
private:
	void timeout(const unsigned int& id);
	bool showTextCursor{ false };
	void setImm(const int& x, const int& y);
	std::chrono::system_clock::time_point mouseDownTime;
};