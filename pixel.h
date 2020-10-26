#pragma once

#include <QImage>
#include <QFrame>
#include "point.h"
#include "color.h"
#include "paint.h"

class Pixel
{

public:
    static void setPixelColor(QImage *img, Point *point, Color *color);
    static Color getPixelColor(unsigned char *pointer, int width, Point point);
    static void setPixelColorRightFrame(QImage *img, Point *point, Color *color);
    static void clear(QImage *img);
    static void fill(QImage *img, Color *color);
    static void drawPoint(unsigned char *ptr, Point *point, int width, Color *color);
    static void drawPointRightFrame(unsigned char *ptr, Point *point, int width, Color *color);
    static Color *interpolate(unsigned char *img, int width, double x, double y, Color *output);
    static bool pointClicked(Point *point, std::vector<Point> &points);
    static bool twoPointsInSamePosition(Point *first, Point *second);
    static int getPointIndex(std::vector<Point> points, Point *point);
    static int getTop(std::vector<Point> &points);
    static int getBottom(std::vector<Point> &points);
    static int getLeft(std::vector<Point> &points);
    static int getRight(std::vector<Point> &points);
    static bool inFrameClicked(Point *point, QFrame *frame);
    static Color *convertColor(QColor qtcolor);
    static bool outOfImage(Point *point, int width, int height);
    static void drawPoints(QImage *img, std::vector<Point> points, Color *color);
    static std::vector<int> getIntersections(std::vector<Point> sections, int given_y, std::vector<int> reference);
    static int getIntersection(Point A, Point B, int y);
    static bool notLocalMinMax(int x, int y1, int y2);
    static void monochromatic(QImage *image);
private:

};
