#ifndef COLOR_H
#define COLOR_H


class Color
{
public:
    Color(unsigned r, unsigned g, unsigned b);
    Color();
    unsigned char getRed();
    unsigned char getGreen();
    unsigned char getBlue();
    unsigned char getRGB();
    void setRed(unsigned char r);
    void setGreen(unsigned char g);
    void setBlue(unsigned char b);
    void setRGB(unsigned char r, unsigned char g, unsigned char b);
private:
    unsigned char red, green, blue;
};

#endif // COLOR_H
