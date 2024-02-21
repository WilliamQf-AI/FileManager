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
	font->setSize(24.f);
	paint.setAntiAlias(false);

	auto paddingLeft{ 18.f };
	auto paddingRight{ 38.f };

	auto right = rect.fLeft;
	for (size_t i = 0; i < columns.size(); i++)
	{
		paint.setColor(0xFF888888);
		auto str = std::get<0>(columns[i]);
		auto textLength = wcslen(str.data()) * 2;
		canvas->drawSimpleText(str.data(), textLength, SkTextEncoding::kUTF16,
			right + paddingLeft, rect.fTop + 29.f, *fontText, paint);
		if (i + 1 < columns.size()) {
			right += std::get<1>(columns[i + 1]);
			paint.setColor(0xFFE8E8E8);
			canvas->drawLine(right, rect.fTop, right, rect.fBottom, paint);
		}
		else {
			right = root->w;
		}
		paint.setColor(0xFFBBBBBB);
		canvas->drawString(std::get<2>(columns[i]), right - paddingRight, rect.fTop + 32.f, *font, paint);
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
	rect.setXYWH(root->contentPanel->rect.fLeft+1, 
		root->contentPanel->rect.fTop, 
		root->contentPanel->rect.width(),
		46.f);
}
