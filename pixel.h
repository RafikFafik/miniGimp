#pragma once

#include <QImage>
#include "point.h"
#include "color.h"
#include "paint.h"

class Pixel
{

public:
    static void setPixelColor(QImage *img, Point point, Color color);
    static void clear(QImage *img);
    static void fill(QImage *img, Color color);
};
