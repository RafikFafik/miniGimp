#include "pixel.h"

void Pixel::clear(QImage *img)
{
    fill(img, Color(0, 0, 0));
}
void Pixel::setPixelColor(QImage *img, Point point, Color color)
{
    uchar *pointer = img->bits();
    int width = img->width();
//    int height = img->height();
    int x = point.getX();
    int y = point.getY();

    pointer[width * 4 * y + 4 * x] = color.getBlue();
    pointer[width * 4 * y + 4 * x + 1] = color.getGreen();
    pointer[width * 4 * y + 4 * x + 2] = color.getRed();
}
void Pixel::fill(QImage *img, Color color)
{
    uchar *pointer = img->bits();
    int width = img->width();
    int height = img->height();

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++){
            pointer[width * 4 * i + 4 *j] = color.getBlue();
            pointer[width * 4 * i + 4 *j + 1] = color.getGreen();
            pointer[width * 4 * i + 4 *j + 2] = color.getRed();
        }
    }
}
