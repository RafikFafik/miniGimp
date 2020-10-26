#include "pixel.h"

void Pixel::clear(QImage *img)
{
    Color *c = new Color;
    c->red = 0;
    c->green = 0;
    c->blue = 0;
    fill(img, c);
    delete c;
}
void Pixel::setPixelColor(QImage *img, Point *point, Color *color)
{
    uchar *pointer = img->bits();
    int width = img->width();
    int height = img->height();
    int x = point->x;
    int y = point->y;
    if(Pixel::outOfImage(point, width, height))
        return;
    pointer[width * 4 * y + 4 * x + 2] = color->red;
    pointer[width * 4 * y + 4 * x + 1] = color->green;
    pointer[width * 4 * y + 4 * x] = color->blue;
}
void Pixel::setPixelColorRightFrame(QImage *img, Point *point, Color *color)
{
    uchar *pointer = img->bits();
    int width = img->width();
    int x = point->x;
    int y = point->y;
    pointer[width * 4 * y + 4 * x + 2] = color->red;
    pointer[width * 4 * y + 4 * x + 1] = color->green;
    pointer[width * 4 * y + 4 * x] = color->blue;
}
Color Pixel::getPixelColor(unsigned char *pointer, int width, Point point) {
    Color result;
    result.blue = pointer[width * 4 * point.y + 4 * point.x];
    result.green = pointer[width * 4 * point.y + 4 * point.x + 1];
    result.red = pointer[width * 4 * point.y + 4 * point.x + 2];

    return result;
}
void Pixel::fill(QImage *img, Color *color)
{
    uchar *pointer = img->bits();
    int width = img->width();
    int height = img->height();

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++){
            pointer[width * 4 * i + 4 *j] = color->blue;
            pointer[width * 4 * i + 4 *j + 1] = color->green;
            pointer[width * 4 * i + 4 *j + 2] = color->red;
        }
    }
}
Color *Pixel::interpolate(unsigned char *img, int width, double x, double y, Color *output) {
    int left_up_x = floor(x);
    int left_up_y = floor(y);
    double a = x - left_up_x;
    double b = y - left_up_y;
    output->blue = b * ((1 - a) * img[width * 4 * (left_up_y + 1) + 4 * left_up_x] + a * img[width * 4 * (left_up_y + 1) + 4 * (left_up_x + 1)]) +
                 (1 - b) * ((1 - a) * img[width * 4 * left_up_y + 4 * left_up_x] + a * img[width * 4 * left_up_y + 4 * (left_up_x + 1)]);
    output->red = b * ((1 - a) * img[width * 4 * (left_up_y + 1) + (4 * left_up_x) + 1] + a * img[width * 4 * (left_up_y + 1) + (4 * (left_up_x + 1)) + 1]) +
                 (1 - b) * ((1 - a) * img[width * 4 * left_up_y + (4 * left_up_x) + 1] + a * img[width * 4 * left_up_y + (4 * (left_up_x + 1)) + 1]);
    output->green = b * ((1 - a) * img[width * 4 * (left_up_y + 1) + (4 * left_up_x) + 2] + a * img[width * 4 * (left_up_y + 1) + (4 * (left_up_x + 1)) + 2]) +
                 (1 - b) * ((1 - a) * img[width * 4 * left_up_y + (4 * left_up_x) + 2] + a * img[width * 4 * left_up_y + (4 * (left_up_x + 1)) + 2]);
    return output;
}
void Pixel::drawPoint(unsigned char *ptr, Point *point, int width, Color *color) {
    Point *current = new Point;
    for(int i =  point->y -6; i <  point->y + 6; i++) {
        for(int j = point->x - 6; j < point->x + 6; j++) {
            // no support for non square QImage
            current->x = j;
            current->y = i;
            if(Pixel::outOfImage(current, width, width))
                continue;
            ptr[width * 4 * i + 4 * j + 2] = color->red;
            ptr[width * 4 * i + 4 * j + 1] = color->green;
            ptr[width * 4 * i + 4 * j] = color->blue;
        }
    }
    delete current;
}
void Pixel::drawPointRightFrame(unsigned char *ptr, Point *point, int width, Color *color) {
    Point *current = new Point;
    for(int i =  point->y -6; i <  point->y + 6; i++) {
        for(int j = point->x - 6; j < point->x + 6; j++) {
            ptr[width * 4 * i + 4 * j + 2] = color->red;
            ptr[width * 4 * i + 4 * j + 1] = color->green;
            ptr[width * 4 * i + 4 * j] = color->blue;
        }
    }
    delete current;
}
bool Pixel::pointClicked(Point *point, std::vector<Point> &points) {
    if(points.empty())
        return false;
    for(std::vector<Point>::iterator it = points.begin(); it != points.end(); it++) {
        if(point->x >= it->x - 6 && point->x < it->x + 6 && point->y >= it->y - 6 && point->y < it->y + 6)
            return true;
    }
    return false;
}
bool Pixel::twoPointsInSamePosition(Point *first, Point *second) {
    if(abs(first->x - second->x) < 6 && abs(first->y - second->y) < 6)
        return true;
    return false;
}
int Pixel::getPointIndex(std::vector<Point> points, Point *point) {
    for(std::vector<Point>::iterator it = points.begin(); it != points.end(); it++) {
        if(point->x >= it->x - 6 && point->x < it->x + 6 && point->y >= it->y - 6 && point->y < it->y + 6)
            return it - points.begin();
    }
    return -1;
}
int Pixel::getTop(std::vector<Point> &points) {
    int value = points.at(0).y;
    for(std::vector<Point>::iterator it = points.begin() + 1; it != points.end(); it++) {
        if(it->y < value)
            value = it->y;
    }
    return value;
}
int Pixel::getBottom(std::vector<Point> &points) {
    int value = points.at(0).y;
    for(std::vector<Point>::iterator it = points.begin() + 1; it != points.end(); it++) {
        if(it->y > value)
            value = it->y;
    }
    return value;
}
int Pixel::getLeft(std::vector<Point> &points) {
    int value = points.at(0).x;
    for(std::vector<Point>::iterator it = points.begin() + 1; it != points.end(); it++) {
        if(it->x < value)
            value = it->x;
    }
    return value;
}
int Pixel::getRight(std::vector<Point> &points) {
    int value = points.at(0).x;
    for(std::vector<Point>::iterator it = points.begin() + 1; it != points.end(); it++) {
        if(it->x > value)
            value = it->x;
    }
    return value;
}
bool Pixel::inFrameClicked(Point *point, QFrame *frame) {
    if(point->x >= frame->x() && point->x < frame->x() + frame->width() && point->y >= frame->y() && point->y < frame->y() + frame->height())
           return true;
    return false;
}
bool Pixel::outOfImage(Point *point, int width, int height) {
    // no support for frame located with offset from widget in point (0, 0)
    if(point->x >= width || point->x < 0 || point->y >= height || point->y < 0)
           return true;
    return false;
}
Color *Pixel::convertColor(QColor qtcolor) {
    Color *color = new Color;
    color->red = qtcolor.red();
    color->green = qtcolor.green();
    color->blue = qtcolor.blue();

    return color;
}
void Pixel::drawPoints(QImage *img, std::vector<Point> points, Color *color) {
    for(unsigned int i = 0; i < points.size(); i++)
        drawPoint(img->bits(), &points.at(i), img->width(), color);
}
std::vector<int> Pixel::getIntersections(std::vector<Point> points, int given_y, std::vector<int> reference) {
    if(points.empty())
        return reference;
    int x;
    for(unsigned int i = 0; i < points.size() - 1; i++) {
        Point point_start = points.at(i);
        Point point_end = points.at(i + 1);
        Point previous_point;
        if((point_start.y <= given_y && point_end.y >= given_y) || (point_start.y >= given_y && point_end.y <= given_y)) {
            x = Pixel::getIntersection(point_start, point_end, given_y);
            // first / last point handling
            i > 0 ? previous_point = points.at(i - 1) : previous_point = points.at(points.size() - 1);
            if(i > 0 && given_y == point_start.y && ((previous_point.y < given_y && point_end.y > given_y )||(previous_point.y > given_y && point_end.y < given_y) ))
                continue;
            reference.push_back(x);
        }
    }
    return reference;
}
int Pixel::getIntersection(Point A, Point B, int y) {
    if(B.y - A.y == 0)
        return A.x;
    return A.x + ((y - A.y) * ((B.x - A.x) / (double)(B.y - A.y)));
}
bool Pixel::notLocalMinMax(int y, int y1, int y2) {
    return (y > y1 && y > y2) || ( y < y1 && y < y2) ? true : false;
}
void Pixel::monochromatic(QImage *image) {
    unsigned char *pointer = image->bits();
    int width = image->width();
    Color color;
    Point *point = new Point;
    Color *monochromatic = new Color();
    for(int i = 0; i < image->height(); i++) {
        for(int j = 0; j < width; j++) {
            point->x = j;
            point->y = i;
            color = getPixelColor(pointer, width, Point(j, i));
            monochromatic->red = 0.2126 * color.red + 0.7152 * color.green + 0.0722 * color.blue;
            monochromatic->red < 128 ? monochromatic->red = 0 : monochromatic->red = 255;
            monochromatic->blue = monochromatic->red;
            monochromatic->green = monochromatic->red;
            setPixelColor(image, point, monochromatic);
        }
    }
    delete monochromatic;
    delete point;
}
