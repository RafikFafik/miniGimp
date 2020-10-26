#ifndef SCANLINE_H
#define SCANLINE_H

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
class ScanLine;
}

class ScanLine : public QWidget
{
    Q_OBJECT

public:
    explicit ScanLine(QWidget *parent = nullptr);
    ~ScanLine();

private:
    Ui::ScanLine *ui;
    QImage *img;
    std::vector<Point> verticles;//{{250, 200}, {350, 300}, {250, 400}, {150, 300}, {250, 200}};
    bool closed_circuit = false;
    bool control_verticles = true;
    void drawLines(std::vector<Point> verticles);
    void scanline();
private slots:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void on_cv_clicked();
    void on_reset_clicked();
};

#endif // SCANLINE_H
