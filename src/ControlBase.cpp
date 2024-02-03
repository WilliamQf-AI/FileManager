#include "ControlBase.h"
#include <include/core/SkFontMetrics.h>
#include <include/core/SkFontTypes.h>

ControlBase::ControlBase(WindowBase* root):layout{ YGNodeNew() },root{root}
{
}

ControlBase::~ControlBase()
{
}

SkRect ControlBase::getRect()
{
    auto x = YGNodeLayoutGetLeft(layout);
    auto y = YGNodeLayoutGetTop(layout);
    auto w = YGNodeLayoutGetWidth(layout);
    auto h = YGNodeLayoutGetHeight(layout);
    return SkRect::MakeXYWH(x, y, w, h);
}

SkRect ControlBase::getRect(YGNodeRef target)
{
    auto x = YGNodeLayoutGetLeft(target);
    auto y = YGNodeLayoutGetTop(target);
    auto w = YGNodeLayoutGetWidth(target);
    auto h = YGNodeLayoutGetHeight(target);
    return SkRect::MakeXYWH(x, y, w, h);
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
