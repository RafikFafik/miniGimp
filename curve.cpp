#include "curve.h"
#include "ui_curve.h"

Curve::Curve(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Curve)
{
    ui->setupUi(this);
    img = new QImage(ui->frame->width(), ui->frame->height(), QImage::Format_RGB32);
    Pixel::clear(img);
    ui->b_spline_extend->hide();
}

Curve::~Curve()
{
    delete ui;
}
void Curve::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(0, 0, *img);
}
void Curve::mousePressEvent(QMouseEvent *event) {
    Point point;
    point.x = event->x();
    point.y = event->y();
    if(!Pixel::inFrameClicked(&point, ui->frame))
        return;

    if(Pixel::pointClicked(&point, CVs)) {
        Pixel::clear(img);
        if(event->buttons() == Qt::MiddleButton) {
            CVs.erase(CVs.begin() + Pixel::getPointIndex(CVs, &point));
        } else {
            int index = Pixel::getPointIndex(CVs, &point);
            CVs.at(index) = point;
        }
    } else {
        if(event->buttons() == Qt::LeftButton)
            CVs.push_back(point);
    }
    bezier_checked ? bezier(img, CVs) : bSpline(img, CVs);
    if(show_cv) {
        Color *color = new Color(0, 255, 0);
        Pixel::drawPoints(img, CVs, color);
        delete color;
    }
    update();
}
void Curve::mouseMoveEvent(QMouseEvent *event) {
    Point point;
    point.x = event->x();
    point.y = event->y();
    if(!Pixel::inFrameClicked(&point, ui->frame))
        return;

    if(Pixel::pointClicked(&point, CVs)) {

        Pixel::clear(img);
        if(event->buttons() == Qt::MiddleButton) {
            CVs.erase(CVs.begin() + Pixel::getPointIndex(CVs, &point));
        } else {
            int index = Pixel::getPointIndex(CVs, &point);
            CVs.at(index) = point;
        }
    }
    bezier_checked ? bezier(img, CVs) : bSpline(img, CVs);
    if(show_cv) {
        Color *color = new Color(0, 255, 0);
        Pixel::drawPoints(img, CVs, color);
        delete color;
    }
    update();
}
void Curve::mouseReleaseEvent(QMouseEvent*) {

}
void Curve::bezier(QImage *img, std::vector<Point> CVs) {
    if(CVs.size() < 4)
        return;
    Color *color = new Color(0, 100, 255);
    double t;
    Point P, Q;
    for(unsigned int j = 0; j < CVs.size() - 3; j += 3) { // -3 to avoid getting tail of non existing vector points
        std::vector<Point>::iterator it = CVs.begin() + j;
        for(unsigned int i = 0; i < segments_count; i++) {
            t = i / (double)segments_count;
            P = calcBezierSegment(t, it);
            Q = calcBezierSegment(t + 1 / (double)segments_count, it);
            Geometry::line(img, &P, &Q, color);
        }
    }
    delete color;
}
void Curve::bSpline(QImage *img, std::vector<Point> CVs) {
    if(CVs.size() < 4)
        return;
    Color *color = new Color(0, 100, 255);
    double t;
    Point P, Q;
    std::vector<Point>::iterator it;
    for(unsigned int j = 0; j < CVs.size() - 3; j++) { // -3 to avoid getting tail of non existing vector points
        it = CVs.begin() + j;
        for(unsigned int i = 0; i < segments_count; i++) {
            t = i / (double)segments_count;
            P = calcBSplineSegment(t, *it, *(it + 1), *(it + 2), *(it + 3));
            Q = calcBSplineSegment(t + 1 / (double)segments_count, *it, *(it + 1), *(it + 2), *(it + 3));
            Geometry::line(img, &P, &Q, color);
        }
    }
    if(b_spline_extend) { // calculate two additional segments in the begining and end of the curve
        it = CVs.begin();
        for(unsigned int i = 0; i < segments_count; i++) {
            t = i / (double)segments_count;
            P = calcBSplineSegment(t, *it, *it, *(it + 1), *(it + 2));
            Q = calcBSplineSegment(t + 1 / (double)segments_count, *it, *it, *(it + 1), *(it + 2));
            Geometry::line(img, &P, &Q, color);
        }
        std::vector<Point>::reverse_iterator rit = CVs.rbegin();
        for(unsigned int i = 0; i < segments_count; i++) {
            t = i / (double)segments_count;
            P = calcBSplineSegment(t, *rit, *rit, *(rit + 1), *(rit + 2));
            Q = calcBSplineSegment(t + 1 / (double)segments_count, *rit, *rit, *(rit + 1), *(rit + 2));
            Geometry::line(img, &P, &Q, color);
        }
    }
    delete color;
}
Point Curve::calcBezierSegment(double t, std::vector<Point>::iterator it) {
    Point result;
    Point P1 = *it;
    Point P2 = *(it + 1);
    Point P3 = *(it + 2);
    Point P4 = *(it + 3);
    result.x = P1.x * (1 - t) * (1 - t) * (1 - t) + P2.x * 3 * (1 - t) * (1 - t) * t + P3.x * 3 * (1 - t) * t * t + P4.x * t * t * t;
    result.y = P1.y * (1 - t) * (1 - t) * (1 - t) + P2.y * 3 * (1 - t) * (1 - t) * t + P3.y * 3 * (1 - t) * t * t + P4.y * t * t * t;

    return result;
}
Point Curve::calcBSplineSegment(double t, Point P1, Point P2, Point P3, Point P4) {
    Point result;
    result.x = P1.x * (1 - t) * (1 - t) * (1 - t) / 6 + (3 * t * t * t - 6 * t * t + 4) * P2.x / 6 + (-3 * t * t * t + 3 * t * (t + 1) + 1) * P3.x / 6 + t * t * t * P4.x / 6;
    result.y = P1.y * (1 - t) * (1 - t) * (1 - t) / 6 + (3 * t * t * t - 6 * t * t + 4) * P2.y / 6 + (-3 * t * t * t + 3 * t * (t + 1) + 1) * P3.y / 6 + t * t * t * P4.y / 6;
    return  result;
}
void Curve::on_reset_clicked() {
    CVs.clear();
    Pixel::clear(img);
    update();
}

