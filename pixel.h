#pragma once

#include <QImage>
#include "point.h"
#include "color.h"
#include "paint.h"

class Pixel
{

public:
    static void setPixelColor(QImage *img, Point *point, Color *color);
    static Color getPixelColor(QImage *img, Point *point);
    static void clear(QImage *img);
    static void fill(QImage *img, Color *color);
    static Color *interpolate(unsigned char *img, int width, double x, double y, Color *output);
};
