#ifndef CURVE_H
#define CURVE_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <algorithm>
#include <vector>
#include "point.h"
#include "color.h"
#include "pixel.h"
#include "geometry.h"

namespace Ui {
class Curve;
}

class Curve : public QWidget
{
    Q_OBJECT

public:
    explicit Curve(QWidget *parent = nullptr);
    ~Curve();
    void bezier(QImage *img, std::vector<Point> CVs);
    void bSpline(QImage *img, std::vector<Point> CVs);

private:
    Ui::Curve *ui;
    QImage *img;
    bool bezier_checked = true;
    bool b_spline_checked = false;
    bool b_spline_extend = false;
    bool show_cv = true;
    std::vector<Point> CVs;
    Point calcBezierSegment(double t, std::vector<Point>::iterator it);
    Point calcBSplineSegment(double t, Point P1, Point P2, Point P3, Point P4);
    unsigned int segments_count = 25;
private slots:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void on_reset_clicked();
    void on_bezier_clicked();
    void on_b_spline_clicked();
    void on_show_cv_clicked();
    void on_accuracy_valueChanged(int value);
    void on_b_spline_extend_clicked();
};

#endif // CURVE_H
