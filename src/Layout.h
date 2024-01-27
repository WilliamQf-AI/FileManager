#pragma once
#include <memory>
#include "yoga/Yoga.h"
#include "include/core/SkPoint.h"

class Layout
{
public:
    Layout();
    ~Layout();
    void addLayoutChild(Layout* target);
    void setLayoutPadding(float padding);
    void setLayoutPadding(float left, float top, float right, float bottom);
    void setLayoutMargin(float margin);
    void setLayoutMargin(float left, float top, float right, float bottom);
    
    float getWidth();
    float getHeight();
    float getXOffset();
    float getYOffset();
    SkPoint getPos();
    void setAlignSelf(YGAlign align);
    void setFlexDirection(YGDirection direction);
    void setJustifyContent(YGJustify justifyContent);
    YGNodeRef layout;

protected:
    float xAbsolute = 0;
    float yAbsolute = 0;
};