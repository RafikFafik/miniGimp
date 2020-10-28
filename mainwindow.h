#pragma once

#include <QMainWindow>
#include <QDesktopWidget>
#include "point.h"
#include "pixel.h"
#include "paint.h"
#include "alphablending.h"
#include "transformation2d.h"
#include "texture.h"
#include "morphing.h"
#include "transformation3d.h"
#include "scanline.h"
#include "morphology.h"
#include "curve.h"
#include "colorspace.h"

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
    Texture *texture;
    Morphing *morphing;
    Transformation3D *transformation3D;
    ScanLine *scanLine;
    Morphology *morphology;
    Curve *curve;
    ColorSpace *colorSpace;
private slots:
    void on_alpha_blending_clicked();
    void on_paint_clicked();
    void on_transformation2d_clicked();
    void on_texturing_clicked();
    void on_morphing_clicked();
    void on_transformation3d_clicked();
    void on_scanline_clicked();
    void on_morphology_clicked();
    void on_curve_clicked();
    void on_color_space_clicked();
};

