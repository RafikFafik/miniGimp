#include "color.h"

Color::Color(){};
Color::Color(unsigned r, unsigned g, unsigned b)
{
    this->red = r;
    this->green = g;
    this->blue = b;
}
unsigned char Color::getRed()
{
    return this->red;
}
unsigned char Color::getGreen()
{
    return this->green;
}
unsigned char Color::getBlue()
{
    return this->blue;
}
void Color::setRGB(unsigned char r, unsigned char g, unsigned char b)
{
    this->red = r;
    this->green = g;
    this->blue = b;
}
