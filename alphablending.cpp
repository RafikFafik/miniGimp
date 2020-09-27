#include "alphablending.h"
#include "ui_alphablending.h"

AlphaBlending::AlphaBlending(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlphaBlending)
{
    ui->setupUi(this);
}

AlphaBlending::~AlphaBlending()
{
    delete ui;
}
