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
    int x = point->x;
    int y = point->y;

    pointer[width * 4 * y + 4 * x + 2] = color->blue;
    pointer[width * 4 * y + 4 * x + 1] = color->green;
    pointer[width * 4 * y + 4 * x] = color->red;
}
Color Pixel::getPixelColor(QImage *img, Point *point)
{
    Color color;
    uchar *pointer = img->bits();
    int width = img->width();
    int x = point->x;
    int y = point->y;
    color.red = pointer[width * 4 * y + 4 * x];
    color.green = pointer[width * 4 * y + 4 * x + 1];
    color.blue = pointer[width * 4 * y + 4 * x + 2];
    return color;
}
void Pixel::fill(QImage *img, Color *color)
{
    uchar *pointer = img->bits();
    int width = img->width();
    int height = img->height();

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++){
            pointer[width * 4 * i + 4 *j] = color->red;
            pointer[width * 4 * i + 4 *j + 1] = color->green;
            pointer[width * 4 * i + 4 *j + 2] = color->blue;
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
    for(int i =  point->y -6; i <  point->y + 6; i++) {
        for(int j = point->x - 6; j < point->x + 6; j++) {
            ptr[width * 4 * i + 4 * j + 2] = color->red;
            ptr[width * 4 * i + 4 * j + 1] = color->green;
            ptr[width * 4 * i + 4 * j] = color->blue;
        }
    }
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
    if(point->x >= frame->x() && point->x < frame->x() + frame->width() && point->y >= frame->y() && point->y < frame->y() + frame->width())
           return true;
    return false;
}
