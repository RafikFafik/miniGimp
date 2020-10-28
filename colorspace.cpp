#include "colorspace.h"
#include "ui_colorspace.h"

ColorSpace::ColorSpace(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorSpace)
{
    ui->setupUi(this);
    img = new QImage(ui->frame->width(), ui->frame->height(), QImage::Format_RGB32);
    on_rbg_red_valueChanged(0);
}

ColorSpace::~ColorSpace()
{
    delete ui;
}
void ColorSpace::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(0, 0, *img);
}

void ColorSpace::on_rbg_red_valueChanged(int red) {
    Point *point = new Point;
    Color *color = new Color(red, 0, 0);
    for(int i = 0; i < ui->frame->height(); i++) {
        for(int j = 0; j < ui->frame->width(); j++) {
            point->setXY(j, i);
            color->green = j / 2;
            color->blue = 255 - i / 2;
            Pixel::setPixelColor(img, point, color);
        }
    }
    delete point;
    delete color;
    update();
}

void ColorSpace::on_rgb_green_valueChanged(int green) {
    Point *point = new Point;
    Color *color = new Color(0, green, 0);
    for(int i = 0; i < ui->frame->height(); i++) {
        for(int j = 0; j < ui->frame->width(); j++) {
            point->setXY(j, i);
            color->red = j / 2;
            color->blue = 255 - i / 2;
            Pixel::setPixelColor(img, point, color);
        }
    }
    delete point;
    delete color;
    update();
}

void ColorSpace::on_rgb_blue_valueChanged(int blue) {
    Point *point = new Point;
    Color *color = new Color(0, 0, blue);
    for(int i = 0; i < ui->frame->height(); i++) {
        for(int j = 0; j < ui->frame->width(); j++) {
            point->setXY(j, i);
            color->green = j / 2;
            color->red = 255 - i / 2;
            Pixel::setPixelColor(img, point, color);
        }
    }
    delete point;
    delete color;
    update();
}
// hue - angle, saturation - radius, value - height
void ColorSpace::hsv_to_rgb(int h, double s, double v, Color *color) {
    double C, X, m;
    double r, g, b;
    C = v * s;
    double h_prim = (double)h/60;
    X = C*(1 - abs(fmod(h_prim, 2) - 1));
    m = v - C;
    if(h>=0 && h<60){r = C; g = X; b = 0;}
    else if(h>=60 && h<120){r = X; g = C; b = 0;}
    else if(h>=120 && h<180){r = 0; g = C; b = X;}
    else if(h>=180 && h<240){r = 0; g = X; b = C;}
    else if(h>=240 && h<300){r = X; g = 0; b = C;}
    else {r = C; g = 0; b = X;}

    color->red = (r + m) * 255;
    color->green = (g + m) * 255;
    color->blue = (b + m) * 255;
}
void ColorSpace::on_hsv_hue_valueChanged(int hue) {
    Point *point = new Point;
    Color *color = new Color;
    int width = ui->frame->width();
    int height = ui->frame->height();
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            hsv_to_rgb(hue, ((double)height - i)/height, (double)j/width, color);
            point->setXY(j, i);
            Pixel::setPixelColor(img, point, color);
        }
    }
    delete point;
    delete color;
    update();
}

void ColorSpace::on_hsv_saturation_valueChanged(int saturation) {
    Point *point = new Point;
    Color *color = new Color;
    int width = ui->frame->width();
    int height = ui->frame->height();
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            hsv_to_rgb(((width - j)/(double)width) * 360, saturation / (double)100, ((double)height - i)/height, color);
            point->setXY(j, i);
            Pixel::setPixelColor(img, point, color);
        }
    }
    delete point;
    delete color;
    update();
}

void ColorSpace::on_hsv_value_valueChanged(int value) {
    Point *point = new Point;
    Color *color = new Color;
    int width = ui->frame->width();
    int height = ui->frame->height();
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            hsv_to_rgb(((width - j)/(double)width) * 360, ((double)height - i)/height, value / (double)100, color);
            point->setXY(j, i);
            Pixel::setPixelColor(img, point, color);
        }
    }
    delete point;
    delete color;
    update();
}
