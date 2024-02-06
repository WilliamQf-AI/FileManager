#include "ControlBase.h"
#include <include/core/SkFontMetrics.h>
#include <include/core/SkFontTypes.h>

ControlBase::ControlBase(WindowBase* root):root{root}
{
}

ControlBase::~ControlBase()
{
}

SkPoint ControlBase::getStartPosOfIconAtCenterOfRect(const char* text, SkRect& rect, SkFont* font)
{
    SkFontMetrics metrics;
    font->getMetrics(&metrics);
    SkRect textBounds;
    font->measureText(text, 4, SkTextEncoding::kUTF8, &textBounds);
    SkScalar x = rect.centerX() - textBounds.width() / 2 - textBounds.fLeft/2;
    SkScalar y = rect.centerY() + (metrics.fDescent - metrics.fAscent) / 2 - metrics.fDescent;
    return SkPoint(x, y);
}

SkPoint ControlBase::getStartPosOfIconAtCenterOfRect(std::wstring& str, SkRect& rect, SkFont* font)
{
    auto textLength = wcslen(str.data()) * 2;
    SkFontMetrics metrics;
    font->getMetrics(&metrics);
    SkRect textBounds;
    font->measureText(str.data(), textLength, SkTextEncoding::kUTF16, &textBounds);
    SkScalar x = rect.centerX() - textBounds.width() / 2;
    SkScalar y = rect.centerY() + (metrics.fDescent - metrics.fAscent) / 2 - metrics.fDescent;
    return SkPoint(x, y);
}

float ControlBase::getTextVerticalVal(SkFont* font)
{
    SkFontMetrics metrics;
    font->getMetrics(&metrics);
    return (metrics.fDescent - metrics.fAscent) / 2 - metrics.fDescent;
}
