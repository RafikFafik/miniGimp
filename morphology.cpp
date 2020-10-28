#include "morphology.h"
#include "ui_morphology.h"

Morphology::Morphology(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Morphology)
{
    ui->setupUi(this);
    img_restore = new QImage(":/pictures/ursus.jpg");
    img = new QImage(":/pictures/ursus.jpg");
    tmp = new QImage(":/pictures/ursus.jpg");
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
                if(checkMask(cross_kernel, i, j, searched_color)) {
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
void Morphology::dilation() {
    Point *pixel_pos = new Point;
    Color *color_to_check = new Color(0, 0, 0);
    *tmp = img->copy();
    for(int i = 0; i < ui->frame->height(); i++) {
        for(int j = 0; j < ui->frame->width(); j++) {
            pixel_pos->setXY(j, i);
            if(cross_kernel) {
                if(matchesCrossKernel(img, pixel_pos, color_to_check))
                    Pixel::setPixelColor(tmp, pixel_pos, color_to_check);
            } else {
                if(matchesSquareKernel(img, pixel_pos, color_to_check))
                    Pixel::setPixelColor(tmp, pixel_pos, color_to_check);
            }

        }
    }
    *img = tmp->copy();
    delete color_to_check;
    delete pixel_pos;
}
void Morphology::erosion() {
    Point *pixel_pos = new Point;
    Color *color_to_check = new Color(255, 255, 255);
    *tmp = img->copy();
    for(int i = 0; i < ui->frame->height(); i++) {
        for(int j = 0; j < ui->frame->width(); j++) {
            pixel_pos->setXY(j, i);
            if(cross_kernel) {
                if(matchesCrossKernel(img, pixel_pos, color_to_check))
                    Pixel::setPixelColor(tmp, pixel_pos, color_to_check);
            } else {
                if(matchesSquareKernel(img, pixel_pos, color_to_check))
                    Pixel::setPixelColor(tmp, pixel_pos, color_to_check);
            }

        }
    }
    *img = tmp->copy();
    delete color_to_check;
    delete pixel_pos;
}
bool Morphology::matchesCrossKernel(QImage *image, Point *point, Color *color_to_check) {
    unsigned char *img_pointer = image->bits();
    int img_width = img->width();
    int img_height = img->height();
    Point left, right, top, bottom;
    left = right = top = bottom = *point;
    left.x -= 1;
    right.x += 1;
    top.y -= 1;
    bottom.y += 1;
    if((!Pixel::outOfImage(&left, img_width, img_height) && Pixel::getPixelColor(img_pointer, img_width, left).red == color_to_check->red )|| // red == green == blue == 0 || red == green == blue == 1
       (!Pixel::outOfImage(&right, img_width, img_height) && Pixel::getPixelColor(img_pointer, img_width, right).red == color_to_check->red) ||
       (!Pixel::outOfImage(&top, img_width, img_height) && Pixel::getPixelColor(img_pointer, img_width, top).red == color_to_check->red) ||
       (!Pixel::outOfImage(&bottom, img_width, img_height) && Pixel::getPixelColor(img_pointer, img_width, bottom).red == color_to_check->red)
      )
        return true;

    return false;
}
bool Morphology::matchesSquareKernel(QImage *image, Point *point, Color *color_to_check) {
    unsigned char *img_pointer = image->bits();
    int img_width = img->width();
    int img_height = img->height();
    Point left, right, top, bottom, left_top, right_top, left_bottom, right_bottom;
    left = right = top = bottom = left_top = right_top = left_bottom = right_bottom = *point;
    left.x -= 1;
    right.x += 1;
    top.y -= 1;
    bottom.y += 1;
    left_top.x -= 1;
    left_top.y -= 1;
    right_top.x += 1;
    right_top.y -= 1;
    left_bottom.x -= 1;
    left_bottom.y += 1;
    right_bottom.x += 1;
    right_bottom.y += 1;
    if((!Pixel::outOfImage(&left, img_width, img_height) && Pixel::getPixelColor(img_pointer, img_width, left).red == color_to_check->red) ||
       (!Pixel::outOfImage(&right, img_width, img_height) && Pixel::getPixelColor(img_pointer, img_width, right).red == color_to_check->red) ||
       (!Pixel::outOfImage(&top, img_width, img_height) && Pixel::getPixelColor(img_pointer, img_width, top).red == color_to_check->red) ||
       (!Pixel::outOfImage(&bottom, img_width, img_height) && Pixel::getPixelColor(img_pointer, img_width, bottom).red == color_to_check->red) ||
       (!Pixel::outOfImage(&left_top, img_width, img_height) && Pixel::getPixelColor(img_pointer, img_width, left_top).red == color_to_check->red) ||
       (!Pixel::outOfImage(&right_top, img_width, img_height) && Pixel::getPixelColor(img_pointer, img_width, right_top).red == color_to_check->red) ||
       (!Pixel::outOfImage(&left_bottom, img_width, img_height) && Pixel::getPixelColor(img_pointer, img_width, left_bottom).red == color_to_check->red) ||
       (!Pixel::outOfImage(&right_bottom, img_width, img_height) && Pixel::getPixelColor(img_pointer, img_width, right_bottom).red == color_to_check->red)
      )
        return true;

    return false;
}
void Morphology::on_closing_clicked() {
    dilation();
    erosion();
    update();
}

void Morphology::on_dilation_clicked() {
    dilation();
    update();
}

void Morphology::on_erosion_clicked() {
    erosion();
    update();
}

void Morphology::on_opening_clicked() {
    erosion();
    dilation();
    update();
}

void Morphology::on_restore_clicked()
{
    *img = img_restore->copy();
    Pixel::monochromatic(img);
    update();
}

void Morphology::on_cross_clicked()
{
    cross_kernel = true;
    square_kernel = false;
}

void Morphology::on_square_clicked() {
    square_kernel = true;
    cross_kernel = false;
}
void Morphology::on_loadImage_clicked() {
    QString file = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Images (*.jpg *.png *.jpeg *.bmp *.gif)"));
        if(QString::compare(file,QString()) != 0){
            delete img_restore;
            img_restore = new QImage(file);
            *img = img_restore->copy();
            Pixel::monochromatic(img);
        }
}
