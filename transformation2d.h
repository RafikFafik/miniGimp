#ifndef TRANSFORMATION2D_H
#define TRANSFORMATION2D_H

#include <QWidget>
#include "pixel.h"
#include "matrix.h"

namespace Ui {
class Transformation2D;
}

class Transformation2D : public QWidget
{
    Q_OBJECT

public:
    explicit Transformation2D(QWidget *parent = nullptr);
    ~Transformation2D();   

private:
    Ui::Transformation2D *ui;
    QImage *img, *imgBuffer;
    void transform();
    Matrix matrix = {3};
    Point *point;
    bool interpolation_enabled = true;
private slots:
    void paintEvent(QPaintEvent*);
    void on_translateX_valueChanged(int value);
    void on_translateY_valueChanged(int value);
    void on_scaleX_valueChanged(int value);
    void on_scaleY_valueChanged(int value);
    void on_reset_clicked();
    void on_rotate_valueChanged(int value);
    void on_sheareX_valueChanged(int value);
    void on_sheareY_valueChanged(int value);
    void on_interpolation_clicked();
};

#endif // TRANSFORMATION2D_H
