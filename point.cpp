#include "point.h"

Point::Point(){
    x = 0;
    y = 0;
};

Point::Point(int xpos, int ypos){
    x = xpos;
    y = ypos;
}
int Point::getX()
{
    return this->x;
}
int Point::getY()
{
    return this->y;
}
void Point::setX(int xpos)
{
    this->x = xpos;
}
void Point::setY(int ypos)
{
    this->y = ypos;
}
void Point::setPoint(int xpos, int ypos)
{
    this->x = xpos;
    this->y = ypos;
}
