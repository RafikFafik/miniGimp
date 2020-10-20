#include "transformation2d.h"
#include "ui_transformation2d.h"

Transformation2D::Transformation2D(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Transformation2D)
{
    ui->setupUi(this);
    img = new QImage(":/pictures/ursus.jpg");
    imgBuffer = new QImage(":/pictures/ursus.jpg");
    point = new Point;
}

Transformation2D::~Transformation2D()
{
    delete point;
    delete ui;
}
void Transformation2D::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(0, 0, *img);
}

void Transformation2D::transform() {
    int height = ui->frame->height();
    int width = ui->frame->width();
    double *input = new double[3];
    double *output = new double[3];
    Color *color = new Color;
    unsigned char *fg, *buffer;
    fg = img->bits();
    buffer = imgBuffer->bits();

    matrix.combine();
//    matrix.debug();
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
//            output[0] = matrix.transformationMatrix[0][0] * j + matrix.transformationMatrix[0][1] * i + matrix.transformationMatrix[0][2];
//            output[1] = matrix.transformationMatrix[1][0] * j + matrix.transformationMatrix[1][1] * i + matrix.transformationMatrix[1][2];
            input[X] = j;
            input[Y] = i;
            input[Z] = 1;
            output = matrix.multiply(input, output);

            if(output[0] < 0 || output[0] >= width || output[1] < 0 || output[1] >= height) {
                fg[width * 4 * i + 4 * j + 2] = 0;
                fg[width * 4 * i + 4 * j + 1] = 0;
                fg[width * 4 * i + 4 * j] = 0;
            } else {
                if(interpolation_enabled)
                    color = Pixel::interpolate(buffer, width, output[0], output[1], color);
                else {
                    color->red = buffer[width * 4 * (int)output[1] + 4 * (int)output[0] + 1];
                    color->green = buffer[width * 4 * (int)output[1] + 4 * (int)output[0] + 2];
                    color->blue = buffer[width * 4 * (int)output[1] + 4 * (int)output[0]];
                }
                fg[width * 4 * i + 4 * j + 1] = color->red;
                fg[width * 4 * i + 4 * j + 2] = color->green;
                fg[width * 4 * i + 4 * j] = color->blue;
            }
        }
    }
    delete []input;
    delete []output;
    delete color;
    update();
}

void Transformation2D::on_translateX_valueChanged(int value)
{
    point->x = -value;
    point->y = -ui->translateY->value();
    matrix.translate(point);
    transform();
}

void Transformation2D::on_translateY_valueChanged(int value)
{
    point->y = -value;
    point->x = -ui->translateX->value();
    matrix.translate(point);
    transform();
}

void Transformation2D::on_scaleX_valueChanged(int value)
{
    double y = 100 / (double)ui->scaleY->value();
    double x = 100 / (double)value;
    matrix.scale(x, y, ui->frame->width(), ui->frame->height());
    transform();
}

void Transformation2D::on_scaleY_valueChanged(int value)
{
    double x = 100 / (double)ui->scaleX->value();
    double y = 100 / (double)value;
    matrix.scale(x, y, ui->frame->width(), ui->frame->height());
    transform();
}
void Transformation2D::on_rotate_valueChanged(int value)
{
    double angle = -(M_PI * (value - 180)/(double)180);
    int *center = new int[3];
    int width = ui->frame->width();
    int height = ui->frame->height();
    center[X] = (width / (double)2)*(1-cos(angle))+(height/(double)2)*(sin(angle));
    center[Y] = (height /(double)2)*(1-cos(angle))-(width/(double)2)*(sin(angle));
    center[Z] = 1;
    matrix.rotateZ(angle, center);
    delete[] center;
    transform();
}

void Transformation2D::on_sheareX_valueChanged(int value)
{
    double x = -(value/ (double)100);
    matrix.sheareX(x, ui->frame->width());
    transform();
}

void Transformation2D::on_sheareY_valueChanged(int value)
{
    double y = -(value / (double)100);
    matrix.sheareY(y, ui->frame->height());
    transform();
}


void Transformation2D::on_reset_clicked()
{
    ui->translateX->setValue(0);
    ui->translateY->setValue(0);
    ui->scaleX->setValue(100);
    ui->scaleY->setValue(100);
    ui->rotate->setValue(180);
    ui->sheareX->setValue(0);
    ui->sheareY->setValue(0);
    *img = imgBuffer->copy();
    matrix.reset();
}


void Transformation2D::on_interpolation_clicked()
{
    interpolation_enabled = !interpolation_enabled;
    transform();
}
