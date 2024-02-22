#pragma once
#include "ControlBase.h"
#include "include/core/SkCanvas.h"

class WindowMain;
class FavoritePath : public ControlBase
{
public:
	FavoritePath(WindowMain* root);
	~FavoritePath();
	float y;
private:
	void paint(SkCanvas* canvas) override;
	void mouseMove(const int& x, const int& y) override;
	void mouseDown(const int& x, const int& y) override;
	void mouseUp(const int& x, const int& y) override;
	void mouseDrag(const int& x, const int& y) override;
	void mouseWheel(const int& x, const int& y, const int& delta) override;
	void resize(const int& w, const int& h) override;
	float totalHeight{0};
	SkRect scrollerRect;
	bool hoverScroller{ false };
	double top{ 0.f };
	double downY{ 0.f };
};