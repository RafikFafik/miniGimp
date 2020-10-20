#ifndef MORPHING_H
#define MORPHING_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QFrame>
#include <QTimer>
#include <vector>
#include "pixel.h"
#include "geometry.h"
#include "color.h"
#include "point.h"


namespace Ui {
class Morphing;
}

class Morphing : public QWidget
{
    Q_OBJECT

public:
    explicit Morphing(QWidget *parent = nullptr);
    ~Morphing();

private:
    Ui::Morphing *ui;
    QImage *keyframe_begin, *keyframe_end, *img, *animation;
    std::vector<Point> points_begin, points_end;
    void frameAction(QImage *img, QFrame *frame, std::vector<Point> &points, Point *point, Color *color);
    void renderTriangle(QImage *img, QFrame *frame, std::vector<Point> &points, Color *color, int point_index);
    Point *point;
    Color *color;
    void morphing();
    Point calcPoint(Point A, Point B);
    double calcWv(int x, int y, Point A, Point C);
    double calcWw(int x, int y, Point A, Point B);
    double calcW(Point A, Point B, Point C);
    double ratio = 0;
    bool outsideTriangle(double v, double w, double u);
    void play();
private slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);
    void on_keyframe_valueChanged(int value);
//    void on_reset_clicked();
    void on_animation_valueChanged();
    void on_frames_count_valueChanged(int value);
    void on_play_clicked();
    void on_reset_clicked();
};

#endif // MORPHING_H
