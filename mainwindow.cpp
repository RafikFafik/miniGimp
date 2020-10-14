#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paint.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    paint = new Paint(ui->container);
    alphaBlending = new AlphaBlending(ui->container);
    transformation2D = new Transformation2D(ui->container);
    texure = new Texture(ui->container);
    paint->hide();
    alphaBlending->hide();
//    transformation2D->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_alpha_blending_clicked()
{
    paint->hide();
    transformation2D->hide();
    alphaBlending->show();
}

void MainWindow::on_paint_clicked()
{
    paint->show();
    transformation2D->hide();
    alphaBlending->hide();
}

void MainWindow::on_transformation2d_clicked()
{
    transformation2D->show();
    alphaBlending->hide();
    paint->hide();
}

void MainWindow::on_texturing_clicked()
{
    transformation2D->hide();
    alphaBlending->hide();
    paint->hide();
    texture()->show();
}
