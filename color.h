#ifndef COLOR_H
#define COLOR_H


struct Color {
    unsigned char red, green, blue;
    Color(){
        red = 0;
        green = 0;
        blue = 0;
    }
    Color(unsigned char red, unsigned char green, unsigned char blue){
        this->red = red;
        this->green = green;
        this->blue = blue;
    }
    bool operator== (const Color &a) {
        return (this->red == a.red && this->green == a.green && this->blue == a.blue);
    }
    bool operator!= (const Color &a) {
        return (this->red != a.red || this->green != a.green || this->blue != a.blue);
    }
};

#endif // COLOR_H
