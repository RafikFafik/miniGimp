#include "morphology.h"
#include "ui_morphology.h"

Morphology::Morphology(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Morphology)
{
    ui->setupUi(this);
    img = new QImage(":/pictures/ursus.jpg");
    img_restore = new QImage(":/pictures/ursus.jpg");
    tmp = new QImage(ui->frame->width(), ui->frame->height(), QImage::Format_RGB32);
    Pixel::monochromatic(img);
    width = ui->frame->width();
    height = ui->frame->height();
}

Morphology::~Morphology()
{
    delete ui;
}
void Morphology::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(0, 0, *img);
}
bool Morphology::checkPixel(int x, int y, int searched_color) {
    if(img->bits()[width*4*x + 4*y] == searched_color   && img->bits()[width*4*x + 4*y + 1] == searched_color && img->bits()[width*4*x + 4*y + 2] == searched_color)
        return true;
    return false;
}
bool Morphology::checkMask(bool cross_mask, int x, int y, int searched_color) {
    bool x_min = false;
    bool x_max = false;
    bool y_min = false;
    bool y_max = false;
    if(x == 0)
        x_min = true;
    if(x == this->width - 1)
        x_max = true;
    if(y == 0)
        y_min = true;
    if(y == this->height - 1)
        y_max = true;

    if(cross_mask) {
        if((!x_min && checkPixel(x - 1, y, searched_color)) ||
           (!x_max && checkPixel(x + 1, y, searched_color)) ||
           (!y_min && checkPixel(x, y - 1, searched_color)) ||
           (!y_max && checkPixel(x, y + 1, searched_color)))
           return true;
        return false;
    }
    else {
        if(((!(x_min || y_min)) && checkPixel(x - 1, y - 1, searched_color)) ||
           (!y_min && checkPixel(x, y - 1, searched_color)) ||
           ((!(x_max || y_min)) && checkPixel(x + 1, y - 1, searched_color)) ||
           (!x_min && checkPixel(x - 1, y, searched_color)) ||
           (!x_max && checkPixel(x + 1, y, searched_color)) ||
           ((!(x_min || y_max)) && checkPixel(x - 1, y + 1, searched_color)) ||
           (!y_max && checkPixel(x, y + 1, searched_color)) ||
           ((!(x_max || y_max)) && checkPixel(x + 1, y + 1, searched_color)))
            return true;
        return  false;
    }
}
void Morphology::draw(int searched_color) {
    int current_point;
    searched_color ? current_point = 0 : current_point = 255;
    *tmp = img->copy();
    unsigned char *ptr;
    unsigned char *org;
    int i, j;
    ptr = tmp->bits();
    org = img->bits();
    for(i=0; i<height; i++) {
        for(j=0; j<width; j++) {
            if(org[width*4*i + 4*j] == current_point   && org[width*4*i + 4*j + 1] == current_point && org[width*4*i + 4*j + 2] == current_point) {
                if(checkMask(cross_mask, i, j, searched_color)) {
                    ptr[width*4*i + 4*j] = searched_color;
                    ptr[width*4*i + 4*j + 1] = searched_color;
                    ptr[width*4*i + 4*j + 2] = searched_color;
                }

            }
        }
    }
    *img = tmp->copy();
    update();
}
void Morphology::on_closing_clicked() {
    on_dilation_clicked();
    on_erosion_clicked();
}

void Morphology::on_dilation_clicked() {
    draw(0);
}

void Morphology::on_erosion_clicked() {
    draw(255);
}

void Morphology::on_opening_clicked() {
    on_erosion_clicked();
    on_dilation_clicked();
}

void Morphology::on_restore_clicked()
{
    *img = img_restore->copy();
    Pixel::monochromatic(img);
    update();
}

void Morphology::on_cross_clicked()
{
    cross_mask = true;
}

void Morphology::on_square_clicked()
{
    cross_mask = false;
}
void Morphology::on_loadImage_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Images (*.jpg *.png *.jpeg *.bmp *.gif)"));
        if(QString::compare(file,QString()) != 0){
            img = new QImage(file);
            img_restore = new QImage(file);
            Pixel::monochromatic(img);
        }
}
