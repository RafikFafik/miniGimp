#include "texture.h"
#include "ui_texture.h"

Texture::Texture(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Texture)
{
    ui->setupUi(this);
    img_left = new QImage(":/pictures/ursus.jpg");
    img_left_restore = new QImage(":/pictures/ursus.jpg");
    img_right = new QImage(ui->frame_right->width(), ui->frame_right->height(), QImage::Format_RGB32);
    update();
}

Texture::~Texture()
{
    delete ui;
}
void Texture::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(ui->frame_left->x(), ui->frame_left->y(), *img_left);
    p.drawImage(ui->frame_right->x(), ui->frame_right->y(), *img_right);
}
void Texture::mousePressEvent(QMouseEvent *event)
{
    *img_left_restore = img_left->copy();
    color = new Color(0, 255, 60);
    point = new Point;
    point->x = event->x();
    point->y = event->y();
    if(inFrameClicked(point, ui->frame_left))
        frameAction(img_left, ui->frame_left, points_left, point, color);
    update();
//    if(inFrameClicked(point, ui->frame_right))
//        frameAction();
}
void Texture::mouseMoveEvent(QMouseEvent *event)
{
    *img_left = img_left_restore->copy();
    int x = event->x();
    int y = event->y();
    point->x = x;
    point->y = y;
    if(inFrameClicked(point, ui->frame_left))
        if(point_index >= 0) {
            points_left.at(point_index).x = point->x;
            points_left.at(point_index).y = point->y;
        }
        frameAction(img_left, ui->frame_left, points_left, point, color);
    update();
}
void Texture::mouseReleaseEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
    point->x = x;
    point->y = y;
    if(inFrameClicked(point, ui->frame_left)) {
        color->red = 255;
        color->green = 10;
        frameAction(img_left, ui->frame_left, points_left, point, color);
        if(points_left.size() < 3)
            points_left.push_back(*point);
    }
    update();
    point_index = -1;
    delete color;
    delete point;
}
bool Texture::inFrameClicked(Point *point, QFrame *frame) {
    if(point->x >= frame->x() && point->x < frame->width() && point->y >= frame->y() && point->y < frame->width())
           return true;
    return false;
}
void Texture::frameAction(QImage *img, QFrame *frame, std::vector<Point> &points,  Point *point, Color *color) {
    if(Pixel::pointClicked(point, points)) {
        point_index = Pixel::getPointIndex(points, point);
        Pixel::drawPoint(img->bits(), point, frame->width(), color);
        qDebug() << point_index;
        if(point_index < 0)
            return;
    } else {
        if(points.size() < 3) {
            Pixel::drawPoint(img->bits(), point, frame->width(), color);
        }
    }

}
