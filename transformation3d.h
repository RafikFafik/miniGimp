#ifndef TRANSFORMATION3D_H
#define TRANSFORMATION3D_H

#include <QWidget>
#include "pixel.h"
#include "matrix.h"
#include "cube.h"

namespace Ui {
class Transformation3D;
}

class Transformation3D : public QWidget
{
    Q_OBJECT

public:
    explicit Transformation3D(QWidget *parent = nullptr);
    ~Transformation3D();

private:
    QImage *img;
    Cube cube;
    Point3D *point, center;
private slots:
    void paintEvent(QPaintEvent*);
    void on_translateX_valueChanged(int value);

    void on_translateY_valueChanged(int value);

    void on_translateZ_valueChanged(int value);

    void on_fov_valueChanged(int value);

    void on_volume_valueChanged(int value);

    void on_scaleX_valueChanged(int value);

    void on_scaleY_valueChanged(int value);

    void on_scaleZ_valueChanged(int value);

    void on_rotateX_valueChanged(int value);

    void on_rotateY_valueChanged(int value);

    void on_rotateZ_valueChanged(int value);

    void on_reset_clicked();

    void on_wireframe_clicked();

    void on_flip_normal_clicked();

    void on_draw_points_clicked();

private:
    Ui::Transformation3D *ui;
};

#endif // TRANSFORMATION3D_H
