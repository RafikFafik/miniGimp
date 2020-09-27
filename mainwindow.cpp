#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paint.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->paint = new Paint(ui->container);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_alpha_blending_clicked()
{
    paint->hide();
}

void MainWindow::on_paint_clicked()
{
    paint->show();
}
