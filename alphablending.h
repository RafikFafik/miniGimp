#ifndef ALPHABLENDING_H
#define ALPHABLENDING_H

#include <QWidget>
#include <QPainter>
#include <QImageReader>
#include <QFileDialog>
#include <QDebug>
#include "pixel.h"
#include "point.h"
#include <map>

namespace Ui {
class AlphaBlending;
}

class AlphaBlending : public QWidget
{
    Q_OBJECT
private:
    struct ImageData {
        QImage *image;
        QString filename;
        int active_mode;
        int (*function_pointer)(int, int);
        int value;
        bool visible;
    };


public:
    explicit AlphaBlending(QWidget *parent = nullptr);
    ~AlphaBlending();
    void layersWalk();
    void updateGui();
    void blend(ImageData *foreground);
    unsigned char switchBlendMode(unsigned char foreground, unsigned char background, int mode);
private:
    Ui::AlphaBlending *ui;
    QImage *img;
    std::vector<ImageData*> imgs;
    QImageReader reader;
    void loadImages();
    unsigned char multiply(unsigned char bg, unsigned char fg);
    unsigned char screen(unsigned char bg, unsigned char fg);
    unsigned char overlay(unsigned char bg, unsigned char fg);
    unsigned char darken(unsigned char bg, unsigned char fg);
    unsigned char lighten(unsigned char bg, unsigned char fg);
    unsigned char difference(unsigned char bg, unsigned char fg);

//    std::map<int, void> functions;

private slots:
    void paintEvent(QPaintEvent*);
    void on_images_currentIndexChanged(int index);
    void on_visibility_stateChanged(int arg1);
    void on_value_valueChanged(int value);
    void on_mode_currentIndexChanged(int index);
};

#endif // ALPHABLENDING_H
