#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paint.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(QDesktopWidget().availableGeometry(this).size() * 0.65);
    paint = new Paint(ui->container);
    alphaBlending = new AlphaBlending(ui->container);
    transformation2D = new Transformation2D(ui->container);
    texture = new Texture(ui->container);
    morphing = new Morphing(ui->container);
    transformation3D = new Transformation3D(ui->container);
    scanLine = new ScanLine(ui->container);
    morphology = new Morphology(ui->container);
    curve = new Curve(ui->container);
    colorSpace = new ColorSpace(ui->container);
    paint->hide();
    alphaBlending->hide();
    transformation2D->hide();
    texture->hide();
    morphing->hide();
//    transformation3D->hide();
    scanLine->hide();
    morphology->hide();
    curve->hide();
    colorSpace->hide();
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
    texture->hide();
    morphing->hide();
    transformation3D->hide();
    scanLine->hide();
    morphology->hide();
    curve->hide();
    colorSpace->hide();
}

void MainWindow::on_paint_clicked()
{
    paint->show();
    transformation2D->hide();
    alphaBlending->hide();
    texture->hide();
    morphing->hide();
    transformation3D->hide();
    scanLine->hide();
    morphology->hide();
    curve->hide();
    colorSpace->hide();
}

void MainWindow::on_transformation2d_clicked()
{
    transformation2D->show();
    alphaBlending->hide();
    paint->hide();
    texture->hide();
    morphing->hide();
    transformation3D->hide();
    scanLine->hide();
    morphology->hide();
    curve->hide();
    colorSpace->hide();
}

void MainWindow::on_texturing_clicked()
{
    transformation2D->hide();
    alphaBlending->hide();
    paint->hide();
    texture->show();
    morphing->hide();
    transformation3D->hide();
    scanLine->hide();
    morphology->hide();
    curve->hide();
    colorSpace->hide();
}
void MainWindow::on_morphing_clicked()
{
    transformation2D->hide();
    alphaBlending->hide();
    paint->hide();
    texture->hide();
    morphing->show();
    transformation3D->hide();
    scanLine->hide();
    morphology->hide();
    curve->hide();
    colorSpace->hide();
}

void MainWindow::on_transformation3d_clicked()
{
    transformation2D->hide();
    alphaBlending->hide();
    paint->hide();
    texture->hide();
    morphing->hide();
    transformation3D->show();
    scanLine->hide();
    morphology->hide();
    curve->hide();
    colorSpace->hide();
}

void MainWindow::on_scanline_clicked()
{
    transformation2D->hide();
    alphaBlending->hide();
    paint->hide();
    texture->hide();
    morphing->hide();
    transformation3D->hide();
    scanLine->show();
    morphology->hide();
    curve->hide();
    colorSpace->hide();
}

void MainWindow::on_morphology_clicked()
{
    transformation2D->hide();
    alphaBlending->hide();
    paint->hide();
    texture->hide();
    morphing->hide();
    transformation3D->hide();
    scanLine->hide();
    morphology->show();
    curve->hide();
    colorSpace->hide();
}

void MainWindow::on_curve_clicked()
{
    transformation2D->hide();
    alphaBlending->hide();
    paint->hide();
    texture->hide();
    morphing->hide();
    transformation3D->hide();
    scanLine->hide();
    morphology->hide();
    curve->show();
    colorSpace->hide();
}

void MainWindow::on_color_space_clicked()
{
    transformation2D->hide();
    alphaBlending->hide();
    paint->hide();
    texture->hide();
    morphing->hide();
    transformation3D->hide();
    scanLine->hide();
    morphology->hide();
    curve->hide();
    colorSpace->show();
}
