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
#include <stack>
#include "pixel.h"
#include "color.h"
#include "geometry.h"
#include "point.h"

#define PEN 0
#define LINE 1
#define FLOOD_FILL 2

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
    QImage *img, *color_preview, *fg_color_field, *bg_color_field;
    std::vector<QImage> imgs;
    Point *press, *move, *release;
    Color *lmb_color = new Color(255, 255, 255);
    Color *rmb_color = new Color(0, 0, 0);
    bool insideFrame(Point *point, QFrame *frame);
    unsigned int mode = 1;
    void floodFill(Point *point, Color *color);
    void drawLine(Color *color);
private slots:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void on_clear_clicked();
    void on_pen_clicked();
    void on_line_clicked();
    void on_undo_clicked();
    void on_flood_fill_clicked();
};
