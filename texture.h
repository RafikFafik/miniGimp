#ifndef TEXTURE_H
#define TEXTURE_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QFrame>
#include <vector>
#include "pixel.h"
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
    Point *point;
    Color *color;
    int point_index = -1;
private slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);
};

#endif // TEXTURE_H
