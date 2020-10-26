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

};

#endif // GEOMETRY_H
