#include "Layout.h"
#include <stack>
#include "WindowBase.h"
Layout::Layout(WindowBase* root) : layout{YGNodeNew()},root{root}
{
    YGNodeSetContext(layout, this);
}
Layout::~Layout()
{
    //todo 这里可能有问题
    YGNodeFreeRecursive(layout);
}
void Layout::setSize(float w, float h)
{
    YGNodeStyleSetWidth(layout, w);
    YGNodeStyleSetHeight(layout, h);
}
void Layout::setLayoutPadding(float padding)
{
    YGNodeStyleSetPadding(layout, YGEdgeAll, padding);
}
void Layout::setLayoutPadding(float left, float top, float right, float bottom)
{
    YGNodeStyleSetPadding(layout, YGEdgeLeft, left);
    YGNodeStyleSetPadding(layout, YGEdgeTop, top);
    YGNodeStyleSetPadding(layout, YGEdgeRight, right);
    YGNodeStyleSetPadding(layout, YGEdgeBottom, bottom);
}
void Layout::setLayoutMargin(float margin)
{
    YGNodeStyleSetMargin(layout, YGEdgeAll, margin);
}
void Layout::setLayoutMargin(float left, float top, float right, float bottom)
{
    YGNodeStyleSetMargin(layout, YGEdgeLeft, left);
    YGNodeStyleSetMargin(layout, YGEdgeTop, top);
    YGNodeStyleSetMargin(layout, YGEdgeRight, right);
    YGNodeStyleSetMargin(layout, YGEdgeBottom, bottom);
}
void Layout::addLayoutChild(Layout *target)
{
    auto index = YGNodeGetChildCount(layout);
    YGNodeInsertChild(layout, target->layout, index);
}
SkPoint Layout::getOffset()
{
    auto x = YGNodeLayoutGetLeft(layout);
    auto y = YGNodeLayoutGetTop(layout);
    return SkPoint(x,y);
}
SkRect Layout::getOffsetRect()
{
    auto x = YGNodeLayoutGetLeft(layout);
    auto y = YGNodeLayoutGetTop(layout);
    auto w = YGNodeLayoutGetWidth(layout);
    auto h = YGNodeLayoutGetHeight(layout);
    return SkRect::MakeXYWH(x,y,w,h);
}
float Layout::getWidth()
{
    return YGNodeStyleGetWidth(layout).value;
}
float Layout::getHeight()
{
    return YGNodeStyleGetHeight(layout).value;
}
void Layout::setAlignSelf(YGAlign align)
{
    YGNodeStyleSetAlignSelf(layout, (YGAlign)align);
}
void Layout::setFlexDirection(YGDirection direction)
{
    YGNodeStyleSetFlexDirection(layout, (YGFlexDirection)direction);
}
void Layout::setJustifyContent(YGJustify justifyContent)
{
    YGNodeStyleSetJustifyContent(layout, (YGJustify)justifyContent);
}
float Layout::getXOffset()
{
    return YGNodeLayoutGetLeft(layout);
}
float Layout::getYOffset()
{
    return YGNodeLayoutGetTop(layout);
}

SkPoint Layout::getPos()
{
    float x = 0.f;
    float y = 0.f;
    YGNode* currentNode = layout;
    while (currentNode) {
        x += YGNodeLayoutGetLeft(currentNode);
        y += YGNodeLayoutGetTop(currentNode);
        currentNode = YGNodeGetParent(currentNode);
    }
    return SkPoint(x, y);
}

Layout* Layout::getRoot()
{
    Layout* currentNode = this;
    while (true) {
        auto temp = YGNodeGetParent(currentNode->layout);
        if (temp) {
            currentNode = static_cast<Layout*>(YGNodeGetContext(temp));
        }
        else {
            return static_cast<Layout*>(YGNodeGetContext(currentNode->layout));
        }
    }
}
