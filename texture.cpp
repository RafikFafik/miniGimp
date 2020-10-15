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
    Pixel::clear(img_right);
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

    color = new Color(0, 255, 60);
    point = new Point;
    point->x = event->x();
    point->y = event->y();

    if(inFrameClicked(point, ui->frame_left)) {
        *img_left = img_left_restore->copy();
        frameAction(img_left, ui->frame_left, points_left, point, color);
    }
    if(inFrameClicked(point, ui->frame_right)) {
        frameAction(img_right, ui->frame_right, points_right, point, color);
    }
    texture();
    update();
}
void Texture::mouseMoveEvent(QMouseEvent *event)
{

    point->x = event->x();
    point->y = event->y();
    if(inFrameClicked(point, ui->frame_left)) {
        *img_left = img_left_restore->copy();
        frameAction(img_left, ui->frame_left, points_left, point, color);
    }
    if(inFrameClicked(point, ui->frame_right)) {
        Pixel::clear(img_right);
        frameAction(img_right, ui->frame_right, points_right, point, color);
    }
    texture();
    update();
}
void Texture::mouseReleaseEvent(QMouseEvent *event)
{
    point->x = event->x();
    point->y = event->y();

    color->red = 0;
    color->blue = 60;
    color->green = 255;

    if(inFrameClicked(point, ui->frame_left)) {
        renderTriangle(img_left, ui->frame_left, points_left, color, -1);
    }
    if(inFrameClicked(point, ui->frame_right)) {
        renderTriangle(img_right, ui->frame_right, points_right, color, -1);
    }
    update();
    delete color;
    delete point;

}
bool Texture::inFrameClicked(Point *point, QFrame *frame) {
    if(point->x >= frame->x() && point->x < frame->x() + frame->width() && point->y >= frame->y() && point->y < frame->y() + frame->width())
           return true;
    return false;
}
void Texture::frameAction(QImage *img, QFrame *frame, std::vector<Point> &points,  Point *point, Color *color) {
    int point_index = -1;
    if(Pixel::pointClicked(point, points)) {
        point_index = Pixel::getPointIndex(points, point);
        points.at(point_index).x = point->x;
        points.at(point_index).y = point->y;
        renderTriangle(img, frame, points, color, point_index);
    } else {
        if(points.size() < 3) {
            points.push_back(*point);
            point_index = points.size() - 1;
        }
        renderTriangle(img, frame, points, color, point_index);
    }
}
void Texture::renderTriangle(QImage *img, QFrame *frame, std::vector<Point> &points, Color *color, int point_index) {
    Color *green = new Color(0, 255, 0);
    if(points.size() > 1) {
        for(unsigned int i = 0; i < points.size() - 1; i++) {
            Geometry::line(img, &points.at(i), &points.at(i + 1), green);
        }
        if(points.size() > 2)
            Geometry::line(img, &points.at(0), &points.at(2), green);
    }
    delete green;
    Point *p = new Point;
    for(std::vector<Point>::iterator it = points.begin(); it != points.end(); it++) {
        p->x = it->x;
        p->y = it->y;
        if(it-points.begin() == point_index) {
            color->red = 255;
            color->blue = 0;
            color->green = 0;
        } else {
            color->red = 0;
            color->blue = 60;
            color->green = 255;
        }

        Pixel::drawPoint(img->bits(), p, frame->width(), color);
    }
    delete p;

}
void Texture::texture() {
    if(points_left.size() != 3 || points_right.size() != 3)
            return;
    int top = Pixel::getTop(points_right);
    int bottom = Pixel::getBottom(points_right);
    int left = Pixel::getLeft(points_right);
    int right = Pixel::getRight(points_right);
    Point A = points_right.at(0);
    Point B = points_right.at(1);
    Point C = points_right.at(2);
    Point At = points_left.at(0);
    Point Bt = points_left.at(1);
    Point Ct = points_left.at(2);
    Color *interpolated_color = new Color;
    double u, v, w, x, y;
    double detW = calcW(A, B, C);
    int width = ui->frame_right->width();
    unsigned char *img = img_right->bits();
    unsigned char *texture = img_left_restore->bits();
    for(int i = top; i <= bottom; i++) {
        for(int j = left; j <= right; j++) {
            v = calcWv(j, i, A, C) / detW;
            w = calcWw(j, i, A, B) / detW;
            u = 1 - v - w;
            x = u * At.x + v * Bt.x + w * Ct.x;
            y = u * At.y + v * Bt.y + w * Ct.y;
            if(outsideTriangle(v, w, u))
                continue;
            if(interpolation_enabled)
                interpolated_color = Pixel::interpolate(texture, ui->frame_left->width(), x, y, interpolated_color);
            else {
                interpolated_color->red = texture[width * 4 * (int)y + 4 * (int)x + 1];
                interpolated_color->green = texture[width * 4 * (int)y + 4 * (int)x + 2];
                interpolated_color->blue = texture[width * 4 * (int)y + 4 * (int)x];
            }
            img[width * 4 * i + 4 * j + 1] = interpolated_color->red;
            img[width * 4 * i + 4 * j + 2] = interpolated_color->green;
            img[width * 4 * i + 4 * j] = interpolated_color->blue;
        }
    }
    delete interpolated_color;

}
void Texture::on_reset_clicked()
{
    *img_left = img_left_restore->copy();
    Pixel::clear(img_right);
    points_left.clear();
    points_right.clear();
    update();
}
double Texture::calcWv(int x, int y, Point A, Point C) {
    double Wv = ((x - A.x) * (C.y -A.y)) - ((C.x - A.x) * (y - A.y));
    return Wv;
}
double Texture::calcWw(int x, int y, Point A, Point B) {
    double Ww = ((B.x - A.x) * (y - A.y)) - ((x - A.x) * (B.y - A.y));
    return Ww;
}
double Texture::calcW(Point A, Point B, Point C) {
    double w = (((B.x - A.x) * (C.y - A.y)) - ((C.x - A.x) * (B.y - A.y)));
    return w;
}
bool Texture::outsideTriangle(double v, double w, double u) {
    if(v <= 0 || v >= 1 || w <= 0 || w >= 1 || u <= 0 || u >= 1)
        return true;
    return false;
}

void Texture::debug() {
    int top = Pixel::getTop(points_right);
    int bottom = Pixel::getBottom(points_right);
    int left = Pixel::getLeft(points_right);
    int right = Pixel::getRight(points_right);
    Point *p = new Point;
    p->x = 750;
    p->y = top;
    Pixel::drawPoint(img_right->bits(), p, 500, new Color(255, 165, 0));
    p->x = 750;
    p->y = bottom;
    Pixel::drawPoint(img_right->bits(), p, 500, new Color(199, 21, 133));
    p->x = left;
    p->y = 250;
    Pixel::drawPoint(img_right->bits(), p, 500, new Color(0, 0, 139));
    p->x = right;
    p->y = 250;
    Pixel::drawPoint(img_right->bits(), p, 500, new Color(139, 0, 0));
    delete p;
}

void Texture::on_interpolation_enabled_clicked()
{
    interpolation_enabled = !interpolation_enabled;
    texture();
    update();
}
