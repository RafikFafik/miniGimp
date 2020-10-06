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
void Pixel::setPixelColor(QImage *img, Point point, Color *color)
{
    uchar *pointer = img->bits();
    int width = img->width();
    int x = point.x;
    int y = point.y;

    pointer[width * 4 * y + 4 * x + 2] = color->blue;
    pointer[width * 4 * y + 4 * x + 1] = color->green;
    pointer[width * 4 * y + 4 * x] = color->red;
}
Color Pixel::getPixelColor(QImage *img, Point point)
{
    Color color;
    uchar *pointer = img->bits();
    int width = img->width();
    int x = point.x;
    int y = point.y;
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
