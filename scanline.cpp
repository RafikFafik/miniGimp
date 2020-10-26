#include "scanline.h"
#include "ui_scanline.h"

ScanLine::ScanLine(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScanLine)
{
    ui->setupUi(this);
    img = new QImage(ui->frame->width(), ui->frame->height(), QImage::Format_RGB32);
}
ScanLine::~ScanLine()
{
    delete ui;
}
void ScanLine::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(0, 0, *img);
}
void ScanLine::mousePressEvent(QMouseEvent *event) {
    Point point;
    Color *color = new Color(0, 255, 0);
    point.x = event->x();
    point.y = event->y();
    if(!Pixel::inFrameClicked(&point, ui->frame))
        return;

    if(Pixel::pointClicked(&point, verticles)) {
        unsigned int index = Pixel::getPointIndex(verticles, &point);
        verticles.at(index) = point;
        Pixel::clear(img);
        drawLines(verticles);
        if(control_verticles)
            Pixel::drawPoints(img, verticles, color);
        if(verticles.size() > 2 && Pixel::twoPointsInSamePosition(&verticles.at(0), &verticles.at(verticles.size() - 1))) {
            closed_circuit = true;
            if(index == 0 || index == verticles.size() - 1) {
                verticles.at(0) = point;
                verticles.at(verticles.size() - 1) = point;
            }
        }
    } else {
        if(closed_circuit)
            return;
        verticles.push_back(point);
        Pixel::drawPoint(img->bits(), &point, img->width(), color);
        drawLines(verticles);
    }

    if(closed_circuit) {
        scanline();
        drawLines(verticles);
        if(control_verticles)
            Pixel::drawPoints(img, verticles, color);
    }
    delete color;
    update();
}
void ScanLine::mouseMoveEvent(QMouseEvent *event) {
    Point point;
    Color *color = new Color(0, 255, 0);
    point.x = event->x();
    point.y = event->y();
    if(!Pixel::inFrameClicked(&point, ui->frame))
        return;

    if(Pixel::pointClicked(&point, verticles)) {
        unsigned int index = Pixel::getPointIndex(verticles, &point);
        verticles.at(index) = point;
        Pixel::clear(img);
        drawLines(verticles);
        if(control_verticles)
            Pixel::drawPoints(img, verticles, color);
        if(verticles.size() > 2 && Pixel::twoPointsInSamePosition(&verticles.at(0), &verticles.at(verticles.size() - 1))) {
            closed_circuit = true;
            if(index == 0 || index == verticles.size() - 1) {
                verticles.at(0) = point;
                verticles.at(verticles.size() - 1) = point;
            }
        }

    }
    if(closed_circuit) {
        scanline();
        drawLines(verticles);
        if(control_verticles)
            Pixel::drawPoints(img, verticles, color);
    }
    delete color;
    update();
}
void ScanLine::mouseReleaseEvent(QMouseEvent*)
{

}
void ScanLine::drawLines(std::vector<Point> verticles) {
    if(verticles.size() < 2)
        return;
    Color *color = new Color(0, 255, 0);
    for(unsigned int i = 0; i < verticles.size() - 1; i++)
        Geometry::line(img, &verticles.at(i), &verticles.at(i + 1), color);
    delete color;
}
void ScanLine::scanline() {
    if(verticles.size() < 3)
        return;
    Color *color = new Color(0, 0, 255);
    Point *start = new Point;
    Point *end = new Point;
    int top = Pixel::getTop(verticles);
    int bottom = Pixel::getBottom(verticles);
    std::vector<int> intersections;
    qDebug() << "Scanline start";
    for(int i = top; i < bottom; i++) {
        intersections.clear();
        intersections = Pixel::getIntersections(verticles, i, intersections);
        if(intersections.size() < 2)
            continue;
        std::sort(intersections.begin(), intersections.end());
        for(unsigned int j = 0; j < intersections.size() - 1; j += 2) {
            start->x = intersections.at(j);
            start->y = i;
            end->x = intersections.at(j + 1);
            end->y = i;
            Geometry::line(img, start, end, color);
        }
    }
    delete color;
    delete start;
    delete end;
}
void ScanLine::on_cv_clicked() {
    control_verticles = !control_verticles;
    Pixel::clear(img);
    Color *color = new Color(0, 255, 0);
    drawLines(verticles);
    if(control_verticles) {
        Pixel::drawPoints(img, verticles, color);
    }
    if(closed_circuit) {
        scanline();
        drawLines(verticles);
        if(control_verticles)
            Pixel::drawPoints(img, verticles, color);
    }
    delete color;
    update();
}

void ScanLine::on_reset_clicked()
{
    verticles.clear();
    Pixel::clear(img);
    closed_circuit = false;
    update();
}
