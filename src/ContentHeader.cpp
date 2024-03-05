#include "ContentHeader.h"
#include <string>
#include "App.h"
#include "WindowMain.h"
#include "ContentPanel.h"
#include "TitleBar.h"
#include "TitleBarTab.h"

ContentHeader::ContentHeader(WindowMain* root) :ControlBase(root)
{
	auto func = std::bind(&ContentHeader::tabChange, this, std::placeholders::_1, std::placeholders::_2);
	root->titleBar->tabChangeEvents.push_back(std::move(func));
}

ContentHeader::~ContentHeader()
{
}

void ContentHeader::paint(SkCanvas* canvas)
{
	if (!needPaint(canvas)) return;
	SkPaint paint;
	paint.setColor(0xFFE8E8E8);
	canvas->drawLine(rect.fLeft, rect.fBottom, rect.fRight, rect.fBottom, paint);
	auto fontText = App::GetFontText();
	fontText->setSize(16.8);
	auto font = App::GetFontIcon();
	font->setSize(24.f);
	paint.setAntiAlias(false);
	canvas->save();
	canvas->clipRect(rect);
	for (size_t i = 0; i < columns.size(); i++)
	{
		paint.setColor(0xFF888888);
		auto len = wcslen(columns[i].title.data()) * 2;
		canvas->drawSimpleText(columns[i].title.data(), len, SkTextEncoding::kUTF16,
			scrollerLeft + columns[i].left + padding, rect.fTop + 29.f, *fontText, paint);
		paint.setColor(0xFFE8E8E8);
		if (i != 0) {
			canvas->drawLine(scrollerLeft + columns[i].left, rect.fTop, scrollerLeft + columns[i].left, rect.fBottom, paint);
		}
		if (columns[i].right - padding - 60.f > columns[i].left) {
			paint.setColor(0xFFBBBBBB);
			auto icon = columns[i].isSort ? (const char*)u8"\ue606" : (const char*)u8"\ue60f";
			canvas->drawString(icon, scrollerLeft + columns[i].right - padding-18.f, rect.fTop + 32.f, *font, paint);
		}
	}
	canvas->restore();
}

void ContentHeader::mouseMove(const int& x, const int& y)
{
	int index{ -1 };
	if (rect.contains(x, y)) {
		for (size_t i = 0; i < columns.size()-1; i++)
		{
			if (x<columns[i].right + 6 && x>columns[i].right - 6) {
				index = i;
				break;
			}
		}
	}
	if (index != hoverIndex) {		
		if (index > -1) {
			SetCursor(LoadCursor(nullptr, IDC_SIZEWE));
		}
		else {
			SetCursor(LoadCursor(nullptr, IDC_ARROW));
		}
		hoverIndex = index;
	}
}

void ContentHeader::mouseDown(const int& x, const int& y)
{
	if (hoverIndex < 0) {
		return;
	}
	SetCapture(root->hwnd);
	mouseDownX = x;
}

void ContentHeader::mouseUp(const int& x, const int& y)
{
	ReleaseCapture();
}

void ContentHeader::mouseDrag(const int& x, const int& y)
{
	if (hoverIndex < 0) {
		return;
	}
	float span = x - mouseDownX;	
	if (span < 0) {
		auto remain = columns[hoverIndex].right - columns[hoverIndex].left- columns[hoverIndex].minWidth;
		if (remain <=0) {
			return;
		}
		span = 0-std::min(remain, 0-span);
		columns[hoverIndex].right += span;
	}
	else {
		columns[hoverIndex].right += span;
	}
	for (size_t i = hoverIndex + 1; i < columns.size(); i++)
	{
		columns[i].right += span;
		columns[i].left += span;
	}
	isDirty = true;
	root->contentPanel->contentList->isDirty = true;
	InvalidateRect(root->hwnd, nullptr, false);
	mouseDownX = x;
	return;
	
}

void ContentHeader::resize(const int& w, const int& h)
{
	rect.setXYWH(root->contentPanel->rect.fLeft + 1,
		root->contentPanel->rect.fTop,
		root->contentPanel->rect.width(),
		46.f);
	if (columns.size() > 0) {
		columns[3].right = rect.fRight;
	}
}

void ContentHeader::tabChange(TitleBarTab* tab, TitleBarTab* tabNew)
{
	//columns.push_back(FileColumnHeader(L"最近使用的文件", false));
	//columns.push_back(FileColumnHeader(L"使用时间", true));
	columns.clear();
	columns.push_back(FileColumnHeader(L"名称", false,380.f));
	columns.push_back(FileColumnHeader(L"修改日期", true,238.f));
	columns.push_back(FileColumnHeader(L"大小", false,200.f));
	columns.push_back(FileColumnHeader(L"类型", false,280.f));
	columns[0].left = rect.fLeft;
	columns[0].right = rect.fLeft + 460.f;
	columns[1].left = columns[0].right;
	columns[1].right = columns[1].left + 260.f;
	columns[2].left = columns[1].right;
	columns[2].right = columns[2].left + 200.f;
	columns[3].left = columns[2].right;
	if (rect.fRight < columns[3].left) {
		columns[3].right = columns[3].left +280.f;
		totalWidth = 460.f + 260.f + 200.f + 280.f;
	}
	else {
		columns[3].right = rect.fRight;
	}	
}
