#ifndef TEXTURE_H
#define TEXTURE_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QFrame>
#include <vector>
#include "pixel.h"
#include "geometry.h"
#include "color.h"
#include "point.h"

namespace Ui {
class Texture;
}

class Texture : public QWidget
{
    Q_OBJECT

public:
    explicit Texture(QWidget *parent = nullptr);
    ~Texture();

private:
    Ui::Texture *ui;
    QImage *img_left, *img_right, *img_left_restore, *img_right_restore;
    std::vector<Point> points_left, points_right;
    void frameAction(QImage *img, QFrame *frame, std::vector<Point> &points, Point *point, Color *color);
    bool inFrameClicked(Point *point, QFrame *frame);
    void renderTriangle(QImage *img, QFrame *frame, std::vector<Point> &points, Color *color, int point_index);
    Point *point;
    Color *color;
    void texture();
    double calcWv(int x, int y, Point A, Point C);
    double calcWw(int x, int y, Point A, Point B);
    double calcW(Point A, Point B, Point C);
    bool outsideTriangle(double v, double w, double u);
    void debug();
    bool interpolation_enabled = true;
private slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);
    void on_reset_clicked();
    void on_interpolation_enabled_clicked();
};

#endif // TEXTURE_H
