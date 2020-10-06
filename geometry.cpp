#include "geometry.h"

Geometry::Geometry()
{

}
void Geometry::line(QImage *img, Point start, Point end, Color *color)
{
    if(end.getX()-start.getX() == 0){
       return;
     }
    double m = (end.getY()-start.getY())/(double)(end.getX()-start.getX());
    if(abs(m) < 1) {
        if(start.getX() > end.getX())
            std::swap(start, end);
        for(int x = start.getX(); x <= end.getX(); x++)
        {
            double y = m * (x - start.getX()) + start.getY();
            Pixel::setPixelColor(img, Point(x, (int)floor(y+0.5)), color);
        }
    }
    else {
        if(start.getY() > end.getY())
            std::swap(start, end);
        double m = (end.getX()-start.getX())/(double)(end.getY()-start.getY());
        for(int y = start.getY(); y <= end.getY(); y++)
        {
            double x = m * (y - start.getY()) + start.getX();
            Pixel::setPixelColor(img, Point((int)floor(x+0.5), y), color);
        }
    }

}
