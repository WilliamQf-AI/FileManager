#include "ContentHeader.h"
#include <string>
#include "App.h"
#include "WindowMain.h"
#include "ContentPanel.h"

ContentHeader::ContentHeader(WindowMain* root) :ControlBase(root)
{
	columns.push_back(FileColumnHeader(L"最近使用的文件", false));
	columns.push_back(FileColumnHeader(L"使用时间", true));
	root->mouseMoveHandlers.push_back(
		std::bind(&ContentHeader::mouseMove, this, std::placeholders::_1, std::placeholders::_2)
	);
	root->mouseDownHandlers.push_back(
		std::bind(&ContentHeader::mouseDown, this, std::placeholders::_1, std::placeholders::_2)
	);
	root->mouseDragHandlers.push_back(
		std::bind(&ContentHeader::mouseDrag, this, std::placeholders::_1, std::placeholders::_2)
	);
	root->mouseUpHandlers.push_back(
		std::bind(&ContentHeader::mouseUp, this, std::placeholders::_1, std::placeholders::_2)
	);
	root->resizeHandlers.push_back(
		std::bind(&ContentHeader::resize, this, std::placeholders::_1, std::placeholders::_2)
	);
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
	for (size_t i = 0; i < columns.size(); i++)
	{
		paint.setColor(0xFF888888);
		auto len = wcslen(columns[i].title.data()) * 2;
		canvas->drawSimpleText(columns[i].title.data(), len, SkTextEncoding::kUTF16,
			columns[i].left + paddingLeft, rect.fTop + 29.f, *fontText, paint);
		paint.setColor(0xFFE8E8E8);
		if (i != 0) {
			canvas->drawLine(columns[i].left, rect.fTop, columns[i].left, rect.fBottom, paint);
		}		
		paint.setColor(0xFFBBBBBB);
		auto icon = columns[i].isSort ? (const char*)u8"\ue606":(const char*)u8"\ue60f";
		canvas->drawString(icon, columns[i].right - paddingRight, rect.fTop + 32.f, *font, paint);
	}
}

void ContentHeader::mouseMove(const int& x, const int& y)
{
}

void ContentHeader::mouseDown(const int& x, const int& y)
{
}

void ContentHeader::mouseUp(const int& x, const int& y)
{
}

void ContentHeader::mouseDrag(const int& x, const int& y)
{
}

void ContentHeader::resize(const int& w, const int& h)
{
	rect.setXYWH(root->contentPanel->rect.fLeft + 1,
		root->contentPanel->rect.fTop,
		root->contentPanel->rect.width(),
		46.f);
	columns[0].left = rect.fLeft;
	columns[0].right = rect.fLeft + 460.f;
	columns[1].left = columns[0].right;
	columns[1].right = rect.fRight;
}