void Curve::on_bezier_clicked() {
    ui->b_spline_extend->hide();
    bezier_checked = !bezier_checked;
    b_spline_checked = !b_spline_checked;
    Pixel::clear(img);
    bezier_checked ? bezier(img, CVs) : bSpline(img, CVs);
    if(show_cv) {
        Color *color = new Color (0, 255, 0);
        Pixel::drawPoints(img, CVs, color);
        delete color;
    }
    update();
}

void Curve::on_b_spline_clicked() {
    ui->b_spline_extend->show();
    b_spline_checked = !b_spline_checked;
    bezier_checked = !bezier_checked;
    Pixel::clear(img);
    bezier_checked ? bezier(img, CVs) : bSpline(img, CVs);
    if(show_cv) {
        Color *color = new Color (0, 255, 0);
        Pixel::drawPoints(img, CVs, color);
        delete color;
    }   
    update();
}

void Curve::on_show_cv_clicked() {
    show_cv = !show_cv;
    if(show_cv) {
        Color *color = new Color (0, 255, 0);
        Pixel::drawPoints(img, CVs, color);
        delete color;
    } else {
        Pixel::clear(img);
        bezier_checked ? bezier(img, CVs) : bSpline(img, CVs);
    }
    update();
}

void Curve::on_accuracy_valueChanged(int value) {
    segments_count = value;
    Pixel::clear(img);
    bezier_checked ? bezier(img, CVs) : bSpline(img, CVs);
    if(show_cv) {
        Color *color = new Color (0, 255, 0);
        Pixel::drawPoints(img, CVs, color);
        delete color;
    }
    update();
}

void Curve::on_b_spline_extend_clicked()
{
    b_spline_extend = !b_spline_extend;
    Pixel::clear(img);
    bSpline(img, CVs);
    if(show_cv) {
        Color *color = new Color (0, 255, 0);
        Pixel::drawPoints(img, CVs, color);
        delete color;
    }
    update();
}
