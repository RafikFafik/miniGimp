#ifndef MORPHOLOGY_H
#define MORPHOLOGY_H

#include <QWidget>
#include <QPainter>
#include <QFileDialog>
#include "pixel.h"

namespace Ui {
class Morphology;
}

class Morphology : public QWidget
{
    Q_OBJECT

public:
    explicit Morphology(QWidget *parent = nullptr);
    ~Morphology();

private:
    Ui::Morphology *ui;
    QImage *img, *img_restore, *tmp;
    bool cross_kernel = true;
    bool square_kernel = false;
    void draw(int black_or_white);
    bool checkMask(bool cross_mask, int x, int y, int searched_color);
    bool checkPixel(int x, int y, int searched_color);
    int width, height;

    void dilation();
    void erosion();
    bool matchesCrossKernel(QImage *img, Point *pixel_pos, Color *color_to_check);
    bool matchesSquareKernel(QImage *img, Point *pixel_pos, Color *color_to_check);
private slots:
    void paintEvent(QPaintEvent*);
    void on_closing_clicked();
    void on_dilation_clicked();
    void on_erosion_clicked();
    void on_opening_clicked();
    void on_restore_clicked();
    void on_cross_clicked();
    void on_square_clicked();
    void on_loadImage_clicked();
};

#endif // MORPHOLOGY_H
