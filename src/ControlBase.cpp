#include "ControlBase.h"
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