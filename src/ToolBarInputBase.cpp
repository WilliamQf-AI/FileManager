#include "ToolBarInputBase.h"
#include "WindowMain.h"
#include "App.h"
#include "ToolBar.h"
#include "TitleBar.h"

ToolBarInputBase::ToolBarInputBase(WindowMain* root) : ControlBase(root)
{
}

ToolBarInputBase::~ToolBarInputBase()
{
}


void ToolBarInputBase::paint(SkCanvas* canvas)
{
	if (!needPaint(canvas)) return;
	SkPaint paint;
	if (isFocus) {
		paint.setAntiAlias(true);
		paint.setStroke(true);
		paint.setStrokeWidth(1.5f);
		paint.setColor(0xFF0B57D0);
		canvas->drawRoundRect(rect.makeInset(1.5f, 1.5f), 6.f, 6.f, paint);
		if (showTextCursor) {
			canvas->drawLine(textCursorPos, rect.fTop + 8.f,textCursorPos, rect.fBottom - 8.f, paint);
		}
	}
	else {
		if (root->toolBar->hoverIndex == hoverIndexVal) {
			paint.setColor(0xFFE0E3EA);
		}
		else {
			paint.setColor(0xFFECEFF7);
		}		
		canvas->drawRoundRect(rect, 6.f, 6.f, paint);
	}
	paint2(canvas);
}

void ToolBarInputBase::mouseDown(const int& x, const int& y)
{
	bool flag{ false };
	if (root->toolBar->hoverIndex == hoverIndexVal) {
		auto span = std::chrono::system_clock::now() - mouseDownTime;
		auto msCount = std::chrono::duration_cast<std::chrono::milliseconds>(span).count();
		if (msCount < 380) {
			//todo
			return;
		}
		mouseDownTime = std::chrono::system_clock::now();
		flag = true;
	}
	else {
		flag = false;
	}
	if (flag != isFocus) {
		isFocus = flag;
		showTextCursor = true;
		if (isFocus) {
			SetTimer(root->hwnd, timerID, 600, (TIMERPROC)nullptr);
			setImm(x, y);
		}
		else {
			KillTimer(root->hwnd, timerID);
			repaint();
		}
	}
	if (isFocus) {
		setTextCursorPos(x);
		repaint();
	}
}

void ToolBarInputBase::timeout(const unsigned int& id)
{
	showTextCursor = !showTextCursor;
	repaint();
}

void ToolBarInputBase::setImm(const int& x, const int& y)
{
	if (HIMC himc = ImmGetContext(root->hwnd))
	{
		COMPOSITIONFORM comp = {};
		comp.ptCurrentPos.x = x;
		comp.ptCurrentPos.y = y;
		comp.dwStyle = CFS_FORCE_POSITION;
		ImmSetCompositionWindow(himc, &comp);
		CANDIDATEFORM cand = {};
		cand.dwStyle = CFS_CANDIDATEPOS;
		cand.ptCurrentPos.x = x;
		cand.ptCurrentPos.y = y;
		ImmSetCandidateWindow(himc, &cand);
		ImmReleaseContext(root->hwnd, himc);
	}
}

void ToolBarInputBase::setTextCursorPos(const int& x)
{
	SkRect r;
	auto font = App::GetFontText();
	font->setSize(16.f);
	auto length = wcslen(address.data()) * 2;
	font->measureText(address.data(), length, SkTextEncoding::kUTF16, &r);
	auto temp = rect.fLeft + paddingLeft + r.fLeft + r.width();
	if (x > temp) {
		textCursorPos = temp;
	}
	else {
		textCursorPos = rect.fLeft + paddingLeft;
	}

	//for (size_t i = 0; i < lines[lineIndex].length() + 1; i++)
	//{
	//	auto str = lines[lineIndex].substr(0, i);
	//	auto data = str.data();
	//	auto length = wcslen(data) * 2;
	//	font->measureText(data, length, SkTextEncoding::kUTF16, &Rect);
	//	if (Rect.right() > width) {
	//		float half = (Rect.right() - right) / 2 + right;
	//		if (half > width) {
	//			wordIndex = i - 1;
	//		}
	//		else
	//		{
	//			wordIndex = i;
	//		}
	//		flag = true;
	//		break;
	//	}
	//	right = Rect.right();
	//}
	//return 0.0f;
}
