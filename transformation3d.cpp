#include "transformation3d.h"
#include "ui_transformation3d.h"

Transformation3D::Transformation3D(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Transformation3D)
{
    ui->setupUi(this);
    img = new QImage(ui->frame->width(), ui->frame->height(), QImage::Format_RGB32);
    Pixel::clear(img);
    center.x = ui->frame->width() / 2;
    center.y = ui->frame->height() / 2;
    center.z = 250;
    cube.setup(center, 50, 500);
    point  = new Point3D;
    point->x = 0;
    point->y = 0;
    point->z = 0;
    cube.draw(img);
    ui->draw_points->hide();
}

Transformation3D::~Transformation3D()
{
    delete ui;
}

void Transformation3D::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(0, 0, *img);
}
void Transformation3D::on_translateX_valueChanged(int value)
{
    point->x = -value;
    point->y = -ui->translateY->value();
    point->z = -ui->translateZ->value();
    cube.translate(point);
    cube.draw(img);
    update();
}

void Transformation3D::on_translateY_valueChanged(int value)
{
    point->x = -ui->translateX->value();
    point->y = -value;
    point->z = -ui->translateZ->value();
    cube.translate(point);
    cube.draw(img);
    update();
}

void Transformation3D::on_translateZ_valueChanged(int value)
{
    point->x = -ui->translateX->value();
    point->y = -ui->translateY->value();
    point->z = -value;
    cube.translate(point);
    cube.draw(img);
    update();
}

void Transformation3D::on_fov_valueChanged(int value)
{
    cube.setFov(value);
    cube.draw(img);
    update();
}

void Transformation3D::on_volume_valueChanged(int volume)
{
    cube.setup(center, volume, 500);
    cube.draw(img);
    update();
}

void Transformation3D::on_scaleX_valueChanged(int value)
{
    double y = (double)ui->scaleY->value() / 100;
    double x = (double)value / 100;
    double z = (double)ui->scaleZ->value() / 100;
    cube.scale(x, y, z);
    cube.draw(img);
    update();
}

void Transformation3D::on_scaleY_valueChanged(int value)
{
    double y = (double)value / 100;
    double x = (double)ui->scaleX->value() / 100;
    double z = (double)ui->scaleZ->value() / 100;
    cube.scale(x, y, z);
    cube.draw(img);
    update();
}

void Transformation3D::on_scaleZ_valueChanged(int value)
{
    double y = (double)ui->scaleY->value() / 100;
    double x = (double)ui->scaleX->value() / 100;
    double z = (double)value / 100;
    cube.scale(x, y, z);
    cube.draw(img);
    update();
}

void Transformation3D::on_rotateX_valueChanged(int value)
{
    double angle = value / 180.0 * M_PI;
    cube.rotateX(angle);
    cube.draw(img);
    update();
}

void Transformation3D::on_rotateY_valueChanged(int value)
{
    double angle = value / 180.0 * M_PI;
    cube.rotateY(angle);
    cube.draw(img);
    update();
}

void Transformation3D::on_rotateZ_valueChanged(int value)
{
    double angle = value / 180.0 * M_PI;
    cube.rotateZ(angle);
    cube.draw(img);
    update();
}

void Transformation3D::on_reset_clicked()
{
    ui->translateX->setValue(0);
    ui->translateY->setValue(0);
    ui->translateZ->setValue(0);
    ui->scaleX->setValue(100);
    ui->scaleY->setValue(100);
    ui->scaleZ->setValue(100);
    ui->rotateX->setValue(180);
    ui->rotateY->setValue(180);
    ui->rotateZ->setValue(180);
    cube.reset();
    cube.draw(img);
    update();
}

void Transformation3D::on_wireframe_clicked()
{
    cube.toggleWireframe();
    ui->flip_normal->hide();
    ui->wireframe->isChecked() ? ui->flip_normal->hide() : ui->flip_normal->show();
    ui->wireframe->isChecked() ? ui->draw_points->show() : ui->draw_points->hide();
    cube.draw(img);
    update();
}

void Transformation3D::on_flip_normal_clicked()
{
    cube.toggleNormals();
    cube.draw(img);
    update();
}

void Transformation3D::on_draw_points_clicked()
{
    cube.setCornersVisible();
    cube.draw(img);
    update();
}
