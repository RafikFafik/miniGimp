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
