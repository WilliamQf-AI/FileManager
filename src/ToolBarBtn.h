#pragma once
#include "ControlBase.h"

class ToolBarBtn :public ControlBase
{
public:
	ToolBarBtn(WindowMain* root);
	~ToolBarBtn();

private:
	void resize(const int& w, const int& h) override;
	void paint(SkCanvas* canvas) override;
	void mouseDown(const int& x, const int& y) override;
	std::vector<bool> enableFlag{true,true,true,true};
	std::vector<const char*> codes{ (const char*)u8"\ue80b", (const char*)u8"\ue80c" ,
	(const char*)u8"\ue80a" ,(const char*)u8"\ue741" };
};

