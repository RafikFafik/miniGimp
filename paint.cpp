#include "paint.h"
#include "ui_paint.h"

Paint::Paint(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Paint)
{

    ui->setupUi(this);

    img = new QImage(ui->frame->width(), ui->frame->height(), QImage::Format_RGB32);
    Pixel::clear(img);
}

Paint::~Paint()
{
    delete ui;
}

void Paint::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(0, 0, *img);
}
void Paint::mousePressEvent(QMouseEvent *event)
{
    imgs.push_back(img->copy());
    press.setPoint(event->x(), event->y());
    if(!insideFrame(ui->frame, press))
        return;
}
void Paint::mouseMoveEvent(QMouseEvent *event)
{
    *img = imgs.back();
    move.setPoint(event->x(), event->y());
    if(!(insideFrame(ui->frame, move)&&(insideFrame(ui->frame, press))))
        return;
    Color *color = new Color();
    color->red = 0;
    color->green = 0;
    color->blue = 0;
    Pixel::setPixelColor(img, move, color);
    delete color;
    draw();
}

bool Paint::insideFrame(QFrame *frame, Point point)
{
    int x = point.getX();
    int y = point.getY();
    int width = frame->width();
    int height = frame->height();
    if(x > width || y > height || x < frame->x() || y < frame->y())
        return  false;
    return true;
}

void Paint::on_clear_clicked()
{
    Pixel::clear(img);
    update();
}
void Paint::draw()
{
    Color *color = new Color(255, 255, 255);
    Geometry::line(img, press, move, color);
    update();
    delete color;
}

void Paint::on_pen_clicked()
{
    mode = 0;
}

void Paint::on_line_clicked()
{
    mode = 1;
}

void Paint::on_undo_clicked()
{
    if(imgs.empty())
        return;
    *img = imgs.back();
    imgs.pop_back();
    update();
}
