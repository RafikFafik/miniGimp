#include "paint.h"
#include "ui_paint.h"

Paint::Paint(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Paint)
{

    ui->setupUi(this);

    img = new QImage(ui->frame->width(), ui->frame->height(), QImage::Format_RGB32);
    fg_color_field = new QImage(ui->fg_color->width(), ui->fg_color->height(), QImage::Format_RGB32);
    bg_color_field = new QImage(ui->bg_color->width(), ui->bg_color->height(), QImage::Format_RGB32);
    Pixel::clear(img);
    Pixel::fill(fg_color_field, lmb_color);
    Pixel::clear(bg_color_field);
}

Paint::~Paint()
{
    delete ui;
}

void Paint::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(0, 0, *img);
    p.drawImage(ui->fg_color->x(), ui->fg_color->height() + 210, *fg_color_field);
    p.drawImage(ui->bg_color->x(), ui->bg_color->height() + 210, *bg_color_field);
}
void Paint::mousePressEvent(QMouseEvent *event) {
    press = new Point;
    move = new Point;
    imgs.push_back(img->copy());
    press->x = event->x(); // offset because of QT
    press->y = event->y(); // offset because of QT
    if(Pixel::inFrameClicked(press, ui->fg_color)) {
        QColor qtcolor = QColorDialog::getColor();
        lmb_color = Pixel::convertColor(qtcolor);
        Pixel::fill(fg_color_field, lmb_color);
    }
    else if (Pixel::inFrameClicked(press, ui->bg_color)) {
        QColor qtcolor = QColorDialog::getColor();
        rmb_color = Pixel::convertColor(qtcolor);
        Pixel::fill(bg_color_field, rmb_color);
    }
    else if(Pixel::inFrameClicked(press, ui->frame)) {
        Color *active_color = new Color(255, 255, 255);
        if(event->buttons() == Qt::LeftButton)
            active_color = lmb_color;
        else if(event->buttons() == Qt::RightButton)
            active_color = rmb_color;

        if(mode == FLOOD_FILL)
            floodFill(press, active_color);
    }
    update();
}
void Paint::mouseMoveEvent(QMouseEvent *event) {
    if(mode == FLOOD_FILL)
        return;
    if(mode != PEN)
        *img = imgs.back();
    Color *active_color = new Color(255, 255, 255);
    move->x = event->x();
    move->y =  event->y();
    if(event->buttons() == Qt::LeftButton)
        active_color = lmb_color;
    else if(event->buttons() == Qt::RightButton)
        active_color = rmb_color;

    if(mode == PEN)
        Pixel::setPixelColor(img, move, active_color);
    else if(mode == LINE)
        Geometry::line(img, press, move, active_color);
    else if(mode == CIRCLE)
        Geometry::circle(img, press, move, active_color);
    else if(mode == ELIPSE)
        Geometry::elipse(img, press, move, active_color, verticles_count);
    update();
}
void Paint::mouseReleaseEvent(QMouseEvent*)
{
    delete press;
    delete move;
}
void Paint::floodFill(Point *incoming_point, Color *incoming_color) {
    std::stack<Point> stack;
    Point current_point;
    Point point(incoming_point->x, incoming_point->y);
    Color color(incoming_color->red, incoming_color->green, incoming_color->blue);
    Color background = Pixel::getPixelColor(img->bits(), img->width(), point);
    if(background == color)
        return;
    stack.push(point);
    while(!stack.empty()) {
        current_point = stack.top();
        stack.pop();
        if(Pixel::outOfImage(&current_point, img->width(), img->height()) || Pixel::getPixelColor(img->bits(), img->width(), current_point) != background)
            continue;
        Pixel::setPixelColor(img, &current_point, &color);
        Point left(current_point.x - 1, current_point.y);
        Point right(current_point.x + 1, current_point.y);
        Point top(current_point.x, current_point.y - 1);
        Point bottom(current_point.x, current_point.y + 1);
        stack.push(left);
        stack.push(right);
        stack.push(top);
        stack.push(bottom);

    }
}
void Paint::on_clear_clicked()
{
    Pixel::clear(img);
    update();
}
void Paint::drawLine(Color *color)
{
    Geometry::line(img, press, move, color);
}
void Paint::on_undo_clicked()
{
    if(imgs.empty())
        return;
    *img = imgs.back();
    imgs.pop_back();
    update();
}
void Paint::on_flood_fill_clicked() {
    mode = FLOOD_FILL;
    ui->verticles->hide();
}
void Paint::on_pen_clicked() {
    mode = PEN;
    ui->verticles->hide();
}

void Paint::on_line_clicked() {
    mode = LINE;
    ui->verticles->hide();
}

void Paint::on_circle_clicked() {
    mode = CIRCLE;
    ui->verticles->hide();
}

void Paint::on_elipse_clicked() {
    mode = ELIPSE;
    ui->verticles->show();
}
void Paint::on_verticles_valueChanged(int value) {
    verticles_count = value;
}
