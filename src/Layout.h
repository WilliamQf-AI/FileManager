#pragma once
#include <memory>
#include "yoga/Yoga.h"
#include "include/core/SkPoint.h"
#include "include/core/SkRect.h"

class Layout
{
public:
    Layout();
    ~Layout();
    void setSize(float w, float h);
    void addLayoutChild(Layout* target);
    SkPoint getOffset();
    SkRect getOffsetRect();
    SkPoint getPos();

    void setLayoutPadding(float padding);
    void setLayoutPadding(float left, float top, float right, float bottom);
    void setLayoutMargin(float margin);
    void setLayoutMargin(float left, float top, float right, float bottom);
    
    float getWidth();
    float getHeight();
    float getXOffset();
    float getYOffset();
    
    void setAlignSelf(YGAlign align);
    void setFlexDirection(YGDirection direction);
    void setJustifyContent(YGJustify justifyContent);
    YGNodeRef layout;

protected:
    float xAbsolute = 0;
    float yAbsolute = 0;
};