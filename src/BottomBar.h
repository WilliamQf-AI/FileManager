#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <vector>
#include "include/core/SkCanvas.h"

class WindowMain
{
public:
    WindowMain();
    ~WindowMain();

private:
    void paintCanvas(SkCanvas *canvas) override;
    void initSize();
};