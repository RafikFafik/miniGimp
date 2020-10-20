#include "morphing.h"
#include "ui_morphing.h"

Morphing::Morphing(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Morphing)
{
    ui->setupUi(this);
    keyframe_begin = new QImage(":/pictures/ciapek.jpg");
    keyframe_end = new QImage(":/pictures/ursus.jpg");
    img = new QImage(":/pictures/ciapek.jpg");
    animation = new QImage(ui->frame_right->width(), ui->frame_right->height(), QImage::Format_RGB32);
    Pixel::clear(animation);
    update();
}

Morphing::~Morphing()
{
    delete ui;
}
void Morphing::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(ui->frame_left->x(), ui->frame_left->y(), *img);
    p.drawImage(ui->frame_right->x(), ui->frame_right->y(), *animation);
}
void Morphing::mousePressEvent(QMouseEvent *event)
{

    color = new Color(0, 255, 60);
    point = new Point;
    point->x = event->x();
    point->y = event->y();

    if(Pixel::inFrameClicked(point, ui->frame_left)) {
        if(ui->keyframe->value()) {
            *img = keyframe_end->copy();
            frameAction(img, ui->frame_left, points_end, point, color);
        } else {
            *img = keyframe_begin->copy();
            frameAction(img, ui->frame_left, points_begin, point, color);
        }
        morphing();
        update();
    }  
}
void Morphing::mouseMoveEvent(QMouseEvent *event)
{
    point->x = event->x();
    point->y = event->y();
    if(Pixel::inFrameClicked(point, ui->frame_left)) {
        if(ui->keyframe->value()) {
            *img = keyframe_end->copy();
            frameAction(img, ui->frame_left, points_end, point, color);
        } else {
            *img = keyframe_begin->copy();
            frameAction(img, ui->frame_left, points_begin, point, color);
        }
        morphing();
        update();
    }
}
void Morphing::mouseReleaseEvent(QMouseEvent *event)
{
    point->x = event->x();
    point->y = event->y();
    if(Pixel::inFrameClicked(point, ui->frame_left)) {
        if(ui->keyframe->value()) {
            *img = keyframe_end->copy();
            renderTriangle(img, ui->frame_left, points_end, color, -1);
        } else {
            *img = keyframe_begin->copy();
            renderTriangle(img, ui->frame_left, points_begin, color, -1);
        }
        update();
        delete color;
        delete point;
    }
}

