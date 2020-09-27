#pragma once

#include <QWidget>
#include <QImage>
#include <QDebug>
#include <QMouseEvent>
#include <QColorDialog>
#include <QPainter>
#include <QFrame>
#include <algorithm>
#include <vector>
#include "pixel.h"
#include "color.h"
#include "geometry.h"
#include "point.h"

namespace Ui {
class Paint;
}

class Paint : public QWidget
{
    Q_OBJECT

public:
    explicit Paint(QWidget *parent = nullptr);
    ~Paint();

private:
    Ui::Paint *ui;
    QImage *img, *color_preview;
    std::vector<QImage> imgs;
    Point press, move, release;
    bool insideFrame(QFrame *frame, Point point);
    unsigned int mode = 0;

private slots:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void setDrawingColor();
    void draw();
    void on_clear_clicked();
    void on_pen_clicked();
    void on_line_clicked();
    void on_undo_clicked();
};
