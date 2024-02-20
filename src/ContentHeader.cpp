#include "ContentHeader.h"

#include "App.h"
#include "WindowMain.h"
#include "ContentPanel.h"

ContentHeader::ContentHeader(WindowMain* root) :ControlBase(root)
{
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
	font->setSize(23.f);
	paint.setAntiAlias(false);
	auto iconCode = (const char*)u8"\ue67d";

	auto paddingLeft{ 18.f };
	auto paddingRight{ 38.f };
	paint.setColor(0xFF888888);

	auto left = rect.fLeft;
	for (auto& column:columns)
	{
		left += std::get<1>(column);
		paint.setColor(0xFFD8D8D8);
		canvas->drawLine(left, rect.fTop, left, rect.fBottom, paint);
		if (left > rect.fLeft) {
			canvas->drawString(iconCode, left - paddingRight, rect.fTop + 32.f, *font, paint);
		}
		paint.setColor(0xFF888888);
		auto str = std::get<0>(column);
		auto textLength = wcslen(str.data()) * 2;
		canvas->drawSimpleText(str.data(), textLength, SkTextEncoding::kUTF16,
			left + paddingLeft, rect.fTop+29.f, *fontText, paint);
	}
	paint.setColor(0xFFD8D8D8);
	canvas->drawString(iconCode, root->w - paddingRight, rect.fTop + 32.f, *font, paint);
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
	rect.setXYWH(root->contentPanel->rect.fLeft, 
		root->contentPanel->rect.fTop, 
		root->contentPanel->rect.width(),
		46.f);
}
