#include "transformation2d.h"
#include "ui_transformation2d.h"

Transformation2D::Transformation2D(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Transformation2D)
{
    ui->setupUi(this);
}

Transformation2D::~Transformation2D()
{
    delete ui;
}
