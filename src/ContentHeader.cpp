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
	auto leftRect = SkRect::MakeXYWH(rect.fLeft, rect.fTop, 460.f, 46.f);
	auto rightRect = SkRect::MakeLTRB(rect.fLeft + 460.f, rect.fTop, root->w, rect.fTop + 46.f);

	SkPaint paint;
	paint.setColor(0xFFE8E8E8);
	canvas->drawLine(rect.fLeft, rect.fTop + 46.f, rect.fRight, rect.fTop + 46.f, paint);
	canvas->drawLine(rightRect.fLeft, rightRect.fTop, rightRect.fLeft, rightRect.fBottom, paint);

	auto paddingLeft{ 18.f };
	auto paddingRight{ 38.f };
	paint.setColor(0xFF888888);
	std::wstring str = L"最近使用的文件";
	auto textLength = wcslen(str.data()) * 2;
	auto fontText = App::GetFontText();
	fontText->setSize(16.8);
	auto verticalVal = getTextVerticalVal(fontText.get());
	canvas->drawSimpleText(str.data(), textLength, SkTextEncoding::kUTF16,
		rect.fLeft + paddingLeft, rect.fTop + 24 + verticalVal, *fontText, paint);

	str = L"使用时间";
	textLength = wcslen(str.data()) * 2;
	canvas->drawSimpleText(str.data(), textLength, SkTextEncoding::kUTF16,
		rightRect.fLeft + paddingLeft, rect.fTop + 24 + verticalVal, *fontText, paint);

	auto font = App::GetFontIcon();
	font->setSize(23.f);
	paint.setAntiAlias(false);
	auto iconCode = (const char*)u8"\ue67d";
	canvas->drawString(iconCode, leftRect.fRight - paddingRight, rect.fTop + 32.f, *font, paint);
	canvas->drawString(iconCode, rightRect.fRight - paddingRight, rect.fTop + 32.f, *font, paint);

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
