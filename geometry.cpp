#include "geometry.h"

Geometry::Geometry()
{

}
void Geometry::line(QImage *img, Point *start, Point *end, Color *color)
{
    if(end->x-start->x == 0){
        Point *p = new Point();
        if(start->y < end->y) {
            for(int i = start->y; i < end->y; i++)
                Pixel::setPixelColor(img, p, color);
        } else {
            for(int i = end->y; i < start->y; i++)
                Pixel::setPixelColor(img, p, color);
        }
       delete p;
     }
    double m = (end->y-start->y)/(double)(end->x-start->x);
    if(abs(m) < 1) {
        if(start->x > end->x)
            std::swap(start, end);
        Point *p = new Point();
        for(int x = start->x; x <= end->x; x++)
        {
            double y = m * (x - start->x) + start->y;
            p->x = x;
            p->y = (int)floor(y+0.5);
            Pixel::setPixelColor(img, p, color);

        }
        delete p;
    }
    else {
        if(start->y > end->y)
            std::swap(start, end);
        Point *p = new Point();
        double m = (end->x-start->x)/(double)(end->y-start->y);
        for(int y = start->y; y <= end->y; y++)
        {
            double x = m * (y - start->y) + start->x;
            p->x = x;
            p->y = y;
            Pixel::setPixelColor(img, p, color);
        }
        delete p;
    }

}
void Geometry::lineRightFrame(QImage *img, Point *start, Point *end, Color *color)
{
    if(end->x-start->x == 0){
        Point *p = new Point();
        if(start->y < end->y) {
            for(int i = start->y; i < end->y; i++)
                Pixel::setPixelColorRightFrame(img, p, color);
        } else {
            for(int i = end->y; i < start->y; i++)
                Pixel::setPixelColorRightFrame(img, p, color);
        }
       delete p;
     }
    double m = (end->y-start->y)/(double)(end->x-start->x);
    if(abs(m) < 1) {
        if(start->x > end->x)
            std::swap(start, end);
        Point *p = new Point();
        for(int x = start->x; x <= end->x; x++)
        {
            double y = m * (x - start->x) + start->y;
            p->x = x;
            p->y = (int)floor(y+0.5);
            Pixel::setPixelColorRightFrame(img, p, color);

        }
        delete p;
    }
    else {
        if(start->y > end->y)
            std::swap(start, end);
        Point *p = new Point();
        double m = (end->x-start->x)/(double)(end->y-start->y);
        for(int y = start->y; y <= end->y; y++)
        {
            double x = m * (y - start->y) + start->x;
            p->x = x;
            p->y = y;
            Pixel::setPixelColorRightFrame(img, p, color);
        }
        delete p;
    }

}

void Geometry::circle(QImage *img, Point *center, Point *edge, Color *color) {
    double radius_square = (edge->x - center->x) * (edge->x - center->x) + (edge->y - center->y) * (edge->y - center->y);
    double y;
    Point *p = new Point;
    for(int x = 0; x <= sqrt(radius_square) / sqrt(2); x++) {
        y = sqrt(radius_square - x * x);
        p->setXY(x + center->x, y + center->y);
        Pixel::setPixelColor(img, p, color); // (x, y)
        p->y = -y + center->y;
        Pixel::setPixelColor(img, p, color); // (x, -y)
        p->x = -x + center->x;
        Pixel::setPixelColor(img, p, color); // (-x, -y)
        p->y = y + center->y;
        Pixel::setPixelColor(img, p, color); // (-x, y)

        p->setXY(y + center->x, x + center->y);
        Pixel::setPixelColor(img, p, color); // (y, x)
        p->setXY(y + center->x, -x + center->y);
        Pixel::setPixelColor(img, p, color); // (x, -y)
        p->setXY(-y + center->x, -x + center->y);
        Pixel::setPixelColor(img, p, color); // (-x, -y)
        p->setXY(-y + center->x, x + center->y);
        Pixel::setPixelColor(img, p, color); // (-x, y)
    }

    delete p;
}
void Geometry::elipse(QImage *img, Point *center, Point *edge, Color *color, int verticles) {
    Point *start = new Point;
    Point *end = new Point;
    double step = 2 * M_PI / verticles;
    int a = abs(center->x - edge->x);
    int b = abs(center->y - edge->y);
    for(double i = 0; i < 2 * M_PI; i += step) {
        start->x = a * cos(i) + center->x;
        start->y = b * sin(i) + center->y;
        end->x = a * cos(i + step) + center->x;
        end->y = b * sin(i + step) + center->y;
        line(img, start, end, color);
    }
    delete start;
    delete end;
}

