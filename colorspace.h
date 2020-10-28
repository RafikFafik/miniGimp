#ifndef COLORSPACE_H
#define COLORSPACE_H

#include <QWidget>
#include <QPainter>
#include "pixel.h"

namespace Ui {
class ColorSpace;
}

class ColorSpace : public QWidget
{
    Q_OBJECT

public:
    explicit ColorSpace(QWidget *parent = nullptr);
    ~ColorSpace();
    void hsv_to_rgb(int h, double s, double v, Color *color);
private:
    QImage *img;
    Ui::ColorSpace *ui;
private slots:
    void paintEvent(QPaintEvent*);
    void on_rbg_red_valueChanged(int value);
    void on_rgb_green_valueChanged(int value);
    void on_rgb_blue_valueChanged(int value);
    void on_hsv_hue_valueChanged(int value);
    void on_hsv_saturation_valueChanged(int value);
    void on_hsv_value_valueChanged(int value);
};

#endif // COLORSPACE_H
