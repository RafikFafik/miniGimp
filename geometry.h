#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "point.h"
#include "pixel.h"
#include <math.h>

class Geometry
{
public:
    Geometry();
    static void line(QImage *img, Point *start, Point *end, Color *color);
    static void lineRightFrame(QImage *img, Point *start, Point *end, Color *color);
    static void circle(QImage *img, Point *center, Point *edge, Color *color);
    static void elipse(QImage *img, Point *center, Point *edge, Color *color, int verticles);
};

#endif // GEOMETRY_H
