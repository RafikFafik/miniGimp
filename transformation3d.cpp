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

void Transformation3D::on_checkBox_clicked()
{
    cube.setCornersVisible();
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
    double y = 100 / (double)ui->scaleY->value();
    double x = 100 / (double)value;
    double z = 100 / (double)ui->scaleZ->value();
    cube.scale(x, y, z);
    cube.draw(img);
    update();
}

void Transformation3D::on_scaleY_valueChanged(int value)
{
    double y = 100 / (double)value;
    double x = 100 / (double)ui->scaleX->value();
    double z = 100 / (double)ui->scaleZ->value();
    cube.scale(x, y, z);
    cube.draw(img);
    update();
}

void Transformation3D::on_scaleZ_valueChanged(int value)
{
    double y = 100 / (double)ui->scaleY->value();
    double x = 100 / (double)ui->scaleX->value();
    double z = 100 / (double)value;
    cube.scale(x, y, z);
    cube.draw(img);
    update();
}

void Transformation3D::on_rotateX_valueChanged(int value)
{
    double xAxis = -(M_PI * (value - 180)/(double)180);
    double yAxis = -(M_PI * (ui->rotateY->value() - 180)/(double)180);
    double zAxis = -(M_PI * (ui->rotateZ->value() - 180)/(double)180);
//    cube.rotate(xAxis, yAxis, zAxis);
}

void Transformation3D::on_rotateY_valueChanged(int value)
{

}

void Transformation3D::on_rotateZ_valueChanged(int value)
{
    double angle = value / 180.0 * M_PI;
    cube.rotateZ(angle);
    cube.draw(img);
    update();
}
