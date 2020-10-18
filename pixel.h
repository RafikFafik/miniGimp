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
    static void drawPoint(unsigned char *ptr, Point *point, int width, Color *color);
    static Color *interpolate(unsigned char *img, int width, double x, double y, Color *output);
    static bool pointClicked(Point *point, std::vector<Point> &points);
    static int getPointIndex(std::vector<Point> points, Point *point);
    static int getTop(std::vector<Point> &points);
    static int getBottom(std::vector<Point> &points);
    static int getLeft(std::vector<Point> &points);
    static int getRight(std::vector<Point> &points);
    static bool inFrameClicked(Point *point, QFrame *frame);
};