void Morphing::frameAction(QImage *img, QFrame *frame, std::vector<Point> &points,  Point *point, Color *color) {
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
void Morphing::renderTriangle(QImage *img, QFrame *frame, std::vector<Point> &points, Color *color, int point_index) {
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

void Morphing::morphing() {
    if(points_end.size() != 3 || points_begin.size() != 3)
            return;
    Pixel::clear(animation);
    Point A = points_begin.at(0);
    Point B = points_begin.at(1);
    Point C = points_begin.at(2);
    Point Aprim = points_end.at(0);
    Point Bprim = points_end.at(1);
    Point Cprim = points_end.at(2);

    Point An = calcPoint(A, Aprim);
    Point Bn = calcPoint(B, Bprim);
    Point Cn = calcPoint(C, Cprim);
    std::vector<Point> nTriangle;
    nTriangle.push_back(An);
    nTriangle.push_back(Bn);
    nTriangle.push_back(Cn);
    int top = Pixel::getTop(nTriangle);
    int bottom = Pixel::getBottom(nTriangle);
    int left = Pixel::getLeft(nTriangle);
    int right = Pixel::getRight(nTriangle);
    Color *c1 = new Color;
    Color *c2 = new Color;
    double u, v, w;
    double detW = calcW(An, Bn, Cn);
    int width = ui->frame_right->width();
    unsigned char *img = animation->bits();
    unsigned char *keyframe_begin_ptr = keyframe_begin->bits();
    unsigned char *keyframe_end_ptr = keyframe_end->bits();
    double x1, x2, y1, y2;
    for(int i = top; i <= bottom; i++) {
        for(int j = left; j <= right; j++) {
            v = calcWv(j, i, An, Cn) / detW;
            w = calcWw(j, i, An, Bn) / detW;
            u = 1 - v - w;
            x1 = u * A.x + v * B.x + w * C.x;
            y1 = u * A.y + v * B.y + w * C.y;
            x2 = u * Aprim.x + v * Bprim.x + w * Cprim.x;
            y2 = u * Aprim.y + v * Bprim.y + w * Cprim.y;

            if(outsideTriangle(v, w, u))
                continue;
            c1 = Pixel::interpolate(keyframe_begin_ptr, ui->frame_left->width(), x1, y1, c1);
            c2 = Pixel::interpolate(keyframe_end_ptr, ui->frame_left->width(), x2, y2, c2);
            c1->red = (1 - ratio) * c1->red + ratio * c2->red;
            c1->green= (1 - ratio) * c1->green + ratio * c2->green;
            c1->blue = (1 - ratio) * c1->blue + ratio * c2->blue;
            img[width * 4 * i + 4 * j + 1] = c1->red;
            img[width * 4 * i + 4 * j + 2] = c1->green;
            img[width * 4 * i + 4 * j] = c1->blue;
        }
    }
    delete c1;
    delete c2;
    update();

}

Point Morphing::calcPoint(Point P, Point Pprim) {

    double x = (1 - ratio) * P.x + ratio * Pprim.x;
    double y = (1 - ratio) * P.y + ratio * Pprim.y;
    Point p;
    p.x = x;
    p.y = y;
    return p;
}
//void Morphing::on_reset_clicked()
//{
//    *img_left = img_left_restore->copy();
//    Pixel::clear(img_right);
//    points_left.clear();
//    points_right.clear();
//    update();
//}
double Morphing::calcWv(int x, int y, Point A, Point C) {
    double Wv = ((x - A.x) * (C.y -A.y)) - ((C.x - A.x) * (y - A.y));
    return Wv;
}
double Morphing::calcWw(int x, int y, Point A, Point B) {
    double Ww = ((B.x - A.x) * (y - A.y)) - ((x - A.x) * (B.y - A.y));
    return Ww;
}
double Morphing::calcW(Point A, Point B, Point C) {
    double w = (((B.x - A.x) * (C.y - A.y)) - ((C.x - A.x) * (B.y - A.y)));
    return w;
}
bool Morphing::outsideTriangle(double v, double w, double u) {
    if(v <= 0 || v >= 1 || w <= 0 || w >= 1 || u <= 0 || u >= 1)
        return true;
    return false;
}

void Morphing::on_keyframe_valueChanged(int value)
{
    Color *c = new Color(0, 255, 0);

    if(value) {
        *img = keyframe_end->copy();
        renderTriangle(img, ui->frame_left, points_end, c, -1);
    } else {
        *img = keyframe_begin->copy();
        renderTriangle(img, ui->frame_left, points_begin, c, -1);
    }
    delete c;
    update();
}

void Morphing::on_animation_valueChanged()
{
    double n = ui->animation->value();
    double N = ui->animation->maximum();
    ratio = n / N;
    color = new Color(0, 255, 60);
    morphing();
    delete  color;
    update();
}


void Morphing::on_frames_count_valueChanged(int value)
{
    ui->animation->setMaximum(value);

    morphing();
    update();
}
void Morphing::play(){
    int frames_count = ui->animation->maximum();
    QTimer  *t= new QTimer(this);
    t->setInterval(frames_count / 500);
    int i = 0;
    connect(t, &QTimer::timeout, [=]() mutable{
        morphing();
        i++;
        ui->animation->setValue(i);
        if(i >= frames_count){
            t->stop();
        }
        update();

    });

    t->start();
}

void Morphing::on_play_clicked()
{
    play();
}

void Morphing::on_reset_clicked()
{
    if(ui->keyframe->value()) {
        *img = keyframe_end->copy();
    } else {
        *img = keyframe_begin->copy();
    }
    points_end.clear();
    points_begin.clear();
    Pixel::clear(animation);
    ui->animation->setValue(0);
    update();
}
