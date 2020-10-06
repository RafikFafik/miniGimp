#ifndef COLOR_H
#define COLOR_H


struct Color {
    unsigned char red, green, blue;
    Color(){
        red = 0;
        green = 0;
        blue = 0;
    }
    Color(unsigned char _red, unsigned char _green, unsigned char _blue){
        red = _red;
        green = _green;
        blue = _blue;
    }
};

#endif // COLOR_H
