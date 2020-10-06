#pragma once

#include <QMainWindow>
#include "point.h"
#include "pixel.h"
#include "paint.h"
#include "alphablending.h"
#include "transformation2d.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Paint *paint;
    AlphaBlending *alphaBlending;
    Transformation2D *transformation2D;
private slots:
    void on_alpha_blending_clicked();
    void on_paint_clicked();
    void on_transformation2d_clicked();
};

